//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Laboratorul II - 02_01_Shader.frag |
// ======================================
// 
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330 core

in vec4 ex_Color;
out vec4 out_Color;

//	Variabilele uniforme;
uniform int codColShader;
uniform vec3 randomColor;

//	Actualizeaza culoarea in functie de codColShader;
void main(void)
{
	switch (codColShader) {
		case 0:
			out_Color = vec4 (0.0, 0.0, 0.0, 1.0);
			break;
		case 1:
			out_Color = vec4 (1.0, 0.0, 0.0, 1.0);
			break;
		case 2:
			out_Color = vec4 (randomColor[0], randomColor[1], randomColor[2], 1.0);
			break;
		default:
			out_Color = ex_Color;
			break;
	}
}
 