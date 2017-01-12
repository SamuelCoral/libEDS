#include "EDS_tipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char error_EDS_x[80];


const char* error_EDS() {
	
	return error_EDS_x;
}


DIBUJO_EDS* crear_dibujo_vacio(uint32_t ancho, uint32_t alto, uint8_t bpp) {
	
	error_EDS_x[0] = 0;
	if(bpp <= 8 && bpp != 1 && bpp != 4 && bpp != 8) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "Solo se pueden crear dibujos de una profundidad de color múltiplo de 2.");
		return NULL;
	}
	
	DIBUJO_EDS *dibujo = (DIBUJO_EDS*)malloc(sizeof(DIBUJO_EDS));
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para la estructura de dibujo.");
		return NULL;
	}
	
	dibujo->ancho = ancho;
	dibujo->alto = alto;
	
	if(bpp > 8) {
		
		dibujo->bpp = 32;
		dibujo->paleta = NULL;
		dibujo->bitmap_p = NULL;
		dibujo->bitmap = (p32*)calloc(alto * ancho, sizeof(p32));
		if(dibujo->bitmap == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear el mapa de bits.");
			free(dibujo);
			return NULL;
		}
	}
	
	else {
		
		dibujo->bpp = bpp;
		dibujo->bitmap = NULL;
		dibujo->paleta = (uint32_t*)malloc((1 << bpp) * 4);
		if(dibujo->paleta == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear la paleta de colores.");
			free(dibujo);
			return NULL;
		}
		
		uint16_t C;
		for(C = 0; C < (1 << bpp); C++) dibujo->paleta[C] = bpp == 1 ? colores_std_1[C] : bpp == 4 ? colores_std_4[C] : bpp == 8 ? colores_std_8[C] : 0x000000;
		
		dibujo->bitmap_p = (uint8_t*)calloc(alto * ancho, 1);
		if(dibujo->bitmap_p == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear el mapa de bits.");
			free(dibujo->paleta);
			free(dibujo);
			return NULL;
		}
	}
	
	return dibujo;
}


