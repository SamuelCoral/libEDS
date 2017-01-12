// Para ignorar las advertencias sobre funciones no seguras al compilar con Visual C++
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libbmp.h"



const uint32_t colores_std_1[2] = {
	
	0x000000,
	0xFFFFFF
};

const uint32_t colores_std_4[16] = {
	
	0x000000,
	0x800000,
	0x008000,
	0x808000,
	0x000080,
	0x800080,
	0x008080,
	0x808080,
	0xC0C0C0,
	0xFF0000,
	0x00FF00,
	0xFFFF00,
	0x0000FF,
	0xFF00FF,
	0x00FFFF,
	0xFFFFFF
};

const uint32_t colores_std_8[256] = {
	
	0x000000, 0x0000A8, 0x00A800, 0x00A8A8, 0xA80000, 0xA800A8, 0xA85400, 0xA8A8A8,
	0x545454, 0x5454FC, 0x54FC54, 0x54FCFC, 0xFC5454, 0xFC54FC, 0xFCFC54, 0xFCFCFC,
	0x000000, 0x141414, 0x202020, 0x2C2C2C, 0x383838, 0x444444, 0x505050, 0x606060,
	0x707070, 0x808080, 0x909090, 0xA0A0A0, 0xB4B4B4, 0xC8C8C8, 0xE0E0E0, 0xFCFCFC,
	0x0000FC, 0x4000FC, 0x7C00FC, 0xBC00FC, 0xFC00FC, 0xFC00BC, 0xFC007C, 0xFC0040,
	0xFC0000, 0xFC4000, 0xFC7C00, 0xFCBC00, 0xFCFC00, 0xBCFC00, 0x7CFC00, 0x40FC00,
	0x00FC00, 0x00FC40, 0x00FC7C, 0x00FCBC, 0x00FCFC, 0x00BCFC, 0x007CFC, 0x0040FC,
	0x7C7CFC, 0x9C7CFC, 0xBC7CFC, 0xDC7CFC, 0xFC7CFC, 0xFC7CDC, 0xFC7CBC, 0xFC7C9C,
	0xFC7C7C, 0xFC9C7C, 0xFCBC7C, 0xFCDC7C, 0xFCFC7C, 0xDCFC7C, 0xBCFC7C, 0x9CFC7C,
	0x7CFC7C, 0x7CFC9C, 0x7CFCBC, 0x7CFCDC, 0x7CFCFC, 0x7CDCFC, 0x7CBCFC, 0x7C9CFC,
	0xB4B4FC, 0xC4B4FC, 0xD8B4FC, 0xE8B4FC, 0xFCB4FC, 0xFCB4E8, 0xFCB4D8, 0xFCB4C4,
	0xFCB4B4, 0xFCC4B4, 0xFCD8B4, 0xFCE8B4, 0xFCFCB4, 0xE8FCB4, 0xD8FCB4, 0xC4FCB4,
	0xB4FCB4, 0xB4FCC4, 0xB4FCD8, 0xB4FCE8, 0xB4FCFC, 0xB4E8FC, 0xB4D8FC, 0xB4C4FC,
	0x000070, 0x1C0070, 0x380070, 0x540070, 0x700070, 0x700054, 0x700038, 0x70001C,
	0x700000, 0x701C00, 0x703800, 0x705400, 0x707000, 0x547000, 0x387000, 0x1C7000,
	0x007000, 0x00701C, 0x007038, 0x007054, 0x007070, 0x005470, 0x003870, 0x001C70,
	0x383870, 0x443870, 0x543870, 0x603870, 0x703870, 0x703860, 0x703854, 0x703844,
	0x703838, 0x704438, 0x705438, 0x706038, 0x707038, 0x607038, 0x547038, 0x447038,
	0x387038, 0x387044, 0x387054, 0x387060, 0x387070, 0x386070, 0x385470, 0x384470,
	0x505070, 0x585070, 0x605070, 0x685070, 0x705070, 0x705068, 0x705060, 0x705058,
	0x705050, 0x705850, 0x706050, 0x706850, 0x707050, 0x687050, 0x607050, 0x587050,
	0x507050, 0x507058, 0x507060, 0x507068, 0x507070, 0x506870, 0x506070, 0x505870,
	0x000040, 0x100040, 0x200040, 0x300040, 0x400040, 0x400030, 0x400020, 0x400010,
	0x400000, 0x401000, 0x402000, 0x403000, 0x404000, 0x304000, 0x204000, 0x104000,
	0x004000, 0x004010, 0x004020, 0x004030, 0x004040, 0x003040, 0x002040, 0x001040,
	0x202040, 0x282040, 0x302040, 0x382040, 0x402040, 0x402038, 0x402030, 0x402028,
	0x402020, 0x402820, 0x403020, 0x403820, 0x404020, 0x384020, 0x304020, 0x284020,
	0x204020, 0x204028, 0x204030, 0x204038, 0x204040, 0x203840, 0x203040, 0x202840,
	0x2C2C40, 0x302C40, 0x342C40, 0x3C2C40, 0x402C40, 0x402C3C, 0x402C34, 0x402C30,
	0x402C2C, 0x40302C, 0x40342C, 0x403C2C, 0x40402C, 0x3C402C, 0x34402C, 0x30402C,
	0x2C402C, 0x2C4030, 0x2C4034, 0x2C403C, 0x2C4040, 0x2C3C40, 0x2C3440, 0x2C3040,
	0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};


char error_bmp_x[80];


const char* error_bmp() {
	
	return error_bmp_x;
}


uint32_t ancho_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20:	return imagen->dib_info.dib_win20->ancho;
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	return imagen->dib_info.dib_winnt->ancho;
		
		default: return 0;
	}
}


int32_t alto_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20:	return imagen->dib_info.dib_win20->alto;
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	return imagen->dib_info.dib_winnt->alto;
		
		default: return 0;
	}
}


uint16_t bpp_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20:	return imagen->dib_info.dib_win20->bpp;
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	return imagen->dib_info.dib_winnt->bpp;
		
		default: return 0;
	}
}


uint16_t planos_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20:	return imagen->dib_info.dib_win20->planos;
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	return imagen->dib_info.dib_winnt->planos;
		
		default: return 0;
	}
}


uint32_t compresion_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	return imagen->dib_info.dib_winnt->compresion;
		
		default: return BMP_MC_RGB;
	}
}


uint32_t res_horizontal_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	return imagen->dib_info.dib_winnt->res_horizontal;
		
		default: return 0;
	}
}


uint32_t res_vertical_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	return imagen->dib_info.dib_winnt->res_vertical;
		
		default: return 0;
	}
}


uint32_t espacio_color_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:	return imagen->dib_info.dib_win95->tipo_espacio_color;
		
		default: return BMP_ECL_sRGB;
	}
}


uint32_t modo_renderizado_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return 0;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN98:	return imagen->dib_info.dib_win98->modo_renderizado;
		
		default: return BMP_IR_GRAFICOS;
	}
}


void ajustar_res_impresion_bmp(IMAGEN_BMP* imagen, uint32_t res_horizontal, uint32_t res_vertical) {
	
	if(imagen == NULL) return;
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	{
			
			imagen->dib_info.dib_winnt->res_horizontal = res_horizontal;
			imagen->dib_info.dib_winnt->res_vertical = res_vertical;
		}
	}
}


void voltear_bmp(IMAGEN_BMP* imagen) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(compresion_bmp(imagen) != BMP_MC_RGB && compresion_bmp(imagen) != BMP_MC_BITFIELDS) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Solo se pueden voltear de cabeza los mapas de bits no comprimidos.");
		return;
	}
	
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20: imagen->dib_info.dib_win20->alto = -imagen->dib_info.dib_win20->alto; break;
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT:	imagen->dib_info.dib_winnt->alto = -imagen->dib_info.dib_winnt->alto; break;
	}
}


void quitar_perfil_icc_bmp(IMAGEN_BMP* imagen) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(imagen->dib_info.ver != BMP_DIB_WIN98) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta versión del mapa de bits no es compatible con los espacios de color.");
		return;
	}
	
	if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO || imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO) {
		
		if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO) {
			
			imagen->cabecera.tam_archivo -= imagen->dib_info.dib_win98->tam_perfil;
			free(imagen->perfil_icc);
			imagen->perfil_icc = NULL;
		}
		
		else if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO) {
			
			imagen->cabecera.tam_archivo -= (uint32_t)strlen(imagen->ruta_perfil) + 1;
			free(imagen->ruta_perfil);
			imagen->ruta_perfil = NULL;
		}
		
		memset(&imagen->dib_info.dib_win95->puntos_fin, 0, sizeof(COORDENADAS_COLORES));
		memset(&imagen->dib_info.dib_win95->gamma, 0, sizeof(GAMMA_COLORES));
		imagen->dib_info.dib_win95->tipo_espacio_color = BMP_ECL_sRGB;
	}
	
	imagen->dib_info.dib_win98->dir_perfil = 0;
	imagen->dib_info.dib_win98->tam_perfil = 0;
}


