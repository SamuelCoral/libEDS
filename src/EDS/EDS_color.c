#include "EDS_color.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef __USE_MISC
#define __USE_MISC
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>



extern char EDS_Error[80];


const EDS_Color EDS_PaletaEstandar1[2] = {
	
	{0x000000},
	{0xFFFFFF}
};

const EDS_Color EDS_PaletaEstandar4[16] = {
	
	{0x000000},
	{0x800000},
	{0x008000},
	{0x808000},
	{0x000080},
	{0x800080},
	{0x008080},
	{0x808080},
	{0xC0C0C0},
	{0xFF0000},
	{0x00FF00},
	{0xFFFF00},
	{0x0000FF},
	{0xFF00FF},
	{0x00FFFF},
	{0xFFFFFF}
};


const EDS_Color EDS_PaletaEstandar8[256] = {
	
	{0x000000}, {0x0000A8}, {0x00A800}, {0x00A8A8}, {0xA80000}, {0xA800A8}, {0xA85400}, {0xA8A8A8},
	{0x545454}, {0x5454FC}, {0x54FC54}, {0x54FCFC}, {0xFC5454}, {0xFC54FC}, {0xFCFC54}, {0xFCFCFC},
	{0x000000}, {0x141414}, {0x202020}, {0x2C2C2C}, {0x383838}, {0x444444}, {0x505050}, {0x606060},
	{0x707070}, {0x808080}, {0x909090}, {0xA0A0A0}, {0xB4B4B4}, {0xC8C8C8}, {0xE0E0E0}, {0xFCFCFC},
	{0x0000FC}, {0x4000FC}, {0x7C00FC}, {0xBC00FC}, {0xFC00FC}, {0xFC00BC}, {0xFC007C}, {0xFC0040},
	{0xFC0000}, {0xFC4000}, {0xFC7C00}, {0xFCBC00}, {0xFCFC00}, {0xBCFC00}, {0x7CFC00}, {0x40FC00},
	{0x00FC00}, {0x00FC40}, {0x00FC7C}, {0x00FCBC}, {0x00FCFC}, {0x00BCFC}, {0x007CFC}, {0x0040FC},
	{0x7C7CFC}, {0x9C7CFC}, {0xBC7CFC}, {0xDC7CFC}, {0xFC7CFC}, {0xFC7CDC}, {0xFC7CBC}, {0xFC7C9C},
	{0xFC7C7C}, {0xFC9C7C}, {0xFCBC7C}, {0xFCDC7C}, {0xFCFC7C}, {0xDCFC7C}, {0xBCFC7C}, {0x9CFC7C},
	{0x7CFC7C}, {0x7CFC9C}, {0x7CFCBC}, {0x7CFCDC}, {0x7CFCFC}, {0x7CDCFC}, {0x7CBCFC}, {0x7C9CFC},
	{0xB4B4FC}, {0xC4B4FC}, {0xD8B4FC}, {0xE8B4FC}, {0xFCB4FC}, {0xFCB4E8}, {0xFCB4D8}, {0xFCB4C4},
	{0xFCB4B4}, {0xFCC4B4}, {0xFCD8B4}, {0xFCE8B4}, {0xFCFCB4}, {0xE8FCB4}, {0xD8FCB4}, {0xC4FCB4},
	{0xB4FCB4}, {0xB4FCC4}, {0xB4FCD8}, {0xB4FCE8}, {0xB4FCFC}, {0xB4E8FC}, {0xB4D8FC}, {0xB4C4FC},
	{0x000070}, {0x1C0070}, {0x380070}, {0x540070}, {0x700070}, {0x700054}, {0x700038}, {0x70001C},
	{0x700000}, {0x701C00}, {0x703800}, {0x705400}, {0x707000}, {0x547000}, {0x387000}, {0x1C7000},
	{0x007000}, {0x00701C}, {0x007038}, {0x007054}, {0x007070}, {0x005470}, {0x003870}, {0x001C70},
	{0x383870}, {0x443870}, {0x543870}, {0x603870}, {0x703870}, {0x703860}, {0x703854}, {0x703844},
	{0x703838}, {0x704438}, {0x705438}, {0x706038}, {0x707038}, {0x607038}, {0x547038}, {0x447038},
	{0x387038}, {0x387044}, {0x387054}, {0x387060}, {0x387070}, {0x386070}, {0x385470}, {0x384470},
	{0x505070}, {0x585070}, {0x605070}, {0x685070}, {0x705070}, {0x705068}, {0x705060}, {0x705058},
	{0x705050}, {0x705850}, {0x706050}, {0x706850}, {0x707050}, {0x687050}, {0x607050}, {0x587050},
	{0x507050}, {0x507058}, {0x507060}, {0x507068}, {0x507070}, {0x506870}, {0x506070}, {0x505870},
	{0x000040}, {0x100040}, {0x200040}, {0x300040}, {0x400040}, {0x400030}, {0x400020}, {0x400010},
	{0x400000}, {0x401000}, {0x402000}, {0x403000}, {0x404000}, {0x304000}, {0x204000}, {0x104000},
	{0x004000}, {0x004010}, {0x004020}, {0x004030}, {0x004040}, {0x003040}, {0x002040}, {0x001040},
	{0x202040}, {0x282040}, {0x302040}, {0x382040}, {0x402040}, {0x402038}, {0x402030}, {0x402028},
	{0x402020}, {0x402820}, {0x403020}, {0x403820}, {0x404020}, {0x384020}, {0x304020}, {0x284020},
	{0x204020}, {0x204028}, {0x204030}, {0x204038}, {0x204040}, {0x203840}, {0x203040}, {0x202840},
	{0x2C2C40}, {0x302C40}, {0x342C40}, {0x3C2C40}, {0x402C40}, {0x402C3C}, {0x402C34}, {0x402C30},
	{0x402C2C}, {0x40302C}, {0x40342C}, {0x403C2C}, {0x40402C}, {0x3C402C}, {0x34402C}, {0x30402C},
	{0x2C402C}, {0x2C4030}, {0x2C4034}, {0x2C403C}, {0x2C4040}, {0x2C3C40}, {0x2C3440}, {0x2C3040},
	{0x000000}, {0x000000}, {0x000000}, {0x000000}, {0x000000}, {0x000000}, {0x000000}, {0x000000}
};


