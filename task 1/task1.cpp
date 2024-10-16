#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawCircle(float centerX, float centerY, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);  // Center of the circle

    for (int i = 0; i <= 300; i++)
    {
        // Angle in radians
        float angle = 2.0f * M_PI * i / 300;
        float x = radius * cos(angle);  // cos() from cmath
        float y = radius * sin(angle);  // sin() from cmath
        glVertex2f(centerX + x, centerY + y);
    }

    glEnd();
}

void drawOval(float centerX, float centerY, float radiusX, float radiusY)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);  // Center of the oval

    for (int i = 0; i <= 300; i++)
    {
        float angle = 2.0f * M_PI * i / 300;
        float x = radiusX * cos(angle);  // Horizontal radius
        float y = radiusY * sin(angle);  // Vertical radius
        glVertex2f(centerX + x, centerY + y);
    }

    glEnd();
}

void createCloud(float x, float y, float scale)  //x,y are coordinates of the lower center of the cloud
{
    glColor3f(1.0, 1.0, 1.0); //white cloud
    //bottom oval
    drawOval(x, y, 20 * scale, 7 * scale);
    //middle oval
    drawOval(x + (2 * scale), y + (4 * scale), 15 * scale, 7 * scale);
    //top oval
    drawOval(x + (4 * scale), y + (10 * scale), 7 * scale, 5 * scale);
    //momken 3shan a resize, a multiply the radiusX and radiusY with a factor like ff=0.9 to decrease and increase.
    //da fe kolo baa
    //w zabaty el indexing bel z
}

void createTree(float x, float y, float scale)
{
    //tree part:
    glColor3f(0.0, 1.0, 0.0);  //grean 
    //center 
    drawCircle(x, y, 9.5 * scale);
    //left
    drawCircle(x - 10, y, 6 * scale);
    //right
    drawCircle(x + 10, y, 6 * scale);

    //wood branch
    glColor3f(0.65f, 0.16f, 0.16f);  // Brown color (RGB)
    glBegin(GL_POLYGON);
    glVertex3f(x - (1.5 * scale), y - (8 * scale), 0.2);
    glVertex3f(x + (1.5 * scale), y - (8 * scale), 0.2);
    glVertex3f(x - (1.5 * scale), y - (30 * scale), 0.2);
    glVertex3f(x + (1.5 * scale), y - (30 * scale), 0.2);
    glEnd();

}


void drawSun(float SunPositionX, float SunPositionY, float sunRadius) {
    glColor3f(1.0f, 1.0f, 0.0f);
    int numberOfTriangles = 100; // Circle is a number of triangles rotated
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(SunPositionX, SunPositionY, 1);
    for (int i = 0; i <= numberOfTriangles; i++) {
        float stepAngle = 2 * (M_PI)*i / numberOfTriangles;
        glVertex3f(
            SunPositionX + (sunRadius * cos(stepAngle)),
            SunPositionY + (sunRadius * sin(stepAngle)), 1
        );
    }
    glEnd();
}

