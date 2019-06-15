#include <stdio.h>
#include <unistd.h>
#include <GLFW/glfw3.h>

#include "Dynamic_Array.h"
#include "Graphics.h"
#include "Algorithms.h"


void draw_array(double arrsize, int *arr, 
		GLdouble *color)
{
    int arrnum;
    double i;
    const double deno = (arrsize/2.0);
    
    for(i= 1.0;i <= arrsize; i++){
	arrnum = get_val(arr, i-1);
	printf("num: %d\n", arrnum);
	column(2.0/arrnum, arrnum/deno, i/deno, -1.0, color);
    }

    glEnd();
    glFlush();
}
void column(GLdouble x, GLdouble y, 
	    GLdouble x0, GLdouble y0, 
	    GLdouble *color)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLdouble position = x0+(-1.0);
    GLdouble height = y + y0;
    GLdouble width = x + position;

    printf("altura %lf largura %lf\n", height, width);

    glBegin(GL_QUADS);
    glColor3dv(color);
      glVertex2f(position, y0); //A(0,0)
      glVertex2f(width, y0); //do lado direito
      glVertex2f(width, height); //de cima
      glVertex2f(position, height); //do lado esquerdo
}
