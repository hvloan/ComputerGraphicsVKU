#include<iostream>
#include<GL/glut.h>
#include<GL/GLU.h>
#include<GL/GL.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

struct Point2D
{
	float x;
	float y;
};

Point2D p1, p2, p3;

void initPoint()
{
	p1.x = 50;
	p1.y = 150;
	p2.x = 50;
	p2.y = 100;
	p3.x = 250;
	p3.y = 10;
}
void drawPol()
{
	glLineWidth(3.0); 
	glBegin(GL_POLYGON);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glVertex2f(p3.x, p3.y);
	glEnd();
}
void scale()
{
	int sx = 2;
	int sy = 3;
	p1.x *= sx;
	p1.y *= sy;
	p2.x *= sx;
	p2.y *= sy;
	p3.x *= sx;
	p3.y *= sy;
	
}
void print()
{
	drawPol();
	glutPostRedisplay();
}
void initGL()
{
	glClearColor(0.0, 0.0, 0.0, 3.0); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0 , 700, 700, 0.0);	
}
void mydisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 3.0f);
  glViewport(0,0,400,400);
  
  
  drawPol();
  glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("My OpenGL program");  
	glutDisplayFunc(mydisplay);
	initGL();
	initPoint();
	scale();
	glutIdleFunc(print);
	glutMainLoop();
	return 0;
}


