#include <GL/glut.h>

#define maxWD 640
#define maxHT 480

void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
	glOrtho(-320,320,-240,240,-1,1);	
}


//void drawPoint
void drawPoint(int x, int y)
{
    glPointSize(7.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

//void drawPointTrans
void translatePoint(int px, int py, int tx, int ty)
{
    int fx = px, fy = py;
	for(int i = 0; i < 1; i++) {
  
        // update
        px = px + tx;
        py = py + ty;
  
        drawPoint(px, py); // drawing the point
  
        glFlush();
	}

}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
	//ve he truc toa do 
	glColor3f(0.0,0.0,3.0);
    glBegin(GL_LINES); 
    glVertex2f(250.0,0.0);
    glVertex2f(-250.0,0.0);
    glVertex2f(0.0,250.0);
    glVertex2f(0.0,-250.0);
    glEnd();
    //ket thuc ve he truc toa do
    
    //ve diem dau tien co toa do (20, 100)
    drawPoint(20, 100);
    //thuc hien dich chuyen cho diem do
    translatePoint(20, 100, 20, 50);
    
    glViewport(0,0,640,480);
    glFlush();
}

int main(int argc, char** argv){
	
	glutInit( & argc, argv );
	int mode=GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("");
	
    initGL();
	glutDisplayFunc(mydisplay);    
	glutMainLoop();
}

