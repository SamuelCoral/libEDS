#include <iostream>
#include <cmath>
#include <complex>
#include "EDS/EDS_dibujo.h"
#include "EDS/EDS_color.h"
#include "EDS/EDS_bmp.h"



void dibujar_flechita(
	EDS_Imagen* imagen,
	int longitud,
	const std::complex<double>& entrada,
	std::complex<double> salida
) {
	uint8_t color = 1 + (int)round(std::abs(salida)) % 255;
	std::complex<double> rotacion = std::exp(std::complex<double>(0, -std::arg(salida)));
	std::complex<double> b1 = longitud * 0.5 * std::exp(std::complex<double>(0, M_PI_2 + M_PI_4));
	std::complex<double> b2 = std::conj(b1);
	salida = rotacion * (double)longitud;
	b1 *= rotacion;
	b2 *= rotacion;
	b1 += salida + entrada;
	b2 += salida + entrada;
	salida += entrada;
	EDS_DibujarLinea(imagen, entrada.real(), entrada.imag(), salida.real(), salida.imag(), color);
	EDS_DibujarLinea(imagen, salida.real(), salida.imag(), b1.real(), b1.imag(), color);
	EDS_DibujarLinea(imagen, salida.real(), salida.imag(), b2.real(), b2.imag(), color);
}


std::complex<double> funcion_compleja(const std::complex<double>& entrada) {

	std::complex<double> salida = entrada;
	return salida;
}


int main(int argc, char*argv[]) {

	EDS_Imagen* img = EDS_CrearImagenVacia(1920, 1080, 8);
	for(int i = 1; i < 0x100; i++) img->paleta[i] = EDS_ColorHSLRGB(i * 0.5 / M_PI, 1, 0.5);

	double escala = 0.05;
	std::complex<double> dim_2 = std::complex<double>(img->ancho / 2, img->alto / 2);
	for(int i = 0; i < img->ancho; i += 50) for(int j = 0; j < img->alto; j += 50)
		dibujar_flechita(img, 40, std::complex<double>(i, j), funcion_compleja(escala * std::complex<double>(
			i - dim_2.real(), -j + dim_2.imag()
		)));

	EDS_GuardarBMP(img, "vector_field.bmp", EDS_BMP_B_COMP_RLE, NULL);

	return 0;
}

