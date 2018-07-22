/**
 *  
 */


#ifndef _EDS_DIBUJO
#define _EDS_DIBUJO


#include "EDS_tipos.h"


#ifdef __cplusplus
extern "C" {
#endif



///////////////////////
//      MÉTODOS      //
///////////////////////


/**
 *  Borra todo el mapa de bits y lo colorea de un sólo y único color especificado.
 *  
 *  @param imagen	Imagen a limpiar
 *  @param color	Color con el cual limpiar la imagen
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_LimpiarDibujo(EDS_Imagen* imagen, uint32_t color);


/**
 *  Dibujar una linea recta entre 2 puntos dadas sus coordenadas.
 * 
 *  @param imagen	Imagen sobre la cual dibujar
 *  @param x1		Coordenada X del primer punto
 *  @param y1		Coordenada Y del primer punto
 *  @param x2		Coordenada X del segundo punto
 *  @param y2		Coordenada Y del segundo punto
 *  @param color	Color de la linea
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_DibujarLinea(EDS_Imagen* imagen, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);


/**
 *  Dibujar un rectángulo sin rellenar dados los 2 puntos de sus esquinas opuestas.
 * 
 *  @param imagen	Imagen sobre la cual dibujar
 *  @param x1		Coordenada X del primer punto
 *  @param y1		Coordenada Y del primer punto
 *  @param x2		Coordenada X del segundo punto
 *  @param y2		Coordenada Y del segundo punto
 *  @param color	Color del rectángulo
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_DibujarRectangulo(EDS_Imagen* imagen, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);


/**
 *  Dibujar un rectángulo y lo rellena dados los 2 puntos de sus esquinas opuestas.
 * 
 *  @param imagen	Imagen sobre la cual dibujar
 *  @param x1		Coordenada X del primer punto
 *  @param y1		Coordenada Y del primer punto
 *  @param x2		Coordenada X del segundo punto
 *  @param y2		Coordenada Y del segundo punto
 *  @param color	Color de la linea
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_DibujarRectanguloSolido(EDS_Imagen* imagen, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);



#ifdef __cplusplus
}
#endif


#endif /* _EDS_DIBUJO */