void establecer_ecl_archivo_bmp(IMAGEN_BMP* imagen, const char* ruta_archivo) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(ruta_archivo == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La ruta de perfil especificada está dañada.");
		return;
	}
	
	if(!ruta_archivo[0]) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La ruta de perfil especificada está dañada.");
		return;
	}
	
	if(imagen->dib_info.ver != BMP_DIB_WIN98) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta versión del mapa de bits no es compatible con los perfiles ICC.");
		return;
	}
	
	char* nueva_ruta_perfil = (char*)malloc(strlen(ruta_archivo) + 1);
	if(nueva_ruta_perfil == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para crear la ruta del perfil ICC.");
		return;
	}
	
	quitar_perfil_icc_bmp(imagen);
	imagen->ruta_perfil = nueva_ruta_perfil;
	memset(&imagen->dib_info.dib_win95->puntos_fin, 0, sizeof(COORDENADAS_COLORES));
	memset(&imagen->dib_info.dib_win95->gamma, 0, sizeof(GAMMA_COLORES));
	strcpy(imagen->ruta_perfil, ruta_archivo);
	imagen->cabecera.tam_archivo += (uint32_t)strlen(ruta_archivo) + 1;
	imagen->dib_info.dib_win98->dir_perfil = imagen->cabecera.dir_bitmap + alto_bmp(imagen) * tam_linea(ancho_bmp(imagen), bpp_bmp(imagen)) - sizeof(BMPFILEHEADER);
	imagen->dib_info.dib_win95->tipo_espacio_color = BMP_ECL_ARCHIVO;
}


void establecer_ecl_embedido_bmp(IMAGEN_BMP* imagen, const void* perfil_icc, uint32_t tam_perfil) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(perfil_icc == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "El perfil especificado está dañado.");
		return;
	}
	
	if(!tam_perfil) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "El tamaño del perfil ICC no es válido.");
		return;
	}
	
	if(imagen->dib_info.ver != BMP_DIB_WIN98) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta versión del mapa de bits no es compatible con los perfiles ICC.");
		return;
	}
	
	void* nuevo_perfil = malloc(tam_perfil);
	if(nuevo_perfil == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para crear el perfil ICC.");
		return;
	}
	
	quitar_perfil_icc_bmp(imagen);
	imagen->perfil_icc = nuevo_perfil;
	memset(&imagen->dib_info.dib_win95->puntos_fin, 0, sizeof(COORDENADAS_COLORES));
	memset(&imagen->dib_info.dib_win95->gamma, 0, sizeof(GAMMA_COLORES));
	memcpy(imagen->perfil_icc, perfil_icc, tam_perfil);
	imagen->cabecera.tam_archivo += tam_perfil;
	imagen->dib_info.dib_win98->dir_perfil = imagen->cabecera.dir_bitmap + alto_bmp(imagen) * tam_linea(ancho_bmp(imagen), bpp_bmp(imagen)) - sizeof(BMPFILEHEADER);
	imagen->dib_info.dib_win98->tam_perfil = tam_perfil;
	imagen->dib_info.dib_win95->tipo_espacio_color = BMP_ECL_EMBEDIDO;
}


void establecer_ecl_calibrado_bmp(IMAGEN_BMP* imagen, COORDENADAS_COLORES puntos_fin, GAMMA_COLORES gamma) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(imagen->dib_info.ver < BMP_DIB_WIN95) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta versión del mapa de bits no es compatible con los espacios de color.");
		return;
	}
	
	quitar_perfil_icc_bmp(imagen);
	memcpy(&imagen->dib_info.dib_win95->puntos_fin, &puntos_fin, sizeof(COORDENADAS_COLORES));
	memcpy(&imagen->dib_info.dib_win95->gamma, &gamma, sizeof(GAMMA_COLORES));
	imagen->dib_info.dib_win95->tipo_espacio_color = BMP_ECL_CALIBRADO;
	
	error_bmp_x[0] = 0;
}


void establecer_ecl_generico_bmp(IMAGEN_BMP* imagen, uint32_t espacio_color) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(espacio_color == BMP_ECL_ARCHIVO || espacio_color == BMP_ECL_CALIBRADO || espacio_color == BMP_ECL_EMBEDIDO) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Este espacio de color requiere más parámetros, use la función correcta.");
		return;
	}
	
	if(espacio_color != BMP_ECL_WINDOWS && espacio_color != BMP_ECL_sRGB) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se reconoce el tipo de espacio de color.");
		return;
	}
	
	if(imagen->dib_info.ver < BMP_DIB_WIN95) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta versión del mapa de bits no es compatible con los espacios de color.");
		return;
	}
	
	quitar_perfil_icc_bmp(imagen);
	memset(&imagen->dib_info.dib_win95->puntos_fin, 0, sizeof(COORDENADAS_COLORES));
	memset(&imagen->dib_info.dib_win95->gamma, 0, sizeof(GAMMA_COLORES));
	imagen->dib_info.dib_win95->tipo_espacio_color = espacio_color;
	
	error_bmp_x[0] = 0;
}


void establecer_intencion_renderizado_bmp(IMAGEN_BMP* imagen, uint32_t modo_renderizado) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(modo_renderizado != BMP_IR_ABSCOLOR &&
		modo_renderizado != BMP_IR_NEGOCIOS &&
		modo_renderizado != BMP_IR_GRAFICOS &&
		modo_renderizado != BMP_IR_IMAGENES) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se reconoce la intención de renderizado.");
		return;
	}
	
	if(imagen->dib_info.ver != BMP_DIB_WIN98) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta versión del mapa de bits no incluye la intención de renderizado.");
		return;
	}
	
	imagen->dib_info.dib_win98->modo_renderizado = modo_renderizado;
}


bool mascaras_validas(MASCARAS_BITS mascaras) {
	
	if(!mascaras.rojo && !mascaras.verde && !mascaras.azul && !mascaras.alpha) return true;
	if(mascaras.rojo & mascaras.verde || mascaras.rojo & mascaras.azul || mascaras.rojo & mascaras.alpha ||
		mascaras.verde & mascaras.azul || mascaras.verde & mascaras.alpha ||
		mascaras.azul & mascaras.alpha)
		return false;
	
	uint32_t m = mascaras.rojo | mascaras.verde | mascaras.azul | mascaras.alpha;
	bool ba = m & 1;
	uint8_t c = 0, cp = !ba, x;
	
	for(x = 1, m >>= 1; x < 32; x++, ba = m & 1, m >>= 1) if(ba != (m & 1)) c++;
	if(!ba) cp++;
	
	return !(c > cp);
}


MASCARAS_BITS crear_mascaras(uint32_t rojo, uint32_t verde, uint32_t azul, uint32_t alpha) {
	
	error_bmp_x[0] = 0;
	MASCARAS_BITS mascaras = MASCARAS_VACIAS;
	if(rojo + verde + azul + alpha <= 32) {
		
		uint32_t C;
		for(C = 0; C < rojo; C++) mascaras.rojo |= (1 << C << verde << azul);
		for(C = 0; C < verde; C++) mascaras.verde |= (1 << C << azul);
		for(C = 0; C < azul; C++) mascaras.azul |= (1 << C);
		for(C = 0; C < alpha; C++) mascaras.alpha |= (1 << C << rojo << verde << azul);
	}
	
	snprintf(error_bmp_x, sizeof(error_bmp_x), "La cantidad de bits de las máscaras no pueden exceder 32.");
	return mascaras;
}


IMAGEN_BMP* crear_bmp_vacio(uint32_t ancho, int32_t alto, uint16_t bpp) {
	
	error_bmp_x[0] = 0;
	
	if(bpp != 1 && bpp != 4 && bpp != 8 && bpp != 16 && bpp != 24 && bpp != 32) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La profundidad de color de la imagen no está soportada.");
		return NULL;
	}
	
	IMAGEN_BMP *imagen = (IMAGEN_BMP*)malloc(sizeof(IMAGEN_BMP));
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la estructura de la imagen.");
		return NULL;
	}
	
	imagen->bitmap = NULL;
	imagen->paleta = NULL;
	imagen->bitfields = NULL;
	imagen->ruta_perfil = NULL;
	imagen->perfil_icc = NULL;
	
	imagen->dib_info.dib_win20 = NULL;
	imagen->dib_info.dib_win98 = NULL;
	imagen->dib_info.dib_win95 = NULL;
	imagen->dib_info.dib_winnt = NULL;
	
	imagen->cabecera.tipo			= BMP_TA_BM;
	imagen->cabecera.tam_archivo	= sizeof(BMPFILEHEADER) + BMP_DIB_WINNT + (tam_linea(ancho, bpp) * labs(alto));
	imagen->cabecera.reservado_1	= 0;
	imagen->cabecera.reservado_2	= 0;
	imagen->cabecera.dir_bitmap		= sizeof(BMPFILEHEADER) + BMP_DIB_WINNT;
	
	imagen->dib_info.ver = BMP_DIB_WINNT;
	imagen->dib_info.dib_winnt = (BMPV3HEADER*)malloc(sizeof(BMPV3HEADER));
	if(imagen->dib_info.dib_winnt == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la cabecera DIB.");
		destruir_puntero_bmp(imagen);
		return NULL;
	}
	
	imagen->dib_info.dib_winnt->tam_dib				= BMP_DIB_WINNT;
	imagen->dib_info.dib_winnt->ancho				= ancho;
	imagen->dib_info.dib_winnt->alto				= alto;
	imagen->dib_info.dib_winnt->planos				= 1;
	imagen->dib_info.dib_winnt->bpp					= bpp;
	imagen->dib_info.dib_winnt->compresion			= BMP_MC_RGB;
	imagen->dib_info.dib_winnt->tam_bitmap			= tam_linea(ancho, bpp) * labs(alto);
	imagen->dib_info.dib_winnt->res_horizontal		= 0;
	imagen->dib_info.dib_winnt->res_vertical		= 0;
	imagen->dib_info.dib_winnt->colores				= 0;
	imagen->dib_info.dib_winnt->colores_importantes	= 0;
	
	if(bpp <= 8) {
		
		imagen->dib_info.dib_winnt->colores = 1 << bpp_bmp(imagen);
		imagen->cabecera.dir_bitmap += (4 * (1 << bpp));
		imagen->cabecera.tam_archivo += (4 * (1 << bpp));
		imagen->paleta = (uint32_t*)malloc((1 << bpp) * 4);
		if(imagen->paleta == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para crear la paleta de colores.");
			destruir_puntero_bmp(imagen);
			return NULL;
		}
		
		uint16_t C;
		for(C = 0; C < (1 << bpp); C++) imagen->paleta[C] = bpp == 1 ? colores_std_1[C] : bpp == 4 ? colores_std_4[C] : bpp == 8 ? colores_std_8[C] : 0x000000;
	}
	
	imagen->bitmap = calloc(labs(alto) * tam_linea(ancho, bpp), 1);
	if(imagen->bitmap == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para crear el mapa de bits.");
		destruir_puntero_bmp(imagen);
		return NULL;
	}
	
	return imagen;
}