void drawGrassMountain(float MountainGrassPositionX, float MountainGrassPositionY, float MountainWidth, float MountainHeight) {
    glColor3f(0.0f, 0.5f, 0.0f);  // Dark green color for the mountains
    int numberOfTriangles = 50;

    float leftCircleX = MountainGrassPositionX - (MountainWidth * 0.2f);
    float rightCircleX = MountainGrassPositionX + (MountainWidth * 0.2f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(leftCircleX, MountainGrassPositionY);
    for (int i = 0; i <= numberOfTriangles; i++) {
        float stepAngle = (M_PI)*i / numberOfTriangles;
        glVertex2f(leftCircleX + (MountainHeight * cos(stepAngle) * 0.9f), MountainGrassPositionY + (MountainHeight * sin(stepAngle) * 0.9f));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(rightCircleX, MountainGrassPositionY);
    for (int i = 0; i <= numberOfTriangles; i++) {
        float stepAngle = (M_PI)*i / numberOfTriangles;
        glVertex2f(rightCircleX + (MountainHeight * cos(stepAngle) * 0.9f), MountainGrassPositionY + (MountainHeight * sin(stepAngle) * 0.9f));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(MountainGrassPositionX, MountainGrassPositionY);
    for (int i = 0; i <= numberOfTriangles; i++) {
        float stepAngle = (M_PI)*i / numberOfTriangles;
        glVertex2f(MountainGrassPositionX + (MountainHeight * cos(stepAngle) * 1.1f), MountainGrassPositionY + (MountainHeight * sin(stepAngle) * 1.1f));
    }
    glEnd();
}

void drawFish(float fishX, float fishY, float fishBody) {
    glColor3f(0.9f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angleStepInRadian = i * M_PI / 180;
        glVertex2f(fishX + 0.07f * fishBody * cos(angleStepInRadian), fishY + 0.02f * fishBody * sin(angleStepInRadian));
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(fishX - 0.05f * fishBody, fishY);                 // Tail base
    glVertex2f(fishX - 0.08f * fishBody, fishY + 0.03f * fishBody); // Tail top
    glVertex2f(fishX - 0.08f * fishBody, fishY - 0.03f * fishBody); // Tail bottom
    glEnd();
}


void drawHouse(float x, float y, float width, float height) {
    // Draw the main body of the house
    glColor3f(1.0, 0.9, 0.7); // Light color for the house
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + width, y, 0.0);
    glVertex3f(x + width, y + height, 0.0);
    glVertex3f(x, y + height, 0.0);
    glEnd();

    // Draw the roof
    glColor3f(0.8, 0.2, 0.2); // Roof color
    glBegin(GL_TRIANGLES);
    glVertex3f(x, y + height, 0.0);
    glVertex3f(x + width / 2, y + height + height * 0.5, 0.0);
    glVertex3f(x + width, y + height, 0.0);
    glEnd();

    // Draw the door
    glColor3f(0.0, 0.4, 0.8); // Door color
    glBegin(GL_POLYGON);
    glVertex3f(x + width * 0.4, y, 0.0);
    glVertex3f(x + width * 0.6, y, 0.0);
    glVertex3f(x + width * 0.6, y + height * 0.5, 0.0);
    glVertex3f(x + width * 0.4, y + height * 0.5, 0.0);
    glEnd();

    // Draw the left window
    glColor3f(0.5, 0.8, 1.0); // Light blue color for windows
    glBegin(GL_POLYGON);
    glVertex3f(x + width * 0.1, y + height * 0.6, 0.0); // Left window
    glVertex3f(x + width * 0.3, y + height * 0.6, 0.0);
    glVertex3f(x + width * 0.3, y + height * 0.8, 0.0);
    glVertex3f(x + width * 0.1, y + height * 0.8, 0.0);
    glEnd();

    // Draw the right window
    glBegin(GL_POLYGON);
    glVertex3f(x + width * 0.7, y + height * 0.6, 0.0); // Right window
    glVertex3f(x + width * 0.9, y + height * 0.6, 0.0);
    glVertex3f(x + width * 0.9, y + height * 0.8, 0.0);
    glVertex3f(x + width * 0.7, y + height * 0.8, 0.0);
    glEnd();
}

// Function to draw the background (sky)
void drawSky() {
    //glColor3f(0.5f, 0.2f, 0.8f); // Purple sky
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glColor3f(127.0f / 255.0f, 238.0f / 255.0f, 240.0f / 255.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);  // Top-left
    glColor3f(1, 1, 1);
    glVertex3f(1.0f, 1.0f, -1.0f);   // Top-right
    glColor3f(160.0f / 255.0f, 225.0f / 255.0f, 241.0f / 255.0f);
    glVertex3f(1.0f, -0.6f, -1.0f);   // Bottom-right
    glVertex3f(-1.0f, -0.6f, -1.0f);  // Bottom-left
    glEnd();
}

// Function to draw the volcano
void drawVolcano() {
    glColor3f(0.5f, 0.5f, 0.5f); // Gray volcano
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f + 0.2, 0.0f, 0.0f);   // Peak of the volcano (center)
    glVertex3f(-0.5f + 0.2, -0.8f, 0.0f); // Bottom-left
    glVertex3f(0.5f + 0.2, -0.8f, 0.0f);  // Bottom-right
    glEnd();
}

// Function to draw the brown mountain
void drawMountain() {
    glColor3f(0.6f, 0.3f, 0.1f);  // Brown mountain
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, -0.2f, 0.0f);   // Peak of the mountain
    glVertex3f(0.2f, -0.8f, 0.0f);   // Bottom-left
    glVertex3f(0.8f, -0.8f, 0.0f);   // Bottom-right
    glEnd();
}

// Function to draw the eruption
void drawEruption() {
    // Red outer explosion
    glColor3f(1.0f, 0.0f, 0.0f);  // Red explosion
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f + 0.2, 0.0f, 0.0f);    // Peak of volcano
    glVertex3f(-0.1f + 0.2, 0.3f, 0.0f);   // Left explosion
    glVertex3f(0.1f + 0.2, 0.3f, 0.0f);    // Right explosion
    glEnd();

    // Yellow inner explosion
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow explosion
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f + 0.2, 0.0f, 0.0f);   // Peak of volcano
    glVertex3f(-0.05f + 0.2, 0.25f, 0.0f); // Left inner explosion
    glVertex3f(0.05f + 0.2, 0.25f, 0.0f);  // Right inner explosion
    glEnd();
}

