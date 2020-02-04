// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h> 
#include <stdlib.h> 
#define GLEW_STATIC 
 
#include"GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream> 

using namespace std;

GLFWwindow* window;

float posXTriangulo = 0.0f, posYTriangulo = 0.0f;
double tiempoActual, tiempoAnterior;
double velTriangulo = 0.5;

float angulo = 0.0f;
float mov = 0.0f;

float componenteX;
float componenteY;

void actualizar() {
	
	
	tiempoActual = glfwGetTime();
	double tiempoDiferencial = tiempoActual - tiempoAnterior;

	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		
		angulo -= 90.00f * tiempoDiferencial;		
	}
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		//posYTriangulo += velTriangulo * tiempoDiferencial;

		componenteX = (cos((angulo + 90) * 3.14159 / 180.0)) * (velTriangulo * tiempoDiferencial);
		componenteY = sin((angulo + 90) * 3.14159 / 180.0) * (velTriangulo * tiempoDiferencial);

		posXTriangulo += componenteX;
		posYTriangulo += componenteY;
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		
		angulo += 90.00f * tiempoDiferencial;		
	}
	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		posYTriangulo -= velTriangulo * tiempoDiferencial;
	}
	tiempoAnterior = tiempoActual;

}


void dibujarTriangulo() {
	glPushMatrix();

	glTranslatef(posXTriangulo,posYTriangulo,0.0f);	
	glRotatef(angulo, 0.0f, 0.0f, 1.0);
	glScalef(0.5f, 0.5f, 0.0f);

	glBegin(GL_TRIANGLES);
    glColor3f(0.2f,0.6f,0.1f);

	glVertex3f(0.0f,0.15f,0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f); 
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();
	glPopMatrix();

}

void dibujar() {
	dibujarTriangulo();
}

int main()
{
	//Declarar una ventana 
	


	//Si no se pudo inicializar GLFW  //Terminamos Ejecución 
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(600, 600, "Ventana Cookie", NULL, NULL);
	
	//Si no se pudo crear la ventana
	//Terminamos ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Si se pudo inicializar GLFW
	//Inicializams la ventana


	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);
	//UsarFuncionesdeOpengl
	//Una vez establecido el contexto. Se activan las funciones "modernas" (gpu)
	glewExperimental = true;
	
	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte  *versionGL = glGetString(GL_VERSION);

	cout << "Version OpenGl: " << versionGL;
	//Ventana y funcion
	//Establecemos que con cada evento del teclado se llama a la funcion teclado_callbak
	//glfwSetKeyCallback(window, teclado_callback);

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;

	//Clilo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {

		//Establecer región de dibujo 
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		glClearColor(3, 0.8, 0.4, 1);
		//Borrar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		actualizar();
		dibujar();
		//Se comunica con los dispositivos de entrada
		glfwPollEvents();
		// Actualizar los valores y dibujar 
		glfwSwapBuffers(window);
	}
	//Despues del ciclo de dibujo Eliminamos ventana y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}