// Codul sursa este adaptat dupa OpenGLBook.com

#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h
#include "loadShaders.h"

#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//////////////////////////////////////

GLuint
	VaoId,
	VboId,
	ColorBufferId,
	ProgramId,
	codColLocation,
	myMatrixLocation;

glm::mat4
	myMatrix, resizeMatrix, matrRot, matrTransl1, matrTransl2,
	matTranslAnim1, matrScale;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;

float PI = 3.141592;

//	Variabile pentru proiectia ortogonala;
float xMin = -400, xMax = 500, yMin = -200, yMax = 400;
float i = 0.0, alpha = 0.0, step = 0.3, beta = 0.002, angle = 0;

void MoveRight(void)
{
	i = i + alpha;
	if (i > 450.0)			
		alpha = -step;	
	else if (i < -350.0)
		alpha = step;
	angle = angle - beta;	
	glutPostRedisplay();
}

void MoveLeft(void)
{
	i = i + alpha;
	if (i < -350.0)
		alpha = step;
	else if (i > 450.0)
		alpha = -step;
	angle = angle + beta;
	glutPostRedisplay();
}

void UseMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:	
		if (state == GLUT_DOWN)
			alpha = -step;
		glutIdleFunc(MoveLeft);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = step;
		glutIdleFunc(MoveRight);
		break;
	default:
		break;
	}
}

void CreateVBO(void)
{
	// varfurile 
	GLfloat Vertices[] = {
		-200.0f,  0.0f, 0.0f, 1.0f,
		0.0f,  0.0f, 0.0f, 1.0f,
		0.0f,  200.0f, 0.0f, 1.0f,
		-200.0f,  200.0f, 0.0f, 1.0f,
		
		100.0f, 0.0f, 0.0f, 1.0f,
		300.0f, 0.0f, 0.0f, 1.0f,
		200.0f, 100.0f, 0.0f, 1.0f,

		200.0f, 100.0f, 0.0f, 1.0f,
		300.0f, 0.0f, 0.0f, 1.0f,
		250.0f, 200.0f, 0.0f, 1.0f,

		// background
		-400.0f, -200.0f, 0.0f, 1.0f,
		500.0f, -200.0f, 0.0f, 1.0f,
		500.0f,  400.0f, 0.0f, 1.0f,
		-400.0f,  400.0f, 0.0f, 1.0f,

		-200.0f,  0.0f, 0.0f, 1.0f,
		0.0f,  0.0f, 0.0f, 1.0f,
		0.0f,  200.0f, 0.0f, 1.0f,
		-200.0f,  200.0f, 0.0f, 1.0f,

		-50.0f, -150.0f, 0.0f, 1.0f,
		50.0f, -150.0f, 0.0f, 1.0f,
		50.0f, -50.0f, 0.0f, 1.0f,
		-50.0f, -50.0f, 0.0f, 1.0f,
	};

	// culorile, ca atribute ale varfurilor
	GLfloat Colors[] = {
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,

	  // background colors
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,

		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
		1.0f, 0.5f, 0.2f, 1.0f,
	};

	// se creeaza un buffer nou
	glGenBuffers(1, &VboId);
	// este setat ca buffer curent
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// varfurile sunt "copiate" in bufferul curent
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	// se activeaza lucrul cu atribute; atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	// 
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	// un nou buffer, pentru culoare
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	// atributul 1 =  culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}
void DestroyVBO(void)
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

void CreateShaders(void)
{
	ProgramId = LoadShaders("example.vert", "example.frag");
	glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

void Initialize(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // culoarea de fond a ecranului
	CreateVBO();
	CreateShaders();

	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");

	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);

	matrRot = glm::rotate(glm::mat4(1.0f), PI/8, glm::vec3(0.0, 0.0, 1.0));
	//	Translatia 1: centrul patratului este translatat in origine;
	matrTransl1 = glm::translate(glm::mat4(1.0f), glm::vec3(-200.f, -100.f, 0.0));
	//	Translatia 2: inversa/opusa translatiei T1;
	matrTransl2 = glm::translate(glm::mat4(1.0f), glm::vec3(200.f, 100.f, 0.0));
}
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);       

	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_QUADS, 10, 4);

	codCol = 2;
	glUniform1i(codColLocation, codCol);

	glDrawArrays(GL_QUADS, 0, 4);
	glDrawArrays(GL_TRIANGLES, 4, 3);
	glDrawArrays(GL_TRIANGLES, 7, 3);

	matrRot = glm::rotate(glm::mat4(1.0f), PI/8, glm::vec3(0.0, 0.0, 1.0));
	myMatrix = resizeMatrix * matrTransl2 * matrRot * matrTransl1;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	codCol = 1;
	glUniform1i(codColLocation, codCol);

	glDrawArrays(GL_QUADS, 14, 4);

	glm::mat4 translateToOrigin = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 100.0f, 0.0f));
	matTranslAnim1 = glm::translate(glm::mat4(1.0f), glm::vec3(i, -150.0f, 0.0f));
	matrScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25, 0.25, 0.0));
	matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));

	// Translate back, rotate, then animate (move) the square
	myMatrix = resizeMatrix * matTranslAnim1 * matrScale * matrRot * translateToOrigin;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawArrays(GL_POLYGON, 18, 4);

	glutSwapBuffers();
	glFlush();
}
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei
	glutInitWindowSize(900, 600); //dimensiunile ferestrei
	glutCreateWindow("Grafica pe calculator - primul exemplu"); // titlul ferestrei
	
	glewInit(); // nu uitati de initializare glew; trebuie initializat inainte de a a initializa desenarea
	Initialize();
	glutDisplayFunc(RenderFunction);

	glutMouseFunc(UseMouse);
	glutCloseFunc(Cleanup);

	glutMainLoop();

	return 0;
}

