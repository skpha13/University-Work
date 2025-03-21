//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | Cursul VI - 06_01_Shader.frag       |
// ======================================
//
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
//

#version 330	//  Versiunea GLSL;

//	Variabile de intrare (dinspre Shader.vert);
in vec4 ex_Color;

//	Variabile de iesire	(spre programul principal);
out vec4 out_Color;		//	Culoarea actualizata;

//	Actualizeaza culoarea in functie de codCol;
void main(void)
  {
	out_Color=ex_Color;
  }
 