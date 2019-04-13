#include "EDS/EDS_color.h"
#include "EDS/EDS_bmp.h"
#include "EDS/EDS_dibujo.h"
#include <cstdlib>
#include <iostream>
#include <cmath>


int main(int argc, char* argv[]) {

	EDS_Imagen* img = EDS_CrearImagenVacia(799, 600, 32);

	EDS_LimpiarDibujo(img, EDS_COLOR_RGBA(0, 0xFF, 0, 0x7F));
	EDS_DibujarRectanguloSolido(img, 0, 0, img->alto, img->alto, EDS_COLOR_RGB(0xFF, 0, 0));
	EDS_DibujarLinea(img, 0, 0, img->alto, img->alto, EDS_COLOR_RGB(0, 0xFF, 0));
	EDS_DibujarRectangulo(img, 0, 0, img->ancho - 1, img->alto - 1, EDS_COLOR_RGB(0xFF, 0, 0xFF));
	EDS_DibujarRectanguloSolido(img, 100, 100, img->ancho - 100, img->alto - 100, EDS_COLOR_RGBA(0xFF, 0xFF, 0xFF, 0x7F));

	/*
	img->paleta[1].v = EDS_COLOR_RGB(0xFF, 0, 0);
	img->paleta[2].v = EDS_COLOR_RGB(0, 0xFF, 0);
	img->paleta[3].v = EDS_COLOR_RGB(0, 0, 0xFF);
	EDS_DibujarRectanguloSolido(img, 1, 1, img->alto, img->alto, 2);
	EDS_DibujarLinea(img, 0, 0, img->alto, img->alto, 3);
	EDS_DibujarRectangulo(img, 0, 0, img->ancho - 1, img->alto - 1, 1);
	
	int i, j;
	for(i = 50; i < 200; i++) for(j = 100; j < 200; j++)
		EDS_DibujarPixel(img, i, j, 5 + (i % 2) + 2 * (j % 2));
	*/

	/*
	double dh = 2 * M_PI / img->ancho, h = 0;
	EDS_Color pixel;
	for(i = 0; i < img->ancho; i++, h += dh) for(j = 0; j < img->alto; j++) {

		pixel = EDS_ColorHSLRGB(h, 1, 0.5);
		pixel.c.a = log1p(j * (M_E - 1) / img->alto) * 0xFF;
		EDS_DibujarPixel(img, i, j, pixel.v);
	}
	*/

	EDS_MascarasBits mascaras = EDS_ConstruirMascaras(8, 8, 8, 8);
	EDS_GuardarBMP(img, "test.bmp", EDS_BMP_B_COMP_MASCARAS | EDS_BMP_B_FMT_32BPP | EDS_BMP_B_VER_4, &mascaras);
	EDS_DestruirImagen(img);

	img = NULL;

	return 0;
}

