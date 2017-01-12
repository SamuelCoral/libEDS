

#ifndef __DIBUJO_EDS_HPP__
#define __DIBUJO_EDS_HPP__


#include "EDS.h"
#include "imagen_bmp.hpp"


namespace eds
{
	class dibujo_eds
	{
		
	private:
		
		/////////////////////
		//    VARIABLES    //
		/////////////////////
		
		DIBUJO_EDS* dibujo;
		
		
		
		//////////////////////
		//    AUXILIARES    //
		//////////////////////
		
		inline static void comprobar_error()
		{
			if(error_EDS()[0]) throw excepcion_eds(error_EDS());
		}
		
		
		
		/////////////////////////
		//    CONSTRUCTORES    //
		/////////////////////////
		
		dibujo_eds(DIBUJO_EDS* nuevo) : dibujo(nuevo) {  }
		
		
		
	public:
		
		/////////////////////////
		//    CONSTRUCTORES    //
		/////////////////////////
		
		dibujo_eds(uint32_t ancho, uint32_t alto, uint8_t bpp = 32)
		{
			dibujo = crear_dibujo_vacio(ancho, alto, bpp);
			comprobar_error();
		}
		
		dibujo_eds(std::string ruta_archivo)
		{
			dibujo = cargar_dibujo_archivo_bmp(ruta_archivo.c_str(), true);
			comprobar_error();
		}
		
		dibujo_eds(const dibujo_eds& copia)
		{
			dibujo = copiar_dibujo(copia.dibujo);
			comprobar_error();
		}
		
		dibujo_eds(const bmp::imagen_bmp& copia)
		{
			dibujo = convertir_bmp_dibujo(copia.imagen, true);
			comprobar_error();
		}
		
		
		
		//////////////////////
		//    OPERADORES    //
		//////////////////////
		
		dibujo_eds operator=(const dibujo_eds& copia)
		{
			return dibujo_eds(copia);
		}
		
		dibujo_eds operator=(const bmp::imagen_bmp& copia)
		{
			return dibujo_eds(copia);
		}
		
		
		
		///////////////////////
		//    PROPIEDADES    //
		///////////////////////
		
		inline uint32_t ancho() const
		{
			return dibujo->ancho;
		}
		
		inline uint32_t alto() const
		{
			return dibujo->alto;
		}
		
		inline uint8_t bpp() const
		{
			return dibujo->bpp;
		}
		
		inline COLOR* paleta() const
		{
			return dibujo->paleta;
		}
		
		
		
		///////////////////
		//    MÉTODOS    //
		///////////////////
		
		inline void inyectar_bmp(const bmp::imagen_bmp& imagen, bool alpha) const
		{
			inyectar_dibujo_bmp(dibujo, imagen.imagen, alpha);
			comprobar_error();
		}
		
		inline bmp::imagen_bmp convertir_a_bmp(bool alpha, bool rle)
		{
			IMAGEN_BMP* nueva = convertir_dibujo_bmp(dibujo, alpha, rle);
			comprobar_error();
			return bmp::imagen_bmp(nueva);
		}
		
		inline void guardar_bmp(std::string ruta_archivo, bool alpha, bool rle) const
		{
			guardar_dibujo_bmp(dibujo, ruta_archivo.c_str(), alpha, rle);
			bmp::imagen_bmp::comprobar_error();
		}
		
		inline dibujo_eds copiar() const
		{
			DIBUJO_EDS* nuevo = copiar_dibujo(dibujo);
			comprobar_error();
			return dibujo_eds(nuevo);
		}
		
		
		inline COLOR ver_pixel(uint32_t x, uint32_t y, bool estricto = false) const
		{
			return v_pixel(dibujo, x, y, estricto);
		}
		
		inline void dibujar_pixel(uint32_t x, uint32_t y, COLOR color, bool sobreescribir = false, bool estricto = false)
		{
			if(sobreescribir) d_pixel_s(dibujo, x, y, color, estricto);
			else d_pixel(dibujo, x, y, color, estricto);
		}
		
		inline void invertir_colores()
		{
			invertir_colores_d(dibujo);
			comprobar_error();
		}
		
		inline void escala_grises()
		{
			escala_grises_d(dibujo);
			comprobar_error();
		}
		
		inline void saturar_colores(COLOR color)
		{
			saturar_colores_d(dibujo, color);
			comprobar_error();
		}
		
		inline void extraer_colores(COLOR color)
		{
			extraer_colores_d(dibujo, color);
			comprobar_error();
		}
		
		inline void cambiar_transparencia(int16_t incremento)
		{
			cambiar_transparencia_d(dibujo, incremento);
			comprobar_error();
		}
		
		inline void cambiar_rojo(int16_t incremento)
		{
			cambiar_rojo_d(dibujo, incremento);
			comprobar_error();
		}
		
		inline void cambiar_verde(int16_t incremento)
		{
			cambiar_verde_d(dibujo, incremento);
			comprobar_error();
		}
		
