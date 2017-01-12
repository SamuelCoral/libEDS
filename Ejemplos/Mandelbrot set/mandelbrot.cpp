#include <complex>
#include <ctime>
#include <iostream>
#include <EDS/dibujo_eds.hpp>

using namespace std;
using namespace eds;


void crearPaletaEstandar(uint32_t numColores, dibujo_eds& dibujo) {
	
	int c, i;
	dibujo.paleta()[numColores] = 0;
	for(c = i = numColores * 0 / 6; c < numColores * 1 / 6; c++) dibujo.paleta()[c] = RGB(255, (c - i) * 6 * 256 / numColores, 0);
	for(c = i = numColores * 1 / 6; c < numColores * 2 / 6; c++) dibujo.paleta()[c] = RGB(255 - (c - i) * 6 * 256 / numColores, 255, 0);
	for(c = i = numColores * 2 / 6; c < numColores * 3 / 6; c++) dibujo.paleta()[c] = RGB(0, 255, (c - i) * 6 * 256 / numColores);
	for(c = i = numColores * 3 / 6; c < numColores * 4 / 6; c++) dibujo.paleta()[c] = RGB(0, 255 - (c - i) * 6 * 256 / numColores, 255);
	for(c = i = numColores * 4 / 6; c < numColores * 5 / 6; c++) dibujo.paleta()[c] = RGB((c - i) * 6 * 256 / numColores, 0, 255);
	for(c = i = numColores * 5 / 6; c < numColores * 6 / 6; c++) dibujo.paleta()[c] = RGB(255, 0, 255 - (c - i) * 6 * 256 / numColores);
}

COLOR colorMandelbrot(complex<double> valor, uint32_t iteraciones, uint32_t colores_paleta) {
	
	complex<double> inicial = valor;
	
	uint32_t c;
	for(c = 0; c < iteraciones; c++) {
		
		valor *= valor;
		valor += inicial;
		if(sqrt(valor.real() * valor.real() + valor.imag() * valor.imag()) > 2) return c % colores_paleta;
	}
	
	return colores_paleta;
}


int main(int agrc, char* args[]) {
	
	clock_t tiempo = clock();
	dibujo_eds d = dibujo_eds(2048, 2048, 8);
	uint32_t num_colores = 64;
	crearPaletaEstandar(num_colores, d);
	tiempo = clock() - tiempo;
	cout << "Crear dibujo y paleta:\t\t" << tiempo / (double)CLOCKS_PER_SEC << endl;
	
	uint32_t x, y;
	double cx = -2, cy = -1.35, ppu = d.ancho() / 2.75;
	for(y = 0; y < d.alto(); y++) for(x = 0; x < d.ancho(); x++)
		d.dibujar_pixel(x, y, colorMandelbrot(complex<double>(cx + x / ppu, cy + y / ppu), 200, num_colores));
	tiempo = clock() - tiempo;
	cout << "Dibujar mandelbrot:\t\t" << tiempo / (double)CLOCKS_PER_SEC << endl;
	
	d.guardar_bmp("mandelbrot.bmp", false, true);
	d.~dibujo_eds();
	tiempo = clock() - tiempo;
	cout << "Comprimir y guardar:\t\t" << tiempo / (double)CLOCKS_PER_SEC << endl;
	
	return 0;
}