IMAGEN_BMP* cargar_bmp(const char* ruta_archivo) {
	
	error_bmp_x[0] = 0;
	FILE* archivo_imagen = fopen(ruta_archivo, "rb");
	if(archivo_imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo encontrar el archivo especificado.");
		return NULL;
	}
	
	IMAGEN_BMP *imagen = (IMAGEN_BMP*)malloc(sizeof(IMAGEN_BMP));
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la estructura de la imagen.");
		fclose(archivo_imagen);
		return NULL;
	}
	
	imagen->bitmap = NULL;
	imagen->paleta = NULL;
	imagen->bitfields = NULL;
	imagen->ruta_perfil = NULL;
	imagen->perfil_icc = NULL;
	
	imagen->dib_info.dib_win20 = NULL;
	imagen->dib_info.dib_win98 = NULL;
	imagen->dib_info.dib_win95 = NULL;
	imagen->dib_info.dib_winnt = NULL;
	
	if(!fread(&imagen->cabecera, sizeof(BMPFILEHEADER), 1, archivo_imagen)) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "El archivo especificado está dañado.");
		destruir_puntero_bmp(imagen);
		fclose(archivo_imagen);
		return NULL;
	}
	
	if(imagen->cabecera.tipo != BMP_TA_BM) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Tipo de archivo desconocido.");
		destruir_puntero_bmp(imagen);
		fclose(archivo_imagen);
		return NULL;
	}
	
	fseek(archivo_imagen, 0, SEEK_END);
	if(imagen->cabecera.tam_archivo != ftell(archivo_imagen)) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "El tamaño del archivo no coincide con el de la cabecera del archivo.");
		destruir_puntero_bmp(imagen);
		fclose(archivo_imagen);
		return NULL;
	}
	
	fseek(archivo_imagen, sizeof(BMPFILEHEADER), SEEK_SET);
	if(!fread(&imagen->dib_info.ver, 4, 1, archivo_imagen)) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer la version de la cabecera DIB.");
		destruir_puntero_bmp(imagen);
		fclose(archivo_imagen);
		return NULL;
	}
	
	fseek(archivo_imagen, sizeof(BMPFILEHEADER), SEEK_SET);
	uint32_t tam_bitmap = 0;
	
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20: {
			
			imagen->dib_info.dib_win20 = (BMPV2HEADER*)malloc(sizeof(BMPV2HEADER));
			if(imagen->dib_info.dib_win20 == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la cabecera DIB.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(!fread(imagen->dib_info.dib_win20, sizeof(BMPV2HEADER), 1, archivo_imagen)) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer la cabecera DIB.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(imagen->dib_info.dib_win20->planos != 1) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se admite mas de 1 plano de color.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(imagen->dib_info.dib_win20->bpp != 1 && imagen->dib_info.dib_win20->bpp != 4 && imagen->dib_info.dib_win20->bpp != 8 && imagen->dib_info.dib_win20->bpp != 24) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "La profundidad de color de la imagen no está soportada.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			tam_bitmap = labs(imagen->dib_info.dib_win20->alto) * tam_linea(imagen->dib_info.dib_win20->ancho, imagen->dib_info.dib_win20->bpp);
			
		} break;
		
		
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT: {
			
			imagen->dib_info.dib_winnt = (BMPV3HEADER*)malloc(sizeof(BMPV3HEADER));
			if(imagen->dib_info.dib_winnt == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la cabecera DIB.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(!fread(imagen->dib_info.dib_winnt, sizeof(BMPV3HEADER), 1, archivo_imagen)) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer la cabecera DIB.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(imagen->dib_info.dib_winnt->planos != 1) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se admite mas de 1 plano de color.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(imagen->dib_info.dib_winnt->bpp != 1 && imagen->dib_info.dib_winnt->bpp != 4 && imagen->dib_info.dib_winnt->bpp != 8 && imagen->dib_info.dib_winnt->bpp != 16 && imagen->dib_info.dib_winnt->bpp != 24 && imagen->dib_info.dib_winnt->bpp != 32) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "La profundidad de color de la imagen no está soportada.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(imagen->dib_info.dib_winnt->compresion != BMP_MC_RGB && imagen->dib_info.dib_winnt->compresion != BMP_MC_RLE8 && imagen->dib_info.dib_winnt->compresion != BMP_MC_RLE4 && imagen->dib_info.dib_winnt->compresion != BMP_MC_BITFIELDS) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "Compresión de imagen desconocida.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(imagen->dib_info.dib_winnt->compresion == BMP_MC_BITFIELDS && imagen->dib_info.dib_winnt->bpp != 16 && imagen->dib_info.dib_winnt->bpp != 32) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "Profundidad de color inválida si se están usando máscaras de bits.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if((imagen->dib_info.ver == BMP_DIB_WINNT + 12 || imagen->dib_info.ver == BMP_DIB_WINNT + 16) && imagen->dib_info.dib_winnt->compresion != BMP_MC_BITFIELDS) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "Tamaño de la cabecera DIB inválido si no se usan máscaras de bits.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if(imagen->dib_info.dib_winnt->compresion != BMP_MC_RGB && imagen->dib_info.dib_winnt->compresion != BMP_MC_BITFIELDS && imagen->dib_info.dib_winnt->tam_bitmap == 0) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "El tamaño del mapa de bits no puede ser 0 si está comprimido.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			if((imagen->dib_info.ver == BMP_DIB_WINNT + 12 || imagen->dib_info.ver == BMP_DIB_WINNT + 16) && imagen->dib_info.dib_winnt->compresion != BMP_MC_BITFIELDS) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se puede usar está versión si no se esán usando máscaras de bits.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			tam_bitmap = imagen->dib_info.dib_winnt->compresion != BMP_MC_RGB && imagen->dib_info.dib_winnt->compresion != BMP_MC_BITFIELDS ? imagen->dib_info.dib_winnt->tam_bitmap : (labs(imagen->dib_info.dib_winnt->alto) * tam_linea(imagen->dib_info.dib_winnt->ancho, imagen->dib_info.dib_winnt->bpp));
			
		} break;
		
		
		default: {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "La versión del archivo de imagen no está soportada.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
	}
	
	
	if(imagen->cabecera.dir_bitmap < sizeof(BMPFILEHEADER) + ((imagen->dib_info.ver == BMP_DIB_WINNT + 12 || imagen->dib_info.ver == BMP_DIB_WINNT + 16) ? BMP_DIB_WINNT : imagen->dib_info.ver) +
		(bpp_bmp(imagen) <= 8 ? (imagen->dib_info.ver == BMP_DIB_WIN20 ? 3 : 4) * (1 << bpp_bmp(imagen)) : 0) +
		(compresion_bmp(imagen) == BMP_MC_BITFIELDS && imagen->dib_info.ver < BMP_DIB_WIN95 ? sizeof(MASCARAS_BITS) - (imagen->dib_info.ver != BMP_DIB_WINNT + 16 ? 4 : 0) : 0)) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La dirección de inicio del mapa de bits no es coherente.");
		destruir_puntero_bmp(imagen);
		fclose(archivo_imagen);
		return NULL;
	}
	
	if(compresion_bmp(imagen) == BMP_MC_BITFIELDS || imagen->dib_info.ver >= BMP_DIB_WIN95) {
		
		imagen->bitfields = (MASCARAS_BITS*)calloc(sizeof(MASCARAS_BITS), 1);
		if(imagen->bitfields == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para copiar las máscaras de bits.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
		
		if(fread(imagen->bitfields, 4, (imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12) ? 3 : 4, archivo_imagen) != ((imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12) ? 3 : 4)) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudieron leer las máscaras de bits.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
		
		if(!mascaras_validas(*imagen->bitfields)) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "Las máscaras de bits no son válidas.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
	}
	
	
	if(imagen->dib_info.ver >= BMP_DIB_WIN95) {
		
		imagen->dib_info.dib_win95 = (BMPV4HEADER*)malloc(sizeof(BMPV4HEADER));
		if(imagen->dib_info.dib_win95 == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para cargar la cabecera DIB.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
		
		if(!fread(imagen->dib_info.dib_win95, sizeof(BMPV4HEADER), 1, archivo_imagen)) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer la cabecera DIB.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
		
		if(imagen->dib_info.dib_win95->tipo_espacio_color != BMP_ECL_sRGB &&
			imagen->dib_info.dib_win95->tipo_espacio_color != BMP_ECL_WINDOWS &&
			imagen->dib_info.dib_win95->tipo_espacio_color != BMP_ECL_CALIBRADO &&
			imagen->dib_info.dib_win95->tipo_espacio_color != BMP_ECL_ARCHIVO &&
			imagen->dib_info.dib_win95->tipo_espacio_color != BMP_ECL_EMBEDIDO) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se reconoce el tipo de espacio de color.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
		
		if((imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO || imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO) && imagen->dib_info.ver == BMP_DIB_WIN95) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta cebecera DIB no soporta perfiles de color ICC.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
	}
	
	if(imagen->dib_info.ver == BMP_DIB_WIN98) {
		
		imagen->dib_info.dib_win98 = (BMPV5HEADER*)malloc(sizeof(BMPV5HEADER));
		if(imagen->dib_info.dib_win98 == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para cargar la cabecera DIB.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
		
		if(!fread(imagen->dib_info.dib_win98, sizeof(BMPV5HEADER), 1, archivo_imagen)) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer la cabecera DIB.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
		
		if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO || imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO) {
			
			if(imagen->dib_info.dib_win98->dir_perfil < imagen->cabecera.dir_bitmap + tam_bitmap - sizeof(BMPFILEHEADER)) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "La dirección de inicio del perfil ICC no es válida.");
				destruir_puntero_bmp(imagen);
				fclose(archivo_imagen);
				return NULL;
			}
			
			fseek(archivo_imagen, imagen->dib_info.dib_win98->dir_perfil + sizeof(BMPFILEHEADER), SEEK_SET);
			if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO) {
				
				char temp[4096];
				uint32_t C = 0;
				
				do {
					
					temp[C] = fgetc(archivo_imagen);
					if(temp[C] == EOF) {
						
						snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer la ruta del perfil ICC.");
						destruir_puntero_bmp(imagen);
						fclose(archivo_imagen);
						return NULL;
					}
					
				} while(temp[C++]);
				
				imagen->ruta_perfil = (char*)calloc(++C, 1);
				if(imagen->ruta_perfil == NULL) {
					
					snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para cargar la ruta del perfil ICC.");
					destruir_puntero_bmp(imagen);
					fclose(archivo_imagen);
					return NULL;
				}
				
				strcpy(imagen->ruta_perfil, temp);
			}
			
			else if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO) {
				
				if(imagen->dib_info.dib_win98->tam_perfil == 0) {
					
					snprintf(error_bmp_x, sizeof(error_bmp_x), "El tamaño del perfil ICC no puede ser 0.");
					destruir_puntero_bmp(imagen);
					fclose(archivo_imagen);
					return NULL;
				}
				
				imagen->perfil_icc = malloc(imagen->dib_info.dib_win98->tam_perfil);
				if(imagen->perfil_icc == NULL) {
					
					snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para cargar el perfil ICC.");
					destruir_puntero_bmp(imagen);
					fclose(archivo_imagen);
					return NULL;
				}
				
				if(!fread(imagen->perfil_icc, imagen->dib_info.dib_win98->tam_perfil, 1, archivo_imagen)) {
					
					snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer el perfil ICC.");
					destruir_puntero_bmp(imagen);
					fclose(archivo_imagen);
					return NULL;
				}
			}
		}
	}
	
	
	if(bpp_bmp(imagen) <= 8) {
		
		imagen->paleta = (uint32_t*)malloc(4 * (1 << bpp_bmp(imagen)));
		if(imagen->paleta == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para cargar la paleta de colores.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
		
		fseek(archivo_imagen, sizeof(BMPFILEHEADER) + imagen->dib_info.ver, SEEK_SET);
		if(imagen->dib_info.ver == BMP_DIB_WIN20) {
			
			uint16_t C;
			uint8_t color[3];
			for(C = 0; C < (1 << bpp_bmp(imagen)); C++) {
				
				if(fread(color, 1, 3, archivo_imagen) != 3) {
					
					snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer la paleta de colores.");
					destruir_puntero_bmp(imagen);
					fclose(archivo_imagen);
					return NULL;
				}
				
				imagen->paleta[C] = (color[2] << 16) | (color[1] << 8) | (color[0] << 0);
			}
		}
		
		else if(fread(imagen->paleta, 4, (size_t)(1 << bpp_bmp(imagen)), archivo_imagen) != (size_t)(1 << bpp_bmp(imagen))) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer la paleta de colores.");
			destruir_puntero_bmp(imagen);
			fclose(archivo_imagen);
			return NULL;
		}
	}
	
	
	imagen->bitmap = malloc(tam_bitmap);
	if(imagen->bitmap == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para cargar el mapa de bits.");
		destruir_puntero_bmp(imagen);
		fclose(archivo_imagen);
		return NULL;
	}
	
	fseek(archivo_imagen, imagen->cabecera.dir_bitmap, SEEK_SET);
	if(fread(imagen->bitmap, 1, tam_bitmap, archivo_imagen) != tam_bitmap) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo leer el mapa de bits.");
		destruir_puntero_bmp(imagen);
		fclose(archivo_imagen);
		return NULL;
	}
	
	fclose(archivo_imagen);
	return imagen;
}


