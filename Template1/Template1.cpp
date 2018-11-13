// Template1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <Windows.h>
#include "include\GL\GL.H"
#include "include\GL\GLU.H"
#include "include\GL\glut.h"
#include "Template1.h"

int b = 0;
bool growing = true;
double angle = 0;
double c = 141.4213562373095;

void Triangle(int a) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);// OpenGL’a state
	//glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//Red;
	glVertex2f(0, 0);
	//glColor4f(0.0f, 1.0f, 0.0f, 1.0f);//Green
	glVertex2f(0, 100);
	//glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//Blue
	glVertex2f(100, 0);
	glEnd();
	//draw triangle line
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//white
	glVertex2f(0, 0);
	glVertex2f(0, 100);
	glVertex2f(100, 0);
	glEnd();
}
double CalcTriangleCenter()
{
	double c2 = c / 2;
	double centerFromZeroBase = sqrt(10000.0 - pow(c2, 2)) * (2 / 3.0);
	return centerFromZeroBase / sqrt(2.0);
}
double RatioFunc(double offsetFromMiddle)
{
	double aSmall = CalcTriangleCenter();
	return ((offsetFromMiddle + aSmall) / aSmall) * 1 + 0;
}
void InnerCircle(int a)
{
	glPushMatrix();
	//glRotatef(a, 0, 0, 1);
	for (size_t i = 0; i < 4; i++)
	{
		double centerLength = CalcTriangleCenter();
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);//Blue
		glPushMatrix();
		glTranslatef(b, b, 0);
		glTranslatef(centerLength, centerLength, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-centerLength, -centerLength, 0);
		Triangle(1);
		glPopMatrix();
		glRotatef(90, 0, 0, 1);
	}
	glPopMatrix();
}
void MiddleCircle(int a)
{
	glPushMatrix();
	glRotatef(a, 0, 0, 1);
	glTranslatef(0, 100, 0);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//Red;
			glPushMatrix();
			//glPushMatrix();
			//glTranslatef(aSmall, aSmall, 0);
			double y = RatioFunc(100);
			if (j == 0)
			{
				glTranslatef(b, b*y, 0);
			}
			else
			{
				glTranslatef(b*y, b , 0);
			}
			double centerLength = CalcTriangleCenter();
			glTranslatef(centerLength, centerLength, 0);
			glRotatef(angle, 0, 0, 1);
			glTranslatef(-centerLength, -centerLength, 0);
			Triangle(1);
			glPopMatrix();
			glRotatef(90, 0, 0, 1);
		}
		glRotatef(-90, 0, 0, 1);
		glTranslatef(-100, +100, 0);
	}
	glPopMatrix();
}

void ExternCircle(int a)
{
	glPushMatrix();
	glRotatef(a, 0, 0, 1);
	glTranslatef(0, 200, 0);
	glRotatef(90, 0, 0, 1);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			glPushMatrix();
			double y = RatioFunc(2 * 100);
			if (j == 0)
			{
				glTranslatef(b*y, b, 0);
			}
			if (j == 1)
			{
				double y = RatioFunc(100*sqrt(2));
				glTranslatef(b*y, b*y, 0);
			}
			if (j == 2)
			{
				glTranslatef(b, b*y, 0);
			}
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);//Green;
			double centerLength = CalcTriangleCenter();
			glTranslatef(centerLength, centerLength, 0);
			glRotatef(angle, 0, 0, 1);
			glTranslatef(-centerLength, -centerLength, 0);
			Triangle(1);
			glPopMatrix();
			glTranslatef(-100, 100, 0);
		}
		glTranslatef(100, -100, 0);
		glRotatef(90, 0, 0, 1);
	}
	glPopMatrix();
}
void render(int a)
{
	Growing();
	Rotation();
	InnerCircle(a*2);
	MiddleCircle(a*(-3));
	ExternCircle(a);
	glutPostRedisplay();
	glutTimerFunc(25, render, ++a);
}

void Growing()
{
	if (growing)
	{
		++b;
	}
	else
	{
		--b;
	}
	if (b <= 0)
	{
		growing = true;
	}
	if (b >= 30)
	{
		growing = false;
	}
}
void Rotation()
{
	angle += 10;
}

void MyDisplay(void) {
	// The new scene
	glLoadIdentity();
	// The end of scene
	glFlush();//start processing buffered OpenGL routines
	glClear(GL_COLOR_BUFFER_BIT);
}
void MyInit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);//select clearing (background) color
									 /* initialize viewing values */
	glViewport(0, 0, 300, 300);//window origin and size
	glMatrixMode(GL_PROJECTION);//
	glLoadIdentity();//=1
	gluOrtho2D(-500, 500, -500, 500);
	//gluPerspective(0.3, 1.777777777777778, 0.5, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();//=1
}

int main(int argc, char** argv) { //<- for normal API
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//single buffer and RGBA
	glutInitWindowSize(600, 600);//initial window size
	glutInitWindowPosition(500, 50);
	glutCreateWindow("Zad2");//create widnow, hello title bar							 
	MyInit();
	glutDisplayFunc(MyDisplay);//
	glutTimerFunc(100, render, 0);
	/*glutTimerFunc(100, MiddleCircle, 0);
	glutTimerFunc(100, ExternCircle, 0);*/
	glutMainLoop();//enter main loop and process events
	return 0;
}