// Function to draw the lake
void drawLake() {
    //glColor3f(0.0f, 0.7f, 1.0f); // Light blue for lake
    glBegin(GL_POLYGON);
    //glColor3f(0.0f, 0.7f, 1.0f); // Light blue for lake
    //glColor3f(82.0f / 255.0f, 133.0f / 255.0f, 145.0f / 255.0f);
    glColor3f(0, 0, 0);
    glVertex3f(-1.0f, -0.6f, 0.0f);  // Bottom-left
    glVertex3f(1.0f, -0.6f, 0.0f);   // Bottom-right
    glVertex3f(1.0f, -1.0f, 0.0f);   // Top-right
    glVertex3f(-1.0f, -1.0f, 0.0f);  // Top-left
    glEnd();
}

void drawWindmill(float x, float y, float scale) {
    // Draw the base of the windmill
    glColor3f(0.9, 0.9, 0.9); // Light gray color for the windmill base
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + scale * 0.1, y, 0.0);
    glVertex3f(x + scale * 0.1, y + scale * 0.3, 0.0);
    glVertex3f(x, y + scale * 0.3, 0.0);
    glEnd();

    // Draw the windmill blades
    glColor3f(0.8, 0.4, 0.2); // Brown color for the blades

    // Blade 1: Right
    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * 0.05, y + scale * 0.3, 0.0); // Center of the windmill
    glVertex3f(x + scale * 0.15, y + scale * 0.3, 0.0); // Right blade
    glVertex3f(x + scale * 0.05, y + scale * 0.35, 0.0); // Extending outwards
    glEnd();

    // Blade 2: Top
    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * 0.05, y + scale * 0.3, 0.0); // Center of the windmill
    glVertex3f(x + scale * 0.05, y + scale * 0.45, 0.0); // Top blade
    glVertex3f(x + scale * 0.00, y + scale * 0.35, 0.0); // Extending outwards
    glEnd();

    // Blade 3: Left
    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * 0.05, y + scale * 0.3, 0.0); // Center of the windmill
    glVertex3f(x - scale * 0.05, y + scale * 0.3, 0.0); // Left blade
    glVertex3f(x + scale * 0.05, y + scale * 0.35, 0.0); // Extending outwards
    glEnd();

    // Blade 4: Bottom
    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * 0.05, y + scale * 0.3, 0.0); // Center of the windmill
    glVertex3f(x + scale * 0.05, y + scale * 0.15, 0.0); // Bottom blade
    glVertex3f(x + scale * 0.00, y + scale * 0.25, 0.0); // Extending outwards
    glEnd();
}

