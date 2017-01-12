#include "EDS_dibujo.h"
#include "EDS_color.h"
// Necesario para usar las constantes en math.h cuando se compila con Visual C++
#define _USE_MATH_DEFINES
// Necesario para usar las constantes en math.h cuando se compila con -std=c11
#ifndef __USE_MISC
#define __USE_MISC
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


extern char error_EDS_x[80];


void d_linea(DIBUJO_EDS *dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	long dx = labs((long)(x2 - x1)), dy = labs((long)(y2 - y1));
	int8_t sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
	long err = (dx > dy ? dx : -dy) / 2, e2;
	
	while(true) {
		
		d_pixel(dibujo, (uint32_t)x1, (uint32_t)y1, color, false);
		if(x1 == x2 && y1 == y2) break;
		e2 = err;
		
		if(e2 > -dx) {
			
			err -= dy;
			x1 += sx;
		}
		
		if(e2 < dy) {
			
			err += dx;
			y1 += sy;
		}
	}
}


void d_rect(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	int32_t C;
	for(C = x1 < x2 ? x1 : x2; C <= (x1 < x2 ? x2 : x1); C++) {
		
		d_pixel(dibujo, C, y1, color, false);
		d_pixel(dibujo, C, y2, color, false);
	}
	
	for(C = y1 < y2 ? y1 : y2; C <= (y1 < y2 ? y2 : y1); C++) {
		
		d_pixel(dibujo, x1, C, color, false);
		d_pixel(dibujo, x2, C, color, false);
	}
}


void d_rect_lleno(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	int32_t X, Y;
	for(X = x1 < x2 ? x1 : x2; X <= (x1 < x2 ? x2 : x1); X++) {
		for(Y = y1 < y2 ? y1 : y2; Y <= (y1 < y2 ? y2 : y1); Y++) {
			d_pixel(dibujo, X, Y, color, false);
		}
	}
}


void d_circ(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t radio, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	int X = 0;
	int Y = radio;
	int delta = 2 - 2 * radio;
	int error = 0;
	
	while(Y >= 0) {
		
		d_pixel(dibujo, x1 + X, y1 + Y, color, false);
		if(X) d_pixel(dibujo, x1 - X, y1 + Y, color, false);
		if(Y) d_pixel(dibujo, x1 + X, y1 - Y, color, false);
		if(X && Y) d_pixel(dibujo, x1 - X, y1 - Y, color, false);
		
		error = 2 * (delta + Y) - 1;
		if(delta < 0 && error <= 0) {
			
			++X;
			delta += 2 * X + 1;
			continue;
		}
		
		error = 2 * (delta - X) - 1;
		if(delta > 0 && error > 0) {
			
			--Y;
			delta += 1 - 2 * Y;
			continue;
		}
		
		++X;
		delta += 2 * (X - Y);
		--Y;
	}
}


void d_circ_lleno(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t radio, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	int X = 0;
	int Y = radio;
	int delta = 2 - 2 * radio;
	int error = 0;
	
	while(Y >= 0) {
		
		error = 2 * (delta + Y) - 1;
		if(delta < 0 && error <= 0) {
			
			++X;
			delta += 2 * X + 1;
			continue;
		}
		
		d_linea(dibujo, x1 - X, y1 + Y, x1 + X, y1 + Y, color);
		if(Y) d_linea(dibujo, x1 - X, y1 - Y, x1 + X, y1 - Y, color);
		
		error = 2 * (delta - X) - 1;
		if(delta > 0 && error > 0) {
			
			--Y;
			delta += 1 - 2 * Y;
			continue;
		}
		
		++X;
		delta += 2 * (X - Y);
		--Y;
	}
}


