#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <GL/glu.h>
#include <cstdlib>
#include <cstdlib>

// Routine to read an uncompressed 24-bit unindexed color RGB BMP file into a 
// 32-bit color RGBA image file (alpha values all being set to 1).

#include <fstream>

#include "getBMP.h"

imageFile* getBMP(std::string fileName)
{
	int offset, // No. of bytes to start of image data in input BMP file. 
		w, // Width in pixels of input BMP file.
		h; // Height in pixels of input BMP file.

	// Initialize imageFile objects.
	imageFile* tempStore = new imageFile; // Temporary storage.
	imageFile* outRGB = new imageFile; // RGB output file.
	imageFile* outRGBA = new imageFile; // RGBA output file.

	// Initialize input stream.
	std::ifstream inFile(fileName.c_str(), std::ios::binary);

	// Get start point of image data in input BMP file.
	inFile.seekg(10);
	inFile.read((char*)&offset, 4);

	// Get image width and height.
	inFile.seekg(18);
	inFile.read((char*)&w, 4);
	inFile.read((char*)&h, 4);

	// Determine the length of padding of the pixel rows 
	// (each pixel row of a BMP file is 4-byte aligned by padding with zero bytes).
	int padding = (3 * w) % 4 ? 4 - (3 * w) % 4 : 0;

	// Allocate storage for temporary input file, read in image data from the BMP file, close input stream.
	tempStore->data = new unsigned char[(3 * w + padding) * h];
	inFile.seekg(offset);
	inFile.read((char*)tempStore->data, (3 * w + padding) * h);
	inFile.close();

	// Set image width and height and allocate storage for image in output RGB file.
	outRGB->width = w;
	outRGB->height = h;
	outRGB->data = new unsigned char[3 * w * h];

	// Copy data from temporary input file to output RGB file adjusting for padding and performing BGR to RGB conversion.
	int tempStorePos = 0;
	int outRGBpos = 0;
	for (int j = 0; j < h; j++)
		for (int i = 0; i < 3 * w; i += 3)
		{
			tempStorePos = (3 * w + padding) * j + i;
			outRGBpos = 3 * w * j + i;
			outRGB->data[outRGBpos] = tempStore->data[tempStorePos + 2];
			outRGB->data[outRGBpos + 1] = tempStore->data[tempStorePos + 1];
			outRGB->data[outRGBpos + 2] = tempStore->data[tempStorePos];
		}

	// Set image width and height and allocate storage for image in output RGBA file.
	outRGBA->width = w;
	outRGBA->height = h;
	outRGBA->data = new unsigned char[4 * w * h];

	// Copy image data from output RGB file to output RGBA file, setting all A values to 1.
	for (int j = 0; j < 4 * w * h; j += 4)
	{
		outRGBA->data[j] = outRGB->data[(j / 4) * 3];
		outRGBA->data[j + 1] = outRGB->data[(j / 4) * 3 + 1];
		outRGBA->data[j + 2] = outRGB->data[(j / 4) * 3 + 2];
		outRGBA->data[j + 3] = 0xFF;
	}

	// Release temporary storage and the output RGB file and return the RGBA version.
	delete tempStore;
	delete outRGB;
	return outRGBA;
}



static unsigned int texture[3];
static int id = 0;


#define ROWS 9  // Number of rows of Cuboids.8 and the last one is for the target
#define COLUMNS 6 // Number of columns of Cuboids. (cubes)
#define FILL_PROBABILITY 100 // Percentage probability that a particular row-column slot will be 
// filled with an Cuboid. It should be an integer between 0 and 100.

// Globals.
static void* font = GLUT_BITMAP_HELVETICA_18; // Using a different font that should be defined
// Font selection.
static int width, height; // Size of the OpenGL window.
static float angle = 0.0; // Angle of the spacecraft.
static float xVal = 0, zVal = 0; // Co-ordinates of the spacecraft.
static int isCollision = 0; // Is there collision between the spacecraft and an Cuboid?
static int isWinner = 0; // The car hit the target
static unsigned int carSpace; // Display lists base index.
static int frameCount = 0; // Number of frames
static int gameState = 0; // 0 = playing, 1 = won.
static int winTimeStart = 0; // Timestamp of when the win state started.


