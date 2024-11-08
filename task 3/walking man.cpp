#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <GL/glu.h>


// Angles to rotate the scene
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;

static float TorsoX = 0.0;  //move back a bit or tilt ACW
static float LeftArm = 0.0;  //rotate ACW abt z axis
static float LeftLeg = 0.0;  //rotate leg CW abt z axis
static float head = 0.0;   //move head back
static int armFront = 1;

bool isBallHeld = true;  // Initially, the ball is in the hand
bool isGoingUp = true;  // Initially, the ball is going up with hand
float ballX = -2.0, ballY = -4.0, ballZ = 0.0; // Ball's position
float ballVelocityY = 0.01; // Initial upward velocity for throwing


//void animate(void) {
//    LeftArm += 10;
//}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -20.0);
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);

    // Floor
    glPushMatrix();
    glColor3f(0.8, 0.52, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, -10.0, -10.0);
    glVertex3f(20.0, -10.0, -10.0);
    glVertex3f(20.0, -10.0, 5.0);
    glVertex3f(-20.0, -10.0, 5.0);
    glEnd();
    glPopMatrix();

    // Right wall
    glPushMatrix();
    glColor3f(0.85, 0.8, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(20.0, -10.0, -10.0);
    glVertex3f(20.0, 15.0, -10.0);
    glVertex3f(20.0, 15.0, 5.0);
    glVertex3f(20.0, -10.0, 5.0);
    glEnd();
    glPopMatrix();

    // Ceiling
    glPushMatrix();
    glColor3f(1.0, 0.95, 0.9);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, 15.0, -10.0);
    glVertex3f(20.0, 15.0, -10.0);
    glVertex3f(20.0, 15.0, 5.0);
    glVertex3f(-20.0, 15.0, 5.0);
    glEnd();
    glPopMatrix();

    // Left wall
    glPushMatrix();
    glColor3f(0.9, 0.85, 0.75);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, -10.0, -10.0);
    glVertex3f(-20.0, 15.0, -10.0);
    glVertex3f(-20.0, 15.0, 5.0);
    glVertex3f(-20.0, -10.0, 5.0);
    glEnd();
    glPopMatrix();

    // Back wall
    glPushMatrix();
    glColor3f(0.8, 0.75, 0.65);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, -10.0, -10.0);
    glVertex3f(20.0, -10.0, -10.0);
    glVertex3f(20.0, 15.0, -10.0);
    glVertex3f(-20.0, 15.0, -10.0);
    glEnd();
    glPopMatrix();


    // Carpet
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.2, 0.1);
    glVertex3f(-7.5, -9.0, -4.0);
    glVertex3f(7.5, -9.0, -4.0);
    glVertex3f(7.5, -9.0, 3.5);
    glVertex3f(-7.5, -9.0, 3.5);
    glEnd();
    glPopMatrix();


    // Horizontal floor lines
    glPushMatrix();
    glColor3f(0.847, 0.701, 0.549);
    for (float x = -20.0; x <= 20.0; x += 1.5)
    {
        glBegin(GL_LINES);
        glVertex3f(x, -10.0, -10.0);
        glVertex3f(x, -10.0, 5.0);
        glEnd();
    }
    glPopMatrix();

    // Vertical floor lines
    glPushMatrix();
    glColor3f(0.847, 0.701, 0.549);
    for (float z = -20.0; z <= 5.0; z += 1.5)
    {
        glBegin(GL_LINES);
        glVertex3f(-20.0, -10.0, z);
        glVertex3f(20.0, -10.0, z);
        glEnd();
    }
    glPopMatrix();




    // Door frame
    glPushMatrix();
    glColor3f(0.6, 0.4, 0.3);
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, -10.0, -5.0);
    glVertex3f(-20.0, 4.0, -5.0);
    glVertex3f(-20.0, 4.0, -1.0);
    glVertex3f(-20.0, -10.0, -1.0);
    glEnd();
    glPopMatrix();

    // Door knob
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-19.7, -3.0, -3.5);
    glutSolidSphere(0.3, 10, 10);
    glPopMatrix();



    //torso
    glPushMatrix();
    glColor3f(0.0, 0.5, 1.0);
    glRotatef(70, 0.0, 1.0, 0.0);
    glTranslatef(-1, -1, 0);
    glScalef(0.5, 1.0, 0.3);
    glutSolidCube(5.0);
    glPopMatrix();

    // head
    glPushMatrix();
    glColor3f(0.9, 0.75, 0.7);
    glRotatef(70, 0.0, 1.0, 0.0);
    glTranslatef(-1, 2.65, 0.0);
    glutSolidSphere(1.2, 15, 10);
    glPopMatrix();

    // left leg
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.5);
    glRotatef(70, 0.0, 1.0, 0.0);
    glTranslatef(-1.75, -6.0, 0.0);
    glScalef(0.15, 1, 0.25);
    glutSolidCube(5.0);
    glPopMatrix();


    // right leg
    glPushMatrix();
    glColor3f(0.1, 0.1, 0.5);
    glRotatef(70, 0.0, 1.0, 0.0);
    glTranslatef(-0.25, -6.0, 0.0);
    glScalef(0.15, 1, 0.25);
    glutSolidCube(5.0);
    glPopMatrix();


    // right hand
    glPushMatrix();
    glColor3f(0.9, 0.75, 0.6);
    glTranslatef(0.65, -1.0, 0.0);
    glScalef(0.15, 1, 0.25);
    glutSolidCube(5.0);
    glPopMatrix();

    // Left hand (holding the ball)
    glPushMatrix();
    glColor3f(0.9, 0.75, 0.6);

    // Position and rotate the arm
    glTranslatef(0.0, 1.3, -0.5);
    glRotatef(LeftArm, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -1.3, 0.5);

    // Position the hand
    glRotatef(70, 0.0, 1.0, 0.0);
    glTranslatef(-2.7, -1.0, 0.0);
    glScalef(0.15, 1, 0.25);
    glutSolidCube(5.0);
    glPopMatrix();

    // Ball in the left hand (follows hand movements)
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Ball color (red)

    if (isBallHeld) {
        // Ball is in hand, follow hand's transformations
        glTranslatef(0.0, 1.3, -0.5);
        glRotatef(LeftArm, 0.0, 0.0, 1.0);
        glTranslatef(0.0, -1.3, 0.5);
        glRotatef(70, 0.0, 1.0, 0.0);
        glTranslatef(-2.0, -4.0, 1.0); // Position in front of hand


        // Check if arm is at the top of its movement
        if (LeftArm >= 200.0) {
            if (isGoingUp) {
                isGoingUp = false;
            }
            else { // Arm is at the top, release the ball
                isBallHeld = false; // Release the ball
                isGoingUp = true;

                // update the ballX and ballY values according to current ball location
                ballX = 2.0;
                ballY = 6.0;
            }
        }

    }
    else {
        // Ball is released

        // move the ball
        glTranslatef(ballX, ballY, 1.0);

        // update ballY and ballX to simulate a throw
        ballY += ballVelocityY;
        ballVelocityY -= 0.001; // Gravity
        ballX += 0.06; // Move ball forward

        // Check if the ball hit the floor
        if (ballY <= -10.0) {
            isBallHeld = true; // Ball is back in the hand
            ballY = -4.0; // Reset ballY
            ballVelocityY = 0.1; // Reset velocity
            ballX = -2.0; // Reset ballX
            // move it
            glTranslatef(ballX, ballY, 1.0);

        }
    }

    // Draw the ball
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();



    // Window frame
    glPushMatrix();
    glColor3f(0.8, 0.52, 0.25);
    glBegin(GL_POLYGON);
    glVertex3f(-3.5, 0.5, -9.9);
    glVertex3f(3.5, 0.5, -9.9);
    glVertex3f(3.5, 7.0, -9.9);
    glVertex3f(-3.5, 7.0, -9.9);
    glEnd();
    glPopMatrix();

    // Window
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.5, 0.8);
    glVertex3f(-3.0, 1.0, -9.8);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(3.0, 1.0, -9.8);
    glColor3f(0.2, 0.5, 0.8);
    glVertex3f(3.0, 6.5, -9.8);
    glColor3f(0.2, 0.5, 0.8);
    glVertex3f(-3.0, 6.5, -9.8);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void animate() {
    LeftArm += 0.05 * armFront;  // Adjust the speed as needed
    if (LeftArm >= 210.0 || LeftArm <= -10.0) armFront = -armFront;  // Swing back and forth
    glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'x':
            Xangle += 5.0;
            if (Xangle > 360.0) Xangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'X':
            Xangle -= 5.0;
            if (Xangle < 0.0) Xangle += 360.0;
            glutPostRedisplay();
            break;
        case 'y':
            Yangle += 5.0;
            if (Yangle > 360.0) Yangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'Y':
            Yangle -= 5.0;
            if (Yangle < 0.0) Yangle += 360.0;
            glutPostRedisplay();
            break;
        case 'z':
            Zangle += 5.0;
            if (Zangle > 360.0) Zangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'Z':
            Zangle -= 5.0;
            if (Zangle < 0.0) Zangle += 360.0;
            glutPostRedisplay();
            break;

            // Add these to your `keyInput` function:
        case 'a':  // Rotate LeftArm counterclockwise
            LeftArm += 5.0;
            if (LeftArm > 45.0) LeftArm = 45.0;  // Limit rotation
            glutPostRedisplay();
            break;
        case 'A':  // Rotate LeftArm clockwise
            LeftArm -= 5.0;
            if (LeftArm < -45.0) LeftArm = -45.0;  // Limit rotation
            glutPostRedisplay();
            break;

        case 'd': // Example to rotate TorsoX
            TorsoX += 5.0;
            if (TorsoX > 360.0) TorsoX -= 360.0;
            glutPostRedisplay();
            break;
        case 'l': // Example to rotate LeftLeg
            LeftLeg += 5.0;
            if (LeftLeg > 360.0) LeftLeg -= 360.0;
            glutPostRedisplay();
            break;

        case ' ':
            if (armFront)
            {
                LeftArm += 5.0;
                if (LeftArm > 170) armFront = 0;

            }
            else
            {
                LeftArm -= 5.0;
                if (LeftArm < 0) armFront = 1;
            }
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("walls_and_floor.cpp");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glutIdleFunc(animate);  // Set idle callback for continuous animation


    glewInit();
    setup();

    glutMainLoop();
    return 0;
}
