/* 
 * ----- Biblioteca BMP genérica por SamuelCoral -----
 * 
 * Usada para abrir, guardar y realizar modificaciones a imágenes BMP
 * sin importar la plataforma de ejecución.
 * 
 */


#ifndef __LIB_BMP__
#define __LIB_BMP__


#ifdef _WIN32
	#define LLAMADO __cdecl
	#ifdef LIBEDS_EXPORTS
		#define EXPORTAR_DLL __declspec(dllexport)
	#else
		#define EXPORTAR_DLL __declspec(dllimport)
	#endif
#else
	#define LLAMADO
	#define EXPORTAR_DLL
#endif


#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif



//////////////////////////
//      CONSTANTES      //
//////////////////////////


//Paletas de colores estandar

extern const uint32_t colores_std_1[2];
extern const uint32_t colores_std_4[16];
extern const uint32_t colores_std_8[256];


#define MASCARAS_VACIAS		(MASCARAS_BITS){0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define RGB888				(MASCARAS_BITS){0x00FF0000, 0x0000FF00, 0x000000FF, 0x00000000}
#define RGBA8888			(MASCARAS_BITS){0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000}
#define RGB555				(MASCARAS_BITS){0x00007C00, 0x000003E0, 0x0000001F, 0x00000000}
#define RGBA5551			(MASCARAS_BITS){0x00007C00, 0x000003E0, 0x0000001F, 0x00008000}
#define RGB565				(MASCARAS_BITS){0x0000F800, 0x000007E0, 0x0000001F, 0x00000000}



/////////////////////////////
//      ENUMERACIONES      //
/////////////////////////////


enum TIPO_BITMAP {
	
	BMP_TA_BM	= 0x4D42,	// Mapa de bits de Windows
	BMP_TA_BA	= 0x4142,	// Estructura de arreglo de mapa de bits de OS/2
	BMP_TA_CI	= 0x4943,	// Estructura de color de ícono de OS/2
	BMP_TA_CP	= 0x5043,	// Color constante de puntero de mouse de OS/2
	BMP_TA_IC	= 0x4349,	// Estructura de ícono de OS/2
	BMP_TA_PT	= 0x5450	// Puntero de mouse de OS/2
};


enum VERSION_DIB {
	
	BMP_DIB_WIN20	= 12,	//BITMAPCOREHEADER
	BMP_DIB_WINNT	= 40,	//BITMAPINFOHEADER
	BMP_DIB_WIN95	= 108,
	BMP_DIB_WIN98	= 124,
	BMP_DIB_OS2		= 64
};


enum METODO_COMPRESION {
	
	BMP_MC_RGB				= 0,
	BMP_MC_RLE8				= 1,
	BMP_MC_RLE4				= 2,
	BMP_MC_BITFIELDS		= 3,
	BMP_MC_JPEG				= 4,
	BMP_MC_PNG				= 5,
	BMP_MC_ALPHABITFIELDS	= 6,
	BMP_MC_CMYK				= 11,
	BMP_MC_CMYKRLE8			= 12,
	BMP_MC_CMYKRLE4			= 13
};


enum ESPACIO_COLOR {
	
	BMP_ECL_sRGB		= 0x73524742,	//'sRGB'
	BMP_ECL_WINDOWS		= 0x57696E20,	//'Win '
	BMP_ECL_CALIBRADO	= 0,
	BMP_ECL_ARCHIVO		= 0x4C494E4B,	//'LINK'
	BMP_ECL_EMBEDIDO	= 0x4D424544,	//'MBED'
};


enum INTENCION_RENDERIZADO {
	
	BMP_IR_ABSCOLOR	= 8,
	BMP_IR_NEGOCIOS	= 1,
	BMP_IR_GRAFICOS	= 2,
	BMP_IR_IMAGENES	= 4
};



///////////////////////////
//      ESTRUCTURAS      //
///////////////////////////


//Para alinear los datos de byte en byte y facilitar su lectura y escritura
#pragma pack(push, 2)

/* 
 * Estructura que contiene las máscaras de bits que se usarán en las imágenes cuya compresión
 * sea BMP_BITFIELDS
 * 
 */
typedef struct _mascaras_bits {
	
	uint32_t rojo;
	uint32_t verde;
	uint32_t azul;
	uint32_t alpha;
	
} MASCARAS_BITS;


