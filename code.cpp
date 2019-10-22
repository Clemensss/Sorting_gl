/*g++ `pkg-config --cflags glfw3` -o thing code.cpp glad.c `pkg-config --static --libs glfw3`*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <bits/stdc++.h> 

//include <iostream>
//include <vector>
//include <cmath>
//include <algorithm>

#define STB_IMAGE_IMPLEMENTATION

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  

void swap(int *first, int *second);
std::vector<int> make_arr(int size);
void bubble_sort(std::vector<int> vect, GLFWwindow* window);

unsigned int shader_maker (char *shader, unsigned int type);
unsigned int program_maker(char* vertex_file, char* frag_file);

void draw_array(std::vector<int> vect, GLFWwindow* window, 
		unsigned int VAO, unsigned int program, int index);

void init_draw(std::vector<int> vec, unsigned int *VAO, unsigned int *program);
char* read_shader(FILE *fp);

int main(int argc, char **argv)
{
    /*initialize glfw context */

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    // init window 
    GLFWwindow* window; 
    window = glfwCreateWindow(1200, 800, "LearnOpenGL", NULL, NULL);
    
    if (window == NULL)
    {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
	std::cout << "Failed to initialize GLAD" << std::endl;
	return -1;
    }
    
    //view port to easy some stuff and func for resizing
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    int size;
    sscanf(argv[1], "%d", &size); 

    std::cout << size;

    std::vector<int> vect = make_arr(size);

    std::random_shuffle(vect.begin(), vect.end());

    bubble_sort(vect, window);

    glfwTerminate();
    return 0;
}

std::vector<int> make_arr(int size)
{
    std::vector<int> vect;

    for(int i = 1; i <= size; i++)
    {
	vect.push_back(i);
    }
    return vect;
}
    
void bubble_sort(std::vector<int> vect, GLFWwindow* window)
{
    unsigned int VAO, program;
    init_draw(vect, &VAO, &program);

    bool sorted = false;

    while(!sorted)
    { 
	sorted = true;
	for(int i = 0; i < vect.size()-1; i++)
	{
	    int index;

	    if(vect[i] > vect[i+1])
	    {   
		index = i;
		sorted = false; 
		swap(&vect[i], &vect[i+1]);
	    }
	    draw_array(vect, window, VAO, program, index);
	}
    }
}

void swap(int *first, int *second)
{
    int middle;
    middle = *second;
    *second = *first;
    *first = middle;
}

/*
    initializes every bit of opengl that is needed for the program to run
    and "returns" the value of the VAO and the shader program.
*/

void init_draw(std::vector<int> vect, unsigned int *VAO, unsigned int *program)
{
    float vertices[] = 
    {
	// positions          // colors           // texture coords
	 0.0f,  0.0f, 3.0f,   1.0f, 1.0f, 1.0f,     // top right
	 0.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,     // bottom right
	-1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,     // bottom left
	-1.0f,  0.0f, 3.0f,   1.0f, 1.0f, 1.0f     // top left 
    };

    unsigned int indices[] = 
    {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
    }; 

    unsigned int EBO, VBO;
    
    //size of the "array" coisa is the width of the rectangulae

    int size = vect.size();
    float rect_width = ((2/(float)size)) -1;
    
    //assign the size of the individual cube
    vertices[0] = rect_width;
    vertices[6] = rect_width;

    glGenBuffers(1, &VBO);  
    glGenBuffers(1, &EBO);  

    glGenVertexArrays(1, VAO); 

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    
    char vert_file[] = "shader.vs";
    char frag_file[] = "shader.fs";

    *program = program_maker(vert_file, frag_file);
    
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}    
    
/*
    this in the pinacle of the program, it draw an array of n elements
    as columns, of which their size and placement in the screen is 
    propornional to the size of the index value, and to the index itself
    so the element n of size m of the array will grow with respect to the
    y axis at m's proportion, that is, its size in realation to the size of
    the array, and then be placed somwhere on the x axis depending on its
    location in the array

    it does this using the variables x_stride, x_jump, y_prop and the uniform
    y_var. x_stride is the width of each column, and for every column drawn
    in the loop, it ads itself to x_jump, which is the value x on the translation
    matrix that does into the shader. y_prop is the proportion at which y should 
    grow with respect to the value in the array's index, it then changes the 
    number var, and sends it to the uniform y_var, which will change the y
    values in only to vertexes in the chader, depending on their z value.
*/
void draw_array(std::vector<int> vect, GLFWwindow* window,
		unsigned int VAO, unsigned int program, int index)
{
    
    //the stride at which x grows
    float size = vect.size();
    float x_stride = ((2/(float)size));

    float number;

    unsigned int trans_t_id = glGetUniformLocation(program, "trans_t");
    unsigned int trans_c_id = glGetUniformLocation(program, "trans_c");
    unsigned int y_var_id = glGetUniformLocation(program, "y_var");

    glClearColor(0.0f, 0.0, 0.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //the jump in the x axes that the rect do 
    //and the the proportion at which the y axis must grow

    float x_jump = 0.0;
    float y_prop = 2.0/size;

    for(int i : vect)
    {
	number = (i*y_prop) -1.0; 
	
	//translation matrix for the x axis movement
	glm::mat4 trans_t = glm::mat4(1.0f);
	glm::mat4 trans_c = glm::mat4(1.0f);

	trans_t = glm::translate(trans_t, glm::vec3(x_jump, 0.0, 0.0));
	
	if(i==vect[index])
	    trans_c = glm::translate(trans_t, glm::vec3(0.0, 0.0, 1.0));
	else
	    trans_c = glm::translate(trans_t, glm::vec3(1.0, 1.0, 1.0));

	glUseProgram(program);
    
	//y growing in the shader 
	glUniform1f(y_var_id, number);
	glUniformMatrix4fv(trans_t_id, 1, GL_FALSE, glm::value_ptr(trans_t));
	glUniformMatrix4fv(trans_c_id, 1, GL_FALSE, glm::value_ptr(trans_c));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	//std::cout << x_jump << std::endl;
	//std::cout <<"num " << number << std::endl;
	
	//x growing
	x_jump += x_stride;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

unsigned int shader_maker(char *shader, unsigned int type)
{
    char* s_name = shader;
    unsigned int shader_id; 
    const char *src;
    FILE *f = fopen(shader, "r");
    
    src = read_shader(f);

    shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &src, NULL);
    glCompileShader(shader_id);

    int success;
    char info_log[512];

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
	printf("ERROR: %s_shader-COMPILATION_FAILED\n%s\n", s_name, info_log);
    }
    
    return shader_id;
}

unsigned int program_maker(char vertex_file[], char frag_file[])
{
    unsigned int vertex_shader, fragment_shader, program;

    vertex_shader = shader_maker(vertex_file, GL_VERTEX_SHADER);
    fragment_shader = shader_maker(frag_file, GL_FRAGMENT_SHADER);
    
    program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    int success;
    char info_log[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(program, 512, NULL, info_log);
	printf("ERROR: shader program FAILED\n%s\n", info_log);
    }

    return program;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

char* read_shader(FILE *fp)
{
    char *buffer = NULL;
    size_t len;
    ssize_t bytes_read = getdelim(&buffer, &len, '\0', fp);
    return buffer;
}

