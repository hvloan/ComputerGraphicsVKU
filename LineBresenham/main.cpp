#include <GL/glut.h>

void initGL()
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f); 
	glOrtho(-320,320,-240,240,-1,1);	
}
void DuongThang1(int x1,int y1,int x2,int y2)	//-1 < m <0
{
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = 2*Dy-Dx;
  	int x = x1;	
	int y = y1;
	int c1 = 2*Dy;
	int c2 = 2*Dy - 2*Dx;
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	while (x < x2)  
	{
		if (p <0)	 
            p+= c1;
		else
            {
			    p = p + c2;
			    y--;
			}
		x++;
        glVertex2i(x,y);
	}
	glEnd();	
  	
}
void DuongThang2(int x1,int y1,int x2,int y2)	//0<m<1
{
	
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = 2*Dy-Dx;
  	int x = x1;	
	int y = y1;
	int c1 = 2*Dy;
	int c2 = 2*Dy - 2*Dx;
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	while (x < x2)  
	{
		if (p <0)	 
            p+= c1;
		else
            {
			    p = p + c2;
			    y++;
			}
		x++;
        glVertex2i(x,y);
	}
	glEnd();	
  	
}

void DuongThang3(int x1,int y1,int x2,int y2) //m >1
{
	int Dx = x2 - x1;
	int Dy = y2 - y1;
	int p = 2 * Dx - Dy;
	int x = x1;
	int y = y1;
	int c1 = 2 * Dx;
	int c2 = 2 * (Dx - Dy);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	while(x < x2) {
		if(p < 0) 
			p += c1;
		else {
			p += c2;
			x++;
		}
		y++;
		glVertex2i(x, y);
	}
	glEnd();
}

void DuongThang4(int x1, int y1, int x2, int y2) //m < -1
{
	int Dx = x2 - x1;
	int Dy = y2 - y1;
	int p = 2 * Dx + Dy;
	int x = x1;
	int y = y1;
	int c1 = 2 * Dx;
	int c2 = 2 * (Dx - Dy);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	while(x < x2) {
		if(p < 0) 
			p += c1;
		else {
			p += c2;
			x++;
		}
		y--;
		glVertex2i(x, y);
	}
	glEnd();
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES); 
    glVertex2f(200.0,0.0);
    glVertex2f(-200.0,0.0);
    glEnd();
 
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES); 
    glVertex2f(0.0,200.0);
    glVertex2f(0.0,-200.0);
    glEnd();
    
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(2.0);
	DuongThang1(10, -10, 150, -150);
	DuongThang2(15, 10, 100, 70);
	DuongThang3(10, 10, 50, 150);
	DuongThang4(10, -10, 50, -150);
	glViewport(0,0,640,480);
	glFlush();

}

int main(int argc, char** argv){
	
	glutInit(&argc, argv);
	int mode=GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("LINE BRESENHAM");
	 
	initGL();  
	glutDisplayFunc(mydisplay);    
	glutMainLoop();
}



