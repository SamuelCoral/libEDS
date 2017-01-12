/* 
 * ----- Biblioteca de Edición y Dibujo Simple v0.5 por SamuelCoral -----
 * Módulo: Tipos
 * 
 * Este módulo contiene todas las macros y definiciones de tipos utilizados por las funciones
 * de los demás módulos junto con los métodos de creación, copiado y destrucción de estructuras
 * utilizadas, además de conversión de otros formatos de imágenes al formato de dibujo utilizado
 * por esta biblioteca y a la inversa (devolverlos a un formato de archivo conocido).
 * 
 */


#ifndef __DIB_TIPOS__
#define __DIB_TIPOS__


#include "libbmp.h"


#ifdef __cplusplus
extern "C" {
#endif


//////////////////////////////
//      TIPOS DE DATOS      //
//////////////////////////////


/* 
 * COLOR puede referirse a un color de 32 bpp o a una entrada de una paleta
 * de colores.
 * 
 * Todas las funciones que requieran un color de parámetro se espera que esté estructurado
 * de la siguiente manera:
 * 
 * Primeros 8 bits		- Canar Azul
 * Siguientes 8 bits	- Canal Verde
 * Siguientes 8 bits	- Canal Rojo
 * Últimos 8 bits		- Canal Alpha
 * 
 */
typedef uint32_t COLOR;


//////////////////////
//      MACROS      //
//////////////////////


//Regresa el color correspondiente especificando la intensidad de sus canales (desde 0 a 255)
#define RGBA(x, y, z, a)	(COLOR)(((uint8_t)(x) << 16) | ((uint8_t)(y) << 8) | ((uint8_t)(z) << 0) | ((uint8_t)(a) << 24))
#define RGB(x, y, z)		RGBA(x, y, z, 255)

//Devuelve la intensidad del canal deseado del color dado
#define B_ALPHA(x)	(uint8_t)((COLOR)(x) >> 24)
#define B_ROJO(x)	(uint8_t)((COLOR)(x) >> 16)
#define B_VERDE(x)	(uint8_t)((COLOR)(x) >> 8)
#define B_AZUL(x)	(uint8_t)((COLOR)(x) >> 0)

//Regresa el color almacenado en una estructura de color
#define RGB_P(x)	(COLOR)((x.R << 16) | (x.G << 8) | (x.B << 0) | (255 << 24))
#define RGBA_P(x)	(COLOR)((x.R << 16) | (x.G << 8) | (x.B << 0) | (x.A << 24))

//Almacena el color especificado en la estructura de color dada
#define P_RGB(x, y) { \
	x.R = B_ROJO(y); \
	x.G = B_VERDE(y); \
	x.B = B_AZUL(y); \
	x.A = 255; \
}

#define P_RGBA(x, y) { \
	x.R = B_ROJO(y); \
	x.G = B_VERDE(y); \
	x.B = B_AZUL(y); \
	x.A = B_ALPHA(y); \
}



///////////////////////////
//      ESTRUCTURAS      //
///////////////////////////


//Estructura de organización de bytes de un color en formato ARGB
typedef struct _p32 {
	
	uint8_t B;
	uint8_t G;
	uint8_t R;
	uint8_t A;
	
} p32;


//Estructura de mapa de bits implementada en esta biblioteca
typedef struct _dibujo_eds {
	
	uint32_t	ancho;		// Longitud del mapa de bits
	uint32_t	alto;		// Altitud del mapa de bits
	uint8_t		bpp;		// Profundidad de color en bits por pixel del mapa de bits (pueden ser 1, 4, 8 ó 32)
	COLOR*		paleta;		// Paleta de colores en formato XRGB en caso de que la profundidad de color sea igual o menor a 8 bpp
	p32*		bitmap;		// Mapa de bits
	uint8_t*	bitmap_p;	// Mapa de bits (contiene las entradas de paleta cuando exista)
	
} DIBUJO_EDS;



/////////////////////////
//      FUNCIONES      //
/////////////////////////


/*
 * Devuelve el mensaje de error si algo salió mal al realizar una operación
 * en esta biblioteca.
 * 
 */
EXPORTAR_DLL const char* LLAMADO error_EDS();


/* 
 * Crea y asigna la memoria necesaria para una estructura de dibujo
 * Devuelve el puntero con la memoria asignada.
 * En caso de que se decida crear un dibujo de 8 bpp o menos, se le
 * asignará una paleta estándar.
 * 
 * NOTA: Cualquier valor para la cantidad de bpp mayor a 8 contará como 32 bpp.
 * 
 * --- PARÁMETROS ---
 * 
 * ancho	- Longitud del mapa de bits
 * alto		- Altitud del mapa de bits
 * bpp		- Profundidad en color de la imagen en bpp
 * 
 */
