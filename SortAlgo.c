#include <stdio.h>
#include <GL/glut.h>
#include "Dynamic_Array.h"
#include "Graphics.h"

void display_col(void);
void bubbleSort(int *arr, int n);
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutCreateWindow("Primeiro");
    glutInitWindowSize(1360, 768);
    glutInitWindowPosition(0, 0);
    glutDisplayFunc(display_col);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
void display_col(void)
{
    int *arr, size=200;
    arr = Init(size);
    make_array(arr, size);
    shuffle(arr, size);
    print_arr(arr, size);
    bubbleSort(arr, size);
}

void bubbleSort(int *arr, int n)
{
   int i, j;
   int num;
   const double DEN =(n/2.0);
   for (i = 0; i < n-1; i++){
       for (j = 0; j < n-i-1; j++){
           if(get_val(arr, j) > get_val(arr,j+1)){
              swap(arr, j, j+1);
	      num = get_val(arr, (int)(i)-1);
	      column(2.0/n, num/DEN, i/DEN, -1.0, 0);
	      glEnd();
              }
	  draw_array(n, arr);
        }
    }
}

