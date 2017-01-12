/* 
 * ----- Biblioteca de Edición y Dibujo Simple v0.5 por SamuelCoral -----
 * Módulo: Texto
 * 
 * Este módulo contiene todas las operaciones relacionadas con el dibujo de texto.
 * 
 */


#ifndef __EDS_TEXTO__
#define __EDS_TEXTO__


#include "EDS_tipos.h"


#ifdef __cplusplus
extern "C" {
#endif


//////////////////////////////
//      TIPOS DE DATOS      //
//////////////////////////////


//Matriz de booleanos en donde se almacena el mapa de bits de las fuentes
typedef bool FUENTE[256][98];


//Matriz de booleanos utilizada como tipo de letra por default en esta biblioteca
extern const FUENTE fuente_std;



/////////////////////////
//      FUNCIONES      //
/////////////////////////


/* 
 * Devuelve la longitud horizontal de la cadena en pixeles.
 * 
 * --- PARÁMETROS ---
 * 
 * cadena	- Cadena de caracteres a medir
 * 
 */
EXPORTAR_DLL uint32_t LLAMADO longitud_cadena(const char* cadena);


/* 
 * Dibuja una letra en la estructura de dibujo especificada en las coordenadas y del color
 * especificados, usando la fuente por default.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a dibujar la letra
 * letra	- Caracter del código ASCII a dibujar
 * X		- Coordenada en X de la letra a dibujar
 * Y		- Coordenada en Y de la letra a dibujar
 * color	- Color de la letra (pueden ser usados los macros RBA y RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_letra(DIBUJO_EDS* dibujo, uint8_t letra, int32_t X, int32_t Y, COLOR color);


/* 
 * Dibuja una cadena de caracteres en la estructura de dibujo especificada
 * en las coordenadas y del color especificad, usando la fuente por default.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a escribir la cadena de caracteres
 * cadena	- Cadena de caracteres a escribir
 * X		- Coordenada en X de la cadena a escribir
 * Y		- Coordenada en Y de la cadena a escribir
 * color	- Color de la cadena (pueden ser usados los macros RGB y RGBA)
 * 
 */
EXPORTAR_DLL void LLAMADO d_cadena(DIBUJO_EDS* dibujo, const char* cadena, int32_t X, int32_t Y, COLOR color);


#ifdef __cplusplus
}
#endif

#endif