void d_semi_circ(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t radio, double ang_inicio, double ang_final, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	while(ang_inicio >= 2 * M_PI) ang_inicio -= 2 * M_PI;
	while(ang_final >= 2 * M_PI) ang_final -= 2 * M_PI;
	while(ang_inicio < 0) ang_inicio += 2 * M_PI;
	while(ang_final < 0) ang_final += 2 * M_PI;
	
	int X = 0;
	int Y = radio;
	int delta = 2 - 2 * radio;
	int error = 0;
	double a;
	
	while(Y >= 0) {
		
		a = atan((double)Y / (double)X);
		if(ang_inicio < ang_final ? (2 * M_PI - a >= ang_inicio && 2 * M_PI - a <= ang_final) : (2 * M_PI - a >= ang_inicio || 2 * M_PI - a <= ang_final)) d_pixel(dibujo, x1 + X, y1 + Y, color, false);
		if(X) if(ang_inicio < ang_final ? (M_PI + a >= ang_inicio && M_PI + a <= ang_final) : (M_PI + a >= ang_inicio || M_PI + a <= ang_final)) d_pixel(dibujo, x1 - X, y1 + Y, color, false);
		if(Y) if(ang_inicio < ang_final ? (a >= ang_inicio && a <= ang_final) : (a >= ang_inicio || a <= ang_final)) d_pixel(dibujo, x1 + X, y1 - Y, color, false);
		if(X && Y) if(ang_inicio < ang_final ? (M_PI - a >= ang_inicio && M_PI - a <= ang_final) : (M_PI - a >= ang_inicio || M_PI - a <= ang_final)) d_pixel(dibujo, x1 - X, y1 - Y, color, false);
		
		error = 2 * (delta + Y) - 1;
		if(delta < 0 && error <= 0) {
			
			++X;
			delta += 2 * X + 1;
			continue;
		}
		
		error = 2 * (delta - X) - 1;
		if(delta > 0 && error > 0) {
			
			--Y;
			delta += 1 - 2 * Y;
			continue;
		}
		
		++X;
		delta += 2 * (X - Y);
		--Y;
	}
}


void d_elipse(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(ancho == alto) {
		
		d_circ(dibujo, x1, y1, ancho, color);
		return;
	}
	
	int a2 = ancho * ancho;
	int b2 = alto * alto;
	int fa2 = 4 * a2, fb2 = 4 * b2;
	int X, Y, sigma;
	
	for (X = 0, Y = alto, sigma = 2 * b2 + a2 * (1 - 2 * alto); b2 * X <= a2 * Y; X++) {
		
		d_pixel(dibujo, x1 + X, y1 + Y, color, false);
		if(X) d_pixel(dibujo, x1 - X, y1 + Y, color, false);
		if(Y) d_pixel(dibujo, x1 + X, y1 - Y, color, false);
		if(X && Y) d_pixel(dibujo, x1 - X, y1 - Y, color, false);
		if (sigma >= 0) {
			
			sigma += fa2 * (1 - Y);
			Y--;
		}
		
		sigma += b2 * ((4 * X) + 6);
	}
	
	for (X = ancho, Y = 0, sigma = 2 * a2 + b2 * (1 - 2 * ancho); a2 * Y <= b2 * X; Y++) {
		
		d_pixel(dibujo, x1 + X, y1 + Y, color, false);
		if(X) d_pixel(dibujo, x1 - X, y1 + Y, color, false);
		if(Y) d_pixel(dibujo, x1 + X, y1 - Y, color, false);
		if(X && Y) d_pixel(dibujo, x1 - X, y1 - Y, color, false);
		if (sigma >= 0) {
			
			sigma += fb2 * (1 - X);
			X--;
		}
		
		sigma += a2 * ((4 * Y) + 6);
	}
}


void d_elipse_llena(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(ancho == alto) {
		
		d_circ_lleno(dibujo, x1, y1, ancho, color);
		return;
	}
	
	int a2 = ancho * ancho;
	int b2 = alto * alto;
	int fa2 = 4 * a2, fb2 = 4 * b2;
	int X, Y, sigma;
	
	for (X = 0, Y = alto, sigma = 2 * b2 + a2 * (1 - 2 * alto); b2 * X <= a2 * Y; X++) {
		
		if(ancho < alto) {
			
			d_linea(dibujo, x1 - X, y1 + Y, x1 - X, y1 - Y, color);
			if(X) d_linea(dibujo, x1 + X, y1 + Y, x1 + X, y1 - Y, color);
		}
		
		if (sigma >= 0) {
			
			if(ancho > alto) {
				
				d_linea(dibujo, x1 - X, y1 + Y, x1 + X, y1 + Y, color);
				if(Y) d_linea(dibujo, x1 - X, y1 - Y, x1 + X, y1 - Y, color);
			}
			
			sigma += fa2 * (1 - Y);
			Y--;
		}
		
		sigma += b2 * ((4 * X) + 6);
	}
	
	for (X = ancho, Y = 0, sigma = 2 * a2 + b2 * (1 - 2 * ancho); a2 * Y <= b2 * X; Y++) {
		
		if(ancho > alto) {
			
			d_linea(dibujo, x1 - X, y1 + Y, x1 + X, y1 + Y, color);
			if(Y) d_linea(dibujo, x1 - X, y1 - Y, x1 + X, y1 - Y, color);
		}
		
		if (sigma >= 0) {
			
			if(ancho < alto) {
				
				d_linea(dibujo, x1 - X, y1 + Y, x1 - X, y1 - Y, color);
				if(X) d_linea(dibujo, x1 + X, y1 + Y, x1 + X, y1 - Y, color);
			}
			
			sigma += fb2 * (1 - X);
			X--;
		}
		
		sigma += a2 * ((4 * Y) + 6);
	}
}


