//
// ================================================
// | Grafica pe calculator                        |
// ===================================================
// | Curs VII - 07_02a_instanced_rendering.cpp       |
// ===================================================
// 
//	Program ce deseneaza un model format din mai multe cuburi, folosindu-se tehnicile MODERN OpenGL;
//	ELEMENTE DE NOUTATE:
//	 - randare instantiata - culorile si pozitia instantelor sunt determinate in programul principal;
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

//	Numarul de multiplicari ale cubului;
#define INSTANCE_COUNT 50

//  Identificatorii obiectelor de tip OpenGL; 
GLuint
	VaoId,
	VbPos,
	VbCol,
	VbModelMat,
	EboId,
	ColorBufferId,
	ProgramId,
	viewLocation,
	projLocation,
	codColLocation,
	codCol;
//	Valaorea lui pi;
const GLfloat PI = 3.141592;
//	Dimensiunile ferestrei de afisare;
GLfloat
	winWidth = 800, winHeight = 600;
//	Variabile catre matricele de transformare;
glm::mat4
	view, projection;

//	Elemente pentru matricea de vizualizare;
float refX = 0.0f, refY = 0.0f, refZ = 0.0f,
obsX, obsY, obsZ,
vX = 0.0f, vY = 0.0f, vZ = 1.0f;
//	Elemente pentru matricea de proiectie;
float width = 800, height = 600, dNear = 1, fovdeg = 90;

//	Elemente pentru deplasarea pe sfera;
float alpha = 0.0f, beta = 0.0f, dist = 200.0f,
		incrAlpha1 = 0.01, incrAlpha2 = 0.01, fov = 90.f * PI / 180;


void ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case '-':
		dist -= 5.0;	//	Apasarea tastelor `+` si `-` schimba pozitia observatorului (se departeaza / aproprie);
		break;
	case '+':
		dist += 5.0;
		break;
	}
	if (key == 27)
		exit(0);
}

void ProcessSpecialKeys(int key, int xx, int yy) {
	switch (key)				//	Procesarea tastelor 'LEFT', 'RIGHT', 'UP', 'DOWN';
	{							//	duce la deplasarea observatorului pe suprafata sferica in jurul cubului;
	case GLUT_KEY_LEFT:
		beta -= 0.01;
		break;
	case GLUT_KEY_RIGHT:
		beta += 0.01;
		break;
	case GLUT_KEY_UP:
		alpha += incrAlpha1;
		if (abs(alpha - PI / 2) < 0.05)
		{
			incrAlpha1 = 0.f;
		}
		else
		{
			incrAlpha1 = 0.01f;
		}
		break;
	case GLUT_KEY_DOWN:
		alpha -= incrAlpha2;
		if (abs(alpha + PI / 2) < 0.05)
		{
			incrAlpha2 = 0.f;
		}
		else
		{
			incrAlpha2 = 0.01f;
		}
		break;
	}
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("07_02a_Shader.vert", "07_02a_Shader.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//	COORDONATELE varfurilor; 
	GLfloat Vertices[] =
	{
		//	Varfurile VERZI din planul z = -50;  
		//	Coordonate;				
		-50.0f, -50.0f, -50.0f,  1.0f,
		 50.0f, -50.0f, -50.0f,  1.0f,
		 50.0f,  50.0f, -50.0f,  1.0f,
		-50.0f,  50.0f, -50.0f,  1.0f,
		//	Varfurile ROSII din planul z = +50;
		//	Coordonate;					Culori;			 
		 0.0f,   0.0f,  50.0f,  1.0f,
	};

	//	CULORILE instantelor;
	//	Culorile sunt generate in functie de indexul de instantiere - fiecare cub va avea o singura culoare;
	glm::vec4 Colors[INSTANCE_COUNT];
	for (int instID = 0; instID < INSTANCE_COUNT; instID++)
	{
		Colors[instID][0] = 0.35f + 0.30f * (sinf(instID / 4.0f + 2.0f) + 1.0f);
		Colors[instID][1] = 0.25f + 0.25f * (sinf(instID / 5.0f + 3.0f) + 1.0f);
		Colors[instID][2] = 0.25f + 0.35f * (sinf(instID / 6.0f + 4.0f) + 1.0f);
		Colors[instID][3] = 1.0f;
	}

	//  MATRICELE instantelor - se defineste tiparul de desenare al cuburilor prin ROTIREA si TRANSLATIA cubului initial (INSTANCED RENDERING);
	glm::mat4 MatModel[INSTANCE_COUNT];
	for (int instID = 0; instID < INSTANCE_COUNT; instID++)
	{
		MatModel[instID] =
			glm::translate(glm::mat4(1.0f), glm::vec3(90 * instID * cos(instID),	//	Deplasarea pe OX;
													  90 * instID * sin(instID),	//	Deplasarea pe OY; 
													  90 * instID * sin(instID) * cos(instID)))									//	Deplasarea pe OZ;
			* glm::rotate(glm::mat4(1.0f), (instID + 1) * PI / 10, glm::vec3(1, 0, 0))
			* glm::rotate(glm::mat4(1.0f),        instID * PI / 6, glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(1.0f),    3 * instID * PI / 2, glm::vec3(0, 0, 1));
	}

	//  Indicii pentru varfuri;
	GLuint Indices[] =
	{
		1, 0, 2,   2, 0, 3, //  Fata "de jos";
		1, 0, 4,   2, 4, 3, //	Lateral;
		4, 0, 3,   4, 2, 1, //	Lateral; 
	};

	//  Transmiterea datelor prin buffere;

	//  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	//  Se creeaza un buffer pentru COORDONATE;
	glGenBuffers(1, &VbPos);														//  Generarea bufferului si indexarea acestuia catre variabila VbPos;
	glBindBuffer(GL_ARRAY_BUFFER, VbPos);											//  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	//	Se activeaza lucrul cu atribute;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	//  Se creeaza un buffer pentru CULORI;
	glGenBuffers(1, &VbCol);
	glBindBuffer(GL_ARRAY_BUFFER, VbCol);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	//	Se activeaza lucrul cu atribute;
	//  Se asociaza atributul (1 = culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (GLvoid*)0);
	//	Rata cu care are loc distribuirea culorilor per instanta;
	glVertexAttribDivisor(1, 1); 

	//  Se creeaza un buffer pentru MATRICEA DE POZITIE (instantierea cuburilor);
	glGenBuffers(1, &VbModelMat);
	glBindBuffer(GL_ARRAY_BUFFER, VbModelMat);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MatModel), MatModel, GL_STATIC_DRAW);
	//	Se activeaza lucrul cu atribute pentru fiecare coloana din fiecare matrice de instantiere;
	//	Se incepe de la primul indice de atribut disponibil (2) si se creeaza pe rand cate unul pentru fiecare coloana (2+i, unde i = 0..3);
	for (int i = 0; i < 4; i++)
	{
		glEnableVertexAttribArray(2 + i);
		glVertexAttribPointer(2 + i,              //  Location;
			4, GL_FLOAT, GL_FALSE,                //  vec4;
			sizeof(glm::mat4),                    //  Stride;
			(void*)(sizeof(glm::vec4) * i));      //  Start offset;
		glVertexAttribDivisor(2 + i, 1);
	}

	//	Se creeaza un buffer pentru INDICI;
	glGenBuffers(1, &EboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

// Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}
void DestroyVBO(void)
{
	//  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru VARFURI (Coordonate, Culori, Instantiere), INDICI;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VbPos);
	glDeleteBuffers(1, &VbCol);
	glDeleteBuffers(1, &VbModelMat);
	glDeleteBuffers(1, &EboId);

	//  Eliberaea obiectelor de tip VAO;
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);		//  Culoarea de fond a ecranului;
	CreateVBO();								//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateShaders();							//  Initilizarea shaderelor;
	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	viewLocation = glGetUniformLocation(ProgramId, "viewMatrix");
	projLocation = glGetUniformLocation(ProgramId, "projectionMatrix");
	codColLocation = glGetUniformLocation(ProgramId, "codColShader");
}

