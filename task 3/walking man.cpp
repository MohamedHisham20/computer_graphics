


#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Angles to rotate the scene
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;

static float TorsoX = 0.0;  //move back a bit or tilt ACW
static float LeftArm = 0.0;  //rotate ACW abt z axis
static float LeftLeg = 0.0;  //rotate leg CW abt z axis
static float head = 0.0;   //move head back
static int armFront = 1;

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
    glVertex3f(-15.0, -10.0, -10.0);
    glVertex3f(15.0, -10.0, -10.0);
    glVertex3f(15.0, -10.0, 5.0);
    glVertex3f(-15.0, -10.0, 5.0);
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


    glPushMatrix();
    glColor3f(0.847, 0.701, 0.549);
    for (float x = -15.0; x <= 15.0; x += 1.5)
    {
        glBegin(GL_LINES);
        glVertex3f(x, -10.0, -10.0);
        glVertex3f(x, -10.0, 5.0);
        glEnd();
    }
    glPopMatrix();


    glPushMatrix();
    glColor3f(0.847, 0.701, 0.549);
    for (float z = -11; z <= 5.2; z += 1.5)
    {
        glBegin(GL_LINES);
        glVertex3f(-15.0, -10.0, z);
        glVertex3f(15.0, -10.0, z);
        glEnd();
    }
    glPopMatrix();


    // Right wall
    glPushMatrix();
    glColor3f(0.85, 0.8, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(15.0, -10.0, -10.0);
    glVertex3f(15.0, 10.0, -10.0);
    glVertex3f(15.0, 10.0, 5.0);
    glVertex3f(15.0, -10.0, 5.0);
    glEnd();
    glPopMatrix();

    // Ceiling
    glPushMatrix();
    glColor3f(1.0, 0.95, 0.9);
    glBegin(GL_POLYGON);
    glVertex3f(-15.0, 10.0, -10.0);
    glVertex3f(15.0, 10.0, -10.0);
    glVertex3f(15.0, 10.0, 5.0);
    glVertex3f(-15.0, 10.0, 5.0);
    glEnd();
    glPopMatrix();

    // Left wall
    glPushMatrix();
    glColor3f(0.9, 0.85, 0.75);
    glBegin(GL_POLYGON);
    glVertex3f(-15.0, -10.0, -10.0);
    glVertex3f(-15.0, 10.0, -10.0);
    glVertex3f(-15.0, 10.0, 5.0);
    glVertex3f(-15.0, -10.0, 5.0);
    glEnd();
    glPopMatrix();

    // Door frame on the left wall (moved further left)
    glPushMatrix();
    glColor3f(0.6, 0.4, 0.3); // Door frame color
    glBegin(GL_POLYGON);
    glVertex3f(-15.0, -10.0, -4.0);
    glVertex3f(-15.0, 4.0, -4.0);
    glVertex3f(-15.0, 4.0, 1.0);
    glVertex3f(-15.0, -10.0, 1.0);
    glEnd();
    glPopMatrix();


    // Door knob
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-14.7, -5.0, -2);
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

    // left hand
    glPushMatrix();
    glColor3f(0.9, 0.75, 0.6);

    glTranslatef(0.0, 1.3, -0.5);
    glRotatef(LeftArm, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -1.3, 0.5);

    glRotatef(70, 0.0, 1.0, 0.0);
    glTranslatef(-2.7, -1.0, 0.0);
    glScalef(0.15, 1, 0.25);
    glutSolidCube(5.0);
    glPopMatrix();



    // Back wall
    glPushMatrix();
    glColor3f(0.8, 0.75, 0.65);
    glBegin(GL_POLYGON);
    glVertex3f(-15.0, -10.0, -10.0);
    glVertex3f(15.0, -10.0, -10.0);
    glVertex3f(15.0, 10.0, -10.0);
    glVertex3f(-15.0, 10.0, -10.0);
    glEnd();
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
    glewInit();
    setup();
    glutMainLoop();
    return 0;
}