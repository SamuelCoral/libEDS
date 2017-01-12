/* 
 * ----- Biblioteca de Edición y Dibujo Simple v0.5 por SamuelCoral -----
 * Módulo: Geometría
 * 
 * Este módulo contiene funciones para realizar recortes o alteraciones en la geometría
 * y escala de la imagen.
 * 
 */


#ifndef __EDS_GEO__
#define __EDS_GEO__


#include "EDS_tipos.h"


#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////
//      FUNCIONES      //
/////////////////////////


/* 
 * Cambia las dimenciones del dibujo sin perder el dibujo original
 * dependiendo de si se reduce o se aumenta la escala.
 * La imagen resultante se escribirá sobre el mismo puntero.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a escalar
 * x2		- Nueva anchura del mapa de bits a escalar
 * y2		- Nueva altura del mapa de bits a escalar
 * 
 */
EXPORTAR_DLL void LLAMADO reescalar_d(DIBUJO_EDS* dibujo, uint32_t x2, uint32_t y2);


/* 
 * Cambia las dimenciones del dibujo sin perder el dibujo original
 * dependiendo de si se reduce o se aumenta la escala.
 * Devuelve el puntero a la imagen a escala.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a escalar
 * x2		- Nueva anchura del mapa de bits a escalar
 * y2		- Nueva altura del mapa de bits a escalar
 * 
 */
EXPORTAR_DLL DIBUJO_EDS* LLAMADO escalar_d(DIBUJO_EDS* dibujo, uint32_t x2, uint32_t y2);


/* 
 * Toma un fragmento rectangular limitado por los puntos de coordenadas dadas
 * y la imagen resultante sobreesbribirá la imagen completa.
 * 
 * NOTA: Si ambos puntos se encuentran en la misma coordenada en X o en Y
 *       se devolverá un puntero nulo.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a recortar
 * x1		- Coordenada en X de la primera esquina a recortar
 * y1		- Coordenada en Y de la primera esquina a recortar
 * x2		- Coordenada en X de la segunda esquina a recortar
 * y2		- Coordenada en Y de la segunda esquina a recortar
 * 
 */
EXPORTAR_DLL void LLAMADO recortar_d(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2);


/* 
 * Toma un fragmento rectangular limitado por los puntos de coordenadas dadas
 * y lo devuelve en un nuevo puntero a estructura de dibujo.
 * 
 * NOTA: Si ambos puntos se encuentran en la misma coordenada en X o en Y
 *       se devolverá un puntero nulo.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a recortar
 * x1		- Coordenada en X de la primera esquina a recortar
 * y1		- Coordenada en Y de la primera esquina a recortar
 * x2		- Coordenada en X de la segunda esquina a recortar
 * y2		- Coordenada en Y de la segunda esquina a recortar
 * 
 */
EXPORTAR_DLL DIBUJO_EDS* LLAMADO cortar_d(DIBUJO_EDS* dibujo, int32_t x1, int32_t y1, int32_t x2, int32_t y2);


/* 
 * Copia el mapa de bits del puntero de origen y lo pega sobre el puntero de destino
 * en las coordenadas especificadas.
 * 
 * --- PARÁMETROS ---
 * 
 * origen	- Puntero a estructura de dibujo del que se tomará el mapa de bits completo
 * destino	- Puntero a estructura de dibujo sobre el que se pegará todo el dibujo de origen
 * x1		- Coordenada en X donde se pegará el dibujo sobre el destino
 * y1		- Coordenada en Y donde se pegará el dibujo sobre el destino
 * 
 */
EXPORTAR_DLL void LLAMADO pegar_d(DIBUJO_EDS* origen, DIBUJO_EDS* destino, int32_t x1, int32_t y1);


/* 
 * Copia el mapa de bits a escala del puntero de origen y lo pega sobre el puntero de destino
 * en las coordenadas especificadas.
 * 
 * --- PARÁMETROS ---
 * 
 * origen	- Puntero a estructura de dibujo del que se tomará el mapa de bits completo
 * destino	- Puntero a estructura de dibujo sobre el que se pegará todo el dibujo de origen
 * x1		- Coordenada en X del primer punto delimitador de la zona a pegar el mapa de bits
 * y1		- Coordenada en Y del primer punto delimitador de la zona a pegar el mapa de bits
 * x2		- Coordenada en X del segundo punto delimitador de la zona a pegar el mapa de bits
 * y2		- Coordenada en Y del segundo punto delimitador de la zona a pegar el mapa de bits
 * 
 */
EXPORTAR_DLL void LLAMADO pegar_escalar_d(DIBUJO_EDS* origen, DIBUJO_EDS* destino, int32_t x1, int32_t y1, int32_t x2, int32_t y2);


/* 
 * Voltea la imágen especificada en el eje X.
 * 
 * --- PARÁMETROS --- 
 * 
 * dibujo	- Puntero a estructura de dibujo a voltear
 * 
 */
EXPORTAR_DLL void LLAMADO espejo_x_d(DIBUJO_EDS* dibujo);


/* 
 * Voltea la imagen especificada en el eje Y.
 * 
 * --- PARÁMETROS --- 
 * 
 * dibujo	- Puntero a estructura de dibujo a voltear
 * 
 */
EXPORTAR_DLL void LLAMADO espejo_y_d(DIBUJO_EDS* dibujo);


/* 
 * Voltea la imagen especificada dejándola de cabeza.
 * 
 * --- PARÁMETROS --- 
 * 
 * dibujo	- Puntero a estructura de dibujo a voltear
 * 
 */
EXPORTAR_DLL void LLAMADO voltear_d(DIBUJO_EDS* dibujo);


/* 
 * Rota la imagen especificada 90 grados a la derecha.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a rotar
 * 
 */
EXPORTAR_DLL void LLAMADO rotar_derecha_d(DIBUJO_EDS* dibujo);


/* 
 * Rota la imagen especificada 90 grados a la izquierda.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a rotar
 * 
 */
EXPORTAR_DLL void LLAMADO rotar_izquierda_d(DIBUJO_EDS* dibujo);


#ifdef __cplusplus
}
#endif

#endif

