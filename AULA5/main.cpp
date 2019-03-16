#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <time.h>

float alfa = 90.0f, beta = 1.0f, radius = 200.0f;
float camX, camY, camZ;

float r = 50, ri = 35, rc = 15;

//Number of teapots
int blueCount = 10, redCount = 20;

float blueSepAngle = 360.0f/blueCount;
float redSepAngle = 360.0f/redCount;

float teaRotation = 0;
unsigned int timeNow = time(NULL);

void spherical2Cartesian() {
    camX = radius * cos(beta) * sin(alfa);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawTorus(float size) {
    glTranslatef(0,1,0);
    glRotatef(90,1,0,0);
    glutSolidTorus(size, 2, 20, 20);
}

void drawBlueTeaPots() {
    glRotatef(-teaRotation,0,1,0);
    glColor3f(0.0, 0.0, 0.7);
    for(int i = 0;i<blueCount;i++) {
        glPushMatrix();
        glTranslatef(rc, 1, 0);
        glutSolidTeapot(1);
        glPopMatrix();
        glRotatef(blueSepAngle,0,1,0);
    }
}

void drawRedTeapots() {
    glRotatef(teaRotation,0,1,0);
    glColor3f(0.9,0.0,0.0);
    for(int i = 0; i<redCount; i++){
        glPushMatrix();
        glTranslatef(ri, 1, 0);
        glRotatef(90,0,1,0);
        glutSolidTeapot(1);
        glPopMatrix();
        glRotatef(redSepAngle,0,1,0);
    }
}

void drawTrees() {
    float rx,rz;
    srand(timeNow);

    for(int i = 0; i<500; i++){
        do{
            rx = (float) rand() / (float) (RAND_MAX) * 200 - 100;
            rz = (float) rand() / (float) (RAND_MAX) * 200 - 100;
        }while(abs(rx)<sqrt(r*r-rz*rz) && abs(rz)<sqrt(r*r-rx*rx) );
        glPushMatrix();
        glTranslatef(rx,0,rz);

        //Cone baixo
        glPushMatrix();
        glTranslatef(0,0.1,0);
        glRotatef(-90,1,0,0);
        glColor3f(0.6,0.3,0.0);
        glutSolidCone(1,2, 10,10);
        glPopMatrix();

        //Cone cima
        glPushMatrix();
        glTranslatef(0,2,0);
        glRotatef(-90,1,0,0);
        glColor3f(0.0,0.9,0.3);
        glutSolidCone(2,8, 15,15);
        glPopMatrix();
        glPopMatrix();
    }
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    gluLookAt(camX, camY, camZ,
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    //Draw plane
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);

    glVertex3f(100.0f, 0, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);
    glVertex3f(100.0f, 0, 100.0f);
    glEnd();

    teaRotation += 1;

    glPushMatrix();
    glColor3f(0.7,0.0,0.3);
    drawTorus(1);
    glPopMatrix();

    glPushMatrix();
    drawBlueTeaPots();
    glPopMatrix();

    glPushMatrix();
    drawRedTeapots();
    glPopMatrix();

    glPushMatrix();
    drawTrees();
    glPopMatrix();

    glutSwapBuffers();
}


void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            alfa -= 0.1; break;

        case GLUT_KEY_LEFT:
            alfa += 0.1; break;

        case GLUT_KEY_UP:
            beta += 0.05f;
            if (beta > 1.5f)
                beta = 1.5f;
            break;

        case GLUT_KEY_DOWN:
            beta -= 0.05f;
            if (beta < -1.5f)
                beta = -1.5f;
            break;

        case GLUT_KEY_PAGE_DOWN: radius -= 8.0f;
            if (radius < 1.0f)
                radius = 1.0f;
            break;

        case GLUT_KEY_PAGE_UP: radius += 8.0f; break;
    }
    spherical2Cartesian();
    glutPostRedisplay();
}


void printInfo() {

    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));

    printf("\nUse Arrows to move the camera up/down and left/right\n");
    printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
    glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);

    spherical2Cartesian();

    printInfo();

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}
