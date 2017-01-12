#include "EDS_geo.h"
#include "EDS_color.h"
#include <stdio.h>
#include <stdlib.h>


extern char error_EDS_x[80];


void reescalar_d(DIBUJO_EDS* dibujo, uint32_t x2, uint32_t y2) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	DIBUJO_EDS *temp = copiar_dibujo(dibujo);
	if(temp == NULL) return;
	
	if(dibujo->bpp > 8) {
		
		dibujo->bitmap = (p32*)realloc(dibujo->bitmap, x2 * y2 * sizeof(p32));
		if(dibujo->bitmap == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo reasignar la memoria necesaria para el mapa de bits");
			destruir_puntero_dibujo(temp);
			return;
		}
	}
	
	else {
		
		dibujo->bitmap_p = (uint8_t*)realloc(dibujo->bitmap_p, x2 * y2);
		if(dibujo->bitmap_p == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo reasignar la memoria necesaria para el mapa de bits");
			destruir_puntero_dibujo(temp);
			return;
		}
	}
	
	dibujo->ancho = x2;
	dibujo->alto = y2;
	
	uint32_t Y, X, x3, y3;
	
	for(Y = 0; Y < temp->alto; Y++) for(y3 = 0; ((Y * y2 / temp->alto) + y3) <= ((Y + 1) * y2 / temp->alto); y3++) {
		
		for(X = 0; X < temp->ancho; X++) for(x3 = 0; ((X * x2 / temp->ancho) + x3) <= ((X + 1) * x2 / temp->ancho); x3++) {
			
			d_pixel_s(dibujo, (X * x2 / temp->ancho) + x3, (Y * y2 / temp->alto) + y3, v_pixel(temp, X, Y, false), false);
		}
	}
	
	destruir_puntero_dibujo(temp);
}


DIBUJO_EDS* escalar_d(DIBUJO_EDS* dibujo, uint32_t x2, uint32_t y2) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return NULL;
	}
	
	DIBUJO_EDS *destino = copiar_dibujo(dibujo);
	if(destino == NULL) return NULL;
	
	reescalar_d(destino, x2, y2);
	
	return destino;
}


void recortar_d(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(x1 == x2 || y1 == y2) return;
	
	int32_t X, Y;
	
	if(x1 > x2) {
		
		X = x1;
		x1 = x2;
		x2 = X;
	}
	
	if(y1 > y2) {
		
		Y = y1;
		y1 = y2;
		y2 = Y;
	}
	
	DIBUJO_EDS *temp = copiar_dibujo(dibujo);
	if(temp == NULL) return;
	
	if(dibujo->bpp > 8) {
		
		dibujo->bitmap = (p32*)realloc(dibujo->bitmap, (x2 - x1) * (y2 - y1) * sizeof(p32));
		if(dibujo->bitmap == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo reasignar la memoria necesaria para el mapa de bits");
			destruir_puntero_dibujo(temp);
			return;
		}
	}
	
	else {
		
		dibujo->bitmap_p = (uint8_t*)realloc(dibujo->bitmap_p, (x2 - x1) * (y2 - y1));
		if(dibujo->bitmap_p == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo reasignar la memoria necesaria para el mapa de bits");
			destruir_puntero_dibujo(temp);
			return;
		}
	}
	
	dibujo->ancho = x2 - x1;
	dibujo->alto = y2 - y1;
	
	for(Y = y1; Y < y2; Y++) for(X = x1; X < x2; X++) d_pixel_s(dibujo, X - x1, Y - y1, v_pixel(temp, X, Y, false), false);
	
	error_EDS_x[0] = 0;
	destruir_puntero_dibujo(temp);
}


DIBUJO_EDS* cortar_d(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return NULL;
	}
	
	DIBUJO_EDS *destino = copiar_dibujo(dibujo);
	if(destino == NULL) return NULL;
	
	recortar_d(destino, x1, y1, x2, y2);
	
	return destino;
}


