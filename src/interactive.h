#pragma once

#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <glut.h>
#include "skeleton.h"

double move_x = 0, move_y = 0, move_z = 2;
int oldposx = 0, oldposy = 0;
double radius = 0.3;
double angle_x = 0, angle_y = 0;
extern double target_x, target_y, target_z;
int op=0;

extern Skeleton skeleton;

void mymouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		oldposx = x; oldposy = y;
	}
	if (button == GLUT_WHEEL_UP)
	{
		//move_x -= 0.5;
		//move_y -= 0.5;
		move_z -= 0.5;
	}
	if (button == GLUT_WHEEL_DOWN)
	{
		//move_x += 0.5;
		//move_y += 0.5;
		move_z += 0.5;
	}
	glutPostRedisplay();
}

void rotate(int x, int y)
{
	int delta_x = x - oldposx;
	int delta_y = y - oldposy;
	angle_x += (double)delta_x;
	angle_y += (double)delta_y;
	if (angle_x >= 1080) angle_x -= 1080;
	if (angle_y >= 1080) angle_y -= 1080;
	oldposx = x;
	oldposy = y;
	glutPostRedisplay();
}

void init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("car");
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)width / (GLdouble)height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': skeleton.joints[op]->angle_x += 0.1; break;
	case 's': skeleton.joints[op]->angle_x -= 0.1; break;
	case 'a': skeleton.joints[op]->angle_y += 0.1; break;
	case 'd': skeleton.joints[op]->angle_y -= 0.1; break;
	case 'q': skeleton.joints[op]->angle_z += 0.1; break;
	case 'e': skeleton.joints[op]->angle_z -= 0.1; break;
	}
	glutPostRedisplay();
}

void switchop(GLint key, GLint x, GLint y)
{
	if (key == GLUT_KEY_UP)
	{
		op++;
		op = op % (skeleton.joints.size());
	}
	else if (key== GLUT_KEY_DOWN)
	{
		op--;
		if (op < 0) op += (skeleton.joints.size());
	}
	std::cout << op << std::endl;
	glutPostRedisplay();
}

#endif