//Estructura de las coordenadas de un punto en el espacio de color
typedef struct _coordenadas_color {
	
	uint32_t X;
	uint32_t Y;
	uint32_t Z;
	
} COORDENADAS_COLOR;


//Estructura de las coordenadas de los puntos de los colores primarios en el espacio de color
typedef struct _coordenadas_colores {
	
	COORDENADAS_COLOR rojo;
	COORDENADAS_COLOR verde;
	COORDENADAS_COLOR azul;
	
} COORDENADAS_COLORES;


//Estructura de la información del Gamma de los colores primarios
typedef struct _gamma_colores {
	
	uint32_t rojo;
	uint32_t verde;
	uint32_t azul;
	
} GAMMA_COLORES;


/* 
 * Estructura de cabecera DIB para mapas de bits de Windows 2.0
 * Esta estructura tiene pocas limitantes y debería ser suficiente para la mayoria
 * de los usuarios, sin embargo no es la mejor recomendada.
 * 
 * Características:
 * 
 * - Resolución máxima de 32767 x 32767 pixeles
 * - Profundidades de color de 1, 4, 8 y 24 bpp
 * - Paleta de colores RGB
 * 
 */
typedef struct _bmpv2header {
	
	uint32_t	tam_dib;	// Tamaño de esta cabecera
	uint16_t	ancho;		// Longitud de la imagen en pixeles
	int16_t		alto;		// Altitud de la imagen en pixeles (si es un número negativo, la imagen estará de cabeza)
	uint16_t	planos;		// Número de planos de color (debe ser 1)
	uint16_t	bpp;		// Profundidad de color en bits por pixel del mapa de bits (para esta versión no se soportan mas de 24 bpp)
	
} BMPV2HEADER;


/* 
 * Estructura de cabecera DIB para mapas de bits de Windows 3.x y Windows NT
 * Esta estructura no tiene casi ninguna limitante, y es la recomendada para la mayoría
 * de los usuarios, además es la usada por default en esta biblioteca.
 * 
 * Nuevas características:
 * 
 * - Resolución máxima de 32767 x 32767 pixeles
 * - Profundidades de color de 1, 4, 8, 16, 24 y 32 bpp
 * - Paleta de colores XRGB
 * - Soporte para compresión de imagen
 * - Información de resolución de impresión
 * 
 */
typedef struct _bmpv3header {
	
	uint32_t	tam_dib;				// Tamaño de esta cabecera
	uint32_t	ancho;					// Longitud de la imagen en pixeles
	int32_t		alto;					// Altitud de la imagen en pixeles (si es un número negativo, la imagen estará de cabeza)
	uint16_t	planos;					// Número de planos de color (debe ser 1)
	uint16_t	bpp;					// Profundidad de color en bits por pixel del mapa de bits
	uint32_t	compresion;				// Método de compresión implementado en el mapa de bits
	uint32_t	tam_bitmap;				// Tamaño del mapa de bits en bytes (solo del mapa de bits, no del archivo completo)
	uint32_t	res_horizontal;			// Resolución de impresión horizontal en pixeles por metro
	uint32_t	res_vertical;			// Resolución de impresión vertical en pixel por metro
	uint32_t	colores;				// Número de colores en la paleta (es igual a 2^bpp pero es ignorado)
	uint32_t	colores_importantes;	// Colores importantes usados o 0 cuando todos son importantes (generalmente ignorado)
	
} BMPV3HEADER;


/* 
 * Estructura de cabecera DIB para mapas de bits de Windows 95
 * Esta estructura es idéntica a la anterior con la excepción que se ha agregado la información
 * de las máscaras de bits en la cabecera, en la versión anterior eran opcionales y solo se
 * especificaban si se ocupaban, ahora siempre están presentes.
 * También se ha agregado la información del espacio de color y corrección Gamma.
 * 
 * Nuevas características:
 * 
 * - Paleta de colores ARGB
 * - Máscaras de bits ahora con canal Alpha
 * - Información del espacio de color
 * - Corrección Gamma
 * 
 */
