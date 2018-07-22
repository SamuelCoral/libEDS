#include "EDS_dibujo.h"
#include "EDS_color.h"
#include <stdlib.h>
#include <stdio.h>


extern char EDS_Error[80];



void EDS_LimpiarDibujo(EDS_Imagen* imagen, uint32_t color) {
	
	if(imagen == NULL) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "La imagen de origen está dañada.");
	}
	
	uint32_t i, j;
	for(j = 0; j < imagen->alto; j++) for(i = 0; i < imagen->ancho; i++)
		EDS_SobreescribirPixel(imagen, i, j, color);
	
	EDS_Error[0] = '\0';
}


void EDS_DibujarLinea(EDS_Imagen* imagen, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color) {
	
	if(imagen == NULL) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "La imagen de origen está dañada.");
		return;
	}
	
	long dx = labs((long)(x2 - x1)), dy = labs((long)(y2 - y1));
	int8_t sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
	long err = (dx > dy ? dx : -dy) / 2, e2;
	
	while(true) {
		
		EDS_DibujarPixel(imagen, (uint32_t)x1, (uint32_t)y1, color);
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

	EDS_Error[0] = '\0';
}

