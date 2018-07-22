#include "EDS_tipos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// Mensaje de error en caso de que algún error ocurra
char EDS_Error[80];

// Paletas de colores estandar
extern const EDS_Color EDS_PaletaEstandar1[2];
extern const EDS_Color EDS_PaletaEstandar4[16];
extern const EDS_Color EDS_PaletaEstandar8[256];


const char* EDS_ObtenerError() {
	
	return EDS_Error;
}


EDS_MascarasBits EDS_ConstruirMascaras(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	
	if(!(r && g && b)) return (EDS_MascarasBits){ .v = { 0, 0, 0, 0 } };
	return (EDS_MascarasBits){ .v = {
		(1 << b) - 1,
		((1 << g) - 1) << b,
		((1 << r) - 1) << (g + b),
		a ? ((1 << a) - 1) << (r + g + b) : 0
	} };
}


bool EDS_VerificarMascaras(const EDS_MascarasBits* mascaras) {
	
	int i, j;
	uint32_t todas = mascaras->v[0];
	for(i = 0; i < 3; todas |= mascaras->v[++i]) {
		if(!mascaras->v[i] && i != 3) return false;
		for(j = i + 1; j < 4; j++)
			if(mascaras->v[i] & mascaras->v[j]) return false;
	}
	
	if(!~todas) return true;
	while(!(todas & 1)) todas >>= 1;
	todas++;
	while(!((todas >>= 1) & 1));
	return !--todas;
	
}


EDS_Imagen* EDS_CrearImagenVacia(uint32_t ancho, uint32_t alto, uint8_t bpp) {
	
	if(bpp != 1 && bpp != 4 && bpp != 8 && bpp != 32) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "La profundidad de color especificada no está soportada.");
		return NULL;
	}
	
	EDS_Imagen* imagen = (EDS_Imagen*)malloc(sizeof(EDS_Imagen));
	if(imagen == NULL) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "No se pudo asignar la memoria necesaria para la estructura de la imagen.");
		return NULL;
	}
	
	if(bpp == 32) {
		
		imagen->mapa_bits = (EDS_Color*)calloc(ancho * alto, 4);
		if(imagen->mapa_bits == NULL) {
			
			snprintf(EDS_Error, sizeof(EDS_Error), "No se pudo asignar la memoria necesaria para el mapa de bits.");
			free(imagen);
			return NULL;
		}
		
		imagen->mapa_bits_p = NULL;
		imagen->paleta = NULL;
	}
	else {
		
		imagen->mapa_bits_p = (uint8_t*)calloc(ancho * alto, 1);
		if(imagen->mapa_bits_p == NULL) {
			
			snprintf(EDS_Error, sizeof(EDS_Error), "No se pudo asignar la memoria necesaria para el mapa de bits.");
			free(imagen);
			return NULL;
		}
		
		imagen->paleta = (EDS_Color*)malloc(4 * (1 << bpp));
		if(imagen->paleta == NULL) {
			
			snprintf(EDS_Error, sizeof(EDS_Error), "No se pudo asignar la memoria necesaria para la paleta de colores.");
			free(imagen->mapa_bits_p);
			free(imagen);
			return NULL;
		}
		
		memcpy(
			imagen->paleta,
			bpp == 1 ? EDS_PaletaEstandar1 :
			bpp == 4 ? EDS_PaletaEstandar4 :
			EDS_PaletaEstandar8,
			4 * (1 << bpp)
      		);
		
		imagen->mapa_bits = NULL;
	}
	
	imagen->ancho = ancho;
	imagen->alto = alto;
	imagen->bpp = bpp;
	
	EDS_Error[0] = '\0';
	return imagen;
}


EDS_Imagen* EDS_CopiarImagen(const EDS_Imagen* copia) {
	
	if(copia == NULL) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "La imagen de origen está dañada.");
		return NULL;
	}
	
	EDS_Imagen* imagen = EDS_CrearImagenVacia(copia->ancho, copia->alto, copia->bpp);
	if(imagen == NULL) return NULL;
	
	if(imagen->bpp == 32) {
		
		memcpy(imagen->mapa_bits, copia->mapa_bits, imagen->ancho * imagen->alto * 4);
	}
	else {
		
		memcpy(imagen->mapa_bits_p, copia->mapa_bits_p, imagen->ancho * imagen->alto);
		memcpy(imagen->paleta, copia->paleta, 4 * (1 << imagen->bpp));
	}
	
	EDS_Error[0] = '\0';
	return imagen;
}


void EDS_DestruirImagen(EDS_Imagen* imagen) {
	
	if(imagen == NULL) return;
	if(imagen->mapa_bits != NULL) free(imagen->mapa_bits);
	if(imagen->mapa_bits_p != NULL) free(imagen->mapa_bits_p);
	if(imagen->paleta != NULL) free(imagen->paleta);
	free(imagen);
}