typedef struct _bmpv4header {
	
	//Los campos anteriores son exactamente los mismos que los de la anterior cabecera
	//La información de las máscaras de bits está implementada fuera de la cabecera
	
	uint32_t			tipo_espacio_color;		// Un elemento de la enumeracion ESPACIOS_COLOR
	COORDENADAS_COLORES	puntos_fin;				// Coordenadas de los puntos finales de los colores en el espacio de color CIE 1931 XYZ (usada solo si se especifica ECL_CALIBRADO)
	GAMMA_COLORES		gamma;					// Gamma de los colores en el formato FXPT2DOT30 (flotante de 2 bits de mantisa y 30 bits del exponente)
	
} BMPV4HEADER;


/* 
 * Estructura de cabecera DIB para mapas de bits de Windows 98
 * Esta estructura es nuevamente idéntica a la anterior, solo con campos adicionales.
 * Esta cabecera añade soporte a perfiles de color ICC, también añadió un campo que
 * sugiere un modo de renderizado y un campo reservado opcional.
 * 
 * Nuevas características:
 * 
 * - Información del modo de renderizado sugerido
 * - Soporte a perfiles de color ICC
 * 
 */
typedef struct _bmpv5header {
	
	//Los campos anteriores son exactamente los mismos que los de la anterior cabecera
	
	uint32_t	modo_renderizado;	// Un elemento de la enumeracion INTENCION_RENDERIZADO
	uint32_t	dir_perfil;			// Posición a partir del comienzo de esta cabecera del perfil ICC si el espacio de color está embedido o enlazado
	uint32_t	tam_perfil;			// Tamaño en bytes del perfil ICC si está embedido
	uint32_t	reservado;			// Espacio reservado (no usado)
	
} BMPV5HEADER;


/* 
 * Estructura de encabezado de todos los archivos de mapas de bits de Windows
 * (a partir de la versión 2.0).
 * 
 */
typedef struct _bmpfileheader {
	
	uint16_t	tipo;			// Identificador de tipo de archivo, (debe ser uno de los que se encuentran en la numeración TIPOS_BITMAP)
	uint32_t	tam_archivo;	// Tamaño del archivo de imagen en bytes;
	uint16_t	reservado_1;	// Espacio reservado (no usado)
	uint16_t	reservado_2;	// Espacio reservado (no usado)
	uint32_t	dir_bitmap;		// Posición de inicio del mapa de bits en el archivo
	
} BMPFILEHEADER;


//Fin de la regla de alineamiento
#pragma pack(pop)


/* 
 * Estructura con punteros a todas las posibles estructuras de cabeceras DIB.
 * Prefiero hacer esto que hacer casting a un puntero void
 * 
 */
typedef struct _dib_header {
	
	uint32_t		ver;
	BMPV2HEADER*	dib_win20;
	BMPV3HEADER*	dib_winnt;
	BMPV4HEADER*	dib_win95;
	BMPV5HEADER*	dib_win98;
	
} DIB_HEADER;



//Estructura del archivo mapa de bits utilizada en la mayoría de las fuciones de esta biblioteca
typedef struct _imagen_bmp {
	
	BMPFILEHEADER	cabecera;		// Cabecera de inicio del archivo (obligatoria y con la misma estructura para todos los mapas de bits)
	DIB_HEADER		dib_info;		// Cabecera de información detallada del mapa de bits (variante para cada plataforma)
	uint32_t*		paleta;			// Paleta de colores si la imagen tiene una profundidad de color menor o igual a 8 bpp
	MASCARAS_BITS*	bitfields;		// Máscaras de bits en caso de que la compresión sea BMP_BITFIELDS
	char*			ruta_perfil;	// Ruta de la ubicación del archivo de perfil de color ICC en caso de que sea enlazado
	void*			perfil_icc;		// Información del perfil de color ICC en caso de que esté embedido (desconocido, pero no se descarta)
	void*			bitmap;			// Mapa de bis
	
} IMAGEN_BMP;



/////////////////////////
//      FUNCIONES      //
/////////////////////////


/*
 * Devuelve el mensaje de error si algo salió mal al realizar una operación
 * en esta biblioteca.
 * 
 */
EXPORTAR_DLL const char* LLAMADO error_bmp();