void pegar_d(DIBUJO_EDS* origen, DIBUJO_EDS* destino, int32_t x1, int32_t y1) {
	
	error_EDS_x[0] = 0;
	if(origen == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(destino == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de destino está dañado.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < origen->alto; Y++) for(X = 0; X < origen->ancho; X++)
		d_pixel(destino, X + x1, Y + y1,
			destino->bpp == origen->bpp ? v_pixel(origen, X, Y, false) :
			destino->bpp == 32 ? origen->paleta[v_pixel(origen, X, Y, false)] | 0xFF000000 :
			color_mas_cercano(
				destino->bpp,
				destino->paleta,
				origen->bpp > 8 ? v_pixel(origen, X, Y, false) :
				origen->paleta[v_pixel(origen, X, Y, false)]
			), false
		);
	
	error_EDS_x[0] = 0;
}


void pegar_escalar_d(DIBUJO_EDS* origen, DIBUJO_EDS* destino, int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
	
	error_EDS_x[0] = 0;
	if(origen == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(destino == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de destino está dañado.");
		return;
	}
	
	int32_t X, Y;
	
	if(x1 > x2) {
		
		X = x1;
		x1 = x2;
		x2 = X;
	}
	
	if(y1 > y2) {
		
		Y = y1;
		y1 = y2;
		y2 = Y;
	}
	
	DIBUJO_EDS *temp = escalar_d(origen, x2 - x1, y2 - y1);
	if(temp == NULL) return;
	
	for(Y = y1; Y < y2; Y++) for(X = x1; X < x2; X++)
		d_pixel(destino, X, Y,
			destino->bpp == origen->bpp ? v_pixel(temp, X - x1, Y - y1, false) :
			destino->bpp == 32 ? origen->paleta[v_pixel(temp, X - x1, Y - y1, false)] | 0xFF000000 :
			color_mas_cercano(
				destino->bpp,
				destino->paleta,
				origen->bpp > 8 ? v_pixel(temp, X - x1, Y - y1, false) :
				origen->paleta[v_pixel(temp, X - x1, Y - y1, false)]
			), false
		);
	
	error_EDS_x[0] = 0;
	destruir_puntero_dibujo(temp);
}


void espejo_x_d(DIBUJO_EDS* dibujo) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	COLOR temp;
	uint32_t X, Y;
	
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho / 2; X++) {
		
		temp = v_pixel(dibujo, X, Y, false);
		d_pixel_s(dibujo, X, Y, v_pixel(dibujo, dibujo->ancho - 1 - X, Y, false), false);
		d_pixel_s(dibujo, dibujo->ancho - 1 - X, Y, temp, false);
	}
}


void espejo_y_d(DIBUJO_EDS* dibujo) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	COLOR temp;
	uint32_t X, Y;
	
	for(Y = 0; Y < dibujo->alto / 2; Y++) for(X = 0; X < dibujo->ancho; X++) {
		
		temp = v_pixel(dibujo, X, Y, false);
		d_pixel_s(dibujo, X, Y, v_pixel(dibujo, X, dibujo->alto - 1 - Y, false), false);
		d_pixel_s(dibujo, X, dibujo->alto - 1 - Y, temp, false);
	}
}


void voltear_d(DIBUJO_EDS* dibujo) {
	
	espejo_x_d(dibujo);
	espejo_y_d(dibujo);
}


void rotar_derecha_d(DIBUJO_EDS* dibujo) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	DIBUJO_EDS *temp = copiar_dibujo(dibujo);
	if(temp == NULL) return;
	
	dibujo->ancho = temp->alto;
	dibujo->alto = temp->ancho;
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho; X++) d_pixel_s(dibujo, X, Y, v_pixel(temp, Y, temp->alto - 1 - X, false), false);
	destruir_puntero_dibujo(temp);
}


void rotar_izquierda_d(DIBUJO_EDS* dibujo) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	DIBUJO_EDS *temp = copiar_dibujo(dibujo);
	if(temp == NULL) return;
	
	dibujo->ancho = temp->alto;
	dibujo->alto = temp->ancho;
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho; X++) d_pixel_s(dibujo, X, Y, v_pixel(temp, temp->ancho - 1 - Y, X, false), false);
	destruir_puntero_dibujo(temp);
}

