#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificación de errores de creacion  ventana
	if (window== NULL) 
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

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	Shader OurShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {

		//Figura 1
		-0.65f, 0.6f, 0.0f,    0.4f,0.0471f,0.6471f,  // E 0
		-0.504f, 0.6f, 0.0f,    0.4f,0.0471f,0.6471f,  // F 1
		-0.65f, 0.452f, 0.0f,   0.4f,0.0471f,0.6471f,  // G 2
		-0.504f, 0.452f, 0.0f,   0.4f,0.0471f,0.6471f, //  H 3

		-0.504f, 0.452f, 0.0f,   0.4745f,0.7804f,0.3843f, //  H 4
		-0.352f, 0.6f, 0.0f,   0.4745f,0.7804f,0.3843f, //  I 5
		-0.205f, 0.452f, 0.0f,   0.4745f,0.7804f,0.3843f, //  J 6
		-0.345f, 0.452f, 0.0f,   0.4745f,0.7804f,0.3843f, //  K 7

		-0.8f, 0.452f, 0.0f,   0.9804f,0.1922f,0.4039f, //  O 8
		-0.8f, 0.3f, 0.0f,   0.9804f,0.1922f,0.4039f, //  P 9
		-0.65f, 0.6f, 0.0f,    0.9804f,0.1922f,0.4039f,  // E 10
		-0.65f, 0.452f, 0.0f,   0.9804f,0.1922f,0.4039f,  // G 11

		-0.504f, 0.452f, 0.0f,   0.9882f,0.4863f,0.302f, //  H 12
		-0.352f, 0.6f, 0.0f,   0.9882f,0.4863f,0.302f, //  I 13
		-0.504f, 0.6f, 0.0f,    0.9882f,0.4863f,0.302f,  // F 14

		-0.205f, 0.452f, 0.0f,   1.0f,0.7373f,0.2784f, //  J 15
		-0.354f, 0.452f, 0.0f,   1.0f,0.7373f,0.2784f, //  K 16
		-0.205f, 0.3f, 0.0f,   1.0f,0.7373f,0.2784f, //  L 17

		-0.65f, 0.452f, 0.0f,   0.7882f,0.0f,0.5412f,  // G 18
		-0.65f, 0.153f, 0.0f,   0.7882f,0.0f,0.5412f,  // N 19
		-0.354f, 0.153f, 0.0f,   0.7882f,0.0f,0.5412f,  // M 20

		-0.354f, 0.452f, 0.0f,   0.0f,0.6039f,0.949f, //  K 21
		-0.65f, 0.452f, 0.0f,   0.0f,0.6039f,0.949f,  // G 22
		-0.354f, 0.153f, 0.0f,   0.0f,0.6039f,0.949f,  // M 23
		

		//Figura 2

		0.515f, -0.374f, 0.0f,   0.9804f,0.1922f,0.4039f,  // U 24
		0.676f, -0.374f, 0.0f,   0.9804f,0.1922f,0.4039f,  // V 25
		0.592f, -0.458, 0.0f,   0.9804f,0.1922f,0.4039f,  // R 26
		0.756f, -0.458, 0.0f,   0.9804f,0.1922f,0.4039f,  // W 27

		0.512f, -0.541f, 0.0f,   0.4f,0.0471f,0.6471f,  // A3 28
		0.431f, -0.622f, 0.0f,   0.4f,0.0471f,0.6471f,  // B2 29
		0.512f, -0.704f, 0.0f,   0.4f,0.0471f,0.6471f,  // C2 30
		0.592f, -0.622f, 0.0f,   0.4f,0.0471f,0.6471f,  // Z 31

		0.431f, -0.294f, 0.0f,   0.0f,0.6039f,0.949f,  // A2 32
		0.268f, -0.457f, 0.0f,   0.0f,0.6039f,0.949f,  // Q 33
		0.592f, -0.457f, 0.0f,   0.0f,0.6039f,0.949f,  // R 34

		0.756f, -0.458, 0.0f,   0.7882f,0.0f,0.5412f,  // W 35
		0.431f, -0.458, 0.0f,   0.7882f,0.0f,0.5412f,  // S 36
		0.592f, -0.622f, 0.0f,   0.7882f,0.0f,0.5412f,  // Z 37

		0.515f, -0.374f, 0.0f,   0.9882f,0.4863f,0.302f,  // U 38
		0.676f, -0.374f, 0.0f,   0.9882f,0.4863f,0.302f,  // V 39
		0.598f, -0.294f, 0.0f,   0.9882f,0.4863f,0.302f,  // T 40

		0.268f, -0.457f, 0.0f,   0.4745f,0.7804f,0.3843f,  // Q 41
		0.431f, -0.622f, 0.0f,   0.4745f,0.7804f,0.3843f,  // B2 42
		0.431f, -0.458, 0.0f,   0.4745f,0.7804f,0.3843f,  // S 43

		0.431f, -0.458, 0.0f,   1.0f,0.7373f,0.2784f,  // S 44
		0.512f, -0.541f, 0.0f,   1.0f,0.7373f,0.2784f,  // A3 45
		0.431f, -0.622f, 0.0f,   1.0f,0.7373f,0.2784f,  // B2 46


		
		



	
	};
	unsigned int indices[] = {  // note that we start from 0!
		2,0,1,// second Triangle
		2,3,1,
		7,4,5,
		7,6,5,
		8,10,11,
		8,9,11,
		26,24,25,
		26,27,25,
		30,29,28,
		30,31,28,

		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);//reserva en mem

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);//dichaa localidad 0 guarda 3 elementos 
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));//apartir del 3er elemento
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Desenlazamos de memoria el VAO


	
	while (!glfwWindowShouldClose(window))
	{
		// Checa si un eveneto ha sido activado y manda a llamar al callback correspondiente
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Dibujar aquí
		OurShader.Use(); //llamo shaders
		glBindVertexArray(VAO);
		glPointSize(10);
		//glDrawArrays(GL_TRIANGLES, 0, 3);//trabaja con vertices, CUANTOS elementos voy a tomar, REPETIR B PARA CERRARLO
	    glDrawElements(GL_TRIANGLE_FAN,6, GL_UNSIGNED_INT, (GLvoid*)(0*sizeof(GLfloat))); //trabaja con indices EBO,1MODO DIBUjo,2elementos,3tipodato,4apartirde donde
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (GLvoid*)(12 * sizeof(GLfloat)));
		glDrawArrays(GL_TRIANGLES, 12, 3);
		glDrawArrays(GL_TRIANGLES, 15, 3);
		glDrawArrays(GL_TRIANGLES, 18, 3);
		glDrawArrays(GL_TRIANGLES, 21, 3);
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (GLvoid*)(18 * sizeof(GLfloat)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (GLvoid*)(24 * sizeof(GLfloat)));
		glDrawArrays(GL_TRIANGLES, 32, 3);
		glDrawArrays(GL_TRIANGLES, 35, 3);
		glDrawArrays(GL_TRIANGLES, 38, 3);
		glDrawArrays(GL_TRIANGLES, 41, 3);
		glDrawArrays(GL_TRIANGLES, 44, 3);
		

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}



// Reyes Herrera Rogelio Daniel