/* 
 * Crea y asigna la memoria necesaria para un archivo de mapa de bits estándar.
 * Devuelve el puntero a la estructura de la imagen creada.
 * 
 * Las características de este mapa de bits son:
 * 
 * - Archivo de tipo BM (mapa de bits de Windows)
 * - Cabecera DIB del tipo BITMAPINFOHEADER (cabecera DIB de Windows NT y posteriores)
 * - Sin información en los campos reservados
 * - Medidas de impresión sin especificar
 * - Formato de pixel RGB sin compresión
 * 
 * 
 * --- PARÁMETROS ---
 * 
 * ancho	- Longitud del mapa de bits
 * alto		- Altitud del mapa de bits
 * bpp		- Profundidad de color de la imagen en bits por pixel (para Windows son válidos 1, 4, 8, 16, 24 ó 32)
 * 
 */
EXPORTAR_DLL IMAGEN_BMP* LLAMADO crear_bmp_vacio(uint32_t ancho, int32_t alto, uint16_t bpp);


/* 
 * Carga un archivo de mapa de bits creado anteriormente y almacenado en la ruta especificada.
 * Devuelve el puntero a la estructura de la imagen cargada.
 * 
 * NOTA: aún no se pueden cargar mapas de bits que no cumplan con las siguientes características:
 * 
 * - El tipo de archivo debe ser BM (mapa de bits de Windows)
 * - Los campos reservados deben estar vacios (aunque no necesariamente, pero podría causar errores)
 * - Solo debe existir un plano de color.
 * 
 * En caso de que el archivo esté dañado o no cumpla con características mencionadas
 * la función devolverá NULO y el motivo específico podrá obtenerse con la función: error_bmp
 * 
 * --- PARÁMETROS ---
 * 
 * ruta_archivo	- Ruta y nombre del archivo BMP a ser cargado
 * 
 */
EXPORTAR_DLL IMAGEN_BMP* LLAMADO cargar_bmp(const char* ruta_archivo);


/* 
 * Guarda un mapa de bits almacenado en memoria hacia un archivo en la ruta especificada.
 * Si el puntero mandado a guardar es nulo la función se detendrá y no guardará el archivo.
 * Tampoco lo hará si la ruta especificada es inaccesible.
 * Si ocurre un error se puede obtener el motivo con la función: error_bmp
 * 
 * NOTA: No se verificará si el mapa de bits estará dañado, se asume que fué modificado solo con estas funciones
 *       Si el mapa de bits está dañado podría causar una salida anormal del programa.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen		- Puntero a estructura del archivo de mapa de bits a ser guardado
 * ruta_archivo	- Ruta y nombre del archivo a ser guardado
 * 
 */
EXPORTAR_DLL void LLAMADO guardar_bmp(IMAGEN_BMP* imagen, const char* ruta_archivo);


/* 
 * Copia los datos almacenados en una estructura de archivo de mapa de bits
 * y los devuelve en un nuevo puntero.
 * 
 * --- PARÁMETROS ---
 * 
 * origen	- Puntero a estructura de archivo de mapa de bits a ser copiado
 * 
 */
EXPORTAR_DLL IMAGEN_BMP* LLAMADO copiar_bmp(IMAGEN_BMP* origen);


/* 
 * Invierte el signo del alto de la estructura de archivo de mapa de bits para indicar a los programas
 * que debe ser leído de cabeza.
 * NOTA: Esta operación solo puede realizarce sobre mapas de bits sin compresión (BMP_MC_BITFIELDS o BMP_MC_RGB)
 * 
 * --- PARÁMETROS ---
 * 
 * imagen	- Puntero a estructura de archivo de mapa de bits que desea voltearse de cabeza
 * 
 */
EXPORTAR_DLL void LLAMADO voltear_bmp(IMAGEN_BMP* imagen);


/* 
 * Ajusta la resolución de impresión de mapa de bits en pixeles por metro.
 * NOTA: No funciona para mapas de bits de versión BMP_DIB_WIN20, la función simplemente no hará nada de lo contrario.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen			- Puntero a estructura de mapa de bits de la que se modificará la resolución de impresión
 * res_horizontal	- Resolución de impresión horizontal en pixeles por metro
 * res_vertical		- Resolución de impresión vertical en pixeles por metro
 * 
 */
EXPORTAR_DLL void LLAMADO ajustar_res_impresion_bmp(IMAGEN_BMP* imagen, uint32_t res_horizontal, uint32_t res_vertical);