void guardar_bmp(IMAGEN_BMP* imagen, const char* ruta_archivo) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	FILE* archivo_imagen = fopen(ruta_archivo, "wb");
	if(archivo_imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo guardar el archivo en la ruta especificada.");
		return;
	}
	
	fwrite(&imagen->cabecera, sizeof(BMPFILEHEADER), 1, archivo_imagen);
	uint32_t tam_bitmap = 0;
	
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20: {
			
			fwrite(imagen->dib_info.dib_win20, sizeof(BMPV2HEADER), 1, archivo_imagen);
			tam_bitmap = labs(imagen->dib_info.dib_win20->alto) * tam_linea(imagen->dib_info.dib_win20->ancho, imagen->dib_info.dib_win20->bpp);
			
		} break;
		
		
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT: {
			
			fwrite(imagen->dib_info.dib_winnt, sizeof(BMPV3HEADER), 1, archivo_imagen);
			tam_bitmap = imagen->dib_info.dib_winnt->compresion != BMP_MC_RGB && imagen->dib_info.dib_winnt->compresion != BMP_MC_BITFIELDS ? imagen->dib_info.dib_winnt->tam_bitmap : (labs(imagen->dib_info.dib_winnt->alto) * tam_linea(imagen->dib_info.dib_winnt->ancho, imagen->dib_info.dib_winnt->bpp));
			
		} break;
	}
	
	if(compresion_bmp(imagen) == BMP_MC_BITFIELDS || imagen->dib_info.ver >= BMP_DIB_WIN95) fwrite(imagen->bitfields, 4, (imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12) ? 3 : 4, archivo_imagen);
	if(imagen->dib_info.ver >= BMP_DIB_WIN95) fwrite(imagen->dib_info.dib_win95, sizeof(BMPV4HEADER), 1, archivo_imagen);
	if(imagen->dib_info.ver == BMP_DIB_WIN98) {
		
		fwrite(imagen->dib_info.dib_win98, sizeof(BMPV5HEADER), 1, archivo_imagen);
		if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO || imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO) {
			
			fseek(archivo_imagen, imagen->dib_info.dib_win98->dir_perfil + sizeof(BMPFILEHEADER), SEEK_SET);
			if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO) fwrite(imagen->ruta_perfil, strlen(imagen->ruta_perfil) + 1, 1, archivo_imagen);
			else if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO) fwrite(imagen->perfil_icc, imagen->dib_info.dib_win98->tam_perfil, 1, archivo_imagen);
		}
	}
	
	if(bpp_bmp(imagen) <= 8) {
		
		fseek(archivo_imagen, sizeof(BMPFILEHEADER) + imagen->dib_info.ver, SEEK_SET);
		if(imagen->dib_info.ver == BMP_DIB_WIN20) {
			
			uint16_t	C;
			uint8_t		color[3];
			for(C = 0; C < (1 << bpp_bmp(imagen)); C++) {
				
				color[0] = imagen->paleta[C] >> 0;
				color[1] = imagen->paleta[C] >> 8;
				color[2] = imagen->paleta[C] >> 16;
				fwrite(color, 1, 3, archivo_imagen);
			}
		}
		
		else fwrite(imagen->paleta, 4, (size_t)(1 << bpp_bmp(imagen)), archivo_imagen);
	}
	
	
	fseek(archivo_imagen, imagen->cabecera.dir_bitmap, SEEK_SET);
	fwrite(imagen->bitmap, 1, tam_bitmap, archivo_imagen);
	
	fclose(archivo_imagen);
}


