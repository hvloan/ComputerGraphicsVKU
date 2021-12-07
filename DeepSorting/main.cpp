#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

#define MAX_HEIGHT 500
#define MAX_WIDTH 700
#define MIDDLE_X MAX_WIDTH/2
#define MIDDLE_Y MAX_HEIGHT/2
#define f(i, a, b) for(int i = a;i < b;i++)
#define MAX 100

struct Point2D {
	int x;
	int y;
};

struct Point3D {
	int x;
	int y;
	int z;
};

struct FaceType {
	int numPoint;
	int indexPoint[MAX];
};

struct FaceModel {
	int numVertex, numFace, depth;
	Point2D vertex[MAX];
	FaceType face[MAX];
	float color[3];
};

void init();

void draw();
void putAPixel2D(Point2D X, float* color);

void depthSortingMethod(FaceModel polygons[], int n);

using namespace std;
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
	glutCreateWindow("Depth Sorting Method");
	glutInitWindowPosition(0, 0);
	glutDisplayFunc(draw);
	init();
	glutMainLoop();
	return 0;
}

void draw() {	
	int z1 = 100;

	Point2D A = {150, 200};
	Point2D B = {150, -200};
	Point2D C = {-300, -200};
	Point2D D = {-300, 200};

	FaceType f1 = {2, {0, 1}};
	FaceType f2 = {2, {1, 2}};
	FaceType f3 = {2, {2, 3}};
	FaceType f4 = {2, {3, 0}};
	FaceModel firstPolygon = {
		4, 4, z1, {A, B, C, D}, {f1, f2, f3, f4}, {1.0, 1.0, 1.0}
	};

	z1 = 200;

	A = {200, 100};
	B = {200, -100};
	C = {-200, -100};
	D = {-200, 100};

	f1 = {2, {0, 1}};
	f2 = {2, {1, 2}};
	f3 = {2, {2, 3}};
	f4 = {2, {3, 0}};
	FaceModel secondPolygon = {
		4, 4, z1, {A, B, C, D}, {f1, f2, f3, f4}, {0.0, 1.0, 0.0}
	};

	z1 = 50;
	A = {0, 150};
	B = {100, 0};
	C = {-100, 0};
	f1 = {2, {0, 1}};
	f2 = {2, {1, 2}};
	f3 = {2, {2, 0}};
	FaceModel thirdPolygon = {
		3, 3, z1, {A, B, C}, {f1, f2, f3}, {0.0, 0.0, 0.0}
	};

	FaceModel f[] = {firstPolygon, secondPolygon, thirdPolygon};
	int n = sizeof(f)/sizeof(f[0]);
	depthSortingMethod(f, n);

}

void depthSortingMethod(FaceModel polygons[], int n) {
	// Sort polygon
	for(int i = 0;i < n - 1;i++) {
		for(int j = i + 1;j < n;j++) {
			if (polygons[i].depth < polygons[j].depth) {
				FaceModel temp = polygons[i];
				polygons[i] = polygons[j];
				polygons[j] = temp;
			}
		}
	}

	for(int k = 0;k < n;k++) {
		FaceModel currentFaceModel = polygons[k];
		glColor3f(currentFaceModel.color[0], currentFaceModel.color[1], currentFaceModel.color[2]);
		glBegin(GL_QUADS);
		for(int i = 0;i < currentFaceModel.numFace;i++) {
			int n = currentFaceModel.face[i].numPoint;
			for(int j = 0;j < n;j++) {
				Point2D M = currentFaceModel.vertex[currentFaceModel.face[i].indexPoint[j]];
				glVertex2i(MIDDLE_X + M.x, MIDDLE_Y + M.y);
			}
		}
		glEnd();
		glFlush();
	}
	
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// glColor3f(0.0f, 0.0f, 0.0f);
	// glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, MAX_WIDTH, 0.0, MAX_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex2i(-MAX_WIDTH, MIDDLE_X);
		glVertex2i(MAX_WIDTH, MIDDLE_X);
		glVertex2i(MIDDLE_Y, MAX_HEIGHT);
		glVertex2i(MIDDLE_Y, -MAX_HEIGHT);
	glEnd();
	glFlush();
}
