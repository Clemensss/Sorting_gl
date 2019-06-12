#ifndef GRAPHICS_
#define GRAPHICS_

#define LIST_SLOPE 1.2

void column(GLdouble x, GLdouble y, GLdouble x0, GLdouble y0, int color);
void draw_array(double list_size, int *arr);
void reshape(GLsizei width, GLsizei height);

#endif
