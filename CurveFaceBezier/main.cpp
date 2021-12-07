#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h> 
#include <gl/glut.h>  

GLfloat ctrlpoints[4][4][3] = { 
	{ { -1.5, -1.5, 4.0 }, { -0.5, -1.5, 2.0 }, { 0.5, -1.5, -1.0 }, { 1.5, -1.5, 2.0 } }, 
	{ { -1.5, 0.5, 4.0 }, { -0.5, 0.5, 0.0 }, { 0.5, 0.5, 3.0 }, { 1.5, 0.5, 4.0 } }, 
	{ { -1.5, -0.5, 1.0 }, { -0.5, -0.5, 3.0 }, { 0.5, -0.5, 0.0 }, { 1.5, -0.5, -1.0 } },
	{ { -1.5, 1.5, -2.0 }, { -0.5, 1.5, -2.0 }, { 0.5, 1.5, 0.0 }, { 1.5, 1.5, -1.0 } } };
	
void display(void)
{
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
	glColor3f(1.0, 1.0, 1.0);   
	glPushMatrix();    
	glRotatef(10.0, 1.0, 1.0, 1.0);    //goc quay 10 do
	for (j = 0; j <= 8; j++) //cho lap de ve 9 doan thang
	{
		glBegin(GL_LINE_STRIP);  
		for (i = 0; i <= 30; i++) //ve ngang (tuong tu voi ve duong cong)         
		glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);     
		glEnd();      
		glBegin(GL_LINE_STRIP);     
		for (i = 0; i <= 30; i++) //ve doc        
		glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);    
		glEnd();
	}   
	glPopMatrix();   
	glFlush();
}

void init(void)
{ 
	glClearColor(0.0, 0.0, 0.0, 0.0);  
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);   
	glEnable(GL_DEPTH_TEST);  
	glShadeModel(GL_FLAT); 
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();  
	if (w <= h)
		glOrtho(-4.0, 4.0, -4.0*(GLfloat)h / (GLfloat)w, 4.0*(GLfloat)h / (GLfloat)w, -4.0, 4.0);
	else
		glOrtho(-4.0*(GLfloat)w / (GLfloat)h, 4.0*(GLfloat)w / (GLfloat)h, -4.0, 4.0, -4.0, 4.0);
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity(); 
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);   
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);  
	glutInitWindowSize(500, 500);   
	glutInitWindowPosition(100, 100);   
	glutCreateWindow("HVLoan");   
	init();
	glutDisplayFunc(display);  
	glutReshapeFunc(reshape);  
	glutMainLoop();  
	return 0;
}