IMAGEN_BMP* copiar_bmp(IMAGEN_BMP* origen) {
	
	error_bmp_x[0] = 0;
	if(origen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return NULL;
	}
	
	IMAGEN_BMP *imagen = (IMAGEN_BMP*)malloc(sizeof(IMAGEN_BMP));
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para copiar la estructura de la imagen.");
		return NULL;
	}
	
	imagen->bitmap = NULL;
	imagen->paleta = NULL;
	imagen->bitfields = NULL;
	imagen->ruta_perfil = NULL;
	imagen->perfil_icc = NULL;
	
	imagen->dib_info.dib_win20 = NULL;
	imagen->dib_info.dib_win98 = NULL;
	imagen->dib_info.dib_win95 = NULL;
	imagen->dib_info.dib_winnt = NULL;
	
	memcpy(&imagen->cabecera, &origen->cabecera, sizeof(BMPFILEHEADER));
	imagen->dib_info.ver = origen->dib_info.ver;
	uint32_t tam_bitmap = 0;
	
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20: {
			
			imagen->dib_info.dib_win20 = (BMPV2HEADER*)malloc(sizeof(BMPV2HEADER));
			if(imagen->dib_info.dib_win20 == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para copiar la cabecera DIB.");
				destruir_puntero_bmp(imagen);
				return NULL;
			}
			
			memcpy(imagen->dib_info.dib_win20, origen->dib_info.dib_win20, sizeof(BMPV2HEADER));
			tam_bitmap = labs(imagen->dib_info.dib_win20->alto) * tam_linea(imagen->dib_info.dib_win20->ancho, imagen->dib_info.dib_win20->bpp);
			
		} break;
		
		
		case BMP_DIB_WIN98: {
			
			imagen->dib_info.dib_win98 = (BMPV5HEADER*)malloc(sizeof(BMPV5HEADER));
			if(imagen->dib_info.dib_win98 == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para copiar la cabecera DIB.");
				destruir_puntero_bmp(imagen);
				return NULL;
			}
			
			memcpy(imagen->dib_info.dib_win98, origen->dib_info.dib_win98, sizeof(BMPV5HEADER));
		}
		
		
		case BMP_DIB_WIN95: {
			
			imagen->dib_info.dib_win95 = (BMPV4HEADER*)malloc(sizeof(BMPV4HEADER));
			if(imagen->dib_info.dib_win95 == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para copiar la cabecera DIB.");
				destruir_puntero_bmp(imagen);
				return NULL;
			}
			
			memcpy(imagen->dib_info.dib_win95, origen->dib_info.dib_win95, sizeof(BMPV4HEADER));
			
			if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO) {
				
				imagen->ruta_perfil = (char*)calloc(strlen(origen->ruta_perfil) + 1, 1);
				if(imagen->ruta_perfil == NULL) {
					
					snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para copiar la ruta del perfil ICC.");
					destruir_puntero_bmp(imagen);
					return NULL;
				}
				
				strcpy(imagen->ruta_perfil, origen->ruta_perfil);
			}
			
			else if(imagen->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_EMBEDIDO) {
				
				imagen->perfil_icc = malloc(imagen->dib_info.dib_win98->tam_perfil);
				if(imagen->perfil_icc == NULL) {
					
					snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para copiar el perfil ICC.");
					destruir_puntero_bmp(imagen);
					return NULL;
				}
				
				memcpy(imagen->perfil_icc, origen->perfil_icc, imagen->dib_info.dib_win98->tam_perfil);
			}
		}
		
		
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT: {
			
			imagen->dib_info.dib_winnt = (BMPV3HEADER*)malloc(sizeof(BMPV3HEADER));
			if(imagen->dib_info.dib_winnt == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para copiar la cabecera DIB.");
				destruir_puntero_bmp(imagen);
				return NULL;
			}
			
			memcpy(imagen->dib_info.dib_winnt, origen->dib_info.dib_winnt, sizeof(BMPV3HEADER));
			tam_bitmap = imagen->dib_info.dib_winnt->compresion != BMP_MC_RGB && imagen->dib_info.dib_winnt->compresion != BMP_MC_BITFIELDS ? imagen->dib_info.dib_winnt->tam_bitmap : (labs(imagen->dib_info.dib_winnt->alto) * tam_linea(imagen->dib_info.dib_winnt->ancho, imagen->dib_info.dib_winnt->bpp));
			
		} break;
	}
	
	
	if(compresion_bmp(imagen) == BMP_MC_BITFIELDS || imagen->dib_info.ver >= BMP_DIB_WIN95) {
		
		imagen->bitfields = (MASCARAS_BITS*)malloc(sizeof(MASCARAS_BITS));
		if(imagen->bitfields == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para copiar las máscaras de bits.");
			destruir_puntero_bmp(imagen);
			return NULL;
		}
		
		memcpy(imagen->bitfields, origen->bitfields, sizeof(MASCARAS_BITS));
	}
	
	
	if(bpp_bmp(imagen) <= 8) {
		
		imagen->paleta = (uint32_t*)malloc(4 * (1 << bpp_bmp(imagen)));
		if(imagen->paleta == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para copiar la paleta de colores.");
			destruir_puntero_bmp(imagen);
			return NULL;
		}
		
		memcpy(imagen->paleta, origen->paleta, (1 << bpp_bmp(imagen)) * 4);
	}
	
	
	imagen->bitmap = malloc(tam_bitmap);
	if(imagen->bitmap == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para copiar el mapa de bits.");
		destruir_puntero_bmp(imagen);
		return NULL;
	}
	
	memcpy(imagen->bitmap, origen->bitmap, tam_bitmap);
	
	return imagen;
}