// Routine to draw a bitmap character string.
void writeBitmapString(void* font, const char* string)
{
	const char* c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void setMaterialProperties(GLfloat r, GLfloat g, GLfloat b) {
	GLfloat matAmbient[] = { r * 0.25f, g * 0.25f, b * 0.25f, 1.0f };  // Ambient color
	GLfloat matDiffuse[] = { r, g, b, 1.0f };                      // Diffuse color
	GLfloat matSpecular[] = { r, g, b, 1.0f };            // Specular color
	GLfloat matShininess[] = { 50.0f };                            // Shininess factor

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void menuCallback(int option) {
	if (option == 0) {
		id = 0;
	}
	else if (option == 1) {
		id = 1;
	}
	glutPostRedisplay();
}
void setupMenu() {
	int menuID = glutCreateMenu(menuCallback);
	glutAddMenuEntry("Grass Texture", 0);
	glutAddMenuEntry("Ground Texture", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



// Cuboid class.
class Cuboid
{
public:
	bool isTarget;
	Cuboid();
	Cuboid(float x, float y, float z, float r, unsigned char colorR,
		unsigned char colorG, unsigned char colorB);
	float getCenterX() { return centerX; }
	float getCenterY() { return centerY; }
	float getCenterZ() { return centerZ; }
	float getRadius() { return radius; }
	virtual void draw(); // Make draw virtual for polymorphism

	virtual ~Cuboid() = default; // Add a virtual destructor for safety

protected:
	float centerX, centerY, centerZ, radius;
	unsigned char color[3];
};

// Target inherits from Cuboid
class Target : public Cuboid
{
public:
	Target(float x, float y, float z, float r);
	void draw() override; // Override the draw method

private:
	void drawCircle(float radius, unsigned char colorR, unsigned char colorG, unsigned char colorB);
	void drawCube(float size);
};

// Cuboid default constructor.
Cuboid::Cuboid()
{
	centerX = 0.0;
	centerY = 0.0;
	centerZ = 0.0;
	radius = 0.0; // Indicates no Cuboid exists in the position.
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
}

// Cuboid constructor.
Cuboid::Cuboid(float x, float y, float z, float r, unsigned char colorR,
	unsigned char colorG, unsigned char colorB)
{
	centerX = x;
	centerY = y;
	centerZ = z;
	radius = r * sqrt(3.0) / 2.0;;
	color[0] = colorR;
	color[1] = colorG;
	color[2] = colorB;
}

// Function to draw Cuboid.
void Cuboid::draw()
{
	if (radius > 0.0) // If Cuboid exists.
	{
		glPushMatrix();
		glTranslatef(centerX, centerY, centerZ);
		glColor3ubv(color);
		setMaterialProperties(color[0] / 128, color[1] / 128, color[2] / 128);
		glutSolidCube(radius);
		glPopMatrix();
	}
}

// Target constructor.
Target::Target(float x, float y, float z, float r) : Cuboid(x, y, z, r, 0, 0, 0) {}

// Function to draw a circle.
void Target::drawCircle(float radius, unsigned char colorR, unsigned char colorG, unsigned char colorB)
{
	glColor3ub(colorR, colorG, colorB);
	setMaterialProperties(colorR / 15, colorG / 15, colorB / 15);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	for (int i = 0; i <= 360; i++)
	{
		float angle = 2 * M_PI * i / 360;
		glVertex3f(radius * cos(angle), radius * sin(angle), 0.0);
	}
	glEnd();
}

// Function to draw a cube.
void Target::drawCube(float size) {
	float halfSize = size / 2.0f;

	glBegin(GL_POLYGON);

	// Front face (with circles)
	glColor3f(1.0f, 1.0f, 1.0f); // White for the base of the face
	setMaterialProperties(1, 1, 1);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);

	// Back face
	glColor3f(0.8f, 0.8f, 0.8f); // Light gray
	setMaterialProperties(0.8, 0.8, 0.8);
	glVertex3f(-halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	// Top face
	glColor3f(0.6f, 0.6f, 0.6f); // Darker gray
	setMaterialProperties(0.6, 0.6, 0.6);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);

	// Bottom face
	glColor3f(0.6f, 0.6f, 0.6f); // Darker gray
	setMaterialProperties(0.6, 0.6, 0.6);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	// Right face
	glColor3f(0.7f, 0.7f, 0.7f); // Medium gray
	setMaterialProperties(0.7, 0.7, 0.7);
	glVertex3f(halfSize, -halfSize, halfSize);
	glVertex3f(halfSize, halfSize, halfSize);
	glVertex3f(halfSize, halfSize, -halfSize);
	glVertex3f(halfSize, -halfSize, -halfSize);

	// Left face
	glColor3f(0.7f, 0.7f, 0.7f); // Medium gray
	setMaterialProperties(0.7, 0.7, 0.7);
	glVertex3f(-halfSize, -halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, halfSize);
	glVertex3f(-halfSize, halfSize, -halfSize);
	glVertex3f(-halfSize, -halfSize, -halfSize);

	glEnd();
}

// Function to draw the target as a cube with circles on its front face.
void Target::draw() {
	glPushMatrix();
	glTranslatef(getCenterX(), getCenterY(), getCenterZ());

	// Draw the cube.
	drawCube(getRadius() * 2.0f); // Cube size is twice the radius of the circle.

	// Draw concentric circles on the front face with depth offsets.
	glEnable(GL_POLYGON_OFFSET_FILL);

	// Draw the red outer circle.
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, getRadius() + 0.01f); // Offset slightly forward.
	drawCircle(getRadius(), 255, 0, 0);           // Red outer circle.
	glPopMatrix();

	// Draw the yellow middle circle.
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, getRadius() + 0.02f); // Slightly further forward than the red circle.
	drawCircle(getRadius() * 0.75f, 255, 255, 0);  // Yellow middle circle.
	glPopMatrix();

	// Draw the green inner circle.
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, getRadius() + 0.03f); // Slightly further forward than the yellow circle.
	drawCircle(getRadius() * 0.5f, 0, 255, 0);     // Green inner circle.
	glPopMatrix();

	// Draw the blue center circle.
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, getRadius() + 0.04f); // Slightly further forward than the green circle.
	drawCircle(getRadius() * 0.25f, 0, 0, 255);    // Blue center circle.
	glPopMatrix();

	glDisable(GL_POLYGON_OFFSET_FILL);

	glPopMatrix();
}



