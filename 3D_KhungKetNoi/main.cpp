#include<GL/glu.h>
#include<GL/glut.h>

GLfloat T = 0;

void MyInit() {
	glClearColor(0,0,0,1);
	glColor3f(1,0,0);
	glEnable(GL_DEPTH_TEST); //khi xoay co the thay duoc mat sau
}

void Spin() {
	T = T + 0.015;
	if(T > 360) {
		T = 0;
	}
	glutPostRedisplay(); //cap nhat
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) {
	glBegin(GL_POLYGON);
		glVertex3fv(A);
		glVertex3fv(B);
		glVertex3fv(C);
		glVertex3fv(D);
	glEnd();
}

void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[]) {
	glColor3f(1.0f, 0.0f, 0.0f);
	Face(V0, V1, V2, V3); //truoc
	glColor3f(0.0f, 1.0f, 0.0f);
	Face(V4, V5, V6, V7); //sau
	glColor3f(0.0f, 0.0f, 1.0f);
	Face(V0, V3, V7, V4); //trai
	glColor3f(1.0f, 0.0f, 1.0f);
	Face(V1, V2, V6, V5); //phai
}

void Draw() {
	GLfloat Vertices[8][3] = {
		{-0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{-0.5f, -0.5f, 0.5f},
		
		{-0.5f, 0.5f, -0.5f},
		{0.5f, 0.5f, -0.5f},
		{0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f}
	};
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(T, 1, 1, 0); //thay doi cach xoay bang cach thay gia tri xyz

	
	Cube(Vertices[0], Vertices[1], Vertices[2], Vertices[3], Vertices[4], Vertices[5], Vertices[6], Vertices[7]);

	glutSwapBuffers();
}

int main(int c, char *v[]) {
	glutInit(&c, v);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(600, 600); 
	glutInitWindowPosition(250, 50);
	glutCreateWindow("HVLoan");
	MyInit(); 
	glutDisplayFunc(Draw); 
	glutIdleFunc(Spin);
	glutMainLoop(); 
	return 0;
}
