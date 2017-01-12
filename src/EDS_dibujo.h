/* 
 * ----- Biblioteca de Edición y Dibujo Simple v0.5 por SamuelCoral -----
 * Módulo: Dibujo
 * 
 * Este módulo contiene funciones relacionadas al dibujo de líneas, curvas y formas
 * vacías o rellenas.
 * 
 */


#ifndef __EDS_DIBUJO__
#define __EDS_DIBUJO__


#include "EDS_tipos.h"


#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////
//      FUNCIONES      //
/////////////////////////


/* 
 * Dibuja una línea recta entre 2 puntos dadas las coordenadas con un color especificado
 * hacía el dibujo usando el algoritmo de Bresenham.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo en el que será dibujado la línea
 * x1		- Coordenada en X del primer punto de la línea
 * y1		- Coordenada en Y del primer punto de la línea
 * x2		- Coordenada en X del segundo punto de la línea
 * y2		- Coordenada en Y del segundo punto de la línea
 * color	- Color de la línea (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_linea(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color);


/* 
 * Dibuja un rectángulo dadas sus 2 esquinas contrarias con un color especificado
 * hacía un dibujo.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo en el que será dibujado el rectángulo
 * x1		- Coordenada en X de la primera esquina del rectángulo
 * y1		- Coordenada en Y de la primera esquina del rectángulo
 * x2		- Coordenada en X de la esquina contraria del rectángulo
 * y2		- Coordenada en Y de la esquina contraria del rectángulo
 * color	- Color del rectángulo (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_rect(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color);


/* 
 * Dibuja y rellena un rectándulo dadas sus 2 esquinas contrarias con un color especificado
 * hacía un dibujo.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo en el que será dibujado el rectángulo
 * x1		- Coordenada en X de la primera esquina del rectángulo
 * y1		- Coordenada en Y de la primera esquina del rectángulo
 * x2		- Coordenada en X de la esquina contraria del rectángulo
 * y2		- Coordenada en Y de la esquina contraria del rectángulo
 * color	- Color del rectángulo (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_rect_lleno(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color);


/* 
 * Dibuja el contorno de un círculo dados su centro y su radio usando el algoritmo de Bresenham.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo en la que será dibujada la circunferencia
 * x1		- Coordenada en X del centro de la circunferencia
 * y1		- Coordenada en Y del centro de la circunferencia
 * radio	- Radio de la circunferencia
 * color	- Color de la circunferencia (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_circ(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t radio, COLOR color);


/* 
 * Dibuja y rellena un círculo de un color específico dados su centro y su radio usando el algoritmo de Bresenham.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo en la que será dibujado el círculo
 * x1		- Coordenada en X del centro del círculo
 * y1		- Coordenada en Y del centro del círculo
 * radio	- Radio del círculo
 * color	- Color del círculo (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_circ_lleno(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t radio, COLOR color);


/* 
 * Dibuja un semicírculo desde el ángulo de inicio hasta el ángulo final
 * en dirección de las manecillas del reloj usando el algoritmo de Bresenham.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo		- Puntero a estructura de dibujo en la que será dibujado el semicírculo
 * x1			- Coordenada en X del centro del círculo
 * y1			- Coordenada en Y del centro del círculo
 * radio		- Radio del círculo
 * ang_inicio	- Ángulo de inicio del semicírculo
 * ang_final	- Ángulo final del semicírculo
 * color		- Color del círculo (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_semi_circ(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t radio, double ang_inicio, double ang_final, COLOR color);


/* 
 * Dibuja el contorno de una elpise dados su centro, su ancho y altura usando el algoritmo de Bresenham.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo en la que será dibujada la elipse
 * x1		- Coordenada en X del centro de la elipse
 * y1		- Coordenada en Y del centro de la elipse
 * ancho	- Radio horizontal de la elipse
 * alto		- Radio horizontal de la elipse
 * color	- Color de la elipse (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_elipse(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, COLOR color);


/* 
 * Dibuja y rellena una elpise dados su centro, su ancho y altura usando el algoritmo de Bresenham.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo en la que será dibujada la elipse
 * x1		- Coordenada en X del centro de la elipse
 * y1		- Coordenada en Y del centro de la elipse
 * ancho	- Radio horizontal de la elipse
 * alto		- Radio horizontal de la elipse
 * color	- Color de la elipse (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_elipse_llena(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, COLOR color);


/* 
 * Dibuja una semielipse desde el ángulo de inicio hasta el ángulo final
 * en dirección de las manecillas del reloj usando el algoritmo de Bresenham.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo		- Puntero a estructura de dibujo en la que será dibujada la semielipse
 * x1			- Coordenada en X del centro de la semielipse
 * y1			- Coordenada en Y del centro de la semielipse
 * ancho		- Radio horizontal de la semielipse
 * alto			- Radio horizontal de la semielipse
 * ang_inicio	- Ángulo de inicio de la semielipse
 * ang_final	- Ángulo final de la semielipse
 * color		- Color de la semielipse (pueden ser usados los macros RGB ó RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_semi_elipse(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, double ang_inicio, double ang_final, COLOR color);


/* 
 * Limpia el mapa de bits del dibujo especificado y lo rellena completamente
 * por el color especificado.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a ser limpiado
 * color	- Color con en que será rellenado
 * 
 */
EXPORTAR_DLL void LLAMADO limpiar_d(DIBUJO_EDS* dibujo, COLOR color);


#ifdef __cplusplus
}
#endif

#endif

