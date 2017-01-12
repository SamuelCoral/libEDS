/* 
 * ----- Biblioteca de Edición y Dibujo Simple v0.5 por SamuelCoral -----
 * Módulo: Color
 * 
 * Este módulo contiene funciones para obtener, mezclar y realizar alteraciones
 * al color de una imágen.
 * 
 */


#ifndef __EDS_COLOR__
#define __EDS_COLOR__


#include "EDS_tipos.h"


#ifdef __cplusplus
extern "C" {
#endif


//////////////////////
//      MACROS      //
//////////////////////


#define mezclar_color(origen, destino) RGBA( \
	B_ROJO(origen) * B_ALPHA(origen) / 255.0 + B_ROJO(destino) * B_ALPHA(destino) * (1 - B_ALPHA(origen) / 255.0) / 255, \
	B_VERDE(origen) * B_ALPHA(origen) / 255.0 + B_VERDE(destino) * B_ALPHA(destino) * (1 - B_ALPHA(origen) / 255.0) / 255, \
	B_AZUL(origen) * B_ALPHA(origen) / 255.0 + B_AZUL(destino) * B_ALPHA(destino) * (1 - B_ALPHA(origen) / 255.0) / 255, \
	B_ALPHA(origen) + B_ALPHA(destino) * (1 - B_ALPHA(origen) / 255.0) \
)



/////////////////////////
//      FUNCIONES      //
/////////////////////////


/* 
 * Devuelve el puntero del arreglo de colores que conforman la paleta de colores
 * usada por defecto para una profundidad de color especificada.
 * 
 * --- PARÁMETROS ---
 * 
 * bpp	- Profundidad de color en bits por pixel de la paleta de color que se desea obtener
 * 
 */
EXPORTAR_DLL const COLOR* LLAMADO paleta_std(uint16_t bpp);


/* 
 * Obtiene el color del pixel del dibujo en las coordenadas especificadas
 * Si la coordenada está fuera de las dimensiones del dibujo, la función
 * devolverá el color negro completamente transparente.
 * Si se trata de un dibujo con paleta de colores, devolverá el número de la
 * entrada en la paleta.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a encontrar el pixel
 * X		- Coordenada en X del pixel a conocer
 * Y		- Coordenada en Y del pixel a conocer
 * estricto	- Indica si se desea obtener una notificación con error_EDS si el pixel solicitado está
 *            por fuera de los límites del dibujo
 * 
 */
EXPORTAR_DLL COLOR LLAMADO v_pixel(DIBUJO_EDS* dibujo, uint32_t X, uint32_t Y, bool estricto);


/* 
 * Dibuja un pixel de un color especificado hacía un dibujo.
 * El color no se mezclará con el color existente del pixel especificado
 * en caso de que se trate de un dibujo de 32 bpp.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a ser insertado el pixel
 * X		- Coordenada en X del pixel
 * Y		- coordenada en Y del pixel
 * color	- Color del pixel (pueden ser usados los macros RGB ó RGBA)
 * estricto	- Indica si se desea obtener una notificación con error_EDS si el pixel solicitado está
 *            por fuera de los límites del dibujo
 * 
 */
EXPORTAR_DLL void LLAMADO d_pixel_s(DIBUJO_EDS* dibujo, uint32_t X, uint32_t Y, COLOR color, bool estricto);


/* 
 * Dibuja un pixel de un color especificado hacía un dibujo.
 * Si el color especificado tiene transparencia, este se mezclará
 * con el color del pixel en donde se desea dibujar en caso de que
 * se trate de un dibujo de 32 bpp.
 * 
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Puntero a estructura de dibujo a ser insertado el pixel
 * X		- Coordenada en X del pixel
 * Y		- coordenada en Y del pixel
 * color	- Color del pixel (pueden ser usados los macros RGB ó RGBA)
 * estricto	- Indica si se desea obtener una notificación con error_EDS si el pixel solicitado está
 *            por fuera de los límites del dibujo
 * 
 */
EXPORTAR_DLL void LLAMADO d_pixel(DIBUJO_EDS* dibujo, uint32_t X, uint32_t Y, COLOR color, bool estricto);


/* 
 * Invierte el color especificado y devuelve el nuevo color
 * Esto no afectará su canal Alpha.
 * 
 * --- PARÁMETROS ---
 * 
 * color	- Color a invertir
 * 
 */
EXPORTAR_DLL COLOR LLAMADO invertir_color(COLOR color);


/* 
 * Convierte el color a su equivalente en escala de grises siguiendo
 * los términos de la iluminación linear del espacio de color CIE 1931
 * 
 * --- PARÁMETROS ---
 * 
 * color	- Color a convertir
 * 
 */
EXPORTAR_DLL COLOR LLAMADO color_escala_grises(COLOR color);


/* 
 * Encuentra el colo mas cercano de la paleta de colores dada.
 * Devuelve la entrada a la paleta del resultado.
 * 
 * --- PARÁMETROS ---
 * 
 * num_colores	- Número de colores o entradas en la paleta a buscar
 * paleta		- Paleta de colores en la que buscar
 * color		- Color del que se desea buscar el color mas cercano
 * 
 */
