#ifndef GRAPHICS_
#define GRAPHICS_

#include <stdio.h>
#include <unistd.h>
#include <GLFW/glfw3.h>

#define LIST_SLOPE 1.2

const GLdouble WHITE[3] = {1.0, 1.0, 1.0};

void column(GLdouble x, GLdouble y, GLdouble x0, GLdouble y0, GLdouble *color);
void draw_array(double list_size, int *arr, GLdouble *color);
void reshape(GLsizei width, GLsizei height);

#endif
