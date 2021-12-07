#include <iostream>
using std::cerr;
using std::endl;
#include <stdlib.h>
#include <GL/glut.h> 
#include <windows.h>
#include <math.h>
#include <gl/Gl.h>
#include <gl/Glu.h>


int SCREEN_HEIGHT = 480;
// dem so lan nhap chuot
int NUMPOINTS = 0;

// Point class to keep it a little cleaner.
class Point {
public:
    float x, y, z;
    void setxy(float x2, float y2) { x = x2; y = y2; }
    const Point & operator=(const Point &rPoint) {
         x = rPoint.x;
         y = rPoint.y;
         z = rPoint.z;

         return *this;
      }

};

Point abc[4];

void myInit() {
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);

}

void drawDot(int x, int y) {
    glBegin(GL_POINTS);
     glVertex2i(x,y);
    glEnd();
    glFlush();
}

void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
      glVertex3f(p1.x, p1.y, p1.z);
      glVertex3f(p2.x, p2.y, p2.z);

    glEnd();
    glFlush();
}

// Calculate the next bezier point.
Point drawBezier(Point A, Point B, Point C, Point D, double t) {
    Point P;




    P.x = pow((1 - t), 3) * A.x + 3 * t * pow((1 -t), 2) * B.x + 3 * (1-t) * pow(t, 2)* C.x + pow (t, 3)* D.x;
    P.y = pow((1 - t), 3) * A.y + 3 * t * pow((1 -t), 2) * B.y + 3 * (1-t) * pow(t, 2)* C.y + pow (t, 3)* D.y;
    P.z = pow((1 - t), 3) * A.z + 3 * t * pow((1 -t), 2) * B.z + 3 * (1-t) * pow(t, 2)* C.z + pow (t, 3)* D.z;

    return P;
}

void myMouse(int button, int state, int x, int y) {
  // If left button was clicked
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      // Store where the user clicked, note Y is backwards.
    abc[NUMPOINTS].setxy((float)x,(float)(SCREEN_HEIGHT - y));
    NUMPOINTS++;

    // Draw the red  dot.
    drawDot(x, SCREEN_HEIGHT - y);

    // If 3 points are drawn do the curve.
    if(NUMPOINTS == 4) {
        glColor3f(1.0,1.0,1.0);
        // Draw two legs of the triangle
        drawLine(abc[0], abc[1]);
        drawLine(abc[1], abc[2]);
        drawLine(abc[2], abc[3]);
        //drawLine(abc[3], abc[4]);
        Point POld = abc[0];
        /* Draw each segment of the curve.  Make t increment in
                   smaller amounts for a more detailed curve. */
        for(double t = 0.0;t <= 1.0; t += 0.1) {
            Point P = drawBezier(abc[0], abc[1], abc[2], abc[3],  t);
            drawLine(POld, P);
            POld = P;
        }
        glColor3f(1.0,0.0,0.0);
        NUMPOINTS = 0;
    }
  }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Bezier Curve");

    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);

    myInit();
    glutMainLoop();

    return 0;
}
