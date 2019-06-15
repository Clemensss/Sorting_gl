#include <stdio.h>
#include <unistd.h>
#include <GLFW/glfw3.h>

#include "Dynamic_Array.h"
#include "Graphics.h"
#include "Algorithms.h"

int main()
{

    return 0;
}
int glfw_display(void)
{
    if(!glfwInit()){
	printf("Error while initializing GLFW\n");
	return 0;
    }

    GLFWwindow *window = glfwCreateWindow(640, 480, "Sorting", NULL, NULL);
    if(!window){
	printf("Error while creating window or context\n");
	return 0;
    }
    glfwMakeContextCurrent(window);
    /*------ to Graphics later ------ */
    Gluint vertex_buffer; 
    

    glfwDestroyWindow(window);

    glfwTerminate();
    return 1;
}