Cuboid* arrayCuboids[ROWS][COLUMNS]; // Use pointers





// Routine to count the number of frames drawn every second.
void frameCounter(int value)
{
	if (value != 0) // No output the first time frameCounter() is called (from main()).
		std::cout << "FPS = " << frameCount << std::endl;
	frameCount = 0;
	glutTimerFunc(1000, frameCounter, 1);
}


void loadTextures()
{
	imageFile* image[3];
	image[0] = getBMP("D:/Faculty/SBE 24-25/Graphics/Task11/Task11/grass.bmp");
	image[1] = getBMP("D:/Faculty/SBE 24-25/Graphics/Task11/Task11/ground.bmp");
	image[2] = getBMP("D:/Faculty/SBE 24-25/Graphics/Task11/Task11/sky.bmp");

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->width, image[2]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->width, image[1]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void drawSky()
{
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 7.0f);
	glVertex3f(-200.0f, 0.0f, -350.0f);

	glTexCoord2f(1.0f, 7.0f);
	glVertex3f(200.0f, 0.0f, -350.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(200.0f, 40.0f, 100.0f);

	glTexCoord2f(0.0f, 0.0f);  // Flip Y
	glVertex3f(-200.0f, 40.0f, 100.0f); // Position adjusted to face downward

	glEnd();

	glDisable(GL_TEXTURE_2D);
}



void drawGround() {
	glPushMatrix();
	glTranslatef(0.0f, -1.5f, 0.0f);

	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[id]);
	glBegin(GL_POLYGON);
	glTexCoord2f(10.0f, 50.0f); glVertex3f(-400.0f, -1.0, -1000.0f);
	glTexCoord2f(0.0f, 50.0f); glVertex3f(400.0f, -1.0, -1000.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(400.0f, -1.0, 100.0f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(-400.0f, -1.0, 100.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


void drawCar() {

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	setMaterialProperties(1, 0, 0);
	glTranslatef(0.0, -0.5, 0.0);
	glScalef(1.5, 0.5, 3.0);
	glutSolidCube(5.0);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.8, 0.0, 0.0);
	setMaterialProperties(0.8, 0, 0);
	glTranslatef(0.0, 2.0, 0.0);
	glScalef(1.2, 0.5, 2.0);
	glutSolidCube(5.0);

	// Windows
	glPushMatrix();
	glColor3f(0.6, 0.8, 1.0);
	setMaterialProperties(0.6, 0.8, 1.0);

	// Left side windows
	glBegin(GL_QUADS);

	// Front-left window
	glVertex3f(-2.6, 2.5, 2.0);
	glVertex3f(-2.6, 0.0, 2.0);
	glVertex3f(-2.6, 0.0, 0.7);
	glVertex3f(-2.6, 2.5, 0.7);

	// Rear-left window
	glVertex3f(-2.6, 2.5, -0.7);
	glVertex3f(-2.6, 0.0, -0.7);
	glVertex3f(-2.6, 0.0, -2.0);
	glVertex3f(-2.6, 2.5, -2.0);
	glEnd();

	// Right side windows
	glBegin(GL_QUADS);
	// Front-right window
	glVertex3f(2.6, 2.5, 2.0);
	glVertex3f(2.6, 0.0, 2.0);
	glVertex3f(2.6, 0.0, 0.7);
	glVertex3f(2.6, 2.5, 0.7);

	// Rear-right window
	glVertex3f(2.6, 2.5, -0.7);
	glVertex3f(2.6, 0.0, -0.7);
	glVertex3f(2.6, 0.0, -2.0);
	glVertex3f(2.6, 2.5, -2.0);
	glEnd();

	// Front window
	glBegin(GL_POLYGON);
	glVertex3f(-2.5, 1.5, 2.6);
	glVertex3f(2.5, 1.5, 2.6);
	glVertex3f(2.5, -1.5, 2.6);
	glVertex3f(-2.5, -1.5, 2.6);
	glEnd();

	// back window
	glBegin(GL_POLYGON);
	glVertex3f(-2.4, 1.5, -2.6);
	glVertex3f(2.4, 1.5, -2.6);
	glVertex3f(2.4, -1.5, -2.6);
	glVertex3f(-2.4, -1.5, -2.6);
	glEnd();

	glPopMatrix();
	glPopMatrix();
	// Wheels
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	setMaterialProperties(0, 0, 0);

	// Front-left wheel
	glPushMatrix();
	glTranslatef(-3.0, -2.5, 7.0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.5, 1.0, 20, 20);
	glPopMatrix();

	// Front-right wheel
	glPushMatrix();
	glTranslatef(3.0, -2.5, 7.0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.5, 1.0, 20, 20);
	glPopMatrix();

	// Rear-left wheel
	glPushMatrix();
	glTranslatef(-3.0, -2.5, -7.0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.5, 1.0, 20, 20);
	glPopMatrix();

	// Rear-right wheel
	glPushMatrix();
	glTranslatef(3.0, -2.5, -7.0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.5, 1.0, 20, 20);
	glPopMatrix();

	glPopMatrix();

	// Headlights
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.5);
	setMaterialProperties(1, 1, 0.5);

	// front Left headlight
	glPushMatrix();
	glTranslatef(-2.0, 0.5, 7.5);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	// front Right headlight
	glPushMatrix();
	glTranslatef(2.0, 0.5, 7.5);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();


	//// back Left headlight
	//glPushMatrix();
	//glTranslatef(-2.0, 0.5, -7.5);
	//glutSolidSphere(0.5, 20, 20);
	//glPopMatrix();

	//// back Right headlight
	//glPushMatrix();
	//glTranslatef(2.0, 0.5, -7.5);
	//glutSolidSphere(0.5, 20, 20);
	//glPopMatrix();

	glPopMatrix();

	//gray rectangles 
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	setMaterialProperties(0.2, 0.2, 0.2);

	// Front gray rectangle 
	glPushMatrix();
	glTranslatef(0.0, -1.0, 7.5);
	glScalef(1.5, 0.3, 0.1);
	glutSolidCube(5.0);
	glPopMatrix();

	// back gray rectangle
	glPushMatrix();
	glTranslatef(0.0, -1.0, -7.5);
	glScalef(1.5, 0.3, 0.1);
	glutSolidCube(5.0);
	glPopMatrix();
	glPopMatrix();
}

// Initialization routine.
void setup(void)
{
	int i, j;

	carSpace = glGenLists(1);
	glNewList(carSpace, GL_COMPILE);
	glPushMatrix();
	glRotatef(180.0, 0.0, 1.0, 0.0);
	drawCar();
	glPopMatrix();
	glEndList();

	// Initialize global arrayCuboids.
	for (int j = 0; j < COLUMNS; j++)
	{
		for (int i = 0; i < ROWS - 1; i++)
		{
			if (rand() % 100 < FILL_PROBABILITY)
			{
				if (COLUMNS % 2) // Odd number of columns
					arrayCuboids[i][j] = new Cuboid(30.0 * (-COLUMNS / 2 + j), 0.0, -40.0 - 40.0 * i, 6.0,
						rand() % 256, rand() % 256, rand() % 256);
				else // Even number of columns
					arrayCuboids[i][j] = new Cuboid(15 + 30.0 * (-COLUMNS / 2 + j), 0.0, -40.0 - 40.0 * i, 6.0,
						rand() % 256, rand() % 256, rand() % 256);
			}
			else
			{
				arrayCuboids[i][j] = nullptr; // No Cuboid
			}
		}
	}

	// Add Target to the last row
	arrayCuboids[ROWS - 1][COLUMNS / 2] = new Target(0.0, 0.0, -40.0 - 30.0 * (ROWS - 1), 5.0);

	// Example: Set target at ROWS - 1, COLUMNS / 2
	arrayCuboids[ROWS - 1][COLUMNS / 2]->isTarget = true;  // Assign that this cube is the Target 

	// All other cubes are obstacles by default
	for (int j = 0; j < COLUMNS; j++) {
		for (int i = 0; i < ROWS - 1; i++) {
			if (arrayCuboids[i][j] && !(i == ROWS - 1 && j == COLUMNS / 2)) {
				arrayCuboids[i][j]->isTarget = false;    // Assign that all the cubes are not Target
			}
		}
	}


	setupMenu();
	glGenTextures(3, texture);

	loadTextures();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5098f, 0.6588f, 0.6980f, 1.0f);
	glutTimerFunc(0, frameCounter, 0);
}

// Function to check if two spheres centered at (x1,y1,z1) and (x2,y2,z2) with
// radius r1 and r2 intersect.
int checkSpheresIntersection(float x1, float y1, float z1, float r1,
	float x2, float y2, float z2, float r2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2) <= (r1 + r2) * (r1 + r2));
}