const EDS_Color* EDS_ObtenerPaletaEstandar(uint8_t bpp) {
	
	return
		bpp == 1 ? EDS_PaletaEstandar1 :
		bpp == 4 ? EDS_PaletaEstandar4 :
		bpp == 8 ? EDS_PaletaEstandar8 :
		NULL;
}


EDS_Color EDS_ColorHSLRGB(double h, double s, double l) {
	
	if(s < 0 || s > 1 || l < 0 || l > 1) return (EDS_Color){ .v = 0 };
	h = (h + 2 * M_PI * ceil(-h / 2 / M_PI)) * 3 / M_PI;
	double c = s * (1 - fabs(2 * l - 1));
	double x = c * (1 - fabs(fmod(h, 2) - 1));
	double m = l - c / 2;
	
	return (EDS_Color){ .c = {
		(uint8_t)(((h >= 3 && h < 5 ? c : h < 2 ? 0 : x) + m) * 0xFF),
		(uint8_t)(((h >= 1 && h < 3 ? c : h >= 4 ? 0 : x) + m) * 0xFF),
		(uint8_t)(((h < 1 || h >= 5 ? c : h < 2 || h >= 4 ? x : 0) + m) * 0xFF),
		0xFF
	} };
}


uint32_t EDS_ObtenerPixel(const EDS_Imagen* imagen, uint32_t x, uint32_t y) {
	
	if(imagen == NULL) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "La imagen de origen está dañada.");
		return 0;
	}
	
	if(x >= imagen->ancho || y >= imagen->alto) return 0;
	
	EDS_Error[0] = '\0';
	return 
		imagen->bpp == 32 ? imagen->mapa_bits[y * imagen->ancho + x].v :
		imagen->mapa_bits_p[y * imagen->ancho + x];
}


void EDS_SobreescribirPixel(EDS_Imagen* imagen, uint32_t x, uint32_t y, uint32_t color) {
	
	if(imagen == NULL) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "La imagen de origen está dañada.");
		return;
	}
	
	if(x >= imagen->ancho || y >= imagen->alto) return;
	
	if(imagen->bpp == 32) imagen->mapa_bits[y * imagen->ancho + x].v = color;
	else imagen->mapa_bits_p[y * imagen->ancho + x] = color;
	EDS_Error[0] = '\0';
}


void EDS_DibujarPixel(EDS_Imagen* imagen, uint32_t x, uint32_t y, uint32_t color) {
	
	if(imagen == NULL) {
		
		snprintf(EDS_Error, sizeof(EDS_Error), "La imagen de origen está dañada.");
		return;
	}
	
	EDS_SobreescribirPixel(
		imagen,
		x,
		y,
		imagen->bpp != 32 || !(~color >> 24) ? color :
		EDS_MEZCLAR_COLOR((EDS_Color){color}, (EDS_Color){EDS_ObtenerPixel(imagen, x, y)}).v
	);
}

