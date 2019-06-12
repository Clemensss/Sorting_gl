#include <stdio.h>
#include <GL/glut.h>
#include "Dynamic_Array.h"
#include "Graphics.h"
#include <unistd.h>
#define DELAY 300

void display_col(void);
void bubbleSort(int *arr, int n);
int partition (int *arr, int low, int high, int *size);
void quickSort(int *arr, int low, int high, int size);
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
    int *arr, size=500;
    arr = Init(size);
    make_array(arr, size);
    shuffle(arr, size);
    print_arr(arr, size);
    quickSort(arr, 0, size-1, size-1);
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
	      num = get_val(arr, j);
	      column(2.0/n, num/DEN, i/DEN, -1.0, 0);
              }
	  draw_array(n, arr);
        }
    }
}
int partition (int *arr, int low, int high, int *size)
{
    int pivot = get_val(arr, high);    
    int i = (low - 1);  

    for (int j = low; j <= high- 1; j++){
        if (get_val(arr, j) <= pivot){
            i++;   
            swap(arr, i, j);
	    draw_array(*size, arr);
	    usleep(DELAY);
        }
    }
    swap(arr, i + 1, high);
    return (i + 1);
}
void quickSort(int *arr, int low, int high, int size)
{
    if (low < high){
        int pi = partition(arr, low, high, &size);

        quickSort(arr, low, pi - 1, size);
        quickSort(arr, pi + 1, high, size);
    }
} 

