/* 
 * ----- Biblioteca de Edición y Dibujo Simple v0.5 por SamuelCoral -----
 * 
 * Implementa la biblioteca BMP genérica para dibujar sobre las imágenes,
 * también contiene algunas herramientas para el manejo de la geometría
 * y alteraciones al color de la imagen.
 * 
 * Es independiente de la plataforma de ejecución
 * 
 */


#ifndef __LIB_EDS__
#define __LIB_EDS__


//Define la versión de la biblioteca (las versiones 0.5.x serán compatibles con esta misma)
#define EDS_VER_STR	"0.5.0"
#define EDS_VER_INT	(int)(EDS_VER_STR[0] - '0')
#define EDS_VER_SUB	(int)(EDS_VER_STR[2] - '0')
#define EDS_VER_REV	(int)(EDS_VER_STR[4] - '0')


#include "libbmp.h"

#include "EDS_tipos.h"
#include "EDS_color.h"
#include "EDS_dibujo.h"
#include "EDS_geo.h"
#include "EDS_texto.h"


#endif

