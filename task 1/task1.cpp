#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawSun(float SunPositionX, float SunPositionY, float sunRadius) {
    glColor3f(1.0f, 1.0f, 0.0f);
    int numberOfTriangles = 50; // Circle is a number of triangles rotated
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(SunPositionX, SunPositionY);
    for (int i = 0; i <= numberOfTriangles; i++) {
        float stepAngle = 2 * (M_PI)*i / numberOfTriangles;
        glVertex2f(
            SunPositionX + (sunRadius * cos(stepAngle)),
            SunPositionY + (sunRadius * sin(stepAngle))
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
}

void drawWindmill(float x, float y) {
    // Draw the base of the windmill
    glColor3f(0.9, 0.9, 0.9); // Light gray color for the windmill
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + 10, y, 0.0);
    glVertex3f(x + 10, y + 30, 0.0);
    glVertex3f(x, y + 30, 0.0);
    glEnd();

    // Draw the windmill blades
    glColor3f(0.8, 0.4, 0.2); // Brown color for the blades
    glBegin(GL_TRIANGLES);
    glVertex3f(x + 5, y + 30, 0.0); // Center of the windmill
    glVertex3f(x + 15, y + 30, 0.0); // Right blade
    glVertex3f(x + 5, y + 50, 0.0); // Top blade
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(x + 5, y + 30, 0.0);
    glVertex3f(x - 5, y + 30, 0.0); // Left blade
    glVertex3f(x + 5, y + 50, 0.0); // Top blade
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(x + 5, y + 30, 0.0);
    glVertex3f(x + 5, y + 20, 0.0); // Bottom blade
    glVertex3f(x + 15, y + 30, 0.0);
    glEnd();
}

void drawBoat(float x, float y) {
    // Draw the boat base
    glColor3f(0.5, 0.3, 0.2); // Brown color for the boat
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + 30, y, 0.0);
    glVertex3f(x + 25, y - 10, 0.0);
    glVertex3f(x + 5, y - 10, 0.0);
    glEnd();

    // Draw the sail
    glColor3f(1.0, 1.0, 1.0); // White color for the sail
    glBegin(GL_TRIANGLES);
    glVertex3f(x + 15, y + 10, 0.0); // Top of the sail
    glVertex3f(x + 25, y, 0.0); // Bottom right of the sail
    glVertex3f(x + 5, y, 0.0); // Bottom left of the sail
    glEnd();
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Sky blue color

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set orthographic projection

    // Draw elements in the scene
    drawSun(0.6f, 0.8f, 0.1f);

    drawGrassMountain(-0.8f, -0.4f, 0.5f, 0.3f); // Adjusted Y position
    drawGrassMountain(-0.3f, -0.4f, 0.6f, 0.35f); // Adjusted Y position
    drawGrassMountain(0.2f, -0.4f, 0.5f, 0.25f); // Adjusted Y position
    drawGrassMountain(0.8f, -0.4f, 0.4f, 0.3f); // Adjusted Y position

    // Draw fish
    drawFish(-0.5f, -0.9f, 1.0f);
    drawFish(0.0f, -0.95f, 1.2f);
    drawFish(0.5f, -0.9f, 1.0f);

    // Draw houses
    drawHouse(20.0, 20.0, 20.0, 20.0); // House 1
    drawHouse(60.0, 20.0, 20.0, 20.0); // House 2

    // Draw windmills
    drawWindmill(10.0, 50.0); // Windmill 1
    drawWindmill(70.0, 50.0); // Windmill 2

    // Draw boat
    drawBoat(10.0, 10.0); // Boat position

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

