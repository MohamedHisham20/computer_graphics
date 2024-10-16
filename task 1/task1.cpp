#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawCircle(float centerX, float centerY, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);

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
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);
        glVertex2f(centerX + x, centerY + y);
    }

    glEnd();
}

void createCloud(float x, float y, float scale)
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

    glColor3f(0.0, 1.0, 0.0);  //grean 
    //center 
    drawCircle(x, y, 9.5 * scale);
    //left
    drawCircle(x - 10, y, 6 * scale);
    //right
    drawCircle(x + 10, y, 6 * scale);

    //wood branch
    glColor3f(0.65f, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
    glVertex3f(x - (1.5 * scale), y - (8 * scale), 0.2);
    glVertex3f(x + (1.5 * scale), y - (8 * scale), 0.2);
    glVertex3f(x - (1.5 * scale), y - (30 * scale), 0.2);
    glVertex3f(x + (1.5 * scale), y - (30 * scale), 0.2);
    glEnd();

}


void drawSun(float SunPositionX, float SunPositionY, float sunRadius) {
    glColor3f(1.0f, 1.0f, 0.0f);
    int numberOfTriangles = 100;
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
    glColor3f(0.0f, 0.5f, 0.0f);
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
    glVertex2f(fishX - 0.05f * fishBody, fishY);
    glVertex2f(fishX - 0.08f * fishBody, fishY + 0.03f * fishBody);
    glVertex2f(fishX - 0.08f * fishBody, fishY - 0.03f * fishBody);
    glEnd();
}


void drawHouse(float x, float y, float width, float height) {

    glColor3f(1.0, 0.9, 0.7);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + width, y, 0.0);
    glVertex3f(x + width, y + height, 0.0);
    glVertex3f(x, y + height, 0.0);
    glEnd();


    glColor3f(0.8, 0.2, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex3f(x, y + height, 0.0);
    glVertex3f(x + width / 2, y + height + height * 0.5, 0.0);
    glVertex3f(x + width, y + height, 0.0);
    glEnd();


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


void drawMountain() {
    glColor3f(0.6f, 0.3f, 0.1f);  // Brown mountain
    glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, -0.2f, 0.0f);
    glVertex3f(0.2f, -0.8f, 0.0f);
    glVertex3f(0.8f, -0.8f, 0.0f);
    glEnd();
}


void drawEruption() {
    float peakX = 0.2f;   // X-coordinate of the volcano peak
    float peakY = 0.0f;  // Y-coordinate of the volcano peak

    // Outer Red Explosion (bigger and more spread)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(peakX, peakY, 0.0f);           // Peak of volcano
    glVertex3f(peakX - 0.15f, peakY + 0.6f, 0.0f); // Left outer explosion
    glVertex3f(peakX + 0.15f, peakY + 0.6f, 0.0f); // Right outer explosion
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(peakX, peakY, 0.0f);           // Peak of volcano
    glVertex3f(peakX - 0.25f, peakY + 0.45f, 0.0f); // Left secondary explosion
    glVertex3f(peakX + 0.25f, peakY + 0.45f, 0.0f); // Right secondary explosion
    glEnd();

    // Middle Orange Explosion
    glColor3f(1.0f, 0.5f, 0.0f);  // Lava-like color (orange)
    glBegin(GL_TRIANGLES);
    glVertex3f(peakX, peakY, 0.0f);           // Peak of volcano
    glVertex3f(peakX - 0.1f, peakY + 0.5f, 0.0f);  // Left middle explosion
    glVertex3f(peakX + 0.1f, peakY + 0.5f, 0.0f);  // Right middle explosion
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(peakX, peakY, 0.0f);           // Peak of volcano
    glVertex3f(peakX - 0.2f, peakY + 0.35f, 0.0f); // Left middle explosion
    glVertex3f(peakX + 0.2f, peakY + 0.35f, 0.0f); // Right middle explosion
    glEnd();

    // Inner Yellow Explosion (smaller and closer to the peak)
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow (hot lava)
    glBegin(GL_TRIANGLES);
    glVertex3f(peakX, peakY, 0.0f);           // Peak of volcano
    glVertex3f(peakX - 0.05f, peakY + 0.35f, 0.0f); // Left inner explosion
    glVertex3f(peakX + 0.05f, peakY + 0.35f, 0.0f); // Right inner explosion
    glEnd();

    // Add smaller particles around for more realism
    glColor3f(1.0f, 0.5f, 0.0f);  // Smaller lava particles
    glBegin(GL_POINTS);
    glVertex3f(peakX + 0.02f, peakY + 0.4f, 0.0f);  // Small particle 1
    glVertex3f(peakX - 0.03f, peakY + 0.43f, 0.0f); // Small particle 2
    glVertex3f(peakX + 0.1f, peakY + 0.55f, 0.0f);  // Small particle 3
    glVertex3f(peakX - 0.08f, peakY + 0.5f, 0.0f);  // Small particle 4
    glEnd();

}