/* 
 * Cambia la versión de la cabecera DIB del archivo de mapa de bits especificado por
 * otro que esté soportado.
 * Se eliminará la estructura de la cabecera DIB anterior y se asignaran los mismos datos
 * para la nueva estructura.
 * Los campos que no contenga la cabecera anterior serán establecidos como los valores
 * por default para la nueva cabecera.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen	- Puntero a estructura de archivo de mapa de bits a convertir
 * tipo_dib	- Nueva versión de la cabecera del archivo (debe ser uno de la enumeracion VERIONES_DIB)
 * 
 */
EXPORTAR_DLL void LLAMADO convertir_dib_bmp(IMAGEN_BMP* imagen, uint32_t tipo_dib);


/* 
 * Comprime o descomprime un mapa de bits utilizando el algoritmo RLE.
 * NOTA: Este formato solo se puede implementar en mapas de bits con profundidades
 * de color de 4 u 8 bpp.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Puntero a estructura de archivo de mapa de bits a comprimir o descomprimir
 * 
 */
EXPORTAR_DLL void LLAMADO compresion_rle_bmp(IMAGEN_BMP* imagen);


/* 
 * Cambia el formato de pixel de una estructura de archivo BMP alterando su profundidad de color
 * ya sea incrementándolo o decrementándolo y opcionalmente agregando o cambiando si ya existe
 * una máscara de bits.
 * 
 * NOTAS:
 * 
 * - Solo se pueden transformar imágenes a 16, 24 y 32 bpp
 * - Las imágenes cuya versión de cabecera DIB sea BMP_WIN_20 solo admiten una profundidad de color de 24 bpp y no soportan máscaras de bits
 *   así que puedes mandar cualquiera y se tomará siempre la máscara RGR888
 * - Si se elige una profundidad de 24 bpp no se podrán agregar máscaras de bits también se tomará por default RGB888
 * - El canal alpha de las máscaras de bits no tendrá efecto si la versión del mapa de bits es BMP_WIN_NT
 * 
 * --- PARÁMETROS ---
 * 
 * imagen	- Puntero a estructura de archivo de mapa de bits a alterar
 * bpp		- Profundidad de color nueva
 * mascaras	- Máscaras de bits opcionales (inserta MASCARAS_VACIAS para quitarlas o no agregarlas)
 * 
 */
EXPORTAR_DLL void LLAMADO cambiar_formato_pixel_bmp(IMAGEN_BMP* imagen, uint16_t bpp, MASCARAS_BITS mascaras);


/* 
 * Borra la información del perfil de color ICC de un mapa de bits en memoria
 * quitando la ruta del archivo de perfil ICC enlazado si es que existía o
 * el bloque de memoria del perfil ICC embedido si es el caso.
 * Reestablece el espacio de color a sRGB.
 * NOTA: Solo funciona para mapas de bits de versión BMP_DIB_WIN98, la función simplemente no hará nada de lo contrario.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Puntero a estructura de archivo de mapa de bits del que se quitará la información del espacio de color
 * 
 */
EXPORTAR_DLL void LLAMADO quitar_perfil_icc_bmp(IMAGEN_BMP* imagen);


/* 
 * Establece una ruta de archivo de perfil ICC para el espacio de color de un mapa de bits.
 * 
 * NOTAS:
 * 
 * - Solo funciona para mapas de bits de versión BMP_DIB_WIN98, la función simplemente no hará nada de lo contrario
 * - Cualquier información del espacio de color anterior será suprimida
 * - No se verificará la existencia del archivo, además debe ingresar solo caracteres codificados en Windows-1252
 * 
 * 
 * --- PARÁMETROS ---
 * 
 * imagen		- Puntero a estructura de archivo de mapa de bits al que se le establecerá la ruta del perfil ICC
 * ruta_archivo	- Cadena que especifica la ruta donde se encuentra el perfil ICC
 * 
 */
EXPORTAR_DLL void LLAMADO establecer_ecl_archivo_bmp(IMAGEN_BMP* imagen, const char* ruta_archivo);


/* 
 * Establece un perfil ICC y lo asigna como espacio de color embedido a un para de bits.
 * 
 * NOTAS:
 * 
 * - Solo funciona para mapas de bits de versión BMP_DIB_WIN98, la función simplemente no hará nada de lo contrario
 * - Cualquier información del espacio de color anterior será suprimida
 * - No se verifica la integridad del perfil ICC, pero el tamaño especificado debe ser mayor a 0
 * 
 * 
 * --- PARÁMETROS ---
 * 
 * imagen		- Puntero a estructura de archivo de mapa de bits donde se ingresará el perfil ICC
 * perfil_icc	- Puntero de la memoria del pefil ICC a copiar
 * tam_perfil	- Tamaño en bytes del perfil ICC a copiar
 * 
 */
