using System;
using System.Runtime.InteropServices;

namespace LibEDS.Net.LibBMP
{
    public partial class ImagenBMP
    {
        internal const string rutaDll = "libEDS.dll";
        internal const CallingConvention convencionLlamado = CallingConvention.Cdecl;


        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private extern static IntPtr error_bmp();

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static eImagenBMP* crear_bmp_vacio(UInt32 ancho, Int32 alto, UInt16 bpp);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static eImagenBMP* cargar_bmp([MarshalAs(UnmanagedType.AnsiBStr)] string ruta);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static eImagenBMP* copiar_bmp(eImagenBMP* origen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void guardar_bmp(eImagenBMP* imagen, [MarshalAs(UnmanagedType.AnsiBStr)] string ruta);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void convertir_dib_bmp(eImagenBMP* imagen, VersionDIB tipo_dib);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void compresion_rle_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void cambiar_formato_pixel_bmp(eImagenBMP* imagen, UInt16 bpp, MascarasBits mascaras);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void voltear_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void ajustar_res_impresion_bmp(eImagenBMP* imagen, UInt32 res_horizontal, UInt32 res_vertical);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void quitar_perfil_icc_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void establecer_ecl_archivo_bmp(eImagenBMP* imagen, [MarshalAs(UnmanagedType.AnsiBStr)] string ruta_archivo);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void establecer_ecl_embedido_bmp(eImagenBMP* imagen, IntPtr perfil_icc, UInt32 tam_perfil);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void establecer_ecl_calibrado_bmp(eImagenBMP* imagen, CoordenadasColores puntos_fin, GammaColores gamma);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void establecer_ecl_generico_bmp(eImagenBMP* imagen, EspacioColor espacio_color);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void establecer_intencion_renderizado_bmp(eImagenBMP* imagen, IntencionRenderizado modo_renderizado);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static UInt32 ancho_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static Int32 alto_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static UInt16 bpp_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static UInt16 planos_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static UInt32 compresion_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static UInt32 res_horizontal_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static UInt32 res_vertical_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static EspacioColor espacio_color_bmp(eImagenBMP* imagen);

        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static IntencionRenderizado modo_renderizado_bmp(eImagenBMP* imagen);


        [DllImport(rutaDll, CallingConvention = convencionLlamado)]
        private unsafe extern static void destruir_puntero_bmp(eImagenBMP* imagen);
    }
}
