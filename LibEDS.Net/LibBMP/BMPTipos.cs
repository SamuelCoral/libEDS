using System;
using System.Runtime.InteropServices;

namespace LibEDS.Net.LibBMP
{
    /// <summary>Números mágicos de archivos de mapas de bits.</summary>
    public enum TipoBitmap : ushort
    {
        /// <summary>Mapa de bits de Windows.</summary>
        BM = 0x4D42,
        /// <summary>Estructura de arreglo de mapa de bits de OS/2.</summary><remarks>No implementado aún.</remarks>
        BA = 0x4142,
        /// <summary>Estructura de color de ícono de OS/2.</summary><remarks>No implementado aún.</remarks>
        CI = 0x4943,
        /// <summary>Color constante de puntero de mouse de OS/2.</summary><remarks>No implementado aún.</remarks>
        CP = 0x5043,
        /// <summary>Estructura de ícono de OS/2.</summary><remarks>No implementado aún.</remarks>
        IC = 0x4349,
        /// <summary>Puntero de mouse de OS/2.</summary><remarks>No implementado aún.</remarks>
        PT = 0x5450
    }

    /// <summary>Tamaños de las diferentes versiones de las cabeceras DIB de los mapas de bits.</summary>
    public enum VersionDIB : uint
    {
        /// <summary>Versión de cabecera DIB para mapas de bits de Windows 2.0.
        /// <see cref="BMPV2Header"/> para más información sobre la cabecera de esta versión.</summary>
        Windows200 = 12,
        /// <summary>Versión de cabecera DIB para mapas de bits de Windows 3.0 o NT.
        /// <see cref="BMPV3Header"/> para más información sobre la cabecera de esta versión.</summary>
        WindowsNT = 40,
        /// <summary>Versión de cabecera DIB para mapas de bits de Windows NT.</summary>
        /// <remarks>
        /// Variante de la versión de la cabecera de Windows 3.0 usada en aplicaciones de Adobe que
        /// agrega máscaras de bits para los componentes de color del espacio RGB.
        /// Debe implementar la compresión <seealso cref="MetodoCompresion.BITFIELDS"/>.
        /// No implementada aún.
        /// </remarks>
        WindowsNTMascaras = WindowsNT + 12,
        /// <summary>Versión de cabecera DIB para mapas de bits de Windows NT.</summary>
        /// <remarks>
        /// Variante de la versión de la cabcera de Windows 3.0 usada en aplicaciones de Adobe que
        /// agrega máscaras de bits para los componentes de color del espacio de color ARGB.
        /// Debe implementar la compresión <seealso cref="MetodoCompresion.BITFIELDS"/>.
        /// </remarks>
        WindowsNTMascarasAlpha = WindowsNT + 16,
        /// <summary>Versión de cabecera DIB para mapas de bits de Windows 95.
        /// <see cref="BMPV4Header"/> para más información sobre la cabecera de esta versión.</summary>
        Windows95 = 108,
        /// <summary>Versión de cabecera DIB para mapas de bits de Windows 98.
        /// <see cref="BMPV5Header"/> para más información sobre la cabecera de esta versión.</summary>
        Windows98 = 124,
        /// <summary>Versión de cabecera DIB para mapas de bits de OS/2.</summary><remarks>No implementada aún.</remarks>
        OS2 = 64
    }

    /// <summary>Métodos de compresión utilizados para mapas de bits de Windows 3.0 o posteriores.</summary>
    public enum MetodoCompresion : uint
    {
        /// <summary>Espacio de color RGB (sin compresión).</summary>
        RGB = 0,
        /// <summary>Algoritmo de compresión RLE para mapas de bits de 8 bpp.</summary>
        RLE8 = 1,
        /// <summary>Algoritmo de compresión RLE para mapas de bits de 4 bpp.</summary>
        RLE4 = 2,
        /// <summary>Espacio de color RGB con máscaras de bits para cada componente de color (sin compresión).</summary>
        BITFIELDS = 3,
        /// <summary>Compresión de archivos JPEG.</summary><remarks>No implementada aún.</remarks>
        JPEG = 4,
        /// <summary>Compresión de archivos PNG.</summary><remarks>No implementada aún.</remarks>
        PNG = 5,
        /// <summary>Espacio de color RGB con máscaras de bits para cada componente de color (sin compresión).</summary>
        /// <remarks>
        /// Compresión utilizado en aplicaciones de Adobe para mapas de bits de 32 bpp con cabecera de Windows NT.
        /// No implementada aún.
        /// </remarks>
        ALPHABITFIELDS = 6,
        /// <summary>Espacio de color CMYK (sin compresión).</summary><remarks>No implementada aún.</remarks>
        CMYK = 11,
        /// <summary>Algoritmo de compresión RLE para mapas de bits de 8 bpp con paleta de color en formato CMYK.</summary><remarks>No implementada aún.</remarks>
        CMYKRLE8 = 12,
        /// <summary>Algoritmo de compresión RLE para mapas de bits de 4 bpp con paleta de color en formato CMYK.</summary><remarks>No implementada aún.</remarks>
        CMYKRLE4 = 13
    }

