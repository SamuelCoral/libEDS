/**
 *  
 */


#ifndef _EDS_COLOR
#define _EDS_COLOR


#include "EDS_tipos.h"


#ifdef __cplusplus
extern "C" {
#endif



//////////////////////
//      MACROS      //
//////////////////////


/**
 *  Combina 2 colores transparentes por medio de sus canales alpha.
 *  
 *  @param origen	Color que se combinará con el destino
 *  @param destino	Color sobre el que se escribirá
 */
#define EDS_MEZCLAR_COLOR(origen, destino) (EDS_Color){ .c = { \
	(origen.c.b * origen.c.a + destino.c.b * destino.c.a * (1.0 - origen.c.a / 255.0)) / 255.0, \
	(origen.c.g * origen.c.a + destino.c.g * destino.c.a * (1.0 - origen.c.a / 255.0)) / 255.0, \
	(origen.c.r * origen.c.a + destino.c.r * destino.c.a * (1.0 - origen.c.a / 255.0)) / 255.0, \
	origen.c.a + destino.c.a * (1.0 - origen.c.a / 255.0) \
} }


#define EDS_COLOR_RGBA(r, g, b, a)	(EDS_Color){ .c = { b, g, r, a } }.v
#define EDS_COLOR_RGB(r, g, b)		EDS_COLOR_RGBA(r, g, b, 0xFF)



///////////////////////
//      MÉTODOS      //
///////////////////////


/**
 *  Obtiene el arreglo de colores de la paleta usada por defecto para la
 *  profundidad de color deseada.
 *  
 *  @param bpp	Profundidad de color de la paleta estándar a obtener
 */
EDS_EXPORTAR_DLL const EDS_Color* EDS_LLAMADO EDS_ObtenerPaletaEstandar(uint8_t bpp);


/**
 *  Devuelve el color en formato RGB equivalente al color HSL proporcionado.
 * 
 *  @param h	Ángulo o matiz del color
 *  @param s	Saturación
 *  @param l	Iluminación
 * 
 *  @returns	Color RGB equivalente al color HSL
 */
EDS_EXPORTAR_DLL EDS_Color EDS_LLAMADO EDS_ColorHSLRGB(double h, double s, double l);


/**
 *  Obtiene un pixel de la imagen en las coordenadas especificadas
 *  Obtiene el color BGRA si se trata de un mapa de bits a colores reales o
 *  la entrada a la paleta de colores en caso contrario.
 *  
 *  @param imagen	Imagen a obtener el pixel
 *  @param x		Coordenada en X del pixel
 *  @param y		Coordenada en Y del pixel
 */
EDS_EXPORTAR_DLL uint32_t EDS_LLAMADO EDS_ObtenerPixel(const EDS_Imagen* imagen, uint32_t x, uint32_t y);


/**
 *  Sobreescribe la información del pixel en las coordenadas especificadas por
 *  el nuevo pixel dado.
 *  @remarks La diferencia entre dibujar y sobreescribir, radica en el hecho
 *           que dibujar, combina los colores transparentes entre el pixel dado
 *           y el pixel que ya se encontraba en el dibujo, mientras que
 *           sobreescribir omite al pixel de destino y sobreescribe tanto
 *           el color como el canal alpha por las del nuevo pixel, por lo que
 *           la función sobreescribir es mas rápida porque se omite la parte de
 *           combinar los colores, y de hecho se recomienda utilizar este
 *           método para mapas de bits con paleta de colores.
 *  
 *  @param imagen	Imagen a sobreescribir el pixel
 *  @param x		Coordenada en X del pixel
 *  @param y		Coordenada en Y del pixel
 *  @param color	Color BGRA o entrada de paleta del pixel
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_SobreescribirPixel(EDS_Imagen* imagen, uint32_t x, uint32_t y, uint32_t color);


/**
 *  Dibuja un pixel en la imagen en las coordenadas especificadas.
 *  Si la imagen es a colores reales, estos colores se combinarán en caso
 *  de que el pixel dado sea semitransparente.
 *  
 *  @param imagen	Imagen a dibujar el pixel
 *  @param x		Coordenada en X del pixel
 *  @param y		Coordenada en Y del pixel
 *  @param color	Color BGRA o entrada de paleta del pixel
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_DibujarPixel(EDS_Imagen* imagen, uint32_t x, uint32_t y, uint32_t color);



#ifdef __cplusplus
}
#endif


#endif /* _EDS_COLOR */