EXPORTAR_DLL void LLAMADO establecer_ecl_embedido_bmp(IMAGEN_BMP* imagen, const void* perfil_icc, uint32_t tam_perfil);


/* 
 * Establece la información de espacio de color dadas la estructura de coordenadas de los puntos finales en el espacio
 * de color CIE 1931 XYZ y la estructura de corrección gamma de los colores.
 * 
 * NOTAS:
 * 
 * - Solo funciona para mapas de bits de versión BMP_DIB_WIN95 o superior, la función simplemente no hará nada de lo contrario
 * - Cualquier información del espacio de color anterior será suprimida
 * 
 * 
 * --- PARÁMETROS ---
 * 
 * imagen		- Puntero a estructura de archivo de mapa de bits donde se ingresará la información del espacio de color
 * puntos_fin	- Coordenadas de los puntos finales en el espacio de color CIE 1931 XYZ
 * gamma		- Corrección gamma de los colores en el formato FXPT2DOT30 (flotante de 2 bits de mantisa y 30 bits del exponente)
 * 
 */
EXPORTAR_DLL void LLAMADO establecer_ecl_calibrado_bmp(IMAGEN_BMP* imagen, COORDENADAS_COLORES puntos_fin, GAMMA_COLORES gamma);


/* 
 * Establece el espacio de color dado un elemento de la enumeración ESPACIOS_COLOR para un mapa de bits.
 * que no no requiere información extra de calibración.
 * 
 * NOTAS:
 * 
 * - Solo funciona para mapas de bits de versión BMP_DIB_WIN95 o superior, la función simplemente no hará nada de lo contrario
 * - Cualquier información del espacio de color anterior será suprimida
 * - Se debe elegir cualquier valor que no sea BMP_ECL_ARCHIVO, BMP_ECL_CALIBRADO ni BMP_ECL_EMBEDIDO, debe usar la función
 *   correspondiente si desea asignar alguno de ellos.
 * 
 * 
 * --- PARÁMETROS ---
 * 
 * imagen			- Puntero a estructura de archivo de mapa de bits donde se ingresará la información del espacio de color
 * espacio_color	- Elemento de la enumeración  ESPACIOS_COLOR
 * 
 */
EXPORTAR_DLL void LLAMADO establecer_ecl_generico_bmp(IMAGEN_BMP* imagen, uint32_t espacio_color);


/* 
 * Estblece la intención de renderizado dado un elemento de la enumeración INTENCION_RENDERIZADO de un mapa de bits.
 * 
 * NOTAS:
 * 
 * - Solo funciona para mapas de bits de versión BMP_DIB_WIN98, la función simplemente no hará nada de lo contrario
 * - Cualquier información anterior será suprimida
 * 
 * 
 * --- PARÁMETROS ---
 * 
 * imagen			- Puntero a estructura de archivo de mapa de bits donde se ingresará la información del tipo de renderizado
 * modo_renderizado	- Elemento de la enumeración INTENCION_RENDERIZADO
 * 
 */
EXPORTAR_DLL void LLAMADO establecer_intencion_renderizado_bmp(IMAGEN_BMP* imagen, uint32_t modo_renderizado);


/*
 * Libera la memoria ocupada por una estructura de archivo de imagen
 * en caso de que ya no se ocupe o para reciclar el puntero.
 * 
 * NOTA: Se recomienda asignar el puntero liberado en NULO después de llamar a esta función
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Puntero a estructura de archivo de mapa de bits a ser liberado
 * 
 */
EXPORTAR_DLL void LLAMADO destruir_puntero_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve el tamaño en bytes que debe tener una linea horizontal de un mapa de bits.
 * 
 * --- PARÁMETROS ---
 * 
 * ancho	- Ancho del mapa de bits
 * bpp		- Profundidad de color del mapa de bits en bits por pixel
 * 
 */
#define tam_linea(ancho, bpp) (uint32_t)((((uint32_t)(ancho) * (uint16_t)(bpp) + 31) & ~31) >> 3)


