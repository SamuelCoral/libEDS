#include "EDS/EDS_bmp.h"
#include "EDS/EDS_color.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Para convertir datos de Big-endian a Little-endian o visceversa
// Útil para este formato de archivo que está en Big-endian
// Y la arquitectura de los procesadores x86 es Little-endian
#define CAMBIAR_ENDIANNES_32(x) (((d & 0x000000FF) << 24) | \
		((d & 0x0000FF00) << 8) | \
		((d & 0x00FF0000) >> 8) | \
		((d & 0xFF000000) >> 24))


int main(int argc, char const *argv[])
{
	FILE* archivo = fopen(argv[1], "rb");
	if(!archivo) return 1;

	uint32_t d = 0;
	// Los primeros 2 bytes de un archivo idx deben ser 0
	fread(&d, 2, 1, archivo);
	if(d) return 2;

	/**
	 * Tipo de dato en el que se almacenarán los datos
	 * 
	 * 0x08: unsigned byte
	 * 0x09: signed byte
	 * 0x0B: short (2 bytes)
	 * 0x0C: int (4 bytes)
	 * 0x0D: float (4 bytes)
	 * 0x0E: double (8 bytes)
	 * 
	 * Nos limitaremos a sólo leer archivos cuyo tipo de dato sea 8
	 */
	fread(&d, 1, 1, archivo);
	if(d != 8) return 2;

	// Leeremos archivos de sólo 3 dimensiones
	fread(&d, 1, 1, archivo);
	if(d != 3) return 2;

	// Dimensiones de cada imagen
	uint32_t n, w, h;
	fread(&d, 4, 1, archivo);
	n = CAMBIAR_ENDIANNES_32(d);
	fread(&d, 4, 1, archivo);
	w = CAMBIAR_ENDIANNES_32(d);
	fread(&d, 4, 1, archivo);
	h = CAMBIAR_ENDIANNES_32(d);

	EDS_Imagen* img = EDS_CrearImagenVacia(w, h, 8);
	int i, j, k;

	for(i = 0; i < 0x100; i++)
		img->paleta[0xFF - i] = (EDS_Color){ .c = { i, i, i } };

	fseek(archivo, atoi(argv[2]) * w * h, SEEK_CUR);
	for(i = 0; i < w; i++) for(j = 0; j < h; j++)
	{
		fread(&d, 1, 1, archivo);
		EDS_DibujarPixel(img, i, j, d);
	}
	
	EDS_GuardarBMP(img, argv[3], EDS_BMP_B_COMP_RLE, NULL);

	fclose(archivo);
	return 0;
}