//	Functia de desenare a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//  Se curata ecranul OpenGL pentru a fi desenat noul continut (bufferul de culoare & adancime);
	glEnable(GL_DEPTH_TEST);

	//	CreateVBO(); //	 Decomentati acest rand daca este cazul;
	glBindVertexArray(VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, VbPos);
	glBindBuffer(GL_ARRAY_BUFFER, VbCol);
	glBindBuffer(GL_ARRAY_BUFFER, VbModelMat);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);

	//	Matricea de vizualizare;
	//	Pozitia observatorului - se deplaseaza pe sfera;
	obsX = refX + dist * cos(alpha) * cos(beta);
	obsY = refY + dist * cos(alpha) * sin(beta);
	obsZ = refZ + dist * sin(alpha);

	//	Matricea de vizualizare;
	glm::vec3 obs = glm::vec3(obsX, obsY, obsZ);		//	Pozitia observatorului;	
	glm::vec3 pctRef = glm::vec3(refX, refY, refZ); 	//	Pozitia punctului de referinta;
	glm::vec3 vert = glm::vec3(vX, vY, vZ);				//	Verticala din planul de vizualizare; 
	view = glm::lookAt(obs, pctRef, vert);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//	Realizarea proiectiei;
	projection = glm::infinitePerspective(GLfloat(fov), GLfloat(width) / GLfloat(height), dNear);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

	//	Desenarea fetelor;
	codCol = 0;															//  Culoarea;
	glUniform1i(codColLocation, codCol);								//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	//	Functia glDrawElementsInstanced primeste 4 argumente:
	//	 - arg1 = modul de desenare;
	//	 - arg2 = numarul de varfuri;
	//	 - arg3 = tipul de date al indicilor;
	//	 - arg4 = pointer spre indici (EBO): pozitia de start a indicilor;
	//	 - arg5 = numarul de instante; 
	glDrawElementsInstanced(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0, INSTANCE_COUNT);
	
	//  Desenarea muchiilor;
	//codCol = 1;															//	Se schimba culoarea;
	//glUniform1i(codColLocation, codCol);
	//glLineWidth(2.5);
	//glDrawElementsInstanced(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(36 * sizeof(GLuint)), INSTANCE_COUNT);
	//glDrawElementsInstanced(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(40 * sizeof(GLuint)), INSTANCE_COUNT);
	//glDrawElementsInstanced(GL_LINES,     8, GL_UNSIGNED_INT, (void*)(44 * sizeof(GLuint)), INSTANCE_COUNT);

	glutSwapBuffers();	//	Inlocuieste imaginea deseneata in fereastra cu cea randata; 
	glFlush();			//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);		//	Se folosesc 2 buffere pentru desen (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB + 1 buffer pentru adancime;
	glutInitWindowSize(winWidth, winHeight);						//  Dimensiunea ferestrei;
	glutInitWindowPosition(100, 100);								//  Pozitia initiala a ferestrei;
	glutCreateWindow("Instanced rendering - OpenGL <<nou>>");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();

	Initialize();							//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);		//  Desenarea scenei in fereastra;
	glutIdleFunc(RenderFunction);			//	Asigura rularea continua a randarii;
	glutKeyboardFunc(ProcessNormalKeys);	//	Functii ce proceseaza inputul de la tastatura utilizatorului;
	glutSpecialFunc(ProcessSpecialKeys);
	glutCloseFunc(Cleanup);					//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}