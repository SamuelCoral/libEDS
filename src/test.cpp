#include "EDS_color.h"
#include "EDS_bmp.h"
#include <cstdlib>
#include <iostream>
#include <cmath>


int main(int argc, char* argv[]) {

	EDS_Imagen* img = EDS_CrearImagenVacia(799, 600, 4);

	/*
	int i, j;
	for(i = 0; i < img->alto; i++) for(j = 0; j < img->alto; j++)
		EDS_DibujarPixel(img, j, i, EDS_COLOR_RGB(0xFF, 0, 0));
	for(i = 0; i < img->alto; i++)
		EDS_DibujarPixel(img, i, i, EDS_COLOR_RGB(0, 0xFF, 0));

	for(i = 0; i < img->ancho; i++) {

		EDS_DibujarPixel(img, i, 0, EDS_COLOR_RGB(0xFF, 0, 0xFF));
		EDS_DibujarPixel(img, i, img->alto - 1, EDS_COLOR_RGB(0xFF, 0, 0xFF));
	}
	for(i = 0; i < img->alto; i++) {

		EDS_DibujarPixel(img, 0, i, EDS_COLOR_RGB(0xFF, 0, 0xFF));
		EDS_DibujarPixel(img, img->ancho - 1, i, EDS_COLOR_RGB(0xFF, 0, 0xFF));
	}

	for(i = 100; i < img->ancho - 100; i++) for(j = 100; j < img->alto - 100; j++)
		EDS_DibujarPixel(img, i, j, EDS_COLOR_RGBA(0xFF, 0xFF, 0xFF, 0x7F));
	*/

	int i, j;
	img->paleta[1].v = EDS_COLOR_RGB(0xFF, 0, 0);
	img->paleta[2].v = EDS_COLOR_RGB(0, 0xFF, 0);
	img->paleta[3].v = EDS_COLOR_RGB(0, 0, 0xFF);
	for(i = 0; i < img->alto; i++) for(j = 0; j < img->alto; j++)
		EDS_DibujarPixel(img, j, i, 1);
	for(i = 0; i < img->alto; i++)
		EDS_DibujarPixel(img, i, i, 2);

	for(i = 0; i < img->ancho; i++) {

		EDS_DibujarPixel(img, i, 0, 3);
		EDS_DibujarPixel(img, i, img->alto - 1, 3);
	}
	for(i = 0; i < img->alto; i++) {

		EDS_DibujarPixel(img, 0, i, 3);
		EDS_DibujarPixel(img, img->ancho - 1, i, 3);
	}

	/*
	int i, j;
	double dh = 2 * M_PI / img->ancho, h = 0;
	EDS_Color pixel;
	for(i = 0; i < img->ancho; i++, h += dh) for(j = 0; j < img->alto; j++) {

		pixel = EDS_ColorHSLRGB(h, 1, 0.5);
		pixel.c.a = log1p(j * (M_E - 1) / img->alto) * 0xFF;
		EDS_DibujarPixel(img, i, j, pixel.v);
	}
	*/

	EDS_GuardarBMP(img, "test.bmp", EDS_BMP_B_COMP_RLE, NULL);
	EDS_DestruirImagen(img);

	img = NULL;

	return 0;
}