    /// <summary>Tipos de espacio de color implementado en el mapa de bits.</summary>
    public enum EspacioColor : uint
    {
        /// <summary>Espacio de color RGB estándar.</summary>
        sRGB = 0x73524742,
        /// <summary>Espacio de color del sistema por defecto (sRGB).</summary>
        Win = 0x57696E20,
        /// <summary>Espacio de color calibrado.</summary>
        /// <remarks>
        /// Indica que la información de los puntos finales de los componentes de color del
        /// espacio de color y la corrección gamma son especificados en sus campos correspondientes de
        /// la cabecera DIB (<seealso cref="BMPV4Header"/>).
        /// </remarks>
        Calibrado = 0,
        /// <summary>Espacio de color especificado en un archivo de perfil ICC que se encuentra en la ruta indicada en <seealso cref="ImagenBMP.RutaPerfilICC"/>.</summary>
        LINK = 0x4C494E4B,
        /// <summary>Espacio de color especificado en un perfil ICC que se localiza en la dirección de memora indicada en <seealso cref="ImagenBMP.PunteroPerfilICCEmbedido"/>.</summary>
        MBED = 0x4D424544,
    }

    /// <summary>Indica a la aplicación la intención de renderizado del mapa de bits de acuerdo a su tipo de contenido.</summary>
    public enum IntencionRenderizado : uint
    {
        /// <summary>Colorimétrica absoluta.</summary>
        /// <remarks>Mantiene el punto blanco. Coincide los colores al color mas cercano en la gamma de destino.</remarks>
        ColorABS = 8,
        /// <summary>Saturación de color.</summary>
        /// <remarks>Mantiene la saturación. Usada para tablas de negocios y otras situaciones en las que los colores no interpolados son requeridos.</remarks>
        Negocios = 1,
        /// <summary>Colorimétrica relativa.</summary>
        /// <remarks>Mantiene las coincidencias colorimétricas. Usado para diseño gráfico y colores nombrados.</remarks>
        Graficos = 2,
        /// <summary>Perceptual.</summary>
        /// <remarks>Mantiene el contraste. Usado para fotografías e imágenes naturales.</remarks>
        Imagenes = 4
    }