EXPORTAR_DLL DIBUJO_EDS* LLAMADO crear_dibujo_vacio(uint32_t ancho, uint32_t alto, uint8_t bpp);


/* 
 * Organiza y transforma el mapa de bits de una imagen a un puntero de la estructura p32
 * (Estructura de bits en un pixel de profundidad de 32 bpp), o bien si este tiene una paleta
 * de colores y se desea conservar a un puntero distinto según se deseé.
 * Devuelve el puntero de la estructura de dibujo.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen	- Imagen del cual se tomará el mapa de bits a transformar
 * paleta	- Dice si debería conservarse la paleta de colores en caso de ser un bmp 8 o menos bpp.
 * 
 */
EXPORTAR_DLL DIBUJO_EDS* LLAMADO convertir_bmp_dibujo(IMAGEN_BMP* imagen, bool paleta);


/* 
 * Crea una estructura de dibujo a partir de un archivo BMP especificado por la ruta de archivo
 * Devuelve el puntero de la estructura de dibujo.
 * 
 * --- PARÁMETROS ---
 * 
 * ruta_bmp	- Ruta del archivo BMP a usar
 * paleta	- Dice si debería conservarse la paleta de colores en caso de ser un bmp 8 o menos bpp.
 * 
 */
EXPORTAR_DLL DIBUJO_EDS* LLAMADO cargar_dibujo_archivo_bmp(const char* ruta_bmp, bool paleta);


/* 
 * Arma el mapa de bits de color verdadero en formato para la estructura de archivo de imagen bmp
 * y lo inyecta en el puntero dado.
 * 
 * --- PARÁMETROS ---
 * 
 * pixeles	- Puntero a estructura donde se almacenan los datos organizados de los pixeles
 * imagen	- Puntero a estructura de archivo de imagen bmp donde se inyectaran los pixeles
 * alpha	- Dice si se debe incluir el canal alpha en la imagen (profundidad de color de 32 bpp)
 * 
 */
EXPORTAR_DLL void LLAMADO inyectar_dibujo_bmp(DIBUJO_EDS* dibujo, IMAGEN_BMP* imagen, bool alpha);


/* 
 * Convierte la estructura de dibujo y lo convierte en una estructura
 * de archivo de imagen bmp, a diferencia de la función inyectar, en esta función
 * no necesitas tener creada la estructura.
 * Devuelve un puntero una estructura de imagen BMP estándar.
 * La estructura resultante será un BMP de Windows NT, y si se especifica que de incluirse el canal alpha
 * será de Windows 95.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Estructura a puntero de dibujo de bpp a ser convertido
 * alpha	- Dice si se debe incluir el canal alpha en la imagen (profundidad de color de 32 bpp)
 * rle		- Indica si se desea intentar comprimir el dibujo con el algoritmo RLE (solo aplica para profundidades de color de 8 y 4 bpp)
 * 
 */
EXPORTAR_DLL IMAGEN_BMP* LLAMADO convertir_dibujo_bmp(DIBUJO_EDS* dibujo, bool alpha, bool rle);


/* 
 * Convierte una estructura de dibujo en una imagen BMP y la guarda en la ruta de archivo especificada.
 * El archivo BMP resultante será un BMP de Windows NT, y si se especifica que de incluirse el canal alpha
 * será de Windows 95.
 * 
 * dibujo	- Estructura a puntero de dibujo de bpp a ser convertido
 * ruta_bmp	- Ruta del archivo BMP resultante
 * alpha	- Dice si se debe incluir el canal alpha en la imagen (profundidad de color de 32 bpp)
 * rle		- Indica si se desea intentar comprimir el dibujo con el algoritmo RLE (solo aplica para profundidades de color de 8 y 4 bpp)
 * 
 */
EXPORTAR_DLL void LLAMADO guardar_dibujo_bmp(DIBUJO_EDS* dibujo, const char* ruta_bmp, bool alpha, bool rle);


/* 
 * Copia los datos almacenados en una estructura dibujo
 * y los devuelve en un nuevo puntero.
 * 
 * --- PARÁMETROS ---
 * 
 * origen	- Puntero a estructura de dibujo a ser copiado
 * 
 */
EXPORTAR_DLL DIBUJO_EDS* LLAMADO copiar_dibujo(DIBUJO_EDS* origen);


/* 
 * Libera la memoria ocupada por un puntero de una estructura de dibujo.
 * 
 * NOTA: Se recomienda asignar el puntero liberado en NULO después de llamar a esta función
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo - Puntero a estructura de dibujo a liberar
 * 
 */
EXPORTAR_DLL void LLAMADO destruir_puntero_dibujo(DIBUJO_EDS* dibujo);


#ifdef __cplusplus
}
#endif

#endif