void drawLake() {
    //glColor3f(0.0f, 0.7f, 1.0f); // Light blue for lake
    glBegin(GL_POLYGON);
    //glColor3f(0.0f, 0.7f, 1.0f); // Light blue for lake
    //glColor3f(82.0f / 255.0f, 133.0f / 255.0f, 145.0f / 255.0f);
    glColor3f(0, 0, 0);
    glVertex3f(-1.0f, -0.6f, 0.0f);
    glVertex3f(1.0f, -0.6f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();
}

void drawWindmill(float x, float y, float scale) {
    glColor3f(0.9, 0.9, 0.9);

    glBegin(GL_POLYGON);
    glVertex3f(x + .48 * scale, y + .48 * scale, 0);
    glVertex3f(x + .53 * scale, y + .48 * scale, 0);
    glVertex3f(x + .53 * scale, y + .53 * scale, 0);
    glVertex3f(x + .48 * scale, y + .53 * scale, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * .70, y + scale * .80, 0);
    glVertex3f(x + scale * .48, y + scale * .53, 0);
    glVertex3f(x + scale * .53, y + scale * .53, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * .80, y + scale * .30, 0);
    glVertex3f(x + scale * .53, y + scale * .53, 0);
    glVertex3f(x + scale * .53, y + scale * .48, 0);

    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * .20, y + scale * .40, 0);
    glVertex3f(x + scale * .48, y + scale * .53, 0);
    glVertex3f(x + scale * .48, y + scale * .48, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * .50, y + scale * 0.50, 0);
    glVertex3f(x + scale * .48, y + scale * 0.0, 0);
    glVertex3f(x + scale * .53, y + scale * 0.0, 0);
    glEnd();
}

void drawBoat(float x, float y, float scale) {
    // Draw the boat base
    glColor3f(0.5, 0.3, 0.2);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + scale * 0.3, y, 0.0);
    glVertex3f(x + scale * 0.25, y - scale * 0.1, 0.0);
    glVertex3f(x + scale * 0.05, y - scale * 0.1, 0.0);
    glEnd();

    // Draw the sail
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(x + scale * 0.15, y + scale * 0.1, 0.0);
    glVertex3f(x + scale * 0.25, y, 0.0);
    glVertex3f(x + scale * 0.05, y, 0.0);
    glEnd();
}

void drawRiver(float x, float y, float width, float height) {

    glColor3f(0.0, 0.5, 1.0); // Blue color for the river
    glBegin(GL_POLYGON);
    glColor3f(26.0f / 255.0f, 40.0f / 255.0f, 147.0f / 255.0f);
    glVertex3f(x, y, 0.0);
    glColor3f(0.0, 0.5, 1.0);
    glVertex3f(x + width, y, 0.0);
    glVertex3f(x + width, y + height, 0.0);
    glVertex3f(x, y + height, 0.0);
    glEnd();
}

