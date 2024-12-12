//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul VIII - 08_03_Shader.vert|
// ======================================
// 
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei; 
//

#version 330 core

//  Variabile de intrare (dinspre programul principal);
layout(location=0) in vec4 in_Position;                 //  Se preia din buffer de pe prima pozitie (0) atributul care contine coordonatele;
layout(location=1) in vec3 in_Color;                    //  Se preia din buffer de pe a doua pozitie (1) atributul care contine culoarea;
layout(location=2) in vec3 in_Normal;

//  Variabile de iesire;
out vec3 FragPos;
out vec3 Normal;
out vec3 inLightPos;
out vec3 inViewPos;
out vec4 ex_Color; 

//  Variabile uniforme;
uniform mat4 myMatrix;
uniform mat4 viewShader;
uniform mat4 projectionShader;

vec3 viewPos = vec3(3, 2, 1);

void main(void)
{
    gl_Position = projectionShader * viewShader * myMatrix * in_Position;
    FragPos = vec3(gl_Position);
    Normal=vec3(projectionShader * viewShader * vec4(in_Normal,0.0));
    inLightPos= vec3(projectionShader * viewShader * myMatrix * vec4(2.0f, 4.0f, 0.0f, 1.0f));
    inViewPos=vec3(projectionShader * viewShader * vec4(viewPos, 1.0f));
    ex_Color= vec4(in_Color, 1.0);
} 