void drawBoat(float x, float y, float scale) {
    // Draw the boat base
    glColor3f(0.5, 0.3, 0.2); // Brown color for the boat
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);                         // Bottom left
    glVertex3f(x + scale * 0.3, y, 0.0);           // Bottom right
    glVertex3f(x + scale * 0.25, y - scale * 0.1, 0.0);  // Lower right
    glVertex3f(x + scale * 0.05, y - scale * 0.1, 0.0);  // Lower left
    glEnd();

    // Draw the sail
    glColor3f(1.0, 1.0, 1.0); // White color for the sail
    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * 0.15, y + scale * 0.1, 0.0);  // Top of the sail
    glVertex3f(x + scale * 0.25, y, 0.0);           // Bottom right of the sail
    glVertex3f(x + scale * 0.05, y, 0.0);           // Bottom left of the sail
    glEnd();
}

void drawRiver(float x, float y, float width, float height) {
    // Draw the river as a rectangle (polygon)
    glColor3f(0.0, 0.5, 1.0); // Blue color for the river
    glBegin(GL_POLYGON);
    glColor3f(26.0f / 255.0f, 40.0f / 255.0f, 147.0f / 255.0f);
    glVertex3f(x, y, 0.0);                  // Bottom-left
    glColor3f(0.0, 0.5, 1.0);
    glVertex3f(x + width, y, 0.0);          // Bottom-right
    glVertex3f(x + width, y + height, 0.0); // Top-right
    glVertex3f(x, y + height, 0.0);         // Top-left
    glEnd();
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Sky blue color

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set orthographic projection

    // Draw elements in the scene
    //drawSun(0.6f, 0.8f, 0.1f);

    drawSky();
    drawSun(0.6f, 0.8f, 0.1f);
    drawVolcano();
    drawMountain();
    drawEruption();
    //drawLake();

    drawGrassMountain(-0.8f, -0.5f, 0.5f, 0.3f); // Adjusted Y position
    drawGrassMountain(-0.3f, -0.5f, 0.45f, 0.35f); // Adjusted Y position
    drawGrassMountain(0.2f, -0.5f, 0.5f, 0.25f); // Adjusted Y position
    drawGrassMountain(0.8f, -0.5f, 0.4f, 0.3f); // Adjusted Y position

    //drawing the trees
    createTree(-0.65, -0.35, 0.005);
    createTree(0.7, -0.18, 0.0035);
    createTree(0.15, -0.35, 0.006);
    createTree(0.35, -0.35, 0.002);


    //drawing the clouds
    createCloud(0.2, 0.6, 0.0015);   //small middle clouds
    createCloud(0.08, 0.55, 0.004);
    createCloud(-0.60, 0.65, 0.01);    //left cloud
    createCloud(0.69, 0.69, 0.007);   //right cloud


    // Draw houses
    drawHouse(20.0, 20.0, 20.0, 20.0); // House 1
    drawHouse(60.0, 20.0, 20.0, 20.0); // House 2
    drawHouse(-0.5, -0.5, 0.5, 0.5); // House centered in the left half of the screen


    // Call the drawWindmill function, scaling the windmill to fit in [-1, 1]
    drawWindmill(-0.85, -0.5, 1.0);  // Scaled to fit the orthographic projection
    drawWindmill(0.55, -0.5, 0.5);   // A smaller windmill
    drawWindmill(0.8, -0.5, 1.0);

    // Draw the river, adjusting position and size to fit in [-1, 1]
    drawRiver(-1.0, -1.0, 2.0, 0.5);  // A wide river covering most of the bottom part of the screen

    // Draw fish
    drawFish(-0.7f, -0.8f, 1.0f);
    drawFish(-0.1f, -0.90f, 0.8f);
    drawFish(0.5f, -0.7f, 0.9f);
    drawFish(0.8f, -0.90f, 0.8f);

    // Call the drawBoat function, scaling the boat to fit in [-1, 1]
    drawBoat(-0.6, -0.55, 1.0);  // Boat centered at (-0.5, -0.5) with a large scale
    drawBoat(0.0, -0.7, 0.5);   // A smaller boat

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(240, 40);
    glutCreateWindow("Fish-Grass-Sun-Boat-Houses-Windmill");

    glutDisplayFunc(drawScene); // Set the display function
    drawScene(); // Initial call to draw the scene
    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}

