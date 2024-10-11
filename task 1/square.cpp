//cr. code: Sumanta Guha.
////////////////////////

//importing the header files
#include <glew.h>
#include <freeglut.h> 

// Drawing routine.
void drawScene(void)
{
	// clearing the buffer and setting the drawing color
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
	// Draw a polygon with specified vertices counterclockwise.
	glBegin(GL_POLYGON);
	glVertex3f(20.0, 20.0, 0.0);	// x, y, z
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	
	glEnd();

	// execute the drawing
	glFlush();
}

// Initialization routine.
void setup(void)
{
	//the clearing color of the opengl window (background)
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	// drawing the entire window
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(left, right, bottom, top, near, far)
	//Sets up a viewing box span along the x-axis is from left to right, along the y-axis from bottom to top, 
	// and along the z-axis from ?far to ?near.
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine. x & y are location of the mouse
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	// ascii of escape key
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);	// initializes the FreeGLUT library.

	// create context, set its version and set backward compatibility. 
	// context is the interface between an instance of OpenGL and the rest of the system
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	// wanting an OpenGL context to support a single-buffered frame, each pixel having red, green, blue and alpha values.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	
	// set the initial size of the OpenGL window and the location of its top left corner on the computer screen
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(200, 200);
	
	// creates the OpenGL context and its associated window with the specified string parameter as title.
	glutCreateWindow("square.cpp");
	
	// callback routines – when the OpenGL window is to be drawn, when it is resized, 
	// and when keyboard input is received, respectively
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	// initializes GLEW (the OpenGL Extension Wrangler Library) which handles the loading of OpenGL extensions, 
	// with the switch set so that extensions implemented even in pre-release drivers are exposed.
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	// begins the event-processing loop, calling registered callback routines as needed
	glutMainLoop();
	
}