// Function to check if the spacecraft collides with an Cuboid when the center of the base
// of the craft is at (x, 0, z) and it is aligned at an angle a to to the -z direction.
// Collision detection is approximate as instead of the spacecraft we use a bounding sphere.
int CuboidCarCollision(float x, float z, float a)
{
	int i, j;

	// Check for collision with each Cuboid.
	for (j = 0; j < COLUMNS; j++)
		for (i = 0; i < ROWS; i++) {
			const auto& cuboid = arrayCuboids[i][j]; // Reference to current cuboid.
			if (cuboid && cuboid->getRadius() > 0) // If Cuboid exists.
				if (checkSpheresIntersection(x - 5 * sin((M_PI / 180.0) * a), 0.0,
					z - 5 * cos((M_PI / 180.0) * a), 7.072,
					cuboid->getCenterX(), cuboid->getCenterY(),
					cuboid->getCenterZ(), cuboid->getRadius()))
					// we have calculated the right xVal and Zval which must be 
					//checkSpheresIntersection(x - 7.5 * sin((M_PI / 180.0) * a), 0.0,
					//z - 7.5 * cos((M_PI / 180.0) * a), 8.4,
					//cuboid->getCenterX(), cuboid->getCenterY(),
					// cuboid->getCenterZ(), cuboid->getRadius())) but the collision doesnt happen correctly
					// we have drawn the sphere accroding to the refrence to debbug and the sphere was rightly drawn but the collision is not correct



					if (arrayCuboids[i][j]->isTarget) {   // Check if the cuboid hit is the target or not 
						gameState = 1;
						winTimeStart = glutGet(GLUT_ELAPSED_TIME); // Record the time when the win occurred
						return 2; // Hit the target
					}
					else {
						gameState = 1;
						winTimeStart = glutGet(GLUT_ELAPSED_TIME); // Record the time when the win occurred
						return 1; // Hit an obstacle
					}
		}
	return 0;
}