DIBUJO_EDS* convertir_bmp_dibujo(IMAGEN_BMP* imagen, bool paleta) {
	
	error_EDS_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "La imagen de origen está dañada.");
		return NULL;
	}
	
	if(bpp_bmp(imagen) != 1 && bpp_bmp(imagen) != 4 && bpp_bmp(imagen) != 8 && bpp_bmp(imagen) != 16 && bpp_bmp(imagen) != 24 && bpp_bmp(imagen) != 32) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "La profundidad de color de la imagen no esá soportada.");
		return NULL;
	}
	
	DIBUJO_EDS *dibujo = (DIBUJO_EDS*)malloc(sizeof(DIBUJO_EDS));
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para la estructura de dibujo.");
		return NULL;
	}
	
	IMAGEN_BMP *imagen_d = imagen;
	
	dibujo->ancho = ancho_bmp(imagen);
	dibujo->alto = labs(alto_bmp(imagen));
	
	uint32_t X, Y, bit, linea, linea_bmp, tam_linea_bmp;
	
	if(paleta && bpp_bmp(imagen) <= 8) {
		
		dibujo->bpp = (uint8_t)bpp_bmp(imagen);
		dibujo->bitmap = NULL;
		dibujo->paleta = (uint32_t*)malloc((1 << dibujo->bpp) * 4);
		if(dibujo->paleta == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear la paleta de colores.");
			free(dibujo);
			return NULL;
		}
		
		memcpy(dibujo->paleta, imagen->paleta, (1 << dibujo->bpp) * 4);
		dibujo->bitmap_p = (uint8_t*)malloc(dibujo->alto * dibujo->ancho);
		if(dibujo->bitmap_p == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear el mapa de bits.");
			free(dibujo->paleta);
			free(dibujo);
			return NULL;
		}
		
		if(compresion_bmp(imagen) == BMP_MC_RLE4 || compresion_bmp(imagen) == BMP_MC_RLE8) {
			
			imagen_d = copiar_bmp(imagen);
			if(imagen_d == NULL) {
				
				snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo copiar la estructura del archivo de imagen.");
				free(dibujo->paleta);
				free(dibujo->bitmap_p);
				free(dibujo);
				return NULL;
			}
			
			compresion_rle_bmp(imagen_d);
		}
		
		tam_linea_bmp = tam_linea(dibujo->ancho, dibujo->bpp);
		for(Y = linea = 0; Y < dibujo->alto; Y++, linea = Y * dibujo->ancho) {
			
			linea_bmp = (alto_bmp(imagen) > 0 ? dibujo->alto - 1 - Y : Y) * tam_linea_bmp;
			for(X = 0, bit = 0; X < dibujo->ancho; X++, bit = X * dibujo->bpp) {
				
				dibujo->bitmap_p[linea + X] = (((uint8_t*)imagen_d->bitmap)[linea_bmp + (bit / 8)] >> (((bit + 8) & ~7) - bit - dibujo->bpp)) % (1 << dibujo->bpp);
			}
		}
	}
	
	else {
		
		dibujo->bpp = 32;
		dibujo->paleta = NULL;
		dibujo->bitmap_p = NULL;
		dibujo->bitmap = (p32*)calloc(dibujo->alto * dibujo->ancho, sizeof(p32));
		if(dibujo->bitmap == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear el mapa de bits.");
			free(dibujo);
			return NULL;
		}
		
		imagen_d = copiar_bmp(imagen);
		if(imagen_d == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo copiar la estructura del archivo de imagen.");
			free(dibujo->bitmap);
			free(dibujo);
			return NULL;
		}
		
		if(imagen_d->dib_info.ver == BMP_DIB_WIN20) convertir_dib_bmp(imagen_d, BMP_DIB_WINNT);
		if(error_bmp()[0]) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo convertir la versión de la cabecera para su tratamiento.");
			free(dibujo->bitmap);
			free(dibujo);
			free(imagen_d);
			return NULL;
		}
		
		cambiar_formato_pixel_bmp(imagen_d, 32, RGBA8888);
		if(error_bmp()[0]) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo cambiar el formato de pixel de la imagen.");
			free(dibujo->bitmap);
			free(dibujo);
			free(imagen_d);
			return NULL;
		}
		
		tam_linea_bmp = tam_linea(dibujo->ancho, 32);
		for(Y = linea = 0; Y < dibujo->alto; Y++, linea = Y * dibujo->ancho) {
			
			linea_bmp = (alto_bmp(imagen) > 0 ? dibujo->alto - 1 - Y : Y) * tam_linea_bmp;
			memcpy(&((uint32_t*)dibujo->bitmap)[linea], &((uint8_t*)imagen_d->bitmap)[linea_bmp], tam_linea_bmp);
		}
	}
	
	if(imagen_d != imagen) destruir_puntero_bmp(imagen_d);
	return dibujo;
}


DIBUJO_EDS* cargar_dibujo_archivo_bmp(const char* ruta_bmp, bool paleta) {
	
	error_EDS_x[0] = 0;
	IMAGEN_BMP* imagen = cargar_bmp(ruta_bmp);
	if(imagen == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo cargar el archivo especificado.");
		return NULL;
	}
	
	DIBUJO_EDS* dibujo = convertir_bmp_dibujo(imagen, paleta);
	destruir_puntero_bmp(imagen);
	return dibujo;
}


