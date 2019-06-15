#include <stdio.h>
#include <unistd.h>
#include <GLFW/glfw3.h>

//-----Project Libraries-----

#include "Dynamic_Array.h"
#include "Graphics.h"
#include "Algorithms.h"


void display_col(void)
{
    //quickSort(arr, 0, size-1, size-1);
}
/*
	    Bubble Sort
    
  Implementacao bem simples do bubblesort
  com array dinamico, que a cada swap 
  desenha o array na tela atualizado
*/
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
              }
	  draw_array(n, arr, white); //Desenha o array
        }
    }
}
/*
	    Quick Sort

 Implementacao do quicksort com array dinamico, 
 que a cada swap desenha o array na tela atualizado, 
 utiliza a variavel size pra manter o verdadeiro 
 tamanho do array, porque eu aprendi da maneira mais
 dificil que o o maior numero do array nem sempre 
 representa o tamanho dele.
*/
int partition (int *arr, int low, int high, int *size)
{
    int pivot = get_val(arr, high);    
    int i = (low - 1);  
    GLdouble white[3] = {1.0, 1.0, 1.0};

    for (int j = low; j <= high- 1; j++){
        if (get_val(arr, j) <= pivot){
            i++;   
            swap(arr, i, j);
	    draw_array(*size, arr, white);
	   // usleep(DELAY);
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

