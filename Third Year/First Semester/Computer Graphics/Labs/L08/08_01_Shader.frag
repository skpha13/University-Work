//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laborator VIII - 08_01_Shader.frag       |
// ===========================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330

float winWidth = 1400; // Latimea ferestrei
float winHeight = 600;

//	Variabile de intrare (dinspre Shader.vert);
in vec4 gl_FragCoord; // Variabila care indica pozitia fragmentului (prin raportare la fereastra de vizualizare)
in vec3 ex_Color; 

//	Variabile de iesire	(spre programul principal);
out vec3 out_Color;

//  Variabile uniforme;
uniform int codCol;
uniform float radius;
uniform float centerY;

void main(void)
{
    float yCoord = abs(gl_FragCoord.y - centerY - winHeight / 2.0) / radius;
    yCoord = clamp(yCoord, 0.0, 1.0);

    switch (codCol)
    {
        case 1: 
            out_Color=vec3(0.0, 0.0, 0.0); 
            break;
        case 2:
            out_Color=vec3(gl_FragCoord.x/winWidth, 0.0, 0.0); // Culoarea este stabilita in functie de pozitia fragmentului in fereastra 
            break;
        case 3:
            out_Color = mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), yCoord);
            break;
        case 4:
            out_Color = mix(vec3(0.0, 0.0, 1.0), vec3(0.0, 1.0, 1.0), yCoord);
            break;
        case 5:
            out_Color = mix(vec3(1.0, 1.0, 0.0), vec3(1.0, 0.0, 1.0), yCoord);
            break;
        default: 
            out_Color=ex_Color;
    }
}