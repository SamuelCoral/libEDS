#include <stdio.h>
#include <EDS/EDS.h>


int main(int argc, char* args[]) {
	
	if(argc != 2) { 
		
		printf("Modo de empleo: bmpinfo [FICHERO]\n");
		return 1;
	}
	
	IMAGEN_BMP *i = cargar_bmp(args[1]);
	if(i == NULL) {
		
		printf("Error: %s\n", error_bmp());
		return 1;
	}
	
	printf("\n\n ----- Información en la cabecera principal -----\n\n");
	
	printf("Tipo de archivo:                 Bitmap de Windows 2.0 o posterior\n");
	printf("Tamaño de archivo:               %d bytes\n", i->cabecera.tam_archivo);
	printf("Valor del campo reservado 1:     0x%X\n", i->cabecera.reservado_1);
	printf("Valor del campo reservado 2:     0x%X\n", i->cabecera.reservado_2);
	printf("Byte del comienzo del bitmap:    0x%X\n", i->cabecera.dir_bitmap);
	
	printf("\n\n ----- Información de la cabecera DIB -----\n\n");
	printf("Versión de cabecera DIB:    Windows ");
	
	switch(i->dib_info.ver) {
		
		case BMP_DIB_WIN20: puts("2.0"); break;
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT: puts((i->dib_info.dib_winnt->compresion == BMP_MC_BITFIELDS || i->dib_info.ver > BMP_DIB_WINNT) ? "NT" : "3.0"); break;
		case BMP_DIB_WIN95: puts("95"); break;
		case BMP_DIB_WIN98: puts("98"); break;
	}
	
	switch(i->dib_info.ver) {
		
		case BMP_DIB_WIN20: {
			
			printf("Ancho de la imagen:         %d pixeles\n", i->dib_info.dib_win20->ancho);
			printf("Alto de la imagen:          %d pixeles\n", i->dib_info.dib_win20->alto);
			printf("Planos de color:            %d\n", i->dib_info.dib_win20->planos);
			printf("Profundidad de color:       %d bits por pixel\n", i->dib_info.dib_win20->bpp);
			
		} break;
		
		
		case BMP_DIB_WIN95:
		case BMP_DIB_WIN98:
		case BMP_DIB_WINNT + 12:
		case BMP_DIB_WINNT + 16:
		case BMP_DIB_WINNT: {
			
			printf("Ancho de la imagen:         %d pixeles\n", i->dib_info.dib_winnt->ancho);
			printf("Alto de la imagen:          %d pixeles\n", i->dib_info.dib_winnt->alto);
			printf("Planos de color:            %d\n", i->dib_info.dib_winnt->planos);
			printf("Profundidad de color:       %d bits por pixel\n", i->dib_info.dib_winnt->bpp);
			printf("Método de compresión:       ");
			switch(i->dib_info.dib_winnt->compresion) {
				
				case BMP_MC_RGB: printf("RGB (sin compresión)\n"); break;
				case BMP_MC_RLE8: printf("RLE8\n"); break;
				case BMP_MC_RLE4: printf("RLE4\n"); break;
				case BMP_MC_BITFIELDS: printf("BITFIELDS (sin compresión)\n"); break;
				case BMP_MC_JPEG: printf("JPEG\n"); break;
				case BMP_MC_PNG: printf("PNG\n"); break;
				case BMP_MC_ALPHABITFIELDS: printf("ALPHABITFIELDS (sin compresión)\n"); break;
				case BMP_MC_CMYK: printf("CMYK (sin compresión)\n"); break;
				case BMP_MC_CMYKRLE8: printf("CMYK con RLE8\n"); break;
				case BMP_MC_CMYKRLE4: printf("CMYK con RLE4\n"); break;
				default: puts("[Desconocido]");
			}
			
			printf("Tamaño del bitmap:          %d bytes\n", i->dib_info.dib_winnt->tam_bitmap);
			printf("Resolución horizontal:      %d pixeles por metro\n", i->dib_info.dib_winnt->res_horizontal);
			printf("Resolución vertical:        %d pixeles por metro\n", i->dib_info.dib_winnt->res_vertical);
			printf("Colores en la paleta:       %d\n", i->dib_info.dib_winnt->colores);
			printf("Colores importantes:        %d\n", i->dib_info.dib_winnt->colores_importantes);
			
		} break;
		
		
		default: printf("Cabecera DIB desconocida\n");
	}
	
	if(i->dib_info.ver >= BMP_DIB_WIN95) {
		
		printf("Tipo de espacio de color:   ");
		switch(i->dib_info.dib_win95->tipo_espacio_color) {
			
			case BMP_ECL_sRGB: puts("sRGB"); break;
			case BMP_ECL_WINDOWS: puts("Default de Windows (sRGB)"); break;
			case BMP_ECL_CALIBRADO: puts("Calibrado"); break;
			case BMP_ECL_ARCHIVO: puts("De archivo"); break;
			case BMP_ECL_EMBEDIDO: puts("Embedido"); break;
			default: puts("[Desconocido]");
		}
		
		if(i->dib_info.ver == BMP_DIB_WIN98) {
			
			printf("Intención de renderizado:   ");
			switch(i->dib_info.dib_win98->modo_renderizado) {
				
				case BMP_IR_ABSCOLOR: puts("Colorimétrica absoluta"); break;
				case BMP_IR_NEGOCIOS: puts("Saturación (Gráficas de negocios)"); break;
				case BMP_IR_GRAFICOS: puts("Colorimétrica relativa (Diseño gráfico)"); break;
				case BMP_IR_IMAGENES: puts("Perceptual (Fotografías)"); break;
				default: puts("[Desconocido]");
			}
			
			printf("Dirección del perfil ICC:   0x%X\n", i->dib_info.dib_win98->dir_perfil);
			printf("Tamaño del perfil ICC:      %d bytes\n", i->dib_info.dib_win98->tam_perfil);
			printf("Valor del campo reservado:  0x%X\n", i->dib_info.dib_win98->reservado);
			
			if(i->dib_info.dib_win95->tipo_espacio_color == BMP_ECL_ARCHIVO) printf("\nRuta del perfil ICC:        %s\n", i->ruta_perfil);
		}
	}
	
	if(bpp_bmp(i) <= 8) {
		
		printf("\n\n ----- Colores en la paleta -----\n\n");
		int C;
		for(C = 0; C < (1 << bpp_bmp(i)); C++)
			printf("%-5d  --->      R = 0x%.2X   G = 0x%.2X   B = 0x%.2X\n", C, (uint8_t)(i->paleta[C] >> 16), (uint8_t)(i->paleta[C] >> 8), (uint8_t)(i->paleta[C] >> 0));
	}
	
	if(compresion_bmp(i) == BMP_MC_BITFIELDS) {
		
		printf("\n\n ----- Máscaras de bits -----\n\n");
		int C, n;
		printf("Rojo:     0x%.8X ", i->bitfields->rojo);
		for(C = n = 0; C < 32; C++) if((i->bitfields->rojo >> C) % 2) n++;
		printf("(%d bits)\n", n);
		printf("Verde:    0x%.8X ", i->bitfields->verde);
		for(C = n = 0; C < 32; C++) if((i->bitfields->verde >> C) % 2) n++;
		printf("(%d bits)\n", n);
		printf("Azul:     0x%.8X ", i->bitfields->azul);
		for(C = n = 0; C < 32; C++) if((i->bitfields->azul >> C) % 2) n++;
		printf("(%d bits)\n", n);
		printf("Alpha:    0x%.8X ", i->bitfields->alpha);
		for(C = n = 0; C < 32; C++) if((i->bitfields->alpha >> C) % 2) n++;
		printf("(%d bits)\n", n);
	}
	
	printf("\n\n");
	
	return 0;
}