void drawPlane(float x, float y, float width, float height) {
    glColor3f(1.0, 0.5, 0.0);

    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + width, y, 0.0);
    glVertex3f(x + width, y + height, 0.0);
    glVertex3f(x + width / 3, y + height, 0.0);
    glEnd();

    //// setting the drawing color
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.028, y, 0.0);
    glVertex3f(x + 0.037, y, 0.0);
    glVertex3f(x + 0.037, y + 0.011, 0.0);
    glVertex3f(x + 0.028, y + 0.011, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + 0.05, y + 0.0033, 0.0);
    glVertex3f(x + 0.063, y + 0.0033, 0.0);
    glVertex3f(x + 0.063, y + 0.011, 0.0);
    glVertex3f(x + 0.05, y + 0.011, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f((x + 0.02) + 0.05, y + 0.0033, 0.0);
    glVertex3f((x + 0.02) + 0.063, y + 0.0033, 0.0);
    glVertex3f((x + 0.02) + 0.063, y + 0.011, 0.0);
    glVertex3f((x + 0.02) + 0.05, y + 0.011, 0.0);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(x + 0.08, (y + 0.025), 0.0);
    glVertex3f(x + 0.1, (y + 0.025), 0.0);
    glVertex3f(x + 0.1, (y + 0.025) + 0.02, 0.0);
    glEnd();



    float x_plan2 = 0.25;
    float y_plan2 = -0.07;

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);
    glVertex3f(x + x_plan2, y + y_plan2, 0.0);
    glVertex3f(x + x_plan2 + width, y + y_plan2, 0.0);
    glVertex3f(x + x_plan2 + width, y + y_plan2 + height, 0.0);
    glVertex3f(x + x_plan2 + (width / 3), y + y_plan2 + height, 0.0);
    glEnd();

    //// setting the drawing color
    glColor3f(1.0, 0.0, 0.0);


    glBegin(GL_POLYGON);
    glVertex3f(x + x_plan2 + 0.028, y + y_plan2, 0.0);
    glVertex3f(x + x_plan2 + 0.037, y + y_plan2, 0.0);
    glVertex3f(x + x_plan2 + 0.037, y + y_plan2 + 0.011, 0.0);
    glVertex3f(x + x_plan2 + 0.028, y + y_plan2 + 0.011, 0.0);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(x + x_plan2 + 0.05, y + y_plan2 + 0.0033, 0.0);
    glVertex3f(x + x_plan2 + 0.063, y + y_plan2 + 0.0033, 0.0);
    glVertex3f(x + x_plan2 + 0.063, y + y_plan2 + 0.011, 0.0);
    glVertex3f(x + x_plan2 + 0.05, y + y_plan2 + 0.011, 0.0);
    glEnd();

    // Draw windows on plan2 with specified vertices counterclockwise.
    glBegin(GL_POLYGON);
    glVertex3f((x + x_plan2 + 0.02) + 0.05, y + y_plan2 + 0.0033, 0.0);
    glVertex3f((x + x_plan2 + 0.02) + 0.063, y + y_plan2 + 0.0033, 0.0);
    glVertex3f((x + x_plan2 + 0.02) + 0.063, y + y_plan2 + 0.0033, 0.0);
    glVertex3f((x + x_plan2 + 0.02) + 0.063, y + y_plan2 + 0.011, 0.0);
    glVertex3f((x + x_plan2 + 0.02) + 0.05, y + y_plan2 + 0.011, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(x + x_plan2 + 0.08, (y + y_plan2 + 0.025), 0.0);
    glVertex3f(x + x_plan2 + 0.1, (y + y_plan2 + 0.025), 0.0);
    glVertex3f(x + x_plan2 + 0.1, (y + y_plan2 + 0.025) + 0.02, 0.0);
    glEnd();

}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Sky blue color

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

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



    drawWindmill(0.55, -0.5, 0.5);
    drawWindmill(0.2, -0.4, 0.2);
    drawWindmill(-1, -0.3, 0.3);

    // Draw the river, adjusting position and size to fit in [-1, 1]
    drawRiver(-1.0, -1.0, 2.0, 0.5);


    drawFish(-0.7f, -0.8f, 1.0f);
    drawFish(-0.1f, -0.90f, 0.8f);
    drawFish(0.5f, -0.7f, 0.9f);
    drawFish(0.8f, -0.90f, 0.8f);


    drawBoat(-0.6, -0.55, 1.0);
    drawBoat(0.0, -0.7, 0.5);   // A smaller boat


    drawPlane(-0.33, 0.7, 0.1, 0.025);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(240, 40);
    glutCreateWindow("Fish-Grass-Sun-Boat-Houses-Windmill");

    glutDisplayFunc(drawScene);
    drawScene();
    glutMainLoop();

    return 0;
}
