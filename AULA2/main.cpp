#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

int angle = 0;
float tx = 0, ty = 0, tz = 0;

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


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

    // put the geometric transformations here
    glRotatef(angle, 0,1,0);
    glTranslatef(tx,ty,tz);

    // put drawing instructions here
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3d(0.0f,0.0f,5.0f);
        glVertex3d(0.0f, 0.0f, -5.0f);
        glVertex3d(0.0f, 5.0f, 0.0f);
        glVertex3d(0.0f, -5.0f, 0.0f);
        glVertex3d(5.0f, 0.0f, 0.0f);
        glVertex3d(-5.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.972f, 0.247f, 0.105f);
        glVertex3d(0.0f, 0.0f, 1.0f);
        glVertex3d(0.0f, 0.0f, -1.0f);
        glVertex3d(1.0f, 0.0f, 0.0f);

        glVertex3d(0.0f, 0.0f, 1.0f);
        glVertex3d(-1.0f, 0.0f, 0.0f);
        glVertex3d(0.0f, 0.0f, -1.0f);

        glColor3f(0.890f, 0.866f, 0.168f);
        glVertex3d(1.0f, 0.0f, 0.0f);
        glVertex3d(0.0f, 2.0f, 0.0f);
        glVertex3d(0.0f, 0.0f, 1.0f);

        glColor3f(0.509f, 0.850f, 0.513f);
        glVertex3d(0.0f, 0.0f, -1.0f);
        glVertex3d(0.0f, 2.0f, 0.0f);
        glVertex3d(1.0f, 0.0f, 0.0f);

        glColor3f(0.721f, 0.509f, 0.850f);
        glVertex3d(0.0f, 0.0f, 1.0f);
        glVertex3d(0.0f, 2.0f, 0.0f);
        glVertex3d(-1.0f, 0.0f, 0.0f);

        glColor3f(0.2f, 0.745f, 0.850f);
        glVertex3d(-1.0f, 0.0f, 0.0f);
        glVertex3d(0.0f, 2.0f, 0.0f);
        glVertex3d(0.0f, 0.0f, -1.0f);
    glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void arrowKeys(unsigned char key, int x, int y){
    if (key == 'd')
        angle += 5;

    if (key == 'a')
        angle -= 5;

    if (key == 'i') {
        tx -= 0.1f;
        tz -= 0.1f;
    }
    if (key == 'k') {
        tx += 0.1f;
        tz += 0.1f;
    }

    if (key == 'j') {
        tx -= 0.1f;
        tz += 0.1f;
    }
    if (key == 'l') {
        tx += 0.1f;
        tz -= 0.1f;
    }
}





int main(int argc, char **argv) {

    // init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(10,100);
	glutInitWindowSize(900,800);
	glutCreateWindow("CG@DI-UM");
		
    // Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    glutIdleFunc( renderScene );
	
    // put here the registration of the keyboard callbacks
    glutKeyboardFunc( arrowKeys );


    //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