void compresion_rle_bmp(IMAGEN_BMP* imagen) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(imagen->dib_info.ver == BMP_DIB_WIN20) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta versión de mapa de bits no soporta la compresión RLE.");
		return;
	}
	
	if(bpp_bmp(imagen) != 4 && bpp_bmp(imagen) != 8) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La compresión RLE solo aplica para mapas de bits de 4 u 8 bpp.");
		return;
	}
	
	if(alto_bmp(imagen) < 0) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pueden comprimir mapas de bits de altura negativa.");
		return;
	}
	
	if(compresion_bmp(imagen) != BMP_MC_RGB && compresion_bmp(imagen) != BMP_MC_RLE4 && compresion_bmp(imagen) != BMP_MC_RLE8) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se reconoce la compresión actual.");
		return;
	}
	
	uint8_t *entrada = (uint8_t*)imagen->bitmap;
	uint32_t X = 0, Y = 0;
	uint32_t Xo = 0, linea, tam_linea_bmp = tam_linea(ancho_bmp(imagen), bpp_bmp(imagen));
	uint8_t *bitmap_comprimido = NULL;
	uint32_t compresion;
	
	if(compresion_bmp(imagen) != BMP_MC_RGB) {
		
		compresion = BMP_MC_RGB;
		uint8_t fin = 0;
		uint8_t C;
		bitmap_comprimido = (uint8_t*)calloc(alto_bmp(imagen) * tam_linea_bmp, 1);
		if(bitmap_comprimido == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para el mapa de bits comprimido.");
			return;
		}
		
		switch(compresion_bmp(imagen)) {
			
			case BMP_MC_RLE8: {
				
				while(!fin) {
					
					if(entrada[Xo] > 0) for(C = 0; C < entrada[Xo]; C++, X++) bitmap_comprimido[Y * tam_linea_bmp + X] = entrada[Xo + 1];
					else {
						
						switch(entrada[Xo + 1]) {
							
							case 0: {
								
								Y++;
								X = 0;
								
							} break;
							
							
							case 1: fin = 1; break;
							
							case 2: {
								
								X += entrada[Xo + 2];
								Y += entrada[Xo + 3];
								Xo += 2;
								
							} break;
							
							
							default: {
								
								for(C = 0; C < entrada[Xo + 1]; C++, X++) bitmap_comprimido[Y * tam_linea_bmp + X] = entrada[Xo + 2 + C];
								while(C % 2) C++;
								Xo += C;
							}
						}
					}
					
					Xo += 2;
				}
				
			} break;
			
			
			case BMP_MC_RLE4: {
				
				while(!fin) {
					
					if(entrada[Xo] > 0) for(C = 0; C < entrada[Xo]; C++, X++) bitmap_comprimido[Y * tam_linea_bmp + X / 2] |= (((entrada[Xo + 1] >> (C % 2 ? 0 : 4)) % 0x10) << (X % 2 ? 0 : 4));
					else {
						
						switch(entrada[Xo + 1]) {
							
							case 0: {
								
								Y++;
								X = 0;
								
							} break;
							
							
							case 1: fin = 1; break;
							
							case 2: {
								
								X += entrada[Xo + 2];
								Y += entrada[Xo + 3];
								Xo += 2;
								
							} break;
							
							
							default: {
								
								for(C = 0; C < entrada[Xo + 1]; C++, X++) bitmap_comprimido[Y * tam_linea_bmp + X / 2] |= (((entrada[Xo + 2 + C / 2] >> (C % 2 ? 0 : 4)) % 0x10) << (X % 2 ? 0 : 4));
								while(C % 4) C++;
								Xo += C / 2;
							}
						}
					}
					
					Xo += 2;
				}
				
			} break;
		}
		
		Xo = alto_bmp(imagen) * tam_linea_bmp;
	}
	
	else {
		
		if(bpp_bmp(imagen) == 8) {
			
			compresion = BMP_MC_RLE8;
			bitmap_comprimido = (uint8_t*)malloc(2 * alto_bmp(imagen) * (ancho_bmp(imagen) + 1));
			if(bitmap_comprimido == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para el mapa de bits comprimido.");
				return;
			}
			
			uint8_t C, C2, pixel, Ca;
			
			for(Y = linea = 0, X = 0; Y < (uint32_t)alto_bmp(imagen); Y++, X = 0, linea = Y * tam_linea_bmp) {
				
				while(X < ancho_bmp(imagen)) {
					
					Ca = 0;
					
					do {
						
						C = 1;
						pixel = entrada[linea + X];
						X++;
						
						while(X < ancho_bmp(imagen) && pixel == entrada[linea + X] && C < 255) {
							
							C++;
							X++;
						}
						
						if(C == 1) Ca++;
						
					} while (C == 1 && Ca < 255 && X < ancho_bmp(imagen));
					
					if(Ca >= 3) {
						
						if(C > 1) X -= C;
						bitmap_comprimido[Xo] = 0;
						Xo++;
						bitmap_comprimido[Xo] = Ca;
						Xo++;
						
						for(C2 = 0; C2 < Ca; C2++, Xo++) bitmap_comprimido[Xo] = entrada[linea + X - Ca + C2];
						while(C2 % 2) {
							
							bitmap_comprimido[Xo] = 0;
							Xo++;
							C2++;
						}
					}
					
					else if(Ca > 0) {
						
						if(C > 1) X -= C;
						for(C2 = 0; C2 < Ca; C2++) {
							
							bitmap_comprimido[Xo] = 1;
							Xo++;
							bitmap_comprimido[Xo] = entrada[linea + X - Ca + C2];
							Xo++;
						}
					}
					
					if(C > 1) {
						
						if(Ca > 0) X += C;
						bitmap_comprimido[Xo] = C;
						Xo++;
						bitmap_comprimido[Xo] = pixel;
						Xo++;
					}
				}
				
				bitmap_comprimido[Xo] = 0;
				Xo++;
				bitmap_comprimido[Xo] = 0;
				Xo++;
			}
			
			bitmap_comprimido[Xo - 1] = 1;
		}
		
		else {
			
			compresion = BMP_MC_RLE4;
			bitmap_comprimido = (uint8_t*)malloc(2 * alto_bmp(imagen) * (ancho_bmp(imagen) + 1));
			if(bitmap_comprimido == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para el mapa de bits comprimido.");
				return;
			}
			
			uint8_t C, C2, pixel, Ca;
			
			for(Y = linea = 0, X = 0; Y < (uint32_t)alto_bmp(imagen); Y++, X = 0, linea = Y * tam_linea_bmp) {
				
				while(X < ancho_bmp(imagen)) {
					
					Ca = 0;
					
					do {
						
						C = 2;
						pixel = ((entrada[linea + (X + 1) / 2] >> (X % 2 != 0 ? 4 : 0)) % 0x10) | (((entrada[linea + X / 2] >> (X % 2 ? 0 : 4)) % 0x10) << 4);
						X += 2;
						
						while(X < ancho_bmp(imagen) && C < 255 && ((pixel >> (C % 2 == 0 ? 4 : 0)) % 0x10) == ((entrada[linea + X / 2] >> (X % 2 ? 0 : 4)) % 0x10)) {
							
							C++;
							X++;
						}
						
						if(C == 2) Ca++;
						
					} while (C == 2 && Ca < 127 && X < ancho_bmp(imagen));
					
					if(Ca > 1) {
						
						if(C > 2) X -= C;
						bitmap_comprimido[Xo] = 0;
						Xo++;
						bitmap_comprimido[Xo] = Ca * 2;
						Xo++;
						
						for(C2 = 0; C2 < Ca; C2++, Xo++) bitmap_comprimido[Xo] = ((entrada[linea + (X + 1) / 2 - Ca + C2] >> (X % 2 ? 4 : 0)) % 0x10) | (((entrada[linea + X / 2 - Ca + C2] >> (X % 2 ? 0 : 4)) % 0x10) << 4);
						while(C2 % 2) {
							
							bitmap_comprimido[Xo] = 0;
							Xo++;
							C2++;
						}
					}
					
					else if(Ca > 0) {
						
						if(C > 2) X -= C;
						bitmap_comprimido[Xo] = 2;
						Xo++;
						bitmap_comprimido[Xo] = ((entrada[linea + (X + 1) / 2 - 1] >> (X % 2 ? 4 : 0)) % 0x10) | (((entrada[linea + X / 2 - 1] >> (X % 2 ? 0 : 4)) % 0x10) << 4);
						Xo++;
					}
					
					if(C > 2) {
						
						if(Ca > 0) X += C;
						bitmap_comprimido[Xo] = C;
						Xo++;
						bitmap_comprimido[Xo] = pixel;
						Xo++;
					}
				}
				
				bitmap_comprimido[Xo] = 0;
				Xo++;
				bitmap_comprimido[Xo] = 0;
				Xo++;
			}
			
			bitmap_comprimido[Xo - 1] = 1;
		}
	}
	
	void* bitmap_nuevo = malloc(Xo);
	if(bitmap_nuevo == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para el nuevo mapa de bits.");
		free(bitmap_comprimido);
		return;
	}
	
	free(imagen->bitmap);
	imagen->bitmap = bitmap_nuevo;
	memcpy(imagen->bitmap, bitmap_comprimido, Xo);
	free(bitmap_comprimido);
	
	imagen->cabecera.tam_archivo -= imagen->dib_info.dib_winnt->tam_bitmap - Xo;
	imagen->dib_info.dib_winnt->compresion = compresion;
	imagen->dib_info.dib_winnt->tam_bitmap = Xo;
}


