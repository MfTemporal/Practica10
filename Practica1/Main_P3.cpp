#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 3", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shaders/core.vs", "Shaders/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {

		//Cubo café
		-0.5f, -0.5f, 0.5f, 0.7569f, 0.5412f,0.2706f,//Front
		0.5f, -0.5f, 0.5f,   0.7569f, 0.5412f,0.2706f,
		0.5f,  0.5f, 0.5f,   0.7569f, 0.5412f,0.2706f,
		0.5f,  0.5f, 0.5f,   0.7569f, 0.5412f,0.2706f,
		-0.5f,  0.5f, 0.5f,  0.7569f, 0.5412f,0.2706f,
		-0.5f, -0.5f, 0.5f,  0.7569f, 0.5412f,0.2706f,

		-0.5f, -0.5f,-0.5f,  0.7569f, 0.5412f,0.2706f,//Back
		 0.5f, -0.5f,-0.5f,  0.7569f, 0.5412f,0.2706f,
		 0.5f,  0.5f,-0.5f,  0.7569f, 0.5412f,0.2706f,
		 0.5f,  0.5f,-0.5f,  0.7569f, 0.5412f,0.2706f,
		-0.5f,  0.5f,-0.5f,  0.7569f, 0.5412f,0.2706f,
		-0.5f, -0.5f,-0.5f,  0.7569f, 0.5412f,0.2706f,

		 0.5f, -0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,
		 0.5f, -0.5f, -0.5f,   0.7569f, 0.5412f,0.2706f,
		 0.5f,  0.5f, -0.5f,   0.7569f, 0.5412f,0.2706f,
		 0.5f,  0.5f, -0.5f,   0.7569f, 0.5412f,0.2706f,
		 0.5f,  0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,
		 0.5f,  -0.5f, 0.5f,  0.7569f, 0.5412f,0.2706f,

		-0.5f,  0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,
		-0.5f,  0.5f, -0.5f,   0.7569f, 0.5412f,0.2706f,
		-0.5f, -0.5f, -0.5f,   0.7569f, 0.5412f,0.2706f,
		-0.5f, -0.5f, -0.5f,   0.7569f, 0.5412f,0.2706f,
		-0.5f, -0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,
		-0.5f,  0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,

		-0.5f, -0.5f, -0.5f,  0.7569f, 0.5412f,0.2706f,
		0.5f, -0.5f, -0.5f,   0.7569f, 0.5412f,0.2706f,
		0.5f, -0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,
		0.5f, -0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,
		-0.5f, -0.5f,  0.5f,  0.7569f, 0.5412f,0.2706f,
		-0.5f, -0.5f, -0.5f,  0.7569f, 0.5412f,0.2706f,

		-0.5f,  0.5f, -0.5f,  0.7569f, 0.5412f,0.2706f,
		0.5f,  0.5f, -0.5f,   0.7569f, 0.5412f,0.2706f,
		0.5f,  0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,
		0.5f,  0.5f,  0.5f,   0.7569f, 0.5412f,0.2706f,
		-0.5f,  0.5f,  0.5f,  0.7569f, 0.5412f,0.2706f,
		-0.5f,  0.5f, -0.5f,  0.7569f, 0.5412f,0.2706f,

		//Segundo color
		-0.5f, -0.5f, 0.5f, 0.2784f, 0.1255f,0.0078f,//Front
		0.5f, -0.5f, 0.5f,   0.2784f, 0.1255f,0.0078f,
		0.5f,  0.5f, 0.5f,   0.2784f, 0.1255f,0.0078f,
		0.5f,  0.5f, 0.5f,   0.2784f, 0.1255f,0.0078f,
		-0.5f,  0.5f, 0.5f,  0.2784f, 0.1255f,0.0078f,
		-0.5f, -0.5f, 0.5f,  0.2784f, 0.1255f,0.0078f,

		-0.5f, -0.5f,-0.5f,  0.2784f, 0.1255f,0.0078f,//Back
		 0.5f, -0.5f,-0.5f,  0.2784f, 0.1255f,0.0078f,
		 0.5f,  0.5f,-0.5f,  0.2784f, 0.1255f,0.0078f,
		 0.5f,  0.5f,-0.5f,  0.2784f, 0.1255f,0.0078f,
		-0.5f,  0.5f,-0.5f,  0.2784f, 0.1255f,0.0078f,
		-0.5f, -0.5f,-0.5f,  0.2784f, 0.1255f,0.0078f,

		 0.5f, -0.5f,  0.5f,  0.2784f, 0.1255f,0.0078f,
		 0.5f, -0.5f, -0.5f,   0.2784f, 0.1255f,0.0078f,
		 0.5f,  0.5f, -0.5f,   0.2784f, 0.1255f,0.0078f,
		 0.5f,  0.5f, -0.5f,   0.2784f, 0.1255f,0.0078f,
		 0.5f,  0.5f,  0.5f,   0.2784f, 0.1255f,0.0078f,
		 0.5f,  -0.5f, 0.5f,  0.2784f, 0.1255f,0.0078f,

		-0.5f,  0.5f,  0.5f,   0.2784f, 0.1255f,0.0078f,
		-0.5f,  0.5f, -0.5f,   0.2784f, 0.1255f,0.0078f,
		-0.5f, -0.5f, -0.5f,   0.2784f, 0.1255f,0.0078f,
		-0.5f, -0.5f, -0.5f,   0.2784f, 0.1255f,0.0078f,
		-0.5f, -0.5f,  0.5f,   0.2784f, 0.1255f,0.0078f,
		-0.5f,  0.5f,  0.5f,   0.2784f, 0.1255f,0.0078f,

		-0.5f, -0.5f, -0.5f,  0.2784f, 0.1255f,0.0078f,
		0.5f, -0.5f, -0.5f,   0.2784f, 0.1255f,0.0078f,
		0.5f, -0.5f,  0.5f,   0.2784f, 0.1255f,0.0078f,
		0.5f, -0.5f,  0.5f,   0.2784f, 0.1255f,0.0078f,
		-0.5f, -0.5f,  0.5f,  0.2784f, 0.1255f,0.0078f,
		-0.5f, -0.5f, -0.5f,  0.2784f, 0.1255f,0.0078f,

		-0.5f,  0.5f, -0.5f,  0.2784f, 0.1255f,0.0078f,
		0.5f,  0.5f, -0.5f,   0.2784f, 0.1255f,0.0078f,
		0.5f,  0.5f,  0.5f,   0.2784f, 0.1255f,0.0078f,
		0.5f,  0.5f,  0.5f,   0.2784f, 0.1255f,0.0078f,
		-0.5f,  0.5f,  0.5f,  0.2784f, 0.1255f,0.0078f,
		-0.5f,  0.5f, -0.5f,  0.2784f, 0.1255f,0.0078f,

		//Tercer color
		-0.5f, -0.5f, 0.5f, 0.9686f, 0.9333f,0.8039f,//Front
		0.5f, -0.5f, 0.5f,   0.9686f, 0.9333f,0.8039f,
		0.5f,  0.5f, 0.5f,   0.9686f, 0.9333f,0.8039f,
		0.5f,  0.5f, 0.5f,   0.9686f, 0.9333f,0.8039f,
		-0.5f,  0.5f, 0.5f,  0.9686f, 0.9333f,0.8039f,
		-0.5f, -0.5f, 0.5f,  0.9686f, 0.9333f,0.8039f,

		-0.5f, -0.5f,-0.5f,  0.9686f, 0.9333f,0.8039f,//Back
		 0.5f, -0.5f,-0.5f,  0.9686f, 0.9333f,0.8039f,
		 0.5f,  0.5f,-0.5f,  0.9686f, 0.9333f,0.8039f,
		 0.5f,  0.5f,-0.5f,  0.9686f, 0.9333f,0.8039f,
		-0.5f,  0.5f,-0.5f,  0.9686f, 0.9333f,0.8039f,
		-0.5f, -0.5f,-0.5f, 0.9686f, 0.9333f, 0.8039f,

		 0.5f, -0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		 0.5f, -0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		 0.5f,  0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		 0.5f,  0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		 0.5f,  0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		 0.5f,  -0.5f, 0.5f, 0.9686f, 0.9333f, 0.8039f,

		-0.5f,  0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f,  0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f, -0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f, -0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f, -0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f,  0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,

		-0.5f, -0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		0.5f, -0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		0.5f, -0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		0.5f, -0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f, -0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f, -0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,

		-0.5f,  0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		0.5f,  0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,
		0.5f,  0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		0.5f,  0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f,  0.5f,  0.5f, 0.9686f, 0.9333f, 0.8039f,
		-0.5f,  0.5f, -0.5f, 0.9686f, 0.9333f, 0.8039f,

		//Cuarto color
			-0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,//Front
			0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,

			-0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,//Back
			0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,

			0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,

			-0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,

			-0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, -0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, -0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,

			-0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, 0.5f, 0.5f, 0.3569f, 0.0863f, 0.1373f,
			-0.5f, 0.5f, -0.5f, 0.3569f, 0.0863f, 0.1373f,

			//Quinto color
			-0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,//Front
			0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,

			-0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,//Back
			0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,

			0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,

			-0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,

			-0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, -0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, -0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,

			-0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, 0.5f, 0.5f, 0.8275f, 0.2863f, 0.3176f,
			-0.5f, 0.5f, -0.5f, 0.8275f, 0.2863f, 0.3176f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
		// Cabeza y cuerpo
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0, .5, 0));
		model = glm::scale(model, glm::vec3(0.7, 0.7, 0.7));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(model, glm::vec3(0, -.55, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//oreja1
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(.40, .95, 0));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(.22, .45, .13));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(0, 0, .5));
		model = glm::scale(model, glm::vec3(.6, .7, .08));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);

		//oreja 2

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-.40, .95, 0));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(.22, .45, .13));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(0, 0, .5));
		model = glm::scale(model, glm::vec3(.6, .7, .08));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);
		

		//ojos
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(.15, .48, .33));
		model = glm::scale(model, glm::vec3(.13, .21, .05));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);

		model = glm::translate(model, glm::vec3(-2.3, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);

		model = glm::translate(model, glm::vec3(0, .36, .6));
		model = glm::scale(model, glm::vec3(.2, .15, .2));
		model = glm::scale(model, glm::vec3(1.7, 1.7, 1.7));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);

		model = glm::translate(model, glm::vec3(6.8, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);

		//boca
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(.0055, .25, .33));
		model = glm::scale(model, glm::vec3(.18, .095, .05));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);

		model = glm::translate(model, glm::vec3(.2, 0, .4));
		model = glm::scale(model, glm::vec3(.5, .5, .5));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);


		//pelaje
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0, -.18, .46));
		model = glm::scale(model, glm::vec3(0.7, 0.65, 0.20));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);

		
		
		model = glm::translate(model, glm::vec3(0, 0, -4.6));
		model = glm::scale(model, glm::vec3(1.4, 1, 1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);

		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(.4, -.18, .05));
		model = glm::scale(model, glm::vec3(.2, .5, .9));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);

		model = glm::translate(model, glm::vec3(-4, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);


		//colita
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0, .5, -.7));
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45, 1.01, 0.55));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(0, .58, 0));
		model = glm::scale(model, glm::vec3(1, .15, 1));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);



	
		model = glm::translate(model, glm::vec3(0, .58, 0));
		model = glm::scale(model, glm::vec3(1, 3.1, 1));
		model = glm::scale(model, glm::vec3(.45, .45, .45));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);


		//patitas
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(.2, -.6, .24));
		model = glm::scale(model, glm::vec3(0.25, 0.35, 0.2));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(model, glm::vec3(-1.7, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::translate(model, glm::vec3(0, 0, -2.5));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		model = glm::translate(model, glm::vec3(1.7, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);





		glBindVertexArray(0);


		



			

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.06f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.06f;
	 if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		 movY += 0.006f;
	 if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		 movY -= 0.006f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.06f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.06f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.06f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.06f;
 }


