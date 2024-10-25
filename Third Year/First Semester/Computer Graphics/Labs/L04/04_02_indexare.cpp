//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IV - 04_02_indexare.cpp |
// ======================================
// 
//	Program ce deseneaza un patrat, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	 - folosirea indexarii varfurilor: elemente asociate (matrice, buffer);
//	 - desenarea se face folosind functia glDrawElements();
//
//
// 
//	Biblioteci

#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>
#include "SOIL.h"			//	Biblioteca pentru texturare;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId1,
	VaoId2,
	VboId2,
	EboId2,
	ColorBufferId1,
	ColorBufferId2,
	VboId1,
	EboId1,
	ProgramId,
	myMatrixLocation,
	texture,
	VaoId3,
	VboId3,
	EboId3;
//	Dimensiunile ferestrei de afisare;
GLfloat
	winWidth = 800, winHeight = 600;
//	Variabile catre matricile de transformare;
glm::mat4
	myMatrix, resizeMatrix;
//	Variabile pentru proiectia ortogonala;
float xMin = -80.f, xMax = 80.f, yMin = -60.f, yMax = 60.f;

//	Functia de incarcare a texturilor in program;
void LoadTexture(const char* texturePath)
{
	// Generarea unui obiect textura si legarea acestuia;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//	Desfasurarea imaginii pe orizontala/verticala in functie de parametrii de texturare;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Modul in care structura de texeli este aplicata pe cea de pixeli;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Incarcarea texturii si transferul datelor in obiectul textura; 
	int width, height;
	unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Eliberarea resurselor
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("04_02_Shader.vert", "04_02_Shader.frag");
	glUseProgram(ProgramId);
}

std::vector<GLfloat> getPointsOnCircle(float centerX = 0, float centerY = 0, float radius = 1, int n = 8) {
	const double pi = 3.14159265358979323846;
	std::vector<GLfloat> arr(4*n, 0);

	for (int k = 0; k < 4*n; k += 4) {
		float x = radius * cos(2 * pi * (k / 4) / n) + centerX;
		float y = radius * sin(2 * pi * (k / 4) / n) + centerY;

		arr[k] = x;
		arr[k + 1] = y;
		arr[k + 2] = 0;
		arr[k + 3] = 1;
	}

	return arr;
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVAO1(void)
{
	//  Coordonatele varfurilor;
	static const GLfloat Vertices1[] =
	{
		15.0f, -5.0f,  0.0f,  1.0f,
		25.0f, -5.0f,  0.0f,  1.0f,
		25.0f,  5.0f,  0.0f,  1.0f,
		15.0f,  5.0f,  0.0f,  1.0f,

		35.0f, -5.0f, 0.0f, 1.0f,
		35.0f, 5.0f, 0.0f, 1.0f,

		45.0f, -5.0f, 0.0f, 1.0f,
		45.0f, 5.0f, 0.0f, 1.0f,

		55.0f, -5.0f, 0.0f, 1.0f,
		55.0f, 5.0f, 0.0f, 1.0f,

		65.0f, -5.0f, 0.0f, 1.0f,
		65.0f, 5.0f, 0.0f, 1.0f,

		-5.0f, 5.0f, 0.0f, 1.0f,
		-5.0f, -5.0f, 0.0f, 1.0f,
		5.0f, -5.0f, 0.0f, 1.0f,
		5.0f, 5.0f, 0.0f, 1.0f
	};

	//	Culorile ca atribute ale varfurilor;
	static const GLfloat Colors1[] =
	{
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
	};
	
	//	Indicii care determina ordinea de parcurgere a varfurilor;
	static const GLuint Indices1[] =
	{
		0, 1, 2, 3, 0, 2,
		1, 4, 5, 2, 1, 5,
		4, 6, 7, 5, 4, 7,
		6, 8, 9, 7, 6, 9,
		8, 10, 11, 9, 8, 11,

		12, 13, 14, 15,
		16, 17, 18, 19
	};

	//  Transmiterea datelor prin buffere;

	//  Se creeaza / se leaga primul VAO (Vertex Array Object);
	glGenVertexArrays(1, &VaoId1);         //  Generarea VAO si indexarea acestuia catre variabila VaoId1;
	glBindVertexArray(VaoId1);

	// Transmiterea datelor prin buffere
	//  Se creeaza un buffer pentru VARFURI;
	glGenBuffers(1, &VboId1);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId1;
	glBindBuffer(GL_ARRAY_BUFFER, VboId1);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices1), Vertices1, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//  Se creeaza un buffer pentru CULOARE;
	glGenBuffers(2, &ColorBufferId1);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors1), Colors1, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(3, &EboId1);														//  Generarea bufferului si indexarea acestuia catre variabila EboId1;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices1), Indices1, GL_STATIC_DRAW);
}

