#include "EDS_color.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern char error_EDS_x[80];


const COLOR* paleta_std(uint16_t bpp) {
	
	return bpp == 1 ? colores_std_1 : bpp == 4 ? colores_std_4 : bpp == 8 ? colores_std_8 : NULL;
}


COLOR v_pixel(DIBUJO_EDS* dibujo, uint32_t X, uint32_t Y, bool estricto) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return 0;
	}
	
	if(X >= dibujo->ancho || Y >= dibujo->alto) {
		
		if(estricto) snprintf(error_EDS_x, sizeof(error_EDS_x), "Las coordenadas están fuera de los límites.");
		return 0;
	}
	
	if(dibujo->bpp > 8) return RGBA_P(dibujo->bitmap[Y * dibujo->ancho + X]);
	else return dibujo->bitmap_p[Y * dibujo->ancho + X];
}


void d_pixel_s(DIBUJO_EDS* dibujo, uint32_t X, uint32_t Y, COLOR color, bool estricto) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(X >= dibujo->ancho || Y >= dibujo->alto) {
		
		if(estricto) snprintf(error_EDS_x, sizeof(error_EDS_x), "Las coordenadas están fuera de los límites.");
		return;
	}
	
	if(dibujo->bpp > 8) P_RGBA(dibujo->bitmap[Y * dibujo->ancho + X], color)
	else dibujo->bitmap_p[Y * dibujo->ancho + X] = color % (1 << dibujo->bpp);
}


void d_pixel(DIBUJO_EDS* dibujo, uint32_t X, uint32_t Y, COLOR color, bool estricto) {
	
	d_pixel_s(dibujo, X, Y, (B_ALPHA(color) == 255 || dibujo->bpp <= 8) ? color : mezclar_color(color, v_pixel(dibujo, X, Y, false)), estricto);
}


COLOR invertir_color(COLOR color) {
	
	uint8_t Alpha = B_ALPHA(color);
	color |= (255 << 24);
	color = ~color;
	color |= (Alpha << 24);
	
	return color;
}


COLOR color_escala_grises(COLOR color) {
	
	uint8_t gris = (uint8_t)(0.2126 * B_ROJO(color) + 0.7152 * B_VERDE(color) + 0.0722 * B_AZUL(color));
	return RGBA(gris, gris, gris, B_ALPHA(color));
}


void invertir_colores_d(DIBUJO_EDS* dibujo) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp <= 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden tratar dibujos con una profundidad de color mayor a 8 bpp.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho; X++) d_pixel_s(dibujo, X, Y, invertir_color(v_pixel(dibujo, X, Y, false)), false);
}


void escala_grises_d(DIBUJO_EDS* dibujo) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp <= 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden tratar dibujos con una profundidad de color mayor a 8 bpp.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho; X++) d_pixel_s(dibujo, X, Y, color_escala_grises(v_pixel(dibujo, X, Y, false)), false);
}


void saturar_colores_d(DIBUJO_EDS* dibujo, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp <= 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden tratar dibujos con una profundidad de color mayor a 8 bpp.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho; X++) d_pixel_s(dibujo, X, Y, v_pixel(dibujo, X, Y, false) | color, false);
}


void extraer_colores_d(DIBUJO_EDS* dibujo, COLOR color) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp <= 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden tratar dibujos con una profundidad de color mayor a 8 bpp.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho; X++) d_pixel_s(dibujo, X, Y, v_pixel(dibujo, X, Y, false) & color, false);
}


void cambiar_transparencia_d(DIBUJO_EDS* dibujo, int16_t incremento) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp <= 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden tratar dibujos con una profundidad de color mayor a 8 bpp.");
		return;
	}
	
	if(incremento > 255 || incremento < -255) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El incremento esá fuera del límite.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) {
		
		for(X = 0; X < dibujo->ancho; X++) {
			
			if(dibujo->bitmap[Y * dibujo->ancho + X].A > 0)
				dibujo->bitmap[Y * dibujo->ancho + X].A =
					((B_ALPHA(v_pixel(dibujo, X, Y, false)) + incremento) > 255) ? 255 :
					((B_ALPHA(v_pixel(dibujo, X, Y, false)) + incremento) < 0) ? 0 :
					(B_ALPHA(v_pixel(dibujo, X, Y, false)) + incremento);
		}
	}
}


void cambiar_rojo_d(DIBUJO_EDS* dibujo, int16_t incremento) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp <= 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden tratar dibujos con una profundidad de color mayor a 8 bpp.");
		return;
	}
	
	if(incremento > 255 || incremento < -255) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El incremento esá fuera del límite.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) {
		
		for(X = 0; X < dibujo->ancho; X++) {
			
			dibujo->bitmap[Y * dibujo->ancho + X].R =
				((B_ROJO(v_pixel(dibujo, X, Y, false)) + incremento) > 255) ? 255 :
				((B_ROJO(v_pixel(dibujo, X, Y, false)) + incremento) < 0) ? 0 :
				(B_ROJO(v_pixel(dibujo, X, Y, false)) + incremento);
		}
	}
}