/* 
 * Crea una máscara de bits de acuerdo al número de bits para cada color dado.
 * NOTA: Recuerde que la máxima produnfidad de color es 32 bits por lo que la suma de cada color
 *       no debe exceder esta cantidad.
 * 
 * --- PARÁMETROS ---
 * 
 * rojo		- Cantidad de bits para el color rojo de la máscara
 * verde	- Cantidad de bits para el color verde de la máscara
 * azul		- Cantidad de bits para el color azul de la máscara
 * alpha	- Cantidad de bits para el canal alpha de la máscara
 * 
 */
EXPORTAR_DLL MASCARAS_BITS LLAMADO crear_mascaras(uint32_t rojo, uint32_t verde, uint32_t azul, uint32_t alpha);


/* 
 * Devuelve verdadero cuando las máscaras de bits sean válidas.
 * Las condiciones que se deben de cumplir para que las máscaras sean válidas son:
 * 
 * - Las máscaras deben de ser contiguas (sin huecos entre colores)
 * - No debe haber superposición de bits entre máscaras
 * 
 * --- PARÁMETROS ---
 * 
 * mascaras - Máscaras de bits a comprobar
 * 
 */
EXPORTAR_DLL bool LLAMADO mascaras_validas(MASCARAS_BITS mascaras);


/* 
 * Devuelve la longitud en pixeles de un mapa de bits en memoria.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar la longitud
 * 
 */
EXPORTAR_DLL uint32_t LLAMADO ancho_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve la altitud en pixeles de un mapa de bits en memoria.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar la altitud
 * 
 */
EXPORTAR_DLL int32_t LLAMADO alto_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve profundidad de color en bits por pixel de un mapa de bits en memoria.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar la profundidad de color.
 * 
 */
EXPORTAR_DLL uint16_t LLAMADO bpp_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve el número de planos de color de un mapa de bits en memoria.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar el número de planos de color
 * 
 */
EXPORTAR_DLL uint16_t LLAMADO planos_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve el método de compresión de un mapa de bits en memoria.
 * Se devuelve un elemento del listado METODO_COMPRESION
 * NOTA: Esta información solo se especifica si la versión del mapa de bits es BMP_DIB_WINNT o superior, de lo contrario devolverá BMP_MC_RGB.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar el método de compresión
 * 
 */
EXPORTAR_DLL uint32_t LLAMADO compresion_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve la resolución de impresión horizontal de un mapa de bits en memoria en pixeles por metro.
 * NOTA: Esta información solo se especifica si la versión del mapa de bits es BMP_DIB_WINNT o superior, de lo contrario devolverá 0.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar la resolución de impresión horizontal
 * 
 */
EXPORTAR_DLL uint32_t LLAMADO res_horizontal_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve la resolución de impresión vertical de un mapa de bits en memoria en pixeles por metro.
 * NOTA: Esta información solo se especifica si la versión del mapa de bits es BMP_DIB_WINNT o superior, de lo contrario devolverá 0.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar la resolución de impresión vertical
 * 
 */
EXPORTAR_DLL uint32_t LLAMADO res_vertical_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve el estacio de color de un mapa de bits en memoria.
 * Se devuelve un elemento del listado ESPACIOS_COLOR
 * NOTA: Esta información solo se especifica si la versión del mapa de bits es BMP_DIB_WIN95 o superior, de lo contrario devolverá BMP_ECL_sRGB.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar el espacio de color
 * 
 */
EXPORTAR_DLL uint32_t LLAMADO espacio_color_bmp(IMAGEN_BMP* imagen);


/* 
 * Devuelve el método de renderizado de un mapa de bits en memoria.
 * Se devuelve un elemento del listado INTENCION_RENDERIZADO
 * NOTA: Esta información solo se especifica si la versión del mapa de bits es BMP_DIB_WIN98, de lo contrario devolverá BMP_IR_GRAFICOS.
 * 
 * --- PARÁMETROS ---
 * 
 * imagen - Imagen a buscar el modo de renderizado
 * 
 */
EXPORTAR_DLL uint32_t LLAMADO modo_renderizado_bmp(IMAGEN_BMP* imagen);


#ifdef __cplusplus
}
#endif

#endif