EXPORTAR_DLL uint8_t LLAMADO color_mas_cercano(uint16_t num_colores, const uint32_t* paleta, COLOR color);


/* 
 * Invierte el color de toda la imagen en el puntero especificado.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Estructura de dibujo de 32 bpp a invertir el color
 * 
 */
EXPORTAR_DLL void LLAMADO invertir_colores_d(DIBUJO_EDS* dibujo);


/* 
 * Convierte de toda la imagen en el puntero especificado a su equivalente
 * en escala de grises.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Estructura de dibujo de 32 bpp a invertir el color
 * 
 */
EXPORTAR_DLL void LLAMADO escala_grises_d(DIBUJO_EDS* dibujo);


/* 
 * Realiza un OR binario con todos los pixeles del dibujo especificado con el color
 * especificado.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Estructura de dibujo de 32 bpp a saturar color
 * color	- Color que saturará la imagen
 * 
 */
EXPORTAR_DLL void LLAMADO saturar_colores_d(DIBUJO_EDS* dibujo, COLOR color);


/* 
 * Realiza un AND binario con todos los pixeles del dibujo especificado con el color
 * especificado.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Estructura de dibujo de 32 bpp a extraer color
 * color	- Color que se extraerá de la imagen
 * 
 */
EXPORTAR_DLL void LLAMADO extraer_colores_d(DIBUJO_EDS* dibujo, COLOR color);


/* 
 * Suma el incremento al canal alpha de todo el dibujo especificado
 * Este puede ser un número negativo en caso de que desee restarse.
 * Debe ser un número entre -255 y 255.
 * No alterará los pixeles que tengan transparencia total
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo		- Estructura de dibujo de 32 bpp a sumar el canal alpha
 * incremento	- Incremento de transparencia
 * 
 */
EXPORTAR_DLL void LLAMADO cambiar_transparencia_d(DIBUJO_EDS* dibujo, int16_t incremento);


/* 
 * Suma el incremento al canal rojo de todo el dibujo especificado
 * Este puede ser un número negativo en caso de que desee restarse.
 * Debe ser un número entre -255 y 255.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo		- Estructura de dibujo de 32 bpp a sumar el canal rojo
 * incremento	- Incremento de color
 * 
 */
EXPORTAR_DLL void LLAMADO cambiar_rojo_d(DIBUJO_EDS* dibujo, int16_t incremento);


/* 
 * Suma el incremento al canal verde de todo el dibujo especificado
 * Este puede ser un número negativo en caso de que desee restarse.
 * Debe ser un número entre -255 y 255.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo		- Estructura de dibujo de 32 bpp a sumar el canal verde
 * incremento	- Incremento de color
 * 
 */
EXPORTAR_DLL void LLAMADO cambiar_verde_d(DIBUJO_EDS* dibujo, int16_t incremento);


/* 
 * Suma el incremento al canal azul de todo el dibujo especificado
 * Este puede ser un número negativo en caso de que desee restarse.
 * Debe ser un número entre -255 y 255.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo		- Estructura de dibujo de 32 bpp a sumar el canal azul
 * incremento	- Incremento de color
 * 
 */
EXPORTAR_DLL void LLAMADO cambiar_azul_d(DIBUJO_EDS* dibujo, int16_t incremento);

/* 
 * Incrementa o decrementa el brillo de todo el dibujo especificado.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo		- Estructura de dibujo de 32 bpp a cambiar el brillo
 * incremento	- Incremento o decremento del brillo
 * 
 */
EXPORTAR_DLL void LLAMADO cambiar_brillo_d(DIBUJO_EDS* dibujo, int16_t incremento);


/* 
 * Aumenta la profundidad de color de un dibujo que contenga una paleta de color.
 * El dibujo resultante será exactamente el mismo, salvo que estará a una produnfidad
 * de color de 32 bpp y ya no tendrá la paleta de color.
 * Si el dibujo ya está a esa profundidad quedará intacto.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Estructura de dibujo a aumentar su profundidad de color a 32 bpp
 * 
 */
EXPORTAR_DLL void LLAMADO aumentar_bpp_d(DIBUJO_EDS* dibujo);


/* 
 * Reduce la produnfidad de color de un dibujo a una profundidad que soporte
 * paleta de colores (1, 4 u 8 bpp).
 * Se utiliza el algoritmo de encontrar el color más cercano a la paleta de colores estándar.
 * 
 * --- PARÁMETROS ---
 * 
 * dibujo	- Estructura de dibujo de 32 bpp a reducir su profundidad de color
 * bpp		- Nueva profundidad de color que acepte paleta de colores (1, 4 u 8 bpp)
 * 
 */
EXPORTAR_DLL void LLAMADO reducir_bpp_d(DIBUJO_EDS* dibujo, uint8_t bpp);


#ifdef __cplusplus
}
#endif

#endif