void cambiar_verde_d(DIBUJO_EDS* dibujo, int16_t incremento) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp <= 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden tratar dibujos con una profundidad de color mayor a 8 bpp.");
		return;
	}
	
	if(incremento > 255 || incremento < -255) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El incremento esá fuera del límite.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) {
		
		for(X = 0; X < dibujo->ancho; X++) {
			
			dibujo->bitmap[Y * dibujo->ancho + X].G =
				((B_VERDE(v_pixel(dibujo, X, Y, false)) + incremento) > 255) ? 255 :
				((B_VERDE(v_pixel(dibujo, X, Y, false)) + incremento) < 0) ? 0 :
				(B_VERDE(v_pixel(dibujo, X, Y, false)) + incremento);
		}
	}
}


void cambiar_azul_d(DIBUJO_EDS* dibujo, int16_t incremento) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp <= 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden tratar dibujos con una profundidad de color mayor a 8 bpp.");
		return;
	}
	
	if(incremento > 255 || incremento < -255) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El incremento esá fuera del límite.");
		return;
	}
	
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) {
		
		for(X = 0; X < dibujo->ancho; X++) {
			
			dibujo->bitmap[Y * dibujo->ancho + X].B =
				((B_AZUL(v_pixel(dibujo, X, Y, false)) + incremento) > 255) ? 255 :
				((B_AZUL(v_pixel(dibujo, X, Y, false)) + incremento) < 0) ? 0 :
				(B_AZUL(v_pixel(dibujo, X, Y, false)) + incremento);
		}
	}
}


void cambiar_brillo_d(DIBUJO_EDS* dibujo, int16_t incremento) {
	
	cambiar_rojo_d(dibujo, incremento);
	cambiar_verde_d(dibujo, incremento);
	cambiar_azul_d(dibujo, incremento);
}


uint8_t color_mas_cercano(uint16_t num_colores, const uint32_t* paleta, COLOR color) {
	
	if(num_colores > 256) return 0;
	uint16_t C = 0;
	uint8_t resp = 0;
	int32_t RO, GO, BO, DR, DG, DB;
	uint32_t dist = ~0, dist_c;
	
	RO = B_ROJO(color);
	GO = B_VERDE(color);
	BO = B_AZUL(color);
	
	do {
		
		DR = B_ROJO(paleta[C]) - RO;
		DG = B_VERDE(paleta[C]) - GO;
		DB = B_AZUL(paleta[C]) - BO;
		dist_c = DR * DR + DG * DG + DB * DB;
		
		if(dist_c < dist) {
			
			dist = dist_c;
			resp = (uint8_t)C;
		}
		
	} while(++C < num_colores);
	
	return resp;
}


void aumentar_bpp_d(DIBUJO_EDS* dibujo) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(dibujo->bpp > 8) return;
	
	dibujo->bitmap = (p32*)calloc(dibujo->ancho * dibujo->alto, sizeof(p32));
	if(dibujo->bitmap == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para el nuevo mapa de bits.");
		return;
	}
	
	dibujo->bpp = 32;
	uint32_t X, Y;
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho; X++) d_pixel_s(dibujo, X, Y, dibujo->paleta[dibujo->bitmap_p[Y * dibujo->ancho + X]], false);
	free(dibujo->bitmap_p);
	free(dibujo->paleta);
	dibujo->bitmap_p = NULL;
	dibujo->paleta = NULL;
}


void reducir_bpp_d(DIBUJO_EDS* dibujo, uint8_t bpp) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(bpp == dibujo->bpp) return;
	
	if(bpp != 1 && bpp != 4 && bpp != 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Debe especificar una profundidad de color que acepte paleta de colores.");
		return;
	}
	
	uint16_t num_colores = 1 << bpp;
	uint8_t* bitmap_nuevo = (uint8_t*)calloc(dibujo->ancho * dibujo->alto, 1);
	if(bitmap_nuevo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para el nuevo mapa de bits.");
		return;
	}
	
	uint32_t* paleta = (uint32_t*)malloc(4 * num_colores);
	if(paleta == NULL) {
		
		free(bitmap_nuevo);
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para la nueva paleta de colores.");
		return;
	}
	
	uint32_t X, Y;
	const uint32_t* paleta_nueva = bpp == 8 ? colores_std_8 : bpp == 4 ? colores_std_4 : colores_std_1;
	for(Y = 0; Y < dibujo->alto; Y++) for(X = 0; X < dibujo->ancho; X++)
		bitmap_nuevo[Y * dibujo->ancho + X] = color_mas_cercano(num_colores, paleta_nueva, dibujo->bpp > 8 ? v_pixel(dibujo, X, Y, false) : dibujo->paleta[dibujo->bitmap_p[Y * dibujo->ancho + X]]);
	
	free(dibujo->bitmap);
	dibujo->bitmap = NULL;
	dibujo->bitmap_p = bitmap_nuevo;
	dibujo->paleta = paleta;
	dibujo->bpp = bpp;
	memcpy(dibujo->paleta, paleta_nueva, 4 * num_colores);
}