void CreateVAO2(void) {
	std::vector<GLfloat> biggerCircle = getPointsOnCircle(-40, 30, 20, 8), smallerCircle = getPointsOnCircle(-40, 30, 10, 8);
	std::vector<GLfloat> Vertices2;
	int n = 64, k=0;

	Vertices2.insert(Vertices2.end(), biggerCircle.begin(), biggerCircle.end());
	Vertices2.insert(Vertices2.end(), smallerCircle.begin(), smallerCircle.end());

	static const GLfloat Colors2[] =
	{
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
	};

	static const GLuint Index2[] =
	{
		0, 1, 
		1, 2, 
		2, 3,
		3, 4,
		4, 5,
		5, 6,
		6, 7,
		7, 0,
		7, 8, 
		8, 9, 
		9, 10,
		10, 11, 
		11, 12,
		12, 13,
		13, 14,
		14, 15,
		15, 8,

		0, 8,
		1, 9,
		2, 10,
		3, 11,
		4, 12,
		5, 13,
		6, 14,
		7, 15,

		0, 10,
		1, 11,
		2, 12,
		3, 13,
		4, 14,
		5, 15,
		6, 8
	};

	glGenVertexArrays(1, &VaoId2);
	glBindVertexArray(VaoId2);

	glGenBuffers(1, &VboId2);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId2;
	glBindBuffer(GL_ARRAY_BUFFER, VboId2);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, 4*Vertices2.size(), &Vertices2[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(2, &ColorBufferId2);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors2), Colors2, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(3, &EboId2);														//  Generarea bufferului si indexarea acestuia catre variabila EboId2;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index2), Index2, GL_STATIC_DRAW);
}

void CreateVAO3(void)
{
	//	Atributele varfurilor -  COORDONATE, CULORI, COORDONATE DE TEXTURARE;
	GLfloat Vertices[] = {
		//	Coordonate;					Culori;				Coordonate de texturare;
		  -5.0f, -5.0f,  0.0f,  1.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// Stanga jos;
		   5.0f, -5.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // Dreapta jos;
		   5.0f,  5.0f,  0.0f,  1.0f,   1.0f, 1.0f, 0.0f,	1.0f, 1.0f,	// Dreapta sus;
		  -5.0f,  5.0f,  0.0f,  1.0f,   0.0f, 1.0f, 1.0f,	0.0f, 1.0f  // Stanga sus;
	};

	//	Indicii care determina ordinea de parcurgere a varfurilor;
	GLuint Indices[] = {
	  0, 1, 2,  //	Primul triunghi;
	  0, 2, 3	//  Al doilea triunghi;
	};

	//  Transmiterea datelor prin buffere;

	//  Se creeaza / se leaga un VAO (Vertex Array Object);
	glGenVertexArrays(1, &VaoId3);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId3);

	//  Se creeaza un buffer pentru VARFURI - COORDONATE, CULORI si TEXTURARE;
	glGenBuffers(1, &VboId3);													//  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId3);										//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId3);														//  Generarea bufferului si indexarea acestuia catre variabila EboId;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId3);									//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	//	Se activeaza lucrul cu atribute;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	//  Se asociaza atributul (2 =  texturare) pentru shader;
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
	//  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru VARFURI(Coordonate + Culori), INDICI;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId1);
	glDeleteBuffers(1, &VboId2);
	glDeleteBuffers(1, &VboId3);
	glDeleteBuffers(1, &EboId1);
	glDeleteBuffers(1, &EboId2);
	glDeleteBuffers(1, &EboId3);
	glDeleteBuffers(1, &ColorBufferId1);
	glDeleteBuffers(1, &ColorBufferId2);

	//  Eliberaea obiectelor de tip VAO;
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId1);
	glDeleteVertexArrays(1, &VaoId2);
	glDeleteVertexArrays(1, &VaoId3);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);		//  Culoarea de fond a ecranului;
	CreateVAO1();								//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateVAO2();
	CreateVAO3();
	CreateShaders();							//  Initilizarea shaderelor;

	LoadTexture("text_smiley_face.png");
	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	//	Dreptunghiul "decupat"; 
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	
	glLineWidth(4.0f);
	//	Transmiterea variabilei uniforme pentru MATRICEA DE TRANSFORMARE spre shadere;
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	//	Desenarea primitivelor
	//	Functia glDrawElements primeste 4 argumente:
	//	 - arg1 = modul de desenare;
	//	 - arg2 = numarul de varfuri;
	//	 - arg3 = tipul de date al indicilor;
	//	 - arg4 = pointer spre indici (EBO): pozitia de start a indicilor;
	glBindVertexArray(VaoId1);
	glDrawElements(GL_LINE_STRIP, 30, GL_UNSIGNED_INT, (void*)(0));



	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * 30));

	myMatrix = resizeMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(30, 30, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(2.0, 0.5, 0.0));
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * 30));


	glBindVertexArray(VaoId3);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	//	Transmiterea variabilei uniforme pentru texturare spre shaderul de fragmente;
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);
	glUniform1i(glGetUniformLocation(ProgramId, "hasTexture"), 1);

	myMatrix = resizeMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(2.0, 0.5, 0.0)) * glm::translate(glm::mat4(1.0f), glm::vec3(30, 30, 0.0));
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0));

	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(ProgramId, "hasTexture"), 0);


	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	glLineWidth(1.0f);
	glBindVertexArray(VaoId2);
	glDrawElements(GL_LINES, 64, GL_UNSIGNED_INT, (void*)(0));
	

	glFlush();								//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);					//	Modul de afisare al ferestrei, se foloseste un singur buffer de afisare si culori RGB;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Indexarea varfurilor - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();


	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}


