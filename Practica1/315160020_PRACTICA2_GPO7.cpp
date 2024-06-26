#include<iostream>
#include<stdio.h>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int opciones();
int salir();



// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2", nullptr, nullptr);

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
	Shader ourShader("Shaders/core.vs", "Shader/core.frag");

	GLfloat vertices[] = {
	   -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
	  	0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
	  	0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
	  	0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
	  	-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
	  	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
	  	
	      -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
	  	 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	  	 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	  	 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	      -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	      -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	  	
	  	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	  	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	  	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	  	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	  	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	  	 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
        
	  	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
	  	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	  	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	  	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	  	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
	  	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
	  	
	  	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
	  	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
	  	0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
	  	0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
	  	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
	  	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
	  	
	  	-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	  	0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
	  	0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
	  	0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
	  	-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
	  	-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1); //matriz unitaria

	


	int x;
	do {
		switch (opciones()) {
		case 1:
			
			projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);//FOV, Radio de aspecto,znear,zfar
			while (!glfwWindowShouldClose(window))
			{
				// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
				glfwPollEvents();

				if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
					break;

				// Render
				// Clear the colorbuffer
				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// Draw our first triangle, despues del shader
				ourShader.Use();
				glm::mat4 model = glm::mat4(1);
				glm::mat4 view = glm::mat4(1);

				view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
				

				GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
				GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
				GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

				glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
				glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


				glBindVertexArray(VAO);
				//model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
				//model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));



				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(3.0f, -3.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(0.0f, 6.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);







				// Swap the screen buffers
				glfwSwapBuffers(window);
				

				

			}
			x = 1;
			break;
		case 2:
			projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
			while (!glfwWindowShouldClose(window))
			{
				// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
				glfwPollEvents();

				if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
					break;

				// Render
				// Clear the colorbuffer
				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// Draw our first triangle, despues del shader
				ourShader.Use();
				glm::mat4 model = glm::mat4(1);
				glm::mat4 view = glm::mat4(1);

				//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
				view = glm::translate(view, glm::vec3(screenWidth / 2, screenHeight / 2, -70.0f)); // Usar con la proyección en orto

				GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
				GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
				GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

				glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
				glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


				glBindVertexArray(VAO);
				model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));
				//model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));



				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(3.0f, -3.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(0.0f, 6.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);







				// Swap the screen buffers
				glfwSwapBuffers(window);




			}
			x = 1;
			break;
		case 3:
			x = 0;
			break;
		default:
			printf("Opcion invalida\nRegresando al menu...\n");
			system("pause");
			system("cls");
			x = 1;
		}

	} while (x == 1);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	salir();
	return 0;



	


	//oeden de transformaciones importa
	//Creación de proyecciones
	
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania, lado inf izq
	

	return EXIT_SUCCESS;

  

}




int opciones() {
	int opc = 0;
	printf("\nQue deseas ver?\n");
	printf("1.-Vista en perspectiva\n2.-Vista ortogonal\n");
	printf("3.-Salir\n");
	scanf_s("%i", &opc);
	system("cls");
	return opc;
}


int salir() {
	int rsp;
	printf("\n\t\t\t\t\tSaliendo.....\n");
	system("pause");
	system("cls");
	printf("\n\t\t\t\t\tVuelva pronto <3\n");
	rsp = 0;
	return rsp;
}