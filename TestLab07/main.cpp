#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <map>
#include <vector>
#include <iostream>

using namespace::std;

const int VERTICES_SIZE = 4;
float vertices[VERTICES_SIZE][3] = {
            {0.1, 0.1, 0.1},
            {0.2, 0.8, 0.3},
            {0.3, 0.5, 0.5},
            {0.8, 0.2, 0.1},
           };


float vertex_normals[VERTICES_SIZE][3];

const int POLYGON_SIZE = 4;
int polygon[POLYGON_SIZE][3] = {
                {0, 1, 3},
                {0, 2, 1},
                {0, 3, 2},
                {1, 2, 3},
};

float av_point[3];
    
void averagePoint(float vertices[][3], int length, float result[3]) {
  for(int i = 0; i < length; i++) {
    result[0] += vertices[i][0];
    result[1] += vertices[i][1];
    result[2] += vertices[i][2];
  }

  result[0] /= length;
  result[1] /= length;
  result[2] /= length;
}


void normalise(float v[3]) {
  GLfloat length = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] /= length;
  v[1] /= length;
  v[2] /= length;
}

void crossProduct(float u[], float v[], float result[]) {
  result[0] = u[1] * v[2] - u[2] * v[1];
  result[1] = u[2] * v[0] - u[0] * v[2];
  result[2] = u[0] * v[1] - u[1] * v[0];
}

void calculate_normal(int polygon[3], float vertices[][3], float normal[3]) {
  GLfloat u[3], v[3];
  for (int i = 0; i < 3; i++) {
    u[i] = vertices[polygon[0]][i] - vertices[polygon[1]][i];
    v[i] = vertices[polygon[2]][i] - vertices[polygon[1]][i];
  }

  crossProduct(u, v, normal);
  normalise(normal);
}
void calculate_vertex_normals(float vertex_normals[VERTICES_SIZE][3])
{

  vector< vector<int> > vertex_to_faces(POLYGON_SIZE);
  vector< vector<float> > faces_to_normal(POLYGON_SIZE);


  for (int i = 0; i < POLYGON_SIZE; i++) {
    vector<float> normal(3);
    calculate_normal(polygon[i], vertices, &normal[0]);
    for (int j = 0; j < 3; j++) {
     vertex_to_faces[polygon[i][j]].push_back(i);
    }
    faces_to_normal[i] = normal;
  }

  for (int v = 0; v < VERTICES_SIZE; v++) {

    vector<int> &faces = vertex_to_faces[v];
    int faces_count = 0;
    float normal[3];
    for (vector<int>::iterator it = faces.begin(); it != faces.end(); ++it){
      normal[0] += faces_to_normal[*it][0];
      normal[1] += faces_to_normal[*it][1];
      normal[2] += faces_to_normal[*it][2];
      faces_count++;
    }
    normalise(normal);
    memcpy(vertex_normals[v], normal, sizeof(normal));
  }
}
void draw_polygon() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, &vertices[0][0]);
  glNormalPointer(GL_FLOAT, 0, &vertex_normals[0][0]);

  glDrawElements(GL_TRIANGLES, POLYGON_SIZE*3, GL_UNSIGNED_INT, polygon);
}
void init_geometry()
{
  averagePoint(vertices, VERTICES_SIZE, av_point);
  calculate_vertex_normals(vertex_normals);
}
void setup_illumination()
{
  GLfloat light_pos[] = {1.0, 1.0, 1.0, 0.0};
  GLfloat light_ka[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat light_kd[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_ks[] = {1.0, 1.0, 1.0, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ka);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_kd);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_ks);

  GLfloat material_ka[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat material_kd[] = {0.43, 0.47, 0.54, 1.0};
  GLfloat material_ks[] = {0.33, 0.33, 0.52, 1.0};
  GLfloat material_ke[] = {0.0, 0.0, 0.0, 0.0};
  GLfloat material_se[] = {10.0};

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  material_ka);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  material_kd);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  material_ks);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  material_ke);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_se);

  glShadeModel(GL_SMOOTH);

  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
}
void display (void)
{

  float const window_width  = glutGet(GLUT_WINDOW_WIDTH);
  float const window_height = glutGet(GLUT_WINDOW_HEIGHT);
  float const window_aspect = window_width / window_height;

  glViewport(0, 0, window_width, window_height);
  glClearDepth(1.);
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70, window_aspect, 1, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, -3, av_point[0], av_point[1], av_point[2], 0, 1, 0);
 
  setup_illumination();
  glEnable(GL_DEPTH_TEST);
  draw_polygon();
  glutSwapBuffers();
}
   
int main (int argc, char **argv)
{    
  glutInit(&argc, argv);
  glutInitWindowSize(350,350);
  glutInitWindowPosition(150, 150);
  glutInitDisplayMode    (GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow("OPENGL SHADING");
  init_geometry();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}