    /// <summary>Coordenadas tridimensionales de un punto final de un componente de color en el espacio de color CIE 1931.</summary>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct CoordenadasColor
    {
        /// <summary>Coordenada en el eje X del punto.</summary>
        public UInt32 x;
        /// <summary>Coordenada en el eje Y del punto.</summary>
        public UInt32 y;
        /// <summary>Coordenada en el eje Z del punto.</summary>
        public UInt32 z;


        /// <summary>
        /// Construye una instancia de esta clase dados sus valores.
        /// </summary>
        /// <param name="x">Coordenada en el eje X del punto.</param>
        /// <param name="y">Coordenada en el eje Y del punto.</param>
        /// <param name="z">Coordenada en el eje Z del punto.</param>
        public CoordenadasColor(UInt32 x, UInt32 y, UInt32 z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    /// <summary>Coordenadas de los puntos finales de los componentes de color en el espacio de color CIE 1931.</summary>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct CoordenadasColores
    {
        /// <summary>Coordenadas del punto del componente rojo.</summary>
        public CoordenadasColor rojo;
        /// <summary>Coordenadas del punto del componente verde.</summary>
        public CoordenadasColor verde;
        /// <summary>Coordenadas del punto del componente azul.</summary>
        public CoordenadasColor azul;


        /// <summary>
        /// Construye una instancia de esta clase dados sus valores.
        /// </summary>
        /// <param name="rojo">Coordenadas del punto del componente rojo.</param>
        /// <param name="verde">Coordenadas del punto del componente verde.</param>
        /// <param name="azul">Coordenadas del punto del componente azul.</param>
        public CoordenadasColores(CoordenadasColor rojo, CoordenadasColor verde, CoordenadasColor azul)
        {
            this.rojo = rojo;
            this.verde = verde;
            this.azul = azul;
        }
    }

    /// <summary>Corrección gamma para cada componente de color en formato FXPT2DOT30 (flotante de 2 bits de mantisa y 30 bits del exponente).</summary>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct GammaColores
    {
        /// <summary>Corrección gamma del componente rojo.</summary>
        public UInt32 rojo;
        /// <summary>Corrección gamma del componente verde.</summary>
        public UInt32 verde;
        /// <summary>Corrección gamma del componente azul.</summary>
        public UInt32 azul;


        /// <summary>
        /// Construye una instancia de esta clase dados sus valores.
        /// </summary>
        /// <param name="rojo">Corrección gamma del componente rojo.</param>
        /// <param name="verde">Corrección gamma del componente verde.</param>
        /// <param name="azul">Corrección gamma del componente azul.</param>
        public GammaColores(UInt32 rojo, UInt32 verde, UInt32 azul)
        {
            this.rojo = rojo;
            this.verde = verde;
            this.azul = azul;
        }
    }

    /// <summary>Estructura de cabecera DIB para mapas de bits de Windows 2.0.</summary>
    /// <remarks>
    ///     <para>
    ///     Esta estructura tiene pocas limitantes y debería ser suficiente para la mayoria
    ///     de los usuarios, sin embargo no es la mejor recomendada.
    ///     </para>
    ///     <list type="bullet">
    ///         <listheader><term>Características:</term></listheader>
    ///         <item><description>Resolución máxima de 32767 x 32767 pixeles</description></item>
    ///         <item><description>Profundidades de color de 1, 4, 8 y 24 bpp</description></item>
    ///         <item><description>Paleta de colores RGB</description></item>
    ///     </list>
    /// </remarks>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct BMPV2Header
    {
        /// <summary>Tamaño de esta cabecera (debe ser igual a <seealso cref="VersionDIB.Windows200"/>).</summary>
        public UInt32 tamDib;
        /// <summary>Ancho del mapa de bits en pixeles.</summary>
        public UInt16 ancho;
        /// <summary>Alto del mapa de bits en pixeles.</summary>
        /// <remarks>Si es un número negativo, indica que debe ser leida de abajo hacia arriba.</remarks>
        public Int16 alto;
        /// <summary>Planos de color del dispositivo de video (debe ser 1).</summary>
        public UInt16 planos;
        /// <summary>Profundidad de color del mapa de bits en bits por pixel.</summary>
        public UInt16 bpp;
    }

    /// <summary>Estructura de cabecera DIB para mapas de bits de Windows 3.x y Windows NT.</summary>
    /// <remarks>
    ///     <para>
    ///     Esta estructura no tiene casi ninguna limitante, y es la recomendada para la mayoría
    ///     de los usuarios, además es la usada por default en esta librería.
    ///     </para>
    ///     <list type="bullet">
    ///         <listheader><term>Nuevas características:</term></listheader>
    ///         <item><description>Resolución máxima de 32767 x 32767 pixeles</description></item>
    ///         <item><description>Profundidades de color de 1, 4, 8, 16, 24 y 32 bpp</description></item>
    ///         <item><description>Paleta de colores XRGB</description></item>
    ///         <item><description>Soporte para compresión de imagen</description></item>
    ///         <item><description>Información de resolución de impresión</description></item>
    ///     </list>
    /// </remarks>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct BMPV3Header
    {
        /// <summary>Tamaño de esta cabecera (debe ser igual a cualquiera que comience con <seealso cref="VersionDIB.WindowsNT"/>).</summary>
        public UInt32 tamDib;
        /// <summary>Ancho del mapa de bits en pixeles.</summary>
        public UInt32 ancho;
        /// <summary>Alto del mapa de bits en pixeles.</summary>
        /// <remarks>Si es un número negativo, indica que debe ser leida de abajo hacia arriba, además debe ser un mapa de bits descomprimido.</remarks>
        public Int32 alto;
        /// <summary>Planos de color del dispositivo de video (debe ser 1).</summary>
        public UInt16 planos;
        /// <summary>Profundidad de color del mapa de bits en bits por pixel.</summary>
        public UInt16 bpp;
        /// <summary>Método de compresión del mapa de bits.
        /// <see cref="MetodoCompresion"/> para más información sobre los métodos de compresión.</summary>
        public MetodoCompresion compresion;
        /// <summary>Tamaño del mapa de bits (sin contar el tamaño de las cabeceras de información).</summary>
        public UInt32 tamBitmap;
        /// <summary>Resolución de impresión horizontal en pixeles por metro.</summary>
        public UInt32 resHorizontal;
        /// <summary>Resolución de impresión vertical en pixeles por metro.</summary>
        public UInt32 resVertical;
        /// <summary>Número de colores en la paleta (para mapas de bits de una profundidad de color de 8 bpp o menor).</summary><remarks>No se verifica.</remarks>
        public UInt32 colores;
        /// <summary>Número de colores importantes (o 0 cuando todos los colores son importantes).</summary><remarks>No se verifica.</remarks>
        public UInt32 coloresImportantes;
    }

    /// <summary>Estructura de cabecera DIB para mapas de bits de Windows 95.</summary>
    /// <remarks>
    ///     <para>
    ///     Esta estructura es idéntica a la anterior con la excepción que se ha agregado la información
    ///     de las máscaras de bits en la cabecera, en la versión anterior eran opcionales y solo se
    ///     especificaban si se ocupaban, ahora siempre están presentes.
    ///     También se ha agregado la información del espacio de color y corrección Gamma.
    ///     </para>
    ///     <para>Los campos anteriores son exactamente los mismos que los de la anterior cabecera.</para>
    ///     <para>La información de las máscaras de bits está implementada fuera de la cabecera.</para>
    ///     <list type="bullet">
    ///         <listheader><term>Nuevas características:</term></listheader>
    ///         <item><description>Paleta de colores ARGB</description></item>
    ///         <item><description>Máscaras de bits ahora con canal Alpha</description></item>
    ///         <item><description>Información del espacio de color</description></item>
    ///         <item><description>Corrección Gamma</description></item>
    ///     </list>
    /// </remarks>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct BMPV4Header
    {
        /// <summary>Tipo de espacio de color del mapa de bits.
        /// <see cref="EspacioColor"/> para más información sobre los espacios de color.</summary>
        /// <remarks>Para esta versión no se pueden usar los valoes <seealso cref="EspacioColor.MBED"/> ni <seealso cref="EspacioColor.LINK"/>.</remarks>
        public EspacioColor tipoEspacioColor;
        /// <summary>Coordenadas de los puntos finales de los componentes de color en el espacio de color CIE 1931.
        /// <see cref="CoordenadasColores"/> para más información sobre la estructura de las coordenadas.</summary>
        public CoordenadasColores puntosFin;
        /// <summary>Corrección gamma para cada componente de color en formato FXPT2DOT30 (flotante de 2 bits de mantisa y 30 bits del exponente).
        /// <see cref="GammaColores"/> para más información sobre la estructura de la corrección gamma.</summary>
        public GammaColores gamma;
    }

    /// <summary>Estructura de cabecera DIB para mapas de bits de Windows 98.</summary>
    /// <remarks>
    ///     <para>
    ///     Esta estructura es nuevamente idéntica a la anterior, solo con campos adicionales.
    ///     Esta cabecera añade soporte a perfiles de color ICC, también añadió un campo que
    ///     sugiere un modo de renderizado y un campo reservado opcional.
    ///     </para>
    ///     <para>Los campos anteriores son exactamente los mismos que los de la anterior cabecera.</para>
    ///     <list type="bullet">
    ///         <listheader><term>Nuevas características:</term></listheader>
    ///         <item><description>Información del modo de renderizado sugerido</description></item>
    ///         <item><description>Soporte a perfiles de color ICC</description></item>
    ///     </list>
    /// </remarks>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct BMPV5Header
    {
        /// <summary>Indica a la aplicación la intención de renderizado de acuerdo al tipo de imagen.
        /// <see cref="IntencionRenderizado"/> para más información sobre las intenciones de renderizado.</summary>
        public IntencionRenderizado modoRenderizado;
        /// <summary>Dirección en bytes, a partir del comienzo de la cabecera DIB, del perfil ICC (si es usado).</summary>
        public UInt32 dirPerfil;
        /// <summary>Tamaño del perfil ICC si está embedido en el archivo.</summary>
        public UInt32 tamPerfil;
        /// <summary>Campo reservado.</summary><remarks>No usado.</remarks>
        public UInt32 reservado;
    }

    /// <summary>Estructura de encabezado de todos los archivos de mapas de bits de Windows (a partir de la versión 2.0).</summary>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct BMPFileHeader
    {
        /// <summary>Número mágico del archivo. Debe ser un elemento de <seealso cref="TipoBitmap"/>
        /// (aunque solo <seealso cref="TipoBitmap.BM"/> está soportado por esta librería).</summary>
        public TipoBitmap tipo;
        /// <summary>Tamaño en bytes del archivo de mapa de bits.</summary>
        public UInt32 tamArchivo;
        /// <summary>Campo reservado.</summary><remarks>No usado.</remarks>
        public UInt16 reservado1;
        /// <summary>Campo reservado.</summary><remarks>No usado.</remarks>
        public UInt16 reservado2;
        /// <summary>Dirección en bytes, desde el comienzo del archivo, del mapa de bits.</summary>
        public UInt32 dirBitmap;
    }

    /// <summary>Estructura que contiene la información del encabezado DIB y la versión que soporta.</summary>
    public struct DIBHeader
    {
        /// <summary>Versión de la cabecera DIB a usar.
        /// <see cref="VersionDIB"/> para más información de las versiones de cabecera DIB.</summary>
        public VersionDIB ver;
        /// <summary>Cabecera DIB de mapas de bits de Windows 2.0.
        /// <see cref="BMPV2Header"/> para más información sobre esta cabecera.</summary>
        public unsafe BMPV2Header* dibWin20;
        /// <summary>Cabecera DIB de mapas de bits de Windows 3.x y NT.
        /// <see cref="BMPV3Header"/> para más información sobre esta cabecera.</summary>
        public unsafe BMPV3Header* dibWinNT;
        /// <summary>Cabecera DIB de mapas de bits de Windows 95.
        /// <see cref="BMPV4Header"/> para más información sobre esta cabecera.</summary>
        public unsafe BMPV4Header* dibWin95;
        /// <summary>Cabecera DIB de mapas de bits de Windows 98.
        /// <see cref="BMPV5Header"/> para más información sobre esta cabecera.</summary>
        public unsafe BMPV5Header* dibWin98;
    }

    /// <summary>Estructura que contiene toda la información posible de un archivo BMP que maneja esta librería.</summary>
    /// <remarks>Esta estructura es inútil para el usuario final, ya que viene encapsulada dentro de la clase.</remarks>
    public struct eImagenBMP
    {
        /// <summary>Cabecera principal de archivo de mapa de bits.
        /// <see cref="BMPFileHeader"/> para más información sobre la cabecera principal.</summary>
        public BMPFileHeader cabecera;
        /// <summary>Información de la cabecera DIB del mapa de bits.
        /// <see cref="DIBHeader"/> para más información sobre la estructura de cabecera DIB.</summary>
        public DIBHeader dibInfo;
        /// <summary>Arreglo de elementos en la paleta de colores (si la profundidad de color es 8 bpp o menor).</summary>
        public unsafe UInt32* paleta;
        /// <summary>Máscaras de bits de los componentes de color en caso de que la compresión sea <seealso cref="MetodoCompresion.BITFIELDS"/>.
        /// <see cref="MascarasBits"/> para más información sobre las máscaras de bits.</summary>
        public unsafe MascarasBits* bitfields;
        /// <summary>Ruta del archivo de perfil ICC en formato ASCII en caso de que el espacio de color sea <seealso cref="EspacioColor.LINK"/>.</summary>
        public unsafe byte* rutaPerfil;
        /// <summary>Perfil de color ICC en caso de que el espacio de color sea <seealso cref="EspacioColor.MBED"/>.</summary>
        public unsafe void* perfilICC;
        /// <summary>Mapa de bits.</summary>
        public unsafe UInt32* bitmap;
    }
}