// Drawing routine.
void drawScene(void)
{
	
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	

	// Light property vectors.
	float lightAmb[] = { 1, 0.5, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 0.5, 0.0, 1.0 };
	float lightPos[] = { 0, 0, 0.0, 10 };
	float globAmb[] = { 0.3, 0.2, 0.1, 1.0 };

	float lightAmbLeft[] = { 1.0, 1.0, 0.0, 1.0 };         // Yellow ambient light
	float lightDifAndSpecLeft[] = { 1.0, 1.0, 0.0, 1.0 };
	float lightPosLeft[] = { -2, 0.5, 7.5, 1 };

	float lightAmbRight[] = { 1.0, 1.0, 0.0, 1.0 };         // Yellow ambient light
	float lightDifAndSpecRight[] = { 1.0, 1.0, 0.0, 1.0 };
	float lightPosRight[] = { 2, 0.5, 7.5, 1 };

	// Light0 properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbLeft);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpecLeft);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpecLeft);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosLeft);


	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbRight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDifAndSpecRight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightDifAndSpecRight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosRight);


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1); // Enable local viewpoint



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Light quadratic attenuation factor.
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);

	frameCount++; // Increment number of frames every redraw.
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Begin left viewport.
	glViewport(0, 0, width / 2.0, height);
	glLoadIdentity();

	// Write text in isolated (i.e., before gluLookAt) translate block.
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(-28.0, 25.0, -30.0);
	if (isCollision) writeBitmapString(font, "You LOST, GAME OVER!");
	if (isWinner) writeBitmapString(font, "You Win!");
	glPopMatrix();

	// Fixed camera.
	gluLookAt(0.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	drawSky();
	drawGround();


	// Draw all the Cuboids in arrayCuboids.
	for (int j = 0; j < COLUMNS; j++)
	{
		for (int i = 0; i < ROWS; i++)
		{
			if (arrayCuboids[i][j]) // Check if the pointer is not null
				arrayCuboids[i][j]->draw();
		}
	}




	// Draw spacecraft.
	glPushMatrix();
	glTranslatef(xVal, 0.0, zVal);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glCallList(carSpace);
	glPopMatrix();
	// End left viewport.

	// Begin right viewport.
	glViewport(width / 2.0, 0, width / 2.0, height);
	glLoadIdentity();

	// Write text in isolated (i.e., before gluLookAt) translate block.
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(-28.0, 25.0, -30.0);
	if (isCollision) writeBitmapString((void*)font, "You LOST, GAME OVER!");
	if (isWinner) writeBitmapString(font, "You Win!");
	glPopMatrix();

	// Draw a vertical line on the left of the viewport to separate the two viewports
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glEnd();
	glLineWidth(1.0);

	gluLookAt(
		xVal - 15 * sin((M_PI / 180.0) * angle),  // Camera position X
		1.0,                                     // Camera height Y
		zVal - 15 * cos((M_PI / 180.0) * angle),  // Camera position Z
		xVal - 16 * sin((M_PI / 180.0) * angle),  // Look-at point X
		1.0,                                     // Look-at height Y
		zVal - 16 * cos((M_PI / 180.0) * angle),  // Look-at point Z
		0.0,                                     // Up vector X
		1.0,                                     // Up vector Y
		0.0                                      // Up vector Z


	);
	drawSky();
	drawGround();


	// Draw all the Cuboids in arrayCuboids.
	for (int j = 0; j < COLUMNS; j++)
	{
		for (int i = 0; i < ROWS; i++)
		{
			if (arrayCuboids[i][j]) // Check if the pointer is not null
				arrayCuboids[i][j]->draw();
		}
	}

	// End right viewport.

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
	glMatrixMode(GL_MODELVIEW);

	// Pass the size of the OpenGL window.
	width = w;
	height = h;
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;

	case ' ':
		id = (id + 1) % 2;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void resetGame() {   // Start the game from the beggining 
	// Reset car position
	xVal = 0.0;
	zVal = 0.0;
	angle = 0.0;

	// Reset game state
	isCollision = 0;
	isWinner = 0;
	gameState = 0;

	// Reset the target or obstacles if needed (optional)
	// Example: Reset the target to its initial position.
	arrayCuboids[ROWS - 1][COLUMNS / 2] = new Target(0.0, 0.0, -40.0 - 30.0 * (ROWS - 1), 5.0);

	std::cout << "Game reset to initial state." << std::endl;

	// Redraw the scene
	glutPostRedisplay();
}


void resetTimer(int value) {
	if (value == 1) {
		resetGame(); // Call the reset function after 3 seconds
	}
}



// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (isWinner or isCollision) return; // Ignore input during resting the game

	float tempxVal = xVal, tempzVal = zVal, tempAngle = angle;

	// Compute next position.
	if (key == GLUT_KEY_LEFT) tempAngle = angle + 5.0;
	if (key == GLUT_KEY_RIGHT) tempAngle = angle - 5.0;
	if (key == GLUT_KEY_UP)
	{
		tempxVal = xVal - sin(angle * M_PI / 180.0);
		tempzVal = zVal - cos(angle * M_PI / 180.0);
	}
	if (key == GLUT_KEY_DOWN)
	{
		tempxVal = xVal + sin(angle * M_PI / 180.0);
		tempzVal = zVal + cos(angle * M_PI / 180.0);
	}

	// Angle correction.
	if (tempAngle > 360.0) tempAngle -= 360.0;
	if (tempAngle < 0.0) tempAngle += 360.0;

	// Move spacecraft to next position only if there will not be collision with an Cuboid.
	if (!CuboidCarCollision(tempxVal, tempzVal, tempAngle))
	{
		isCollision = 0;
		isWinner = 0;
		xVal = tempxVal;
		zVal = tempzVal;
		angle = tempAngle;
	}
	else  // There is a collision 
	{
		if (CuboidCarCollision(tempxVal, tempzVal, tempAngle) == 1)   // The collision is with an Obstacle 
		{
			isCollision = 1;
			isWinner = 0;
			std::cout << "Target hit! Restarting in 3 seconds..." << std::endl;
			glutTimerFunc(3000, resetTimer, 1); // Set timer for 3 seconds
		}
		else if (CuboidCarCollision(tempxVal, tempzVal, tempAngle) == 2) {  // The collision is with the Target
			isCollision = 0;
			isWinner = 1;
			std::cout << "Target hit! Restarting in 3 seconds..." << std::endl;
			glutTimerFunc(3000, resetTimer, 1); // Set timer for 3 seconds
		}
	}
	glutPostRedisplay();
}



// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the left/right arrow keys to turn the craft." << std::endl
		<< "Press the up/down arrow keys to move the craft." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("team10_car");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	//glutDisplayFunc(display);
	glutTimerFunc(1000, frameCounter, 0);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}