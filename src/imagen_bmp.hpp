

#ifndef __IMAGEN_BMP_HPP__
#define __IMAGEN_BMP_HPP__


#include "excepcion_eds.hpp"
#include "libbmp.h"


namespace eds
{
	class dibujo_eds;
	
	namespace bmp
	{
		class excepcion_bmp : excepcion_eds
		{
			
		public:
			
			excepcion_bmp(std::string mensaje) : excepcion_eds(mensaje) {  }
		};
		
		
		
		class imagen_bmp
		{
			friend class eds::dibujo_eds;
			
		private:
			
			/////////////////////
			//    VARIABLES    //
			/////////////////////
			
			IMAGEN_BMP* imagen;
			
			
			
			//////////////////////
			//    AUXILIARES    //
			//////////////////////
			
			inline static void comprobar_error()
			{
				if(error_bmp()[0]) throw excepcion_bmp(error_bmp());
			}
			
			
			
			/////////////////////////
			//    CONSTRUCTORES    //
			/////////////////////////
			
			imagen_bmp(IMAGEN_BMP* nuevo) : imagen(nuevo) {  }
			
			
			
		public:
			
			/////////////////////////
			//    CONSTRUCTORES    //
			/////////////////////////
			
			imagen_bmp(uint32_t ancho, int32_t alto, uint16_t bpp = 24)
			{
				imagen = crear_bmp_vacio(ancho, alto, bpp);
				comprobar_error();
			}
			
			imagen_bmp(std::string ruta_archivo)
			{
				imagen = cargar_bmp(ruta_archivo.c_str());
				comprobar_error();
			}
			
			imagen_bmp(const imagen_bmp& copia)
			{
				imagen = copiar_bmp(copia.imagen);
				comprobar_error();
			}
			
			
			
			//////////////////////
			//    OPERADORES    //
			//////////////////////
			
			imagen_bmp operator=(const imagen_bmp& copia)
			{
				return imagen_bmp(copia);
			}
			
			
			
			///////////////////////
			//    PROPIEDADES    //
			///////////////////////
			
			inline uint32_t ancho() const
			{
				return ancho_bmp(imagen);
			}
			
			inline int32_t alto() const
			{
				return alto_bmp(imagen);
			}
			
			inline uint16_t bpp() const
			{
				return bpp_bmp(imagen);
			}
			
			inline uint32_t* paleta() const
			{
				return imagen->paleta;
			}
			
			inline uint16_t planos() const
			{
				return planos_bmp(imagen);
			}
			
			inline MASCARAS_BITS formato_pixel() const
			{
				return compresion() != BMP_MC_BITFIELDS ? bpp() == 16 ? crear_mascaras(5, 5, 5, 0) : crear_mascaras(8, 8, 8, 0) : *imagen->bitfields;
			}
			
			inline uint32_t resolucion_horizontal() const
			{
				return res_horizontal_bmp(imagen);
			}
			
			inline uint32_t resolucion_vertical() const
			{
				return res_vertical_bmp(imagen);
			}
			
			inline VERSION_DIB version() const
			{
				return (VERSION_DIB)imagen->dib_info.ver;
			}
			
			inline METODO_COMPRESION compresion() const
			{
				return (METODO_COMPRESION)compresion_bmp(imagen);
			}
			
			inline ESPACIO_COLOR espacio_color() const
			{
				return version() >= BMP_DIB_WIN95 ? (ESPACIO_COLOR)imagen->dib_info.dib_win95->tipo_espacio_color : BMP_ECL_sRGB;
			}
			
			inline INTENCION_RENDERIZADO intencion_renderizado() const
			{
				return version() >= BMP_DIB_WIN98 ? (INTENCION_RENDERIZADO)imagen->dib_info.dib_win98->modo_renderizado : BMP_IR_IMAGENES;
			}
			
			inline std::string ruta_perfil_icc() const
			{
				return espacio_color() == BMP_ECL_ARCHIVO ? imagen->ruta_perfil : std::string();
			}
			
			inline void* perfil_icc_embedido() const
			{
				return espacio_color() == BMP_ECL_EMBEDIDO ? imagen->perfil_icc : NULL;
			}
			
			inline uint32_t tam_perfil_icc_embedido() const
			{
				return espacio_color() == BMP_ECL_EMBEDIDO ? imagen->dib_info.dib_win98->tam_perfil : 0;
			}
			
			inline COORDENADAS_COLORES puntos_fin_ecl() const
			{
				return espacio_color() == BMP_ECL_CALIBRADO ? imagen->dib_info.dib_win95->puntos_fin : COORDENADAS_COLORES();
			}
			
			inline GAMMA_COLORES gamma_colores_ecl() const
			{
				return espacio_color() == BMP_ECL_CALIBRADO ? imagen->dib_info.dib_win95->gamma : GAMMA_COLORES();
			}
			
			
			
			///////////////////
			//    MÉTODOS    //
			///////////////////
			
			inline void cambiar_formato_pixel(uint16_t bpp, MASCARAS_BITS mascaras)
			{
				cambiar_formato_pixel_bmp(imagen, bpp, mascaras);
				comprobar_error();
			}
			
			inline void ajustar_resolucion(uint32_t res_horizontal, uint32_t res_vertical)
			{
				ajustar_res_impresion_bmp(imagen, res_horizontal, res_vertical);
			}
			
			inline void cambiar_version(VERSION_DIB version)
			{
				convertir_dib_bmp(imagen, version);
				comprobar_error();
			}
			
			inline void compresion_rle()
			{
				compresion_rle_bmp(imagen);
				comprobar_error();
			}
			
			inline void quitar_perfil_icc()
			{
				quitar_perfil_icc_bmp(imagen);
				comprobar_error();
			}
			
			inline void establecer_ecl_archivo(std::string ruta_archivo)
			{
				establecer_ecl_archivo_bmp(imagen, ruta_archivo.c_str());
				comprobar_error();
			}
			
			inline void establecer_ecl_embedido(const void* ecl, uint32_t tam_perfil)
			{
				establecer_ecl_embedido_bmp(imagen, ecl, tam_perfil);
				comprobar_error();
			}
			
			inline void establecer_ecl_calibrado(COORDENADAS_COLORES puntos_fin, GAMMA_COLORES gamma)
			{
				establecer_ecl_calibrado_bmp(imagen, puntos_fin, gamma);
				comprobar_error();
			}
			
			inline void establecer_ecl_generico(ESPACIO_COLOR ecl)
			{
				establecer_ecl_generico_bmp(imagen, ecl);
				comprobar_error();
			}
			
			inline void establecer_intencion_renderizado(INTENCION_RENDERIZADO modo_renderizado)
			{
				establecer_intencion_renderizado_bmp(imagen, modo_renderizado);
				comprobar_error();
			}
			
			inline void guardar(std::string ruta_archivo)
			{
				guardar_bmp(imagen, ruta_archivo.c_str());
				comprobar_error();
			}
			
			inline imagen_bmp copiar() const
			{
				IMAGEN_BMP* nueva = copiar_bmp(imagen);
				comprobar_error();
				return imagen_bmp(nueva);
			}
			
			inline void voltear()
			{
				voltear_bmp(imagen);
			}
			
			
			
			//////////////////////
			//    DESTRUCTOR    //
			//////////////////////
			
			~imagen_bmp()
			{
				destruir_puntero_bmp(imagen);
				imagen = NULL;
			}
		};
	}
}


#endif /* __IMAGEN_BMP_HPP__ */

