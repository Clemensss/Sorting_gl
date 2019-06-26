#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Dynamic_Array.h"
#include "Algorithms.h"

int glfw_display(void);
char* read_shader(FILE *fp);
void column(float arr[4][12], short index, 
	    float x0, float y0, float x, float y);

void draw_array(double arrsize, int *arr, float twodarr[4][12]);

int main()
{

    glfw_display();
    return 0;
}
int glfw_display(void)
{

    if(!glfwInit()){

	printf("Error while initializing GLFW\n");

	glfwTerminate();
	exit(EXIT_FAILURE);
    }
    const float width = 640, height = 480;

    GLFWwindow *window = glfwCreateWindow(width, height, "Sorting", NULL, NULL);
    if(!window){

	printf("Error while creating window or context\n");

	glfwTerminate();
	exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();


    /*------ to Graphics later ------ */

    int mvp_location, vpos_location, vcol_location;
    unsigned int vertex_buffer, vertex_shader, fragment_shader, program;

    /* ---- Array and stuff ---- */
    float positions[4][12];
    int arr[4] = {1, 2, 3, 4}; 
    draw_array(4, arr, positions); 


    /* ---- Array and stuff ---- */
    

    //read files 
    const char *vertextext, *fragtext;
    FILE *fvertex = fopen("shaderf.vertex", "r");
    FILE *ffrag = fopen("shaderf.fragment", "r");

    vertextext = read_shader(fvertex);
    fragtext = read_shader(ffrag);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 4*(12*(sizeof(float))), positions, GL_STATIC_DRAW);
    
    //shaders 

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertextext, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragtext, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    //atributes

    vpos_location = glGetAttribLocation(program, "vPos");

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, (void*)0);
    glEnableVertexAttribArray(0);


    //draw
    while(!glfwWindowShouldClose(window))
    {
        int w, h;

	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
    
	glDrawArrays(GL_TRIANGLES, 0, 24);

	glfwSwapBuffers(window);
	glfwPollEvents();
    }


    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}


/* Assigns all the values to a certain 
  index of a 2d array in order to make 
  a quad

   Meaning of each assign explained 
   by x,y coordinates
*/
void column(float arr[4][12], short index,
	    float x0, float y0, float x, float y)
{
    float placement = x0 - 1;
    float height    = y + y0;
    float width     = x + placement; 

    //0,0 
    arr[index][0] = placement; 
    arr[index][1] = y0;

    //1,0
    arr[index][2] = width;
    arr[index][3] = y0;

    //0,1
    arr[index][4] = placement;
    arr[index][5] = height;

    //1,1
    arr[index][6] = width;
    arr[index][7] = height; 
    
    /*----- values that are repeated ---- */

    //0,0
    arr[index][8] = y0;
    arr[index][9] = y0;

    //1,1
    arr[index][10] = width;
    arr[index][11] = height;

}
void draw_array(double arrsize, int *arr, float twodarr[4][12])
{
    int arrnum, num;
    double i, deno = arrsize/2.0;
    
    for(i = 1.0; i <= arrsize; i++){
	num = i-1;
	arrnum = arr[num];
	/*arrnum = get_val(arr, i - 1);
	printf("num: %d\n", arrnum);*/

	column(twodarr, i, 2.0/arrnum, arrnum/deno, i/deno, -1.0);
    }
}
char* read_shader(FILE *fp)
{
    char *buffer = NULL;
    ssize_t len;
    ssize_t bytes_read = getdelim(&buffer, &len, '\0', fp);
    return buffer;
}