void inyectar_dibujo_bmp(DIBUJO_EDS* dibujo, IMAGEN_BMP* imagen, bool alpha) {
	
	error_EDS_x[0] = 0;
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return;
	}
	
	if(imagen == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(imagen->dib_info.ver == BMP_DIB_WIN20 || dibujo->bpp <= 8) alpha = false;
	
	uint32_t *bitmap_nuevo = (uint32_t*)calloc(dibujo->alto * tam_linea(dibujo->ancho, dibujo->bpp > 8 ? alpha ? 32 : 24 : dibujo->bpp), 1);
	if(bitmap_nuevo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear el mapa de bits.");
		return;
	}
	
	uint32_t *paleta_nueva = NULL;
	if(dibujo->bpp <= 8) {
		
		paleta_nueva = (uint32_t*)malloc(4 * (1 << dibujo->bpp));
		if(paleta_nueva == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear la paleta de colores.");
			free(bitmap_nuevo);
			return;
		}
	}
	
	if(!alpha && imagen->bitfields != NULL && imagen->dib_info.ver < BMP_DIB_WIN95) {
		
		free(imagen->bitfields);
		imagen->bitfields = NULL;
	}
	
	if(alpha && imagen->bitfields == NULL) {
		
		imagen->bitfields = (MASCARAS_BITS*)malloc(sizeof(MASCARAS_BITS));
		if(imagen->bitfields == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear las máscarasde bits.");
			if(paleta_nueva != NULL) free(paleta_nueva);
			free(bitmap_nuevo);
			return;
		}
	}
	
	free(imagen->bitmap);
	imagen->bitmap = bitmap_nuevo;
	
	if(bpp_bmp(imagen) <= 8) {
		
		free(imagen->paleta);
		imagen->paleta = NULL;
	}
	
	imagen->cabecera.dir_bitmap = sizeof(BMPFILEHEADER) + ((imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12 || imagen->dib_info.ver == BMP_DIB_WINNT + 16) ? BMP_DIB_WINNT + (alpha ? 16 : 0) : imagen->dib_info.ver);
	
	uint32_t	X, Y, linea, linea_bmp, tam_linea_bmp = tam_linea(dibujo->ancho, dibujo->bpp > 8 ? alpha ? 32 : 24 : dibujo->bpp) / (alpha ? 4 : 1);
	uint8_t		C;
	
	if(dibujo->bpp > 8) {
		
		for(Y = linea = 0; Y < dibujo->alto; Y++, linea = Y * dibujo->ancho) {
			
			linea_bmp = (dibujo->alto - 1 - Y) * tam_linea_bmp;
			for(X = 0; X < dibujo->ancho; X++) {
				
				if(!alpha) for(C = 0; C < 3; C++) ((uint8_t*)imagen->bitmap)[linea_bmp + X * 3 + C] |= (uint8_t)(RGB_P(dibujo->bitmap[linea + X]) >> (C * 8));
				else ((uint32_t*)imagen->bitmap)[linea_bmp + X] = RGBA_P(dibujo->bitmap[linea + X]);
			}
		}
	}
	
	else {
		
		imagen->paleta = paleta_nueva;
		memcpy(imagen->paleta, dibujo->paleta, (1 << dibujo->bpp) * 4);
		uint32_t bit, num_colores = 1 << dibujo->bpp;
		
		for(Y = linea = 0; Y < dibujo->alto; Y++, linea = Y * dibujo->ancho) {
			
			linea_bmp = (dibujo->alto - 1 - Y) * tam_linea_bmp;
			for(X = 0, bit = 0; X < dibujo->ancho; X++, bit = X * dibujo->bpp) ((uint8_t*)imagen->bitmap)[linea_bmp + (bit / 8)] |= (dibujo->bitmap_p[linea + X] % num_colores) << (((bit + 8) & ~7) - bit - dibujo->bpp);
		}
		
		imagen->cabecera.dir_bitmap += (imagen->dib_info.ver == BMP_DIB_WIN20 ? 3 : 4) * (1 << dibujo->bpp);
	}
	
	
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20: {
			
			imagen->dib_info.dib_win20->ancho = dibujo->ancho;
			imagen->dib_info.dib_win20->alto = dibujo->alto;
			imagen->dib_info.dib_win20->bpp = dibujo->bpp > 8 ? 24 : dibujo->bpp;
			
		} break;
		
		
		case BMP_DIB_WIN98: {
			
			if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO) imagen->cabecera.dir_bitmap += imagen->dib_info.dib_win98->tam_perfil;
			else if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO) imagen->cabecera.dir_bitmap += (uint32_t)strlen(imagen->ruta_perfil) + 1;
		}
		
		
		case BMP_DIB_WIN95: if(!alpha) *imagen->bitfields = MASCARAS_VACIAS;
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT: {
			
			if(imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12 || imagen->dib_info.ver == BMP_DIB_WINNT + 16)
				imagen->dib_info.ver = imagen->dib_info.dib_winnt->tam_dib = BMP_DIB_WINNT + (alpha ? 16 : 0);
			imagen->dib_info.dib_winnt->ancho = dibujo->ancho;
			imagen->dib_info.dib_winnt->alto = dibujo->alto;
			imagen->dib_info.dib_winnt->bpp = dibujo->bpp > 8 ? alpha ? 32 : 24 : dibujo->bpp;
			imagen->dib_info.dib_winnt->compresion = alpha ? BMP_MC_BITFIELDS : BMP_MC_RGB;
			imagen->dib_info.dib_winnt->tam_bitmap = tam_linea(dibujo->ancho, dibujo->bpp > 8 ? alpha ? 32 : 24 : dibujo->bpp) * dibujo->alto;
			imagen->dib_info.dib_winnt->colores = dibujo->bpp > 8 ? 0 : (1 << dibujo->bpp);
			imagen->dib_info.dib_winnt->colores_importantes = 0;
			
		} break;
	}
	
	if(alpha) *imagen->bitfields = RGBA8888;
	imagen->cabecera.tam_archivo = imagen->cabecera.dir_bitmap + (tam_linea(dibujo->ancho, dibujo->bpp > 8 ? alpha ? 32 : 24 : dibujo->bpp) * dibujo->alto);
}