void cambiar_formato_pixel_bmp(IMAGEN_BMP* imagen, uint16_t bpp, MASCARAS_BITS mascaras) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen esá dañada.");
		return;
	}
	
	if(bpp != 16 && bpp != 24 && bpp != 32) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se puede cambiar el formato de color a esta nueva profundidad.");
		return;
	}
	
	if(!mascaras_validas(mascaras)) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Las máscaras de bits no son válidas.");
		return;
	}
	
	MASCARAS_BITS *dummy = (MASCARAS_BITS*)calloc(sizeof(MASCARAS_BITS), 1);
	if(dummy == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para comparar las máscaras de bits.");
		return;
	}
	
	if(compresion_bmp(imagen) == BMP_MC_BITFIELDS) { if(bpp_bmp(imagen) == bpp && !memcmp(imagen->bitfields, &mascaras, sizeof(MASCARAS_BITS))) return; }
	else if(bpp_bmp(imagen) == bpp && !memcmp(dummy, &mascaras, sizeof(MASCARAS_BITS))) return;
	
	if(memcmp(&mascaras, dummy, sizeof(MASCARAS_BITS)) && bpp != 32 && (mascaras.rojo >= (1U << bpp) || mascaras.verde >= (1U << bpp) || mascaras.azul >= (1U << bpp) || mascaras.alpha >= (1U << bpp))) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Las máscaras de bits nuevas son incompatibles con la profundidad de color.");
		free(dummy);
		return;
	}
	
	if(imagen->dib_info.ver == BMP_DIB_WIN20 && bpp != 24) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "Esta versián de archivo solo soporta una resolución de 24 bpp.");
		free(dummy);
		return;
	}
	
	if(compresion_bmp(imagen) == BMP_MC_RLE4 || compresion_bmp(imagen) == BMP_MC_RLE8) {
		
		compresion_rle_bmp(imagen);
		if(compresion_bmp(imagen) != BMP_MC_RGB) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo descomprimir el mapa de bits para su conversión.");
			free(dummy);
			return;
		}
	}
	
	MASCARAS_BITS *mascaras_nuevas = (MASCARAS_BITS*)malloc(sizeof(MASCARAS_BITS));
	if(mascaras_nuevas == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para las nuevas máscaras de bits.");
		free(dummy);
		return;
	}
	
	*mascaras_nuevas = bpp == 16 ? RGB555 : RGB888;
	if(memcmp(&mascaras, dummy, sizeof(MASCARAS_BITS)) && bpp != 24) memcpy(mascaras_nuevas, &mascaras, sizeof(MASCARAS_BITS));
	void* bitmap_nuevo;
	uint32_t pixel, *paleta_nueva = NULL, compresion = !memcmp(&mascaras, dummy, sizeof(MASCARAS_BITS)) || bpp == 24 ? BMP_MC_RGB : BMP_MC_BITFIELDS;
	uint8_t rr_v, rg_v, rb_v, ra_v, rr_n, rg_n, rb_n, ra_n;
	uint32_t X, Y, bit, bit_nuevo, C, linea_vieja, linea_nueva, tam_linea_viejo, tam_linea_nuevo, num_colores_viejo;
	free(dummy);
	
	tam_linea_viejo = tam_linea(ancho_bmp(imagen), bpp_bmp(imagen));
	tam_linea_nuevo = tam_linea(ancho_bmp(imagen), bpp);
	if(!(bpp_bmp(imagen) % 16)) tam_linea_viejo /= bpp_bmp(imagen) / 8;
	if(!(bpp % 16)) tam_linea_nuevo /= bpp / 8;
	num_colores_viejo = bpp_bmp(imagen) <= 8 ? 1 << bpp_bmp(imagen) : 0;
	
	MASCARAS_BITS mascaras_viejas;
	if(compresion_bmp(imagen) == BMP_MC_RGB) mascaras_viejas = bpp_bmp(imagen) == 16 ? RGB555 : RGB888;
	else memcpy(&mascaras_viejas, imagen->bitfields, sizeof(MASCARAS_BITS));
	bitmap_nuevo = calloc(tam_linea(ancho_bmp(imagen), bpp) * labs(alto_bmp(imagen)), 1);
	if(bitmap_nuevo == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para crear el nuevo mapa de bits.");
		return;
	}
	
	rr_v = rg_v = rb_v = ra_v = rr_n = rg_n = rb_n = ra_n = 0;
	if(mascaras_viejas.rojo && !(mascaras_viejas.rojo & 1)) while(!((mascaras_viejas.rojo >> ++rr_v) & 1));
	if(mascaras_viejas.verde && !(mascaras_viejas.verde & 1)) while(!((mascaras_viejas.verde >> ++rg_v) & 1));
	if(mascaras_viejas.azul && !(mascaras_viejas.azul & 1)) while(!((mascaras_viejas.azul >> ++rb_v) & 1));
	if(mascaras_viejas.alpha && !(mascaras_viejas.alpha & 1)) while(!((mascaras_viejas.alpha >> ++ra_v) & 1));
	
	if(mascaras_nuevas->rojo && !(mascaras_nuevas->rojo & 1)) while(!((mascaras_nuevas->rojo >> ++rr_n) & 1));
	if(mascaras_nuevas->verde && !(mascaras_nuevas->verde & 1)) while(!((mascaras_nuevas->verde >> ++rg_n) & 1));
	if(mascaras_nuevas->azul && !(mascaras_nuevas->azul & 1)) while(!((mascaras_nuevas->azul >> ++rb_n) & 1));
	if(mascaras_nuevas->alpha && !(mascaras_nuevas->alpha & 1)) while(!((mascaras_nuevas->alpha >> ++ra_n) & 1));
	
	if(bpp_bmp(imagen) <= 8) {
		
		paleta_nueva = (uint32_t*)malloc(num_colores_viejo * 4);
		if(paleta_nueva == NULL) {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para crear la paleta modificada.");
			free(bitmap_nuevo);
			return;
		}
		
		for(X = 0; X < num_colores_viejo; X++) paleta_nueva[X] =
			(!mascaras_nuevas->rojo ? 0 : (uint32_t)round((double)((imagen->paleta[X] & 0xFF0000) >> 16) * (mascaras_nuevas->rojo >> rr_n) / 0xFF) << rr_n) |
			(!mascaras_nuevas->verde ? 0 : (uint32_t)round((double)((imagen->paleta[X] & 0x00FF00) >> 8) * (mascaras_nuevas->verde >> rg_n) / 0xFF) << rg_n) |
			(!mascaras_nuevas->azul ? 0 : (uint32_t)round((double)((imagen->paleta[X] & 0x0000FF) >> 0) * (mascaras_nuevas->azul >> rb_n) / 0xFF) << rb_n) |
			(mascaras_nuevas->alpha);
		
		free(imagen->paleta);
		imagen->paleta = NULL;
		imagen->cabecera.tam_archivo -= (1 << bpp_bmp(imagen)) * (imagen->dib_info.ver == BMP_DIB_WIN20 ? 3 : 4);
		imagen->cabecera.dir_bitmap -= (1 << bpp_bmp(imagen)) * (imagen->dib_info.ver == BMP_DIB_WIN20 ? 3 : 4);
	}
	
	for(Y = linea_vieja = linea_nueva = 0; Y < (uint32_t)labs(alto_bmp(imagen)); Y++, linea_vieja = Y * tam_linea_viejo, linea_nueva = Y * tam_linea_nuevo) {
		
		for(X = bit = bit_nuevo = 0; X < ancho_bmp(imagen); X++, bit = X * bpp_bmp(imagen), bit_nuevo = X * bpp) {
			
			switch(bpp_bmp(imagen)) {
				
				case 32: pixel = ((uint32_t*)imagen->bitmap)[linea_vieja + X]; break;
				case 24: for(C = 0, pixel = 0; C < 3; C++) pixel |= ((uint8_t*)imagen->bitmap)[linea_vieja + X * 3 + C] << (C * 8); break;
				case 16: pixel = ((uint16_t*)imagen->bitmap)[linea_vieja + X]; break;
				default: pixel = paleta_nueva[(((uint8_t*)imagen->bitmap)[linea_vieja + (bit / 8)] >> (((bit + 8) & ~7) - bit - bpp_bmp(imagen))) % num_colores_viejo];
			}
			
			if(bpp_bmp(imagen) > 8) {
				
				pixel =
					((!mascaras_nuevas->rojo || !mascaras_viejas.rojo) ? 0 : (uint32_t)round((double)((pixel & mascaras_viejas.rojo) >> rr_v) * (mascaras_nuevas->rojo >> rr_n) / (mascaras_viejas.rojo >> rr_v)) << rr_n) |
					((!mascaras_nuevas->verde || !mascaras_viejas.verde) ? 0 : (uint32_t)round((double)((pixel & mascaras_viejas.verde) >> rg_v) * (mascaras_nuevas->verde >> rg_n) / (mascaras_viejas.verde >> rg_v)) << rg_n) |
					((!mascaras_nuevas->azul || !mascaras_viejas.azul) ? 0 : (uint32_t)round((double)((pixel & mascaras_viejas.azul) >> rb_v) * (mascaras_nuevas->azul >> rb_n) / (mascaras_viejas.azul >> rb_v)) << rb_n) |
					(!mascaras_viejas.alpha ? mascaras_nuevas->alpha : (uint32_t)ceil((double)((pixel & mascaras_viejas.alpha) >> ra_v) * (mascaras_nuevas->alpha >> ra_n) / (mascaras_viejas.alpha >> ra_v)) << ra_n);
			}
			
			switch(bpp) {
				
				case 32: ((uint32_t*)bitmap_nuevo)[linea_nueva + X] = pixel; break;
				case 24: for(C = 0; C < 3; C++) ((uint8_t*)bitmap_nuevo)[linea_nueva + X * 3 + C] |= (uint8_t)(pixel >> (C * 8)); break;
				case 16: ((uint16_t*)bitmap_nuevo)[linea_nueva + X] = pixel; break;
			}
		}
	}
	
	if(paleta_nueva != NULL) free(paleta_nueva);
	free(imagen->bitmap);
	imagen->bitmap = bitmap_nuevo;
	if(compresion_bmp(imagen) == BMP_MC_BITFIELDS && imagen->dib_info.ver < BMP_DIB_WIN95) {
		
		free(imagen->bitfields);
		imagen->bitfields = NULL;
		if(imagen->cabecera.tam_archivo) imagen->cabecera.tam_archivo -= sizeof(MASCARAS_BITS) - ((imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12) ? 4 : 0);
		imagen->cabecera.dir_bitmap -= sizeof(MASCARAS_BITS) - ((imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12) ? 4 : 0);
	}
	
	if(compresion == BMP_MC_BITFIELDS) {
		
		if(imagen->dib_info.ver == BMP_DIB_WINNT + 12 || imagen->dib_info.ver == BMP_DIB_WINNT + 16 || imagen->dib_info.ver == BMP_DIB_WINNT) imagen->dib_info.ver = BMP_DIB_WINNT + (mascaras_nuevas->alpha ? 16 : 0);
		imagen->bitfields = mascaras_nuevas;
		if(imagen->dib_info.ver < BMP_DIB_WIN95) {
			
			if(imagen->cabecera.tam_archivo) imagen->cabecera.tam_archivo += sizeof(MASCARAS_BITS) - ((imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12) ? 4 : 0);
			imagen->cabecera.dir_bitmap += sizeof(MASCARAS_BITS) - ((imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12) ? 4 : 0);
		}
	}
	
	else if(imagen->dib_info.ver == BMP_DIB_WINNT + 12 || imagen->dib_info.ver == BMP_DIB_WINNT + 16) imagen->dib_info.ver = BMP_DIB_WINNT;
	
	if(imagen->cabecera.tam_archivo) imagen->cabecera.tam_archivo -= labs(alto_bmp(imagen)) * tam_linea(ancho_bmp(imagen), bpp_bmp(imagen));
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20: {
			
			imagen->dib_info.dib_win20->bpp = bpp;
			
		} break;
		
		case BMP_DIB_WIN98:
		case BMP_DIB_WIN95:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT: {
			
			imagen->dib_info.dib_winnt->tam_dib = imagen->dib_info.ver;
			imagen->dib_info.dib_winnt->bpp = bpp;
			imagen->dib_info.dib_winnt->compresion = compresion;
			imagen->dib_info.dib_winnt->tam_bitmap = labs(imagen->dib_info.dib_winnt->alto) * tam_linea(imagen->dib_info.dib_winnt->ancho, bpp);
			
		} break;
	}
	
	if(imagen->cabecera.tam_archivo) imagen->cabecera.tam_archivo += labs(alto_bmp(imagen)) * tam_linea(ancho_bmp(imagen), bpp_bmp(imagen));
}


