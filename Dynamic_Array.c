#include <stdio.h>
#include <GL/glut.h>
#include "Dynamic_Array.h"

/* Arrange the N elements of ARRAY in random order.
Only effective if N is much smaller than RAND_MAX;
if this may not be the case, use a better random
number generator. */

void shuffle(int *arr, size_t n)
{
    if(n > 1){
	size_t i;
	for(i = 0; i < n - 1; i++){
	    size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
	    swap(arr, j, i);
	}
    }
}
int* Init(int n)
{
    int *arr = (int*)malloc(sizeof(int)*n);
    return arr;
}
int get_val(int *arr, int index)
{
    int *num = arr + index;
    return *num;
}
void insert(int *arr, int n, int index)
{
    int *num = (arr + index);
    *num = n;
}
void swap(int *arr, int index1, int index2)
{
    int temp, *num1, *num2;
    num2 = arr + index2;
    num1 = arr + index1; 
    temp = *num2;
    *num2 = *num1;
    *num1 = temp;
}
void print_arr(int *arr, int index)
{
    printf("(");
    for(int i=0; i<index; i++){
	printf("%d ", *(arr + i));
    }
    printf(")");
}
void make_array(int *arr, int len)
{
    for(int i=1;i<=len;i++){
	insert(arr, i, i-1);
	}
}
