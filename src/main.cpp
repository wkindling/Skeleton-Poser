#include "skeleton.h"
#include "interactive.h"
#include <glut.h>

double target_x=0, target_y=0, target_z=0;

Skeleton skeleton;

void display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	gluLookAt(move_x, move_y, move_z, skeleton.joints[0]->position.x(), skeleton.joints[0]->position.y(), skeleton.joints[0]->position.z(), 0, 1, 0);
	glRotatef(angle_x*radius, 0, 1, 0);
	glRotatef(angle_y*radius, 1, 0, 0);

	skeleton.updateJoint();
	skeleton.updateMesh();
	skeleton.drawJoint();
	skeleton.drawMesh();

	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	skeleton.readSkeletonInfo("C:/Users/dell/Desktop/bunnyinfo.txt");
	for (int i = 0; i < skeleton.joints.size(); i++)
	{
		std::cout << skeleton.joints[i]->position.transpose() << std::endl;
	}
	glutInit(&argc, argv);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykeyboard);
	glutSpecialFunc(switchop);
	glutMouseFunc(mymouse);
	glutMotionFunc(rotate);
	glutMainLoop();

	return 0;
}