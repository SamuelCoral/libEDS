using System;
using System.Runtime.InteropServices;
using LibEDS.Net.LibBMP;

namespace LibEDS.Net
{
    public partial class DibujoEDS
    {
        #region Tipos

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private extern static IntPtr error_EDS();

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static eDibujoEDS* crear_dibujo_vacio(UInt32 ancho, UInt32 alto, byte bpp);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static eDibujoEDS* convertir_bmp_dibujo(eImagenBMP* imagen, bool paleta);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static eDibujoEDS* cargar_dibujo_archivo_bmp([MarshalAs(UnmanagedType.AnsiBStr)] string ruta, bool paleta);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void inyectar_dibujo_bmp(eDibujoEDS* dibujo, eImagenBMP* imagen, bool alpha);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static eImagenBMP* convertir_dibujo_bmp(eDibujoEDS* dibujo, bool alpha, bool rle);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void guardar_dibujo_bmp(eDibujoEDS* dibujo, [MarshalAs(UnmanagedType.AnsiBStr)] string ruta, bool alpha, bool rle);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static eDibujoEDS* copiar_dibujo(eDibujoEDS* dibujo);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void destruir_puntero_dibujo(eDibujoEDS* dibujo);

        #endregion

        #region Color

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static UInt32 v_pixel(eDibujoEDS* dibujo, UInt32 X, UInt32 Y, bool estricto);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_pixel_s(eDibujoEDS* dibujo, UInt32 X, UInt32 Y, UInt32 color, bool estricto);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_pixel(eDibujoEDS* dibujo, UInt32 X, UInt32 Y, UInt32 color, bool estricto);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private extern static UInt32 invertir_color(UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private extern static UInt32 color_escala_grises(UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static byte color_mas_cercano(UInt16 num_colores, UInt32* paleta, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void invertir_colores_d(eDibujoEDS* dibujo);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void escala_grises_d(eDibujoEDS* dibujo);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void saturar_colores_d(eDibujoEDS* dibujo, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void extraer_colores_d(eDibujoEDS* dibujo, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void cambiar_transparencia_d(eDibujoEDS* dibujo, Int16 incremento);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void cambiar_rojo_d(eDibujoEDS* dibujo, Int16 incremento);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void cambiar_verde_d(eDibujoEDS* dibujo, Int16 incremento);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void cambiar_azul_d(eDibujoEDS* dibujo, Int16 incremento);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void cambiar_brillo_d(eDibujoEDS* dibujo, Int16 incremento);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void aumentar_bpp_d(eDibujoEDS* dibujo);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void reducir_bpp_d(eDibujoEDS* dibujo, byte bpp);

        #endregion

        #region Dibujo

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_linea(eDibujoEDS* dibujo, Int32 x1, Int32 y1, Int32 x2, Int32 y2, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_rect(eDibujoEDS* dibujo, Int32 x1, Int32 y1, Int32 x2, Int32 y2, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_rect_lleno(eDibujoEDS* dibujo, Int32 x1, Int32 y1, Int32 x2, Int32 y2, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_circ(eDibujoEDS* dibujo, Int32 x1, Int32 y1, UInt32 radio, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_circ_lleno(eDibujoEDS* dibujo, Int32 x1, Int32 y1, UInt32 radio, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_semi_circ(eDibujoEDS* dibujo, Int32 x1, Int32 y1, UInt32 radio, double ang_inicio, double ang_final, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_elipse(eDibujoEDS* dibujo, Int32 x1, Int32 y1, UInt32 radio_x, UInt32 radio_y, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_elipse_llena(eDibujoEDS* dibujo, Int32 x1, Int32 y1, UInt32 radio_x, UInt32 radio_y, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_semi_elipse(eDibujoEDS* dibujo, Int32 x1, Int32 y1, UInt32 radio_x, UInt32 radio_y, double ang_inicio, double ang_final, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void limpiar_d(eDibujoEDS* dibujo, UInt32 color);

        #endregion

        #region Geometría

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void reescalar_d(eDibujoEDS* dibujo, UInt32 x2, UInt32 y2);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static eDibujoEDS* escalar_d(eDibujoEDS* dibujo, UInt32 x2, UInt32 y2);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void recortar_d(eDibujoEDS* dibujo, Int32 x1, Int32 y1, Int32 x2, Int32 y2);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static eDibujoEDS* cortar_d(eDibujoEDS* dibujo, Int32 x1, Int32 y1, Int32 x2, Int32 y2);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void pegar_d(eDibujoEDS* origen, eDibujoEDS* destino, Int32 x1, Int32 y1);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void pegar_escalar_d(eDibujoEDS* origen, eDibujoEDS* destino, Int32 x1, Int32 y1, Int32 x2, Int32 y2);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void espejo_x_d(eDibujoEDS* dibujo);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void espejo_y_d(eDibujoEDS* dibujo);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void voltear_d(eDibujoEDS* dibujo);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void rotar_derecha_d(eDibujoEDS* dibujo);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void rotar_izquierda_d(eDibujoEDS* dibujo);

        #endregion

        #region Texto

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private extern static UInt32 longitud_cadena([MarshalAs(UnmanagedType.AnsiBStr)] string cadena);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_letra(eDibujoEDS* dibujo, byte letra, Int32 x1, Int32 y1, UInt32 color);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private unsafe extern static void d_cadena(eDibujoEDS* dibujo, [MarshalAs(UnmanagedType.AnsiBStr)] string cadena, Int32 x1, Int32 y1, UInt32 color);

        #endregion
    }
}
