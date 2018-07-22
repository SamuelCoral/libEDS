#include "EDS_bmp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>



extern char EDS_Error[80];


void EDS_EscribirPixelesBPPBajo(
	FILE* archivo,
	const EDS_Imagen* imagen,
	int32_t lugares_linea,
	int* i,
	int fin,
	uint8_t pixeles_byte,
	uint8_t pixeles_chunk,
	uint8_t tam_chunk
) {

	int j, k;
	uint8_t chunk[4];
	while(*i < fin) {

		for(
			j = k = 0, memset(chunk, 0, 4);
			j < pixeles_chunk && *i < fin;
			k %= pixeles_byte
		) 
			chunk[j++ / pixeles_byte] |= imagen->mapa_bits_p[lugares_linea + (*i)++] << (8 - imagen->bpp * ++k);
		
		fwrite(chunk, 1, tam_chunk, archivo);
	}
}


void EDS_GuardarBMP(
	const EDS_Imagen* imagen,
	const char* ruta,
	uint16_t bmp_banderas,
	const EDS_MascarasBits* mascaras
) {

	if(imagen == NULL) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "La imagen de origen está dañada.");
		return;
	}

	if(mascaras != NULL) if(!EDS_VerificarMascaras(mascaras)) {

		snprintf(EDS_Error, sizeof(EDS_Error), "Las máscaras de bits proporcionadas no son válidas.");
		return;
	}

	FILE* archivo = fopen(ruta, "wb");
	if(archivo == NULL) {

		snprintf(EDS_Error, sizeof(EDS_Error), "No se pudo abrir el archivo para escritura.");
		return;
	}

	// Creamos la cabecera principal, pero no la escribimos aún en el archivo, ya que
	// el tamaño del archivo y la dirección del bitmap serán reescritas más tarde
	EDS_BMP_CabeceraArchivo cabecera = { EDS_BMP_TA_BM };
	fseek(archivo, sizeof(EDS_BMP_CabeceraArchivo), SEEK_SET);

	// Leemos la información de las banderas
	uint16_t version = bmp_banderas & EDS_BMP_B_VER;
	int8_t invertir = bmp_banderas & EDS_BMP_B_SENTIDO ? -1 : 1;
	uint16_t formato_pixel = bmp_banderas & EDS_BMP_B_FMT;

	bool usar_mascaras = false;
	bool rle = false;
	uint8_t bpp;
	int i, j, k;	// Contadores genéricos

	// Escribimos la cabecera de la versión solicitada
	if(version == EDS_BMP_B_VER_2) {

		bpp = imagen->bpp == 32 ? 24 : imagen->bpp;

		EDS_BMP_CabeceraV2 ver2 = {
			EDS_BMP_VER_2,
			imagen->ancho,
			imagen->alto * invertir,
			1,
			bpp
		};

		fwrite(&ver2, EDS_BMP_VER_2, 1, archivo);
	}
	else {
		
		bpp = imagen->bpp <= 8 ? imagen->bpp :
			formato_pixel == EDS_BMP_B_FMT_16BPP ? 16 :
			formato_pixel == EDS_BMP_B_FMT_32BPP ? 32 : 24;
		usar_mascaras = bpp > 8 && bpp != 24 &&
			(bmp_banderas & EDS_BMP_B_COMP) == EDS_BMP_B_COMP_MASCARAS &&
			mascaras != NULL;
		rle = bpp <= 8 && (bmp_banderas & EDS_BMP_B_COMP) == EDS_BMP_B_COMP_RLE;

		EDS_BMP_CabeceraV3 ver3 = {
			version == EDS_BMP_B_VER_4 ? EDS_BMP_VER_4 :
				version == EDS_BMP_B_VER_5 ? EDS_BMP_VER_5 :
				EDS_BMP_VER_3 + 16 * usar_mascaras,
			imagen->ancho,
			imagen->alto * invertir,
			1,
			bpp,
			usar_mascaras ? EDS_BMP_COMP_BITFIELDS :
				rle ? bpp == 4 ? EDS_BMP_COMP_RLE4 : EDS_BMP_COMP_RLE8 : EDS_BMP_COMP_RGB,
			0,
			EDS_BMP_DEFAULT_PPM,
			EDS_BMP_DEFAULT_PPM,
			bpp <= 8 ? 1 << bpp : 0,
			0
		};

		fwrite(&ver3, EDS_BMP_VER_3, 1, archivo);

		if(version) {
			
			// Escribiremos las máscaras de bits mas tarde en caso de ser requeridas
			fseek(archivo, 16, SEEK_CUR);

			uint32_t ecl = EDS_BMP_ECL_sRGB;
			fwrite(&ecl, 4, 1, archivo);

			// Omitimos la información de los puntos finales del espacio de color y de
			// la corrección gamma, ya que no están implementados en esta librería
			fseek(archivo, 0x30, SEEK_CUR);

			if(version == EDS_BMP_B_VER_5) {
				
				uint32_t int_rend = bmp_banderas & EDS_BMP_B_IR;
				int_rend = int_rend == EDS_BMP_B_IR_GRAFICOS ? EDS_BMP_IR_GRAFICOS :
					int_rend == EDS_BMP_B_IR_IMAGENES ? EDS_BMP_IR_IMAGENES :
					int_rend == EDS_BMP_B_IR_ABSCOLOR ? EDS_BMP_IR_ABSCOLOR : 0;

				fwrite(&int_rend, 4, 1, archivo);

				// Omitir la información del perfil de color ICC y el campo reservado
				fseek(archivo, 12, SEEK_CUR);
			}
		}
	}

	// Escribir la paleta de colores en caso de existir
	if(bpp <= 8) {

		if(version == EDS_BMP_B_VER_2) for(i = 0; i < 1 << bpp; i++)
			fwrite(imagen->paleta + i, 3, 1, archivo);
		else
			fwrite(imagen->paleta, 4, 1 << bpp, archivo);
	}

	// Escribimos el mapa de bits y recordamos su dirección de inicio en el archivo
	cabecera.inicio_bitmap = ftell(archivo);
	int32_t lugares_linea;
	uint32_t lugares_u_linea = imagen->ancho * (imagen->alto - 1);
	if(bpp <= 8) {

		uint8_t chunk[4];
		uint8_t tam_chunk = rle ? 2 : 4;
		uint8_t pixeles_chunk = (tam_chunk << 3) / bpp;
		uint8_t pixeles_byte = 8 / bpp;
		uint8_t comodin[3][2] = { {0, 0}, {0, 1} };
		for(
			lugares_linea = invertir < 0 ? 0 : lugares_u_linea, i = 0;
			lugares_linea >= 0 && lugares_linea <= lugares_u_linea;
			lugares_linea -= imagen->ancho * invertir, i = 0
		) {

			if(!rle) {

				EDS_EscribirPixelesBPPBajo(
					archivo,
					imagen,
					lugares_linea,
					&i,
					imagen->ancho,
					pixeles_byte,
					pixeles_chunk,
					tam_chunk
				);
				continue;
			}

			while(i < imagen->ancho) {

				for(j = pixeles_byte, k = 0; i + j < imagen->ancho && j < 0xFF; j++) {

					while(
						imagen->mapa_bits_p[lugares_linea + i + j + k] !=
						imagen->mapa_bits_p[lugares_linea + i + j + k - pixeles_byte] &&
						i + j + k < imagen->ancho && k < 0xFF
					) k++;

					if(k) break;
				}

				if(j > pixeles_byte || k <= 2) {

					comodin[2][0] = j - (i + j > imagen->ancho);
					comodin[2][1] = (imagen->mapa_bits_p[lugares_linea + i] << (bpp < 8 ? 4 : 0)) |
						(bpp < 8 && i + j <= imagen->ancho ? imagen->mapa_bits_p[lugares_linea + i + 1] : 0);
					fwrite(comodin[2], 1, 2, archivo);
					i += j;
				}
				
				if(k > 2) {

					comodin[2][0] = 0;
					comodin[2][1] = k;
					fwrite(comodin[2], 1, 2, archivo);
					EDS_EscribirPixelesBPPBajo(
						archivo,
						imagen,
						lugares_linea,
						&i,
						i + k,
						pixeles_byte,
						pixeles_chunk,
						tam_chunk
					);
				}
			}

			fwrite(comodin[0], 1, 2, archivo);
		}

		if(rle) fwrite(comodin[1], 1, 2, archivo);
	}
	else {

		EDS_MascarasBits mascaras_usar;
		uint32_t valores[4];
		uint8_t desplazamientos[4];
		uint8_t num_mascaras = 4;
		uint32_t pixel;
		uint32_t pixel_escribir = 0;
		uint8_t bytes_pixel = bpp >> 3;
		uint8_t bytes_extra = (((imagen->ancho * bpp + 31) & ~31) >> 3) - imagen->ancho * bytes_pixel;

		if(usar_mascaras) {

			if(!version) cabecera.inicio_bitmap += 16;
			fseek(archivo, sizeof(EDS_BMP_CabeceraArchivo) + EDS_BMP_VER_3, SEEK_SET);
			fwrite(&mascaras->m.r, 4, 1, archivo);
			fwrite(&mascaras->m.g, 4, 1, archivo);
			fwrite(&mascaras->m.b, 4, 1, archivo);
			fwrite(&mascaras->m.a, 4, 1, archivo);
			fseek(archivo, cabecera.inicio_bitmap, SEEK_SET);
			memcpy(&mascaras_usar, mascaras, 16);

			if(!mascaras_usar.m.a) num_mascaras--;
			for(i = 0; i < num_mascaras; i++) {

				pixel = mascaras_usar.v[i];
				desplazamientos[i] = 0;
				while(!(pixel & 1)) { pixel >>= 1; desplazamientos[i]++; }
				valores[i] = pixel;
			}
		}
		else if(bpp == 16) {

			mascaras_usar = EDS_ConstruirMascaras(5, 5, 5, 0);
			usar_mascaras = true;
			num_mascaras--;
			for(i = 0; i < num_mascaras; i++) {

				valores[i] = (1 << 5) - 1;
				desplazamientos[i] = 5 * i;
			}
		}

		for(
			lugares_linea = invertir < 0 ? 0 : lugares_u_linea;
			lugares_linea >= 0 && lugares_linea <= lugares_u_linea;
			lugares_linea -= imagen->ancho * invertir, fseek(archivo, bytes_extra, SEEK_CUR)
		)
			for(i = 0; i < imagen->ancho; i++) {

				pixel = imagen->mapa_bits[lugares_linea + i].v;
				if(usar_mascaras) for(j = 0, pixel_escribir = 0; j < num_mascaras; j++)
					pixel_escribir |= (uint32_t)round((uint8_t)(pixel >> (j << 3)) * valores[j] / 255.0)
						<< desplazamientos[j];
				else pixel_escribir = pixel;
				fwrite(&pixel_escribir, bytes_pixel, 1, archivo);
			}
	}

	// Escribimos la cabecera principal ahora con la información del tamaño de archivo y dirección
	// de inicio del bitmap reales, además actualizamos el tamaño del bitmap en caso de ser necesario
	cabecera.tam_archivo = ftell(archivo);
	fseek(archivo, 0, SEEK_SET);
	fwrite(&cabecera, sizeof(EDS_BMP_CabeceraArchivo), 1, archivo);
	if(version != EDS_BMP_VER_2) {

		fseek(archivo, 0x22, SEEK_SET);
		cabecera.tam_archivo -= cabecera.inicio_bitmap;
		fwrite(&cabecera.tam_archivo, 4, 1, archivo);
	}
	
	fclose(archivo);
	EDS_Error[0] = '\0';
}