IMAGEN_BMP* convertir_dibujo_bmp(DIBUJO_EDS* dibujo, bool alpha, bool rle) {
	
	error_EDS_x[0] = 0;
	IMAGEN_BMP *imagen = crear_bmp_vacio(0, 0, 24);
	if(imagen == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear la imagen");
		return NULL;
	}
	
	if(alpha && dibujo->bpp > 8) convertir_dib_bmp(imagen, BMP_DIB_WIN95);
	inyectar_dibujo_bmp(dibujo, imagen, alpha);
	if(rle && (dibujo->bpp == 8 || dibujo->bpp == 4)) compresion_rle_bmp(imagen);
	return imagen;
}


void guardar_dibujo_bmp(DIBUJO_EDS* dibujo, const char* ruta_bmp, bool alpha, bool rle) {
	
	error_EDS_x[0] = 0;
	IMAGEN_BMP* imagen = convertir_dibujo_bmp(dibujo, alpha, rle);
	if(imagen == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo convertir la estructura de dibujo en estructura de archivo BMP.");
		return;
	}
	
	guardar_bmp(imagen, ruta_bmp);
	destruir_puntero_bmp(imagen);
}



DIBUJO_EDS* copiar_dibujo(DIBUJO_EDS* origen) {
	
	error_EDS_x[0] = 0;
	if(origen == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "El dibujo de origen está dañado.");
		return NULL;
	}
	
	DIBUJO_EDS *dibujo = (DIBUJO_EDS*)malloc(sizeof(DIBUJO_EDS));
	if(dibujo == NULL) {
		
		snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para la estructura de dibujo.");
		return NULL;
	}
	
	dibujo->ancho = origen->ancho;
	dibujo->alto = origen->alto;
	dibujo->bpp = origen->bpp;
	
	if(dibujo->bpp > 8) {
		
		dibujo->paleta = NULL;
		dibujo->bitmap_p = NULL;
		dibujo->bitmap = (p32*)malloc(sizeof(p32) * dibujo->ancho * dibujo->alto);
		if(dibujo->bitmap == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear el mapa de bits.");
			free(dibujo);
			return NULL;
		}
		
		memcpy(dibujo->bitmap, origen->bitmap, dibujo->alto * dibujo->ancho * 4);
	}
	
	else {
		
		dibujo->bitmap = NULL;
		dibujo->paleta = (uint32_t*)malloc(4 * (1 << dibujo->bpp));
		if(dibujo->paleta == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear la paleta de colores.");
			free(dibujo);
			return NULL;
		}
		
		memcpy(dibujo->paleta, origen->paleta, (1 << dibujo->bpp) * 4);
		dibujo->bitmap_p = (uint8_t*)malloc(dibujo->ancho * dibujo->alto);
		if(dibujo->bitmap_p == NULL) {
			
			snprintf(error_EDS_x, sizeof(error_EDS_x), "No se pudo asignar la memoria necesaria para crear el mapa de bits.");
			free(dibujo->paleta);
			free(dibujo);
			return NULL;
		}
		
		memcpy(dibujo->bitmap_p, origen->bitmap_p, dibujo->alto * dibujo->ancho);
	}
	
	return dibujo;
}


void destruir_puntero_dibujo(DIBUJO_EDS* dibujo) {
	
	if(dibujo == NULL) return;
	if(dibujo->bitmap != NULL) free(dibujo->bitmap);
	if(dibujo->bitmap_p != NULL) free(dibujo->bitmap_p);
	if(dibujo->paleta != NULL) free(dibujo->paleta);
	free(dibujo);
}

