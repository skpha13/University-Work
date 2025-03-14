//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul IX - 09_03v_Shader.vert |
// ======================================
// 
//  Shaderul de varfuri; 

#version 330 core

//  Variabile de intrare (dinspre programul principal);
layout(location=0) in vec4 in_Position;
layout(location=1) in vec3 in_Color;
layout(location=2) in vec3 in_Normal;
 
//  Variabile de iesire;
out vec4 ex_Color;

//  Variabile uniforme;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main(void)
  {
    vec3 objectColor=in_Color;
    //  Aplicare transformari si determinare pozitii;
    gl_Position = projection*view*in_Position;
    vec3 FragPos = vec3(gl_Position); 
    vec3 Normal=vec3(projection*view*vec4(in_Normal,0.0)); 
    vec3 inLightPos= vec3(projection*view* vec4(lightPos, 1.0f));
    vec3 inViewPos=vec3(projection*view* vec4(viewPos, 1.0f));

    //  Ambient;
    float ambientStrength = 0.5f;
    vec3 ambient_light = ambientStrength * lightColor;      //  ambient_light=ambientStrength*lightColor; 
    vec3 ambient_term= ambient_light * objectColor;         //  ambient_material=objectColor;
  	
    //  Diffuse;
    vec3 norm = normalize(Normal);                              // vectorul s; 
    vec3 lightDir = normalize(inLightPos - FragPos);            // vectorul L;
    float diff = max(dot(norm, lightDir), 0.0); // 
    vec3 diffuse_light = lightColor;                            // diffuse_light=lightColor;
    vec3 diffuse_term = diff * diffuse_light * objectColor;     // diffuse_material=objectColor;

    //  Specular;
    float specularStrength = 0.5f;
    float shininess = 10.0f;
    vec3 viewDir = normalize(inViewPos - FragPos);              // versorul catre observator;
    vec3 reflectDir = normalize(reflect(-lightDir, norm));      // versorul vectorului R; 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); 
    vec3 specular_light = specularStrength  * lightColor;       // specular_light=specularStrength  * lightColor;
    vec3 specular_term = spec * specular_light * objectColor;   // specular_material=objectColor;
       
    //  Culoarea finala; 
    vec3 result = (ambient_term + diffuse_term + specular_term);  
    // vec3 result=in_Color;
	ex_Color = vec4(result, 1.0f);
   }  