void convertir_dib_bmp(IMAGEN_BMP* imagen, uint32_t tipo_dib) {
	
	error_bmp_x[0] = 0;
	if(imagen == NULL) {
		
		snprintf(error_bmp_x, sizeof(error_bmp_x), "La imagen de origen está dañada.");
		return;
	}
	
	if(imagen->dib_info.ver == tipo_dib) return;
	if((imagen->dib_info.ver == BMP_DIB_WINNT || imagen->dib_info.ver == BMP_DIB_WINNT + 12 || imagen->dib_info.ver == BMP_DIB_WINNT + 16) && tipo_dib == BMP_DIB_WINNT) return;
	
	switch(tipo_dib) {
		
		case BMP_DIB_WIN20: {
			
			if(compresion_bmp(imagen) != BMP_MC_RGB) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "Un mapa de bits comprimido no puede pasar a esta versión.");
				return;
			}
			
			if(bpp_bmp(imagen) > 24 || bpp_bmp(imagen) == 16) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "La profundidad de color actual no es compatible para la nueva cabecera.");
				return;
			}
			
			BMPV2HEADER *nuevo_dib_win20 = (BMPV2HEADER*)malloc(sizeof(BMPV2HEADER));
			if(nuevo_dib_win20 == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la nueva cabecera DIB.");
				return;
			}
			
			nuevo_dib_win20->tam_dib = tipo_dib;
			nuevo_dib_win20->ancho = ancho_bmp(imagen);
			nuevo_dib_win20->alto = alto_bmp(imagen);
			nuevo_dib_win20->planos = planos_bmp(imagen);
			nuevo_dib_win20->bpp = bpp_bmp(imagen);
			
			if(bpp_bmp(imagen) <= 8) {
				
				imagen->cabecera.tam_archivo -= 1 << bpp_bmp(imagen);
				imagen->cabecera.dir_bitmap -= 1 << bpp_bmp(imagen);
			}
			
			imagen->dib_info.dib_win20 = nuevo_dib_win20;
			if(compresion_bmp(imagen) == BMP_MC_BITFIELDS || imagen->dib_info.ver >= BMP_DIB_WIN95) {
				
				free(imagen->bitfields);
				imagen->bitfields = NULL;
			}
			
		} break;
		
		
		case BMP_DIB_WIN98: {
			
			BMPV5HEADER *nuevo_dib_win98 = (BMPV5HEADER*)calloc(sizeof(BMPV5HEADER), 1);
			if(nuevo_dib_win98 == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la nueva cabecera DIB.");
				return;
			}
			
			nuevo_dib_win98->modo_renderizado = BMP_IR_GRAFICOS;
			imagen->dib_info.dib_win98 = nuevo_dib_win98;
		}
		
		
		case BMP_DIB_WIN95: {
			
			if(imagen->dib_info.ver >= BMP_DIB_WIN95) {
				
				imagen->dib_info.dib_winnt->tam_dib = tipo_dib;
				break;
			}
			
			BMPV4HEADER *nuevo_dib_win95 = (BMPV4HEADER*)calloc(sizeof(BMPV4HEADER), 1);
			if(nuevo_dib_win95 == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la nueva cabecera DIB.");
				if(imagen->dib_info.dib_win98 != NULL) free(imagen->dib_info.dib_win98);
				return;
			}
			
			nuevo_dib_win95->tipo_espacio_color = BMP_ECL_sRGB;
			if(compresion_bmp(imagen) != BMP_MC_BITFIELDS) {
				
				imagen->bitfields = (MASCARAS_BITS*)calloc(sizeof(MASCARAS_BITS), 1);
				if(imagen->bitfields == NULL) {
					
					snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria necesaria para las máscaras de bits.");
					if(imagen->dib_info.dib_win98 != NULL) free(imagen->dib_info.dib_win98);
					return;
				}
			}
			
			imagen->dib_info.dib_win95 = nuevo_dib_win95;
		}
		
		
		case BMP_DIB_WINNT: {
			
			if(tipo_dib == BMP_DIB_WINNT && compresion_bmp(imagen) == BMP_MC_BITFIELDS) if(imagen->bitfields->alpha) tipo_dib += 16;
			if(imagen->dib_info.ver >= BMP_DIB_WINNT) {
				
				imagen->dib_info.dib_winnt->tam_dib = tipo_dib;
				break;
			}
			
			BMPV3HEADER *nuevo_dib_winnt = (BMPV3HEADER*)malloc(sizeof(BMPV3HEADER));
			if(nuevo_dib_winnt == NULL) {
				
				snprintf(error_bmp_x, sizeof(error_bmp_x), "No se pudo asignar la memoria para la nueva cabecera DIB.");
				if(imagen->dib_info.dib_win98 != NULL) free(imagen->dib_info.dib_win98);
				if(imagen->dib_info.dib_win95 != NULL) free(imagen->dib_info.dib_win95);
				return;
			}
			
			nuevo_dib_winnt->tam_dib = tipo_dib;
			nuevo_dib_winnt->ancho = ancho_bmp(imagen);
			nuevo_dib_winnt->alto = alto_bmp(imagen);
			nuevo_dib_winnt->planos = planos_bmp(imagen);
			nuevo_dib_winnt->bpp = bpp_bmp(imagen);
			nuevo_dib_winnt->compresion = compresion_bmp(imagen);
			nuevo_dib_winnt->tam_bitmap = alto_bmp(imagen) * tam_linea(ancho_bmp(imagen), bpp_bmp(imagen));
			nuevo_dib_winnt->res_horizontal = 0;
			nuevo_dib_winnt->res_vertical = 0;
			nuevo_dib_winnt->colores = bpp_bmp(imagen) > 8 ? 0 : (1 << bpp_bmp(imagen));
			nuevo_dib_winnt->colores_importantes = 0;
			
			imagen->dib_info.dib_winnt = nuevo_dib_winnt;
			
		} break;
		
		
		default: {
			
			snprintf(error_bmp_x, sizeof(error_bmp_x), "Versión de cabecera DIB desconocida.");
			return;
		}
	}
	
	
	switch(imagen->dib_info.ver) {
		
		case BMP_DIB_WIN20: {
			
			if(bpp_bmp(imagen) <= 8) {
				
				imagen->cabecera.tam_archivo += 1 << bpp_bmp(imagen);
				imagen->cabecera.dir_bitmap += 1 << bpp_bmp(imagen);
			}
			
			free(imagen->dib_info.dib_win20);
			imagen->dib_info.dib_win20 = NULL;
			
		} break;
		
		
		case BMP_DIB_WIN98: {
			
			quitar_perfil_icc_bmp(imagen);
			free(imagen->dib_info.dib_win98);
			imagen->dib_info.dib_win98 = NULL;
		}
		
		
		case BMP_DIB_WIN95: {
			
			if(tipo_dib >= BMP_DIB_WIN95) break;
			free(imagen->dib_info.dib_win95);
			imagen->dib_info.dib_win95 = NULL;
		}
		
		
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT: {
			
			if(imagen->dib_info.ver == BMP_DIB_WINNT && compresion_bmp(imagen) == BMP_MC_BITFIELDS) imagen->dib_info.ver += imagen->bitfields->alpha ? 16 : 12;
			if(tipo_dib >= BMP_DIB_WINNT) break;
			free(imagen->dib_info.dib_winnt);
			imagen->dib_info.dib_winnt = NULL;
			
		} break;
	}
	
	if(tipo_dib == BMP_DIB_WINNT && compresion_bmp(imagen) == BMP_MC_BITFIELDS) tipo_dib += 12;
	imagen->cabecera.tam_archivo -= imagen->dib_info.ver - tipo_dib;
	imagen->cabecera.dir_bitmap -= imagen->dib_info.ver - tipo_dib;
	imagen->dib_info.ver = tipo_dib == BMP_DIB_WINNT + 12 ? BMP_DIB_WINNT : tipo_dib;
}


void destruir_puntero_bmp(IMAGEN_BMP* imagen) {
	
	if(imagen == NULL) return;
	
	if(imagen->bitmap != NULL) free(imagen->bitmap);
	if(imagen->paleta != NULL) free(imagen->paleta);
	if(imagen->bitfields != NULL) free(imagen->bitfields);
	if(imagen->ruta_perfil != NULL) free(imagen->ruta_perfil);
	if(imagen->perfil_icc != NULL) free(imagen->perfil_icc);
	
	if(imagen->dib_info.dib_win20 != NULL) free(imagen->dib_info.dib_win20);
	if(imagen->dib_info.dib_win98 != NULL) free(imagen->dib_info.dib_win98);
	if(imagen->dib_info.dib_win95 != NULL) free(imagen->dib_info.dib_win95);
	if(imagen->dib_info.dib_winnt != NULL) free(imagen->dib_info.dib_winnt);
	
	free(imagen);
}

