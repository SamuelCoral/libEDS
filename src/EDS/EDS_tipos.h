/**
 *  
 */



// Evita que el archivo de cabecera sea incluido más de una vez
#ifndef _EDS_TIPOS
#define _EDS_TIPOS


/**
 *  La macro EDS_LLAMADO se usa para indicar de forma explícita que
 *  la convención de llamado de las funciones será __cdecl en caso de que
 *  estemos en windows, en linux no hay problemas, esto para evitar
 *  problemas en la implementación a .Net.
 *  Mientras que la macro EDS_EXPORTAR_DLL es usada para indicar que
 *  estamos exportando las funciones del DLL a la hora de compilar,
 *  igual, solo aplica para Windows y solo es de utilidad para la
 *  implementación en .Net.
 */
#ifdef _WIN32
	#define EDS_LLAMADO __cdecl
	#ifdef EDS_EXPORTS
		#define EDS_EXPORTAR_DLL __declspec(dllexport)
	#else
		#define EDS_EXPORTAR_DLL __declspec(dllimport)
	#endif
#else
	#define EDS_LLAMADO
	#define EDS_EXPORTAR_DLL
#endif



#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif



#include <stdint.h>



//////////////////////////////
//      TIPOS DE DATOS      //
//////////////////////////////


/**
 *  Estructura que contiene los componentes de color de un pixel en formato
 *  BGRA8888.
 *  
 *  8 bits del componente azul
 *  8 bits del componente verde
 *  8 bits del componente azul
 *  8 bits del canal alpha
 *  
 *  En ese orden, útil para poder leer y escribir imágenes en otros formatos
 *  conocidos porque es su formato de pixel usado por defecto.
 */
typedef struct _EDS_ColorBGRA8888 {
	
	uint8_t	b;	// Componente azul
	uint8_t	g;	// Componente verde
	uint8_t	r;	// Componente rojo
	uint8_t	a;	// Canal alpha
	
} EDS_ColorBGRA8888;


/**
 *  Unión que contiene la informaci�n del color de un pixel, útil para poder
 *  acceder a los componentes de color de forma individual u obtener todo el
 *  valor del color en 32 bits.
 *  Implementa el formato de pixel BGRA8888 y es la uni�n usada por defecto
 *  en esta librería.
 */
typedef union _EDS_Color {
	
	uint32_t			v;	// Valor del pixel en 32 bits en formato BGRA8888
	EDS_ColorBGRA8888	c;	// Componentes de color del pixel
	
} EDS_Color;


/**
 *  Estructura que contiene los 4 componentes de 32 bits cada uno de las máscaras
 *  de bits, usados para indicar los bits que deben ser usados para cada componente
 *  del color BGRA de cada pixel, usadas principalmente para formatos de archivo de
 *  mapas de bits como el formato BMP cuando la profundidad de color es de 32 o 16 bpp.
 */
typedef struct _EDS_MascarasBitsBGRA {
	
	uint32_t b;
	uint32_t g;
	uint32_t r;
	uint32_t a;
	
} EDS_MascarasBitsBGRA;


/**
 *  Uni�n que encapsula la información de las máscaras de bits para poder acceder
 *  a sus componentes individualmente como un arreglo o mediante la estructura.
 */
typedef union _EDS_MascarasBits {
	
	uint32_t				v[4];
	EDS_MascarasBitsBGRA	m;
	
} EDS_MascarasBits;



/**
 *  Estructura que almacena toda la información de un mapa de bits implementado
 *  en esa librería.
 */
typedef struct _EDS_Imagen {
	
	uint32_t	ancho;			// Ancho del mapa de bits
	uint32_t	alto;			// Alto del mapa de bits
	uint8_t		bpp;			// Profundidad de color en bits por pixel
	EDS_Color*	paleta;			// Arreglo de la paleta de colores en caso de que la profundidad de color sea de 8 bpp o menor
	EDS_Color*	mapa_bits;		// Arreglo del mapa de bits
	uint8_t*	mapa_bits_p;	// Arreglo del mapa de bits (para profundidades de color de 8 bpp o menores)
	
} EDS_Imagen;



///////////////////////
//      MÉTODOS      //
///////////////////////


/**
 *  Devuelve la cadena que contenga el mensaje de error que haya ocurrido
 *  durante la última función llamada si es que hubiera ocurrido algún error.
 *  
 *  @returns	Mensaje de error ocurrido en la última función llamada
 */
EDS_EXPORTAR_DLL const char* EDS_LLAMADO EDS_ObtenerError();


/**
 *  Construye una unión de máscaras de bits dados el número de bits para
 *  cada componente de color.
 * 
 *  @param r	Número de bits para la máscara del componente rojo
 *  @param g	Número de bits para la máscara del componente verde
 *  @param b	Número de bits para la máscara del componente azul
 *  @param a	Número de bits para la máscara del canal alpha
 *  
 *  @returns	Las máscaras de bits con el número de bits especificados para cada componente
 */
EDS_EXPORTAR_DLL EDS_MascarasBits EDS_LLAMADO EDS_ConstruirMascaras(uint8_t r, uint8_t g, uint8_t b, uint8_t a);


/**
 *  Verifica que las máscaras de bits sean válidas, para que sean válidas
 *  se debe cumplir la condición de que no existan bits superpuestos entre
 *  2 máscaras, y que no existan huecos (bits en 0) entre ellas.
 *  
 *  @returns	Verdadero si las máscaras son válidas y falso en caso contrario
 */
EDS_EXPORTAR_DLL bool EDS_LLAMADO EDS_VerificarMascaras(const EDS_MascarasBits* mascaras);


/**
 *  Crea una estructura de imagen vacía asignando la memoria necesaria para
 *  el mapa de bits e inicializando sus valores.
 *  Inicializa todo el mapa de bits con pixeles negros totalmente transparentes
 *  o con la entrada 0 de la paleta de colores en caso de que la profundidad
 *  de color sea de 8 bpp o menor.
 *  Si la profundidad de color es de 8 bpp o menos, se asignará la memoria
 *  necesaria también para la paleta de colores y se inicializará con la paleta
 *  estándar.
 *  
 *  @param ancho	Ancho del mapa de bits en pixeles
 *  @param alto		Alto del mapa de bits en pixeles
 *  @param bpp		Profundidad de color del mapa de bits en bits por pixel
 * 					(valores válidos: 1, 4, 8 y 32)
 * 
 *  @returns		Imagen vacía con las dimensiones especificados
 */
EDS_EXPORTAR_DLL EDS_Imagen* EDS_LLAMADO EDS_CrearImagenVacia(uint32_t ancho, uint32_t alto, uint8_t bpp);


/**
 *  Crea una copia idéntica de la imagen dada y devuelve el puntero de la
 *  imagen copiada.
 *  
 *  @param copia	Imagen a copiar
 * 
 *  @returns		Copia de la imagen proporcionada
 */
EDS_EXPORTAR_DLL EDS_Imagen* EDS_LLAMADO EDS_CopiarImagen(const EDS_Imagen* copia);


/**
 *  Libera la memoria ocupada por la estructura de imagen.
 *  @remarks Se recomienda asignar el puntero a NULL después de haber llamado
 *           esta función para evitar violaciones de segmento.
 *  
 *  @param imagen	Puntero a estructura de imagen a liberar
 */
EDS_EXPORTAR_DLL void EDS_LLAMADO EDS_DestruirImagen(EDS_Imagen* imagen);



#ifdef __cplusplus
}
#endif


#endif /* _EDS_TIPOS */

