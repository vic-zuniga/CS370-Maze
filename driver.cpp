//CS370
//Final Project

//#include "mazealg.cpp"
//#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "mazealg.cpp"
#include <iostream>

using namespace std;

float GEX = 10.0;
float GEY = 0.5;
float GEZ = 10.0;
float GLX = 0.0;
float GLY = 0.0;
float GLZ = 0.0;
float GUX = 0.0;
float GUY = 1.0;
float GUZ = 0.0;
bool INIT = true;

//<<<<<<<<<<<<<<< wall >>>>>>>>>>>>>>>>
void wall(double thickness)
{ // draw thin wall with top = xz-plane, corner at origin
  glPushMatrix();
  glTranslated(0.5, 0.5 * thickness, 0.5);
  glScaled(1.0, thickness, 1.0);
  glutSolidCube(1.0);
  glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<generateSpace>>>>>>>>>>>>>>>>>>>>>>
void generateSpace()
{
  bool maze[MAX_X][MAX_Z]; //declare maze array

  //loop through maze array and initialize each element with true
  for(unsigned int z = 0; z < MAX_Z; z++)
    {
      for(unsigned int x = 0; x < MAX_X; x++)
        {
          maze[x][z] = true;
        }
    }

  generate_maze(&maze); //generate maze

  for(unsigned int z = 0; z < MAX_Z; z++)
    {
      for(unsigned int x = 0; x < MAX_X; x++)
        {
          //cout<<maze[x][z]<<" ";
          if(maze[x][z] == true) //if there should be a wall
            {
              //draw wall
              glPushMatrix();
              glTranslated(x+0.5, 0, z+0.5);
              glutSolidCube(1);
              glPopMatrix();
            }
        }
      //cout<<endl;
    }
}

//<<<<<<<<<<<<<<<<<<<<< displaySolid >>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
  // set properties of the surface material
  GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f}; // gray
  GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat mat_shininess[] = {50.0f};
  glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
  glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

  // set the light source properties
  GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

  // set the camera
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double winHt = 1.0; // half-height of the window
  glOrtho(-winHt*64/48, winHt*64/48.0, -winHt, winHt, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(GEX, GEY, GEZ, GLX, GLY, GLZ, GUX, GUY, GUZ);

  // start drawing
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear the screen
  /*if(INIT == true)*/ generateSpace(); //draw walls
  INIT = false;
  
  //draw floor
  glPushMatrix();
  glScaled(MAX_X, 0.0, MAX_Z);
  wall(0.1);
  glPopMatrix();
  /*
  //draw ceiling
  glPushMatrix();
  glTranslated(0.0, 1.0, 0.0);
  glScaled(MAX_X, 0.0, MAX_Z);
  wall(0.1);
  glPopMatrix();
  */
  glFlush();
}

/*void sDisplay(void)
{
  glMatrixMode(GL_MODELVIEW);
  // start drawing
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clear the screen
  glPushMatrix();
  glTranslated(0.4, 0.4, 0.6);
  glRotated(45,0,0,1);
  glScaled(0.08, 0.08, 0.08);
  //jack(); // draw the jack
  glPopMatrix();
  glFlush();
}
*/
//<<<<<<<<<<<<<<<<<<<<<<myKeyboard>>>>>>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char Key, int x, int y)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  switch(Key)
    {
    case 'a': 
      GEX-=0.2; 
      GLX-=0.2; 
      gluLookAt(GEX, GEY, GEZ, GLX, GLY, GLZ, GUX, GUY, GUZ); 
      break; //left translate
    case 's': 
      GEX+=0.2; 
      GLX+=0.2; 
      gluLookAt(GEX, GEY, GEZ, GLX, GLY, GLZ, GUX, GUY, GUZ); 
      break; //right translate
    case 'q': 
      GEY+=0.2; 
      GLY+=0.2; 
      gluLookAt(GEX, GEY, GEZ, GLX, GLY, GLZ, GUX, GUY, GUZ); 
      break; //up translate
    case 'w': 
      GEY-=0.2; 
      GLY-=0.2; 
      gluLookAt(GEX, GEY, GEZ, GLX, GLY, GLZ, GUX, GUY, GUZ); 
      break; //down translate
    case 'z': 
      GEZ-=0.2; 
      GLZ-=0.2; 
      gluLookAt(GEX, GEY, GEZ, GLX, GLY, GLZ, GUX, GUY, GUZ); 
      break; //in translate
    case 'x': 
      GEZ+=0.2; 
      GLZ+=0.2; 
      gluLookAt(GEX, GEY, GEZ, GLX, GLY, GLZ, GUX, GUY, GUZ); 
      break; //out translate
    default: gluLookAt(GEX, GEY, GEZ, GLX, GLY, GLZ, GUX, GUY, GUZ); break;
    };
  //glutDisplayFunc(sDisplay);
  glutPostRedisplay();
  }

//<<<<<<<<<<<<<<<<<<<<<<main>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB| GLUT_DEPTH);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Maze Final Project");
  glutDisplayFunc(myDisplay);
  glEnable(GL_LIGHTING); // enable the light source
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST); // for hidden surface removal
  glEnable(GL_NORMALIZE); // normalize vectors for proper shading
  glClearColor(0.1f,0.1f,0.1f,0.0f); // background is light gray
  glViewport(0, 0, 640, 480);
  glutKeyboardFunc(myKeyboard);
  glutMainLoop();
  return 0;
}
