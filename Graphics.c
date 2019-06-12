#include <stdio.h>
#include <GL/glut.h>
#include "Dynamic_Array.h"
#include "Graphics.h"

void draw_array(double list_size, int *arr)
{
    int num;
    const double DEN =(list_size/2.0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    for(double i=1.0;i<=list_size; i++){
	num = get_val(arr, (int)(i)-1);
	printf("num: %d\n", num);
	column(2.0/list_size, num/DEN, i/DEN, -1.0, 1);
    }
    glEnd();
    glFlush();
}
void column(GLdouble x, GLdouble y, 
	    GLdouble x0, GLdouble y0, int color)
{
    glBegin(GL_QUADS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    GLdouble Position = x0+(-1.0);
    GLdouble Altura = y + y0;
    GLdouble Largura = x + Position;
    printf("altura %lf largura %lf\n", Altura, Largura);
      glVertex2f(Position, y0); //A(0,0)
      glVertex2f(Largura, y0); //do lado direito
      glVertex2f(Largura, Altura); //de cima
      glVertex2f(Position,Altura); //do lado esquerdo
}
void reshape(GLsizei width, GLsizei height) 
{
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}