void d_semi_elipse(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, double ang_inicio, double ang_final, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(ancho == alto) {
		
		d_semi_circ(dibujo, x1, y1, ancho, ang_inicio, ang_final, color);
		return;
	}
	
	while(ang_inicio >= 2 * M_PI) ang_inicio -= 2 * M_PI;
	while(ang_final >= 2 * M_PI) ang_final -= 2 * M_PI;
	while(ang_inicio < 0) ang_inicio += 2 * M_PI;
	while(ang_final < 0) ang_final += 2 * M_PI;
	
	int a2 = ancho * ancho;
	int b2 = alto * alto;
	int fa2 = 4 * a2, fb2 = 4 * b2;
	int X, Y, sigma;
	double a;
	
	for (X = 0, Y = alto, sigma = 2 * b2 + a2 * (1 - 2 * alto); b2 * X <= a2 * Y; X++) {
		
		a = atan((double)Y / (double)X);
		if(ang_inicio < ang_final ? (2 * M_PI - a >= ang_inicio && 2 * M_PI - a <= ang_final) : (2 * M_PI - a >= ang_inicio || 2 * M_PI - a <= ang_final)) d_pixel(dibujo, x1 + X, y1 + Y, color, false);
		if(X) if(ang_inicio < ang_final ? (M_PI + a >= ang_inicio && M_PI + a <= ang_final) : (M_PI + a >= ang_inicio || M_PI + a <= ang_final)) d_pixel(dibujo, x1 - X, y1 + Y, color, false);
		if(Y) if(ang_inicio < ang_final ? (a >= ang_inicio && a <= ang_final) : (a >= ang_inicio || a <= ang_final)) d_pixel(dibujo, x1 + X, y1 - Y, color, false);
		if(X && Y) if(ang_inicio < ang_final ? (M_PI - a >= ang_inicio && M_PI - a <= ang_final) : (M_PI - a >= ang_inicio || M_PI - a <= ang_final)) d_pixel(dibujo, x1 - X, y1 - Y, color, false);
		if (sigma >= 0) {
			
			sigma += fa2 * (1 - Y);
			Y--;
		}
		
		sigma += b2 * ((4 * X) + 6);
	}
	
	for (X = ancho, Y = 0, sigma = 2 * a2 + b2 * (1 - 2 * ancho); a2 * Y <= b2 * X; Y++) {
		
		a = atan((double)Y / (double)X);
		if(ang_inicio < ang_final ? (2 * M_PI - a >= ang_inicio && 2 * M_PI - a <= ang_final) : (2 * M_PI - a >= ang_inicio || 2 * M_PI - a <= ang_final)) d_pixel(dibujo, x1 + X, y1 + Y, color, false);
		if(X) if(ang_inicio < ang_final ? (M_PI + a >= ang_inicio && M_PI + a <= ang_final) : (M_PI + a >= ang_inicio || M_PI + a <= ang_final)) d_pixel(dibujo, x1 - X, y1 + Y, color, false);
		if(Y) if(ang_inicio < ang_final ? (a >= ang_inicio && a <= ang_final) : (a >= ang_inicio || a <= ang_final)) d_pixel(dibujo, x1 + X, y1 - Y, color, false);
		if(X && Y) if(ang_inicio < ang_final ? (M_PI - a >= ang_inicio && M_PI - a <= ang_final) : (M_PI - a >= ang_inicio || M_PI - a <= ang_final)) d_pixel(dibujo, x1 - X, y1 - Y, color, false);
		if (sigma >= 0) {
			
			sigma += fb2 * (1 - X);
			X--;
		}
		
		sigma += a2 * ((4 * Y) + 6);
	}
}


void limpiar_d(DIBUJO_EDS* dibujo, COLOR color) {
	
	d_rect_lleno(dibujo, 0, 0, dibujo->ancho - 1, dibujo->alto - 1, color);
}

