

#ifndef _EDS_BMP
#define _EDS_BMP


#include "EDS_tipos.h"


#ifdef __cplusplus
extern "C" {
#endif



/**
 *  Banderas usadas en la función de guardar.
 */
enum EDS_BMP_BANDERAS {
	
	EDS_BMP_B_VER_3	= 0,
	EDS_BMP_B_VER_2	= 1,
	EDS_BMP_B_VER_4	= 2,
	EDS_BMP_B_VER_5	= 3,
	EDS_BMP_B_VER	= 3,
	
	EDS_BMP_B_COMP_RGB	= 0,
	EDS_BMP_B_COMP_RLE	= 4,
	EDS_BMP_B_COMP_MASCARAS	= 8,
	EDS_BMP_B_COMP		= 12,
	
	EDS_BMP_B_SENTIDO_ABARR	= 0,
	EDS_BMP_B_SENTIDO_ARRAB	= 16,
	EDS_BMP_B_SENTIDO	= 16,
	
	EDS_BMP_B_IR_GRAFICOS	= 0,
	EDS_BMP_B_IR_NEGOCIOS	= 32,
	EDS_BMP_B_IR_IMAGENES	= 64,
	EDS_BMP_B_IR_ABSCOLOR	= 96,
	EDS_BMP_B_IR		= 96,
	
	EDS_BMP_B_FMT_24BPP	= 0,
	EDS_BMP_B_FMT_32BPP	= 128,
	EDS_BMP_B_FMT_16BPP	= 256,
	EDS_BMP_B_FMT		= 384
};



enum EDS_BMP_VERSIONES {
	
	EDS_BMP_VER_2	= 12,
	EDS_BMP_VER_3	= 40,
	EDS_BMP_VER_4	= 108,
	EDS_BMP_VER_5	= 124
};



enum EDS_BMP_METODOS_COMPRESION {
	
	EDS_BMP_COMP_RGB	= 0,
	EDS_BMP_COMP_RLE8	= 1,
	EDS_BMP_COMP_RLE4	= 2,
	EDS_BMP_COMP_BITFIELDS	= 3,
	EDS_BMP_COMP_JPEG	= 4,
	EDS_BMP_COMP_PNG	= 5
};



enum EDS_BMP_ESPACIOS_COLOR {
	
	EDS_BMP_ECL_sRGB	= 0x73524742,	//'sRGB'
	EDS_BMP_ECL_WINDOWS	= 0x57696E20,	//'Win '
	EDS_BMP_ECL_CALIBRADO	= 0,
	EDS_BMP_ECL_ARCHIVO	= 0x4C494E4B,	//'LINK'
	EDS_BMP_ECL_EMBEDIDO	= 0x4D424544,	//'MBED'
};



enum EDS_BMP_INTENCIONES_RENDERIZADO {
	
	EDS_BMP_IR_NEGOCIOS	= 1,
	EDS_BMP_IR_GRAFICOS	= 2,
	EDS_BMP_IR_IMAGENES	= 4,
	EDS_BMP_IR_ABSCOLOR	= 8
};



// Número mágico de todos los archivos BMP
#define EDS_BMP_TA_BM	0x4D42

#define EDS_BMP_DEFAULT_PPM	11811




#pragma pack(push, 2)


typedef struct _EDS_BMP_CabeceraArchivo {
	
	uint16_t tipo_archivo;
	uint32_t tam_archivo;
	uint16_t reservado_1;
	uint16_t reservado_2;
	uint32_t inicio_bitmap;
	
} EDS_BMP_CabeceraArchivo;



typedef struct _EDS_BMP_CabeceraV2 {
	
	uint32_t tam_cabecera;
	int16_t ancho;
	int16_t alto;
	uint16_t planos;
	uint16_t bpp;
	
} EDS_BMP_CabeceraV2;



typedef struct _EDS_BMP_CabeceraV3 {
	
	uint32_t	tam_cabecera;
	int32_t		ancho;
	int32_t		alto;
	uint16_t	planos;
	uint16_t	bpp;
	uint32_t	compresion;
	uint32_t	tam_bitmap;
	int32_t		res_horizontal;
	int32_t		res_vertical;
	uint32_t	colores_paleta;
	uint32_t	colores_importantes;
	
} EDS_BMP_CabeceraV3;


#pragma pack(pop)



/**
 * 
 * 
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_GuardarBMP(const EDS_Imagen* imagen, const char* ruta, uint16_t bmp_banderas, const EDS_MascarasBits* mascaras);


/**
 * 
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_AbrirBMP(const char* ruta);



#ifdef __cplusplus
}
#endif


#endif /* _EDS_BMP */