		inline void cambiar_azul(int16_t incremento)
		{
			cambiar_azul_d(dibujo, incremento);
			comprobar_error();
		}
		
		inline void cambiar_brillo(int16_t incremento)
		{
			cambiar_transparencia_d(dibujo, incremento);
			comprobar_error();
		}
		
		inline void aumentar_bpp()
		{
			aumentar_bpp_d(dibujo);
			comprobar_error();
		}
		
		inline void reducir_bpp(uint8_t bpp)
		{
			reducir_bpp_d(dibujo, bpp);
			comprobar_error();
		}
		
		
		inline void limpiar(COLOR color)
		{
			limpiar_d(dibujo, color);
		}
		
		inline void dibujar_linea(int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color)
		{
			d_linea(dibujo, x1, y1, x2, y2, color);
		}
		
		inline void dibujar_rectangulo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color)
		{
			d_rect(dibujo, x1, y1, x2, y2, color);
		}
		
		inline void dibujar_rectangulo_lleno(int32_t x1, int32_t y1, int32_t x2, int32_t y2, COLOR color)
		{
			d_rect_lleno(dibujo, x1, y1, x2, y2, color);
		}
		
		inline void dibujar_circulo(int32_t x1, int32_t y1, uint32_t radio, COLOR color)
		{
			d_circ(dibujo, x1, y1, radio, color);
		}
		
		inline void dibujar_circulo_lleno(int32_t x1, int32_t y1, uint32_t radio, COLOR color)
		{
			d_circ_lleno(dibujo, x1, y1, radio, color);
		}
		
		inline void dibujar_semi_circulo(int32_t x1, int32_t y1, uint32_t radio, double ang_inicio, double ang_final, COLOR color)
		{
			d_semi_circ(dibujo, x1, y1, radio, ang_inicio, ang_final, color);
		}
		
		inline void dibujar_elipse(int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, COLOR color)
		{
			d_elipse(dibujo, x1, y1, ancho, alto, color);
		}
		
		inline void dibujar_elipse_llena(int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, COLOR color)
		{
			d_elipse_llena(dibujo, x1, y1, ancho, alto, color);
		}
		
		inline void dibujar_semi_elipse(int32_t x1, int32_t y1, uint32_t ancho, uint32_t alto, double ang_inicio, double ang_final, COLOR color)
		{
			d_semi_elipse(dibujo, x1, y1, ancho, alto, ang_inicio, ang_final, color);
		}
		
		
		inline void reescalar(uint32_t ancho, uint32_t alto)
		{
			reescalar_d(dibujo, ancho, alto);
			comprobar_error();
		}
		
		inline dibujo_eds escalar(uint32_t ancho, uint32_t alto)
		{
			DIBUJO_EDS* nuevo = escalar_d(dibujo, ancho, alto);
			comprobar_error();
			return dibujo_eds(nuevo);
		}
		
		inline void recortar(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
		{
			recortar_d(dibujo, x1, y1, x2, y2);
			comprobar_error();
		}
		
		inline dibujo_eds cortar(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
		{
			DIBUJO_EDS* nuevo = cortar_d(dibujo, x1, y1, x2, y2);
			comprobar_error();
			return dibujo_eds(nuevo);
		}
		
		inline void pegar_sobre(dibujo_eds destino, int32_t x1, int32_t y1)
		{
			pegar_d(dibujo, destino.dibujo, x1, y1);
			comprobar_error();
		}
		
		inline void pegar_sobre(dibujo_eds destino, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
		{
			pegar_escalar_d(dibujo, destino.dibujo, x1, y1, x2, y2);
			comprobar_error();
		}
		
		inline void espejo_x()
		{
			espejo_x_d(dibujo);
			comprobar_error();
		}
		
		inline void espejo_y()
		{
			espejo_y_d(dibujo);
			comprobar_error();
		}
		
		inline void rotar_derecha()
		{
			rotar_derecha_d(dibujo);
			comprobar_error();
		}
		
		inline void rotar_izquierda()
		{
			rotar_izquierda_d(dibujo);
			comprobar_error();
		}
		
		inline void voltear()
		{
			voltear_d(dibujo);
			comprobar_error();
		}
		
		
		inline void dibujar_letra(uint8_t letra, int32_t x1, int32_t y1, COLOR color)
		{
			d_letra(dibujo, letra, x1, y1, color);
		}
		
		inline void dibujar_cadena(std::string cadena, int32_t x1, int32_t y1, COLOR color)
		{
			d_cadena(dibujo, cadena.c_str(), x1, y1, color);
		}
		
		
		
		//////////////////////
		//    DESTRUCTOR    //
		//////////////////////
		
		~dibujo_eds()
		{
			destruir_puntero_dibujo(dibujo);
			dibujo = NULL;
		}
	};
}


#endif /* __DIBUJO_EDS_HPP__ */

