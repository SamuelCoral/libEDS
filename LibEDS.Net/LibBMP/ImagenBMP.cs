using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace LibEDS.Net.LibBMP
{
    /// <summary>
    /// Clase que encapsula todas las propiedades de una imagen de mapa de bits de Windows (BMP o DIB).
    /// </summary>
    public partial class ImagenBMP : IDisposable, ICloneable
    {
        #region Variables

        internal unsafe eImagenBMP* imagen = null;
        private PaletaColores _paleta;

        #endregion

        #region Propiedades

        /// <summary>
        /// Paleta de colores (si la profundidad de color es 8 bpp o menor).
        /// <see cref="PaletaColores"/> para más información sobre las paletas de colores.
        /// <see cref="BPP"/> sobre la profundidad de color del mapa de bits.
        /// </summary>
        public PaletaColores Paleta
        {
            get { return _paleta; }
        }

        /// <summary>
        /// Devuelve o cambia la versión de la cabecera DIB del mapa de bits.
        /// <see cref="VersionDIB"/> para más información sobre las versiones de cabecera DIB.
        /// </summary>
        public VersionDIB Version
        {
            get { unsafe { return imagen->dibInfo.ver; } }
            set
            {
                unsafe
                {
                    convertir_dib_bmp(imagen, value);
                    ComprobarError();
                }
            }
        }

        /// <summary>
        /// Devuelve el método de compresión implementado en el mapa de bits.
        /// <see cref="MetodoCompresion"/> para más información sobre los métodos de compresión.
        /// </summary>
        /// <remarks>La versión <seealso cref="VersionDIB.Windows200"/> no soporta compresiones, por lo que siempre se devolverá <seealso cref="MetodoCompresion.RGB"/>.</remarks>
        public MetodoCompresion Compresion
        {
            get { unsafe { return (MetodoCompresion)compresion_bmp(imagen); } }
        }

        /// <summary>Devuelve el ancho en pixeles del mapa de bits.</summary>
        public int Ancho
        {
            get { unsafe { return (int)ancho_bmp(imagen); } }
        }

        /// <summary>Devuelve el alto en pixeles del mapa de bits.</summary>
        /// <remarks>
        /// De acuerdo al formato de archivo BMP si la altura es un valor negativo y se trata de un
        /// mapa de bits descomprimido, esto indica que debe ser leida de arriba hacia hacía abajo,
        /// pero esta propiedad siempre devolverá el valor absoluto del mapa de bits.
        /// Si desea conocer o alterar esta propiedad utilice <see cref="EstaDeCabeza"/>.
        /// </remarks>
        public int Alto
        {
            get { unsafe { return Math.Abs(alto_bmp(imagen)); } }
        }

        /// <summary>
        /// Indica o establece el orden de lectura de las líneas horizontales del mapa de bits.
        /// Un valor verdadero indica que las líneas están ordenadas en forma descendente,
        /// de lo contrario el orden de las líneas es ascendente.
        /// </summary>
        /// <remarks>
        /// Está propiedad está definida por el signo de la altura del mapa de bits pero como
        /// esta información puede ser pasada por alto por la mayoría de los usuarios ya que
        /// el resto de las funciones en esta librería detectan y aplican automáticamente las
        /// operaciones necesarias para cada uno, el signo devuelto por <seealso cref="Alto"/> será
        /// siempre positivo.
        /// Además no se puede efectuar esta operación si la <seealso cref="Compresion"/> no es <seealso cref="MetodoCompresion.RGB"/> o <seealso cref="MetodoCompresion.BITFIELDS"/>
        /// es decir, mapas de bits sin compresión.
        /// </remarks>
        public bool EstaDeCabeza
        {
            get { unsafe { return alto_bmp(imagen) < 0; } }
            set { unsafe { if ((!value && EstaDeCabeza) || (value && !EstaDeCabeza)) voltear_bmp(imagen); } }
        }

        /// <summary>Devuelve la profundidad de color del mapa de bits en bits por pixel.</summary>
        /// <remarks>
        /// La API de Windows solo maneja las siguentes profundidades de color: 1, 4, 8, 16, 24 y 32 bpp.
        /// Los mapas de bits con una profundidad de color menor o igual a 8 bpp contendrán paleta de colores.
        /// <see cref="PaletaColores"/> para más información sobre la paleta de colores.
        /// Los mapas de bits con una profundidad de color de 16 bpp tendrán por defecto el formato de pixel <seealso cref="MascarasBits.RGB555"/>.
        /// Los mapas de bits con una profundidad de color de 24 o 32 bpp tendrán por defecto el formato de pixel <seealso cref="MascarasBits.RGB888"/>.
        /// Las mapas de bits con una profundidad de color de 16 o 32 bpp pueden llevar una máscara de bits si su compresión es <seealso cref="MetodoCompresion.BITFIELDS"/>.
        /// Los mapas de bits cuya versión de cabecera DIB sea <seealso cref="VersionDIB.Windows200"/> no pueden tener una profundidad de color de 32 ni 16 bpp.
        /// <see cref="MascarasBits"/> para más información sobre las máscaras de bits.
        /// </remarks>
        public int BPP
        {
            get { unsafe { return bpp_bmp(imagen); } }
        }

        /// <summary>Devuelve el número de planos de color del dispositivo de video (siempre debe ser 1).</summary>
        public int PlanosColor
        {
            get { unsafe { return planos_bmp(imagen); } }
        }

        /// <summary>Devuelve o ajusta la resolución de impresión del mapa de bits en pixeles por metro.</summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.WindowsNT"/> o superior,
        /// de lo contrario devolverá <seealso cref="Size.Empty"/> y no se realizará ninguna acción al ajustarla.
        /// </remarks>
        public Size Resolucion
        {
            get { unsafe { return new Size((int)res_horizontal_bmp(imagen), (int)res_vertical_bmp(imagen)); } }
            set { unsafe { ajustar_res_impresion_bmp(imagen, (uint)value.Width, (uint)value.Height); } }
        }

        /// <summary>Devuelve las dimensiones del mapa de bits.</summary>
        public Size Dimensiones
        {
            get { return new Size(Ancho, Alto); }
        }

        /// <summary>
        /// Devuelve o ajusta las máscaras de bits de los componentes de color del mapa de bits.
        /// <see cref="MascarasBits"/> para más información sobre las máscaras de bits.
        /// </summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.WindowsNT"/> o superior,
        /// de lo contrario devolverá el formato de pixel por defecto para la profundidad de color del mapa de bits, y si se tratara de un mapa
        /// de bits con paleta de colores, devolverá el formato <seealso cref="MascarasBits.RGB888"/>, que corresponde al formato de pixel de la paleta.
        /// <see cref="BPP"/> para más información sobre la profundidad de color.
        /// Si se intenta cambiar el formato de pixel utilizando esta propiedad en un mapa de bits de una versión no soportada se forzará el
        /// cambio de versión a <seealso cref="VersionDIB.WindowsNT"/>.
        /// Si se intenta cambiar el formato de pixel utilizando máscaras de bits con canal Alpha, se forzará el
        /// cambio de versión a <seealso cref="VersionDIB.Windows95"/>.
        /// Si no desea forzar cambios en l mapa de bits, utilice la función <seealso cref="CambiarFormatoPixel"/>.
        /// Si se intenta cambiar el formato de pixel a el formato por defecto para la profundidad de color, se omitirán las máscaras de bits.
        /// Si se intenta cambiar el formato de pixel de un mapa de bits con paleta de colores, la paleta será eliminada.
        /// La profundidad de color se obtiene automáticamante entre 16 y 32 bpp dependiendo de las máscaras de bits.
        /// Si desea forzar la profundidad de de color, utilice la función <seealso cref="CambiarFormatoPixel"/>.
        /// </remarks>
        public MascarasBits FormatoPixel
        {
            get
            {
                unsafe
                {
                    if (Compresion != MetodoCompresion.BITFIELDS) return BPP == 16 ? MascarasBits.RGB555 : MascarasBits.RGB888;
                    return *imagen->bitfields;
                }
            }

            set
            {
                unsafe
                {
                    if (value.Alpha != 0 && Version < VersionDIB.Windows95) Version = VersionDIB.Windows95;
                    if (value != MascarasBits.RGB888 && Version < VersionDIB.WindowsNT) Version = VersionDIB.WindowsNT;
                    if (value == MascarasBits.RGB888) CambiarFormatoPixel(24, MascarasBits.MascarasBitsVacias);
                    else if (value == MascarasBits.RGB555) CambiarFormatoPixel(16, MascarasBits.MascarasBitsVacias);
                    else CambiarFormatoPixel(value.SumaBits > 16 ? 32 : 16, value);
                }
            }
        }

        /// <summary>
        /// Devuelve o cambia la ruta del archivo del perfil de color ICC
        /// (en caso de que el espacio de color sea <seealso cref="EspacioColor.LINK"/>).
        /// </summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.Windows98"/>,
        /// de lo contrario devolverá una cadena vacía al ser reclamada o intentará forzar el cambio de versión
        /// y el espacio de color para poder ajustarla.
        /// Si no desea forzar cambios en el mapa de bits, utilice la función <seealso cref="EstablecerPerfilICCEnlazado"/>.
        /// </remarks>
        public string RutaPerfilICC
        {
            get
            {
                if (EspacioColorLogico != EspacioColor.LINK) return String.Empty;
                unsafe { return Marshal.PtrToStringAnsi((IntPtr)imagen->rutaPerfil); }
            }

            set
            {
                if (Version < VersionDIB.Windows98) Version = VersionDIB.Windows98;
                EstablecerPerfilICCEnlazado(value);
            }
        }

        /// <summary>
        /// Devuelve el puntero del perfil de color ICC
        /// (en caso de que el espacio de color sea <seealso cref="EspacioColor.MBED"/>).
        /// </summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.Windows98"/>,
        /// de lo contrario devolverá un puntero nulo.
        /// Si desea actualizar el perfil de color ICC especificando nueva información proveniente de otro
        /// puntero utilice la función <seealso cref="EstablecerPerfilICCEmbedido"/>.
        /// </remarks>
        public IntPtr PunteroPerfilICCEmbedido
        {
            get
            {
                if (EspacioColorLogico != EspacioColor.MBED) return IntPtr.Zero;
                unsafe { return (IntPtr)imagen->perfilICC; }
            }
        }

        /// <summary>
        /// Devuelve el tamaño en bytes que ocupa el perfil de color ICC
        /// (en caso de que el espacio de color sea <seealso cref="EspacioColor.MBED"/>).
        /// </summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.Windows98"/>,
        /// de lo contrario devolverá 0.
        /// Si desea actualizar el perfil de color ICC especificando nueva información proveniente de otro
        /// puntero utilice la función <seealso cref="EstablecerPerfilICCEmbedido"/>.
        /// </remarks>
        public int TamPerfilICCEmbedido
        {
            get
            {
                if (EspacioColorLogico != EspacioColor.MBED) return 0;
                unsafe { return (int)imagen->dibInfo.dibWin98->tamPerfil; }
            }
        }

        /// <summary>
        /// Devuelve o cambia el tipo de espacio de color lógico del mapa de bits.
        /// <see cref="EspacioColor"/> para más información sobre los espacios de color.
        /// </summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.Windows95"/> o superior,
        /// de lo contrario devolverá <seealso cref="EspacioColor.sRGB"/> o intentará forzar el cambio de versión para poder ser ajustado.
        /// Si no desea forzar el cambio de versión, utilice la función <seealso cref="EstablecerECLGenerico(EspacioColor)"/>.
        /// Esta propiedad está dedicada a establecer solamente espacios de color genéricos como
        /// <seealso cref="EspacioColor.sRGB"/> o <seealso cref="EspacioColor.Win"/>,
        /// es decir, espacios de color que no requieren mayor información o parámetros para ser establecidos.
        /// Si desea establecer el espacio de color <seealso cref="EspacioColor.Calibrado"/>
        /// utilice la función <seealso cref="EstablecerECLCalibrado(CoordenadasColores, GammaColores)"/>.
        /// Si desea establecer el espacio de color <seealso cref="EspacioColor.LINK"/>
        /// utilice la función <seealso cref="EstablecerPerfilICCEnlazado(string)"/>
        /// o la propiedad <seealso cref="RutaPerfilICC"/>.
        /// Si desea establecer el espacio de color <seealso cref="EspacioColor.Calibrado"/>
        /// utilice la función <seealso cref="EstablecerPerfilICCEmbedido(IntPtr, int)"/>.
        /// </remarks>
        public EspacioColor EspacioColorLogico
        {
            get { unsafe { return espacio_color_bmp(imagen); } }
            set
            {
                if (Version < VersionDIB.Windows95) Version = VersionDIB.Windows95;
                EstablecerECLGenerico(value);
            }
        }

        /// <summary>
        /// Devuelve o establece las Coordenadas de color en el espacio de color lógico del mapa de bits.
        /// <see cref="CoordenadasColores"/> para más información sobre las coordenadas de color.
        /// </summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.Windows95"/> o superior,
        /// de lo contrario devolverá una estructura vacía o intentará forzar el cambio de versión para poder ajustarlo.
        /// Al forzar el cambio de versión, la información de la <seealso cref="GammaColoresECL"/> quedará vacía.
        /// Si no desea forzar el cambio de versión, utilice la función <seealso cref="EstablecerECLCalibrado(CoordenadasColores, GammaColores)"/>.
        /// </remarks>
        public CoordenadasColores CoordenadasColoresECL
        {
            get
            {
                if (Version < VersionDIB.Windows95) return new CoordenadasColores();
                unsafe { return imagen->dibInfo.dibWin95->puntosFin; }
            }

            set
            {
                if (Version < VersionDIB.Windows95) Version = VersionDIB.Windows95;
                EstablecerECLCalibrado(value, GammaColoresECL);
            }
        }

        /// <summary>
        /// Devuelve o establece la corrección Gamma de los componentes del color del mapa de bits.
        /// <see cref="GammaColores"/> para más información sobre la corrección gamma.
        /// </summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.Windows95"/> o superior,
        /// de lo contrario devolverá una estructura vacía o intentará forzar el cambio de versión para poder ajustarlo.
        /// Al forzar el cambio de versión, la información de la <seealso cref="CoordenadasColoresECL"/> quedará vacía.
        /// Si no desea forzar el cambio de versión, utilice la función <seealso cref="EstablecerECLCalibrado(CoordenadasColores, GammaColores)"/>.
        /// </remarks>
        public GammaColores GammaColoresECL
        {
            get
            {
                if (Version < VersionDIB.Windows95) return new GammaColores();
                unsafe { return imagen->dibInfo.dibWin95->gamma; }
            }

            set
            {
                if (Version < VersionDIB.Windows95) Version = VersionDIB.Windows95;
                EstablecerECLCalibrado(CoordenadasColoresECL, value);
            }
        }

        /// <summary>Devuelve o cambia la intención de renderizado del mapa de bits.
        /// <see cref="IntencionRenderizado"/> para más información sobre las intenciones de renderizado.</summary>
        /// <remarks>
        /// Esta información solo está disponible si la versión del mapa de bits es <seealso cref="VersionDIB.Windows98"/>,
        /// de lo contrario devolverá <seealso cref="IntencionRenderizado.Graficos"/> o intentará forzar el cambio de versión para poder ajustarlo.
        /// Si no desea forzar el cambio de versión, utilice la función <seealso cref="EstablecerIntencionRenderizado"/>.
        /// </remarks>
        public IntencionRenderizado ModoRenderizado
        {
            get { unsafe { return modo_renderizado_bmp(imagen); } }
            set
            {
                if (Version < VersionDIB.Windows98) Version = VersionDIB.Windows98;
                EstablecerIntencionRenderizado(value);
            }
        }

        #endregion

        #region Funciones Auxiliares

        internal static void ComprobarError()
        {
            string error = Marshal.PtrToStringAnsi(error_bmp());
            if (error != string.Empty) throw new ExcepcionBMP(error);
        }

        internal void ConstruirFormatoPixel()
        {
            unsafe { _paleta = new PaletaColores((byte)BPP, imagen->paleta); }
        }

        #endregion

        #region Constructores

        internal unsafe ImagenBMP(eImagenBMP* nueva)
        {
            imagen = nueva;
            ConstruirFormatoPixel();
        }

        /// <summary>
        /// Crea una mapa de bits vacío a partir de sus dimensiones y su pofundidad de color.
        /// <see cref="BPP"/> para más información sobre la profundidad de color.
        /// </summary>
        /// <param name="ancho">Ancho en pixeles del mapa de bits.</param>
        /// <param name="alto">Altura en pixeles del mapa de bits.</param>
        /// <param name="bpp">Profundidad de color del mapa de bits en bits por pixel.</param>
        public ImagenBMP(int ancho, int alto, int bpp)
        {
            unsafe
            {
                imagen = crear_bmp_vacio((UInt32)ancho, (Int32)alto, (UInt16)bpp);
                ComprobarError();
                ConstruirFormatoPixel();
            }
        }

        /// <summary>Carga un mapa de bits de un archivo.</summary>
        /// <param name="ruta">Ruta donde se localiza el mapa de bits.</param>
        public ImagenBMP(string ruta)
        {
            unsafe
            {
                imagen = cargar_bmp(ruta);
                ComprobarError();
                ConstruirFormatoPixel();
            }
        }

        /// <summary>Crea un mapa de bits a partir de uno ya creado copiándolo.</summary>
        /// <param name="origen">Mapa de bits de origen a copiar.</param>
        public ImagenBMP(ImagenBMP origen)
        {
            unsafe
            {
                imagen = copiar_bmp(origen.imagen);
                ComprobarError();
                ConstruirFormatoPixel();
            }
        }

        #endregion

        #region Métodos

        /// <summary>Guarda el mapa de bits en la ruta del archivo especificado.</summary>
        /// <param name="ruta">Nombre y ruta del archivo a guardar.</param>
        public void Guardar(string ruta)
        {
            unsafe
            {
                guardar_bmp(imagen, ruta);
                ComprobarError();
            }
        }

        /// <summary>Copia este mapa de bits.</summary>
        /// <returns>Copia del mapa de bits.</returns>
        public ImagenBMP Copiar()
        {
            unsafe
            {
                eImagenBMP* nueva = copiar_bmp(imagen);
                ComprobarError();
                return new ImagenBMP(nueva);
            }
        }

        /// <summary>Copia este mapa de bits.</summary>
        /// <returns>Copia del mapa de bits.</returns>
        public object Clone()
        {
            return Copiar();
        }

        /// <summary>
        /// Invierte el signo de la altura del mapa de bits para indicar a las aplicaciones que debe ser leído de cabeza.
        /// </summary>
        /// <remarks>
        /// Esta operación solo puede realizarce sobre mapas de bits sin compresión
        /// (como <seealso cref="MetodoCompresion.BITFIELDS"/> o <seealso cref="MetodoCompresion.RGB"/>).
        /// </remarks>
        public void Voltear()
        {
            unsafe
            {
                voltear_bmp(imagen);
                ComprobarError();
            }
        }

        /// <summary>
        /// Comprime o descomprime el mapa de bits utilizando el algoritmo RLE.
        /// <see cref="MetodoCompresion"/> para más información sobre los métodos de compresión.
        /// </summary>
        /// <remarks>
        /// Este formato solo se puede implementar en mapas de bits con profundidades de color de 4 u 8 bpp.
        /// </remarks>
        public void CompresionRLE()
        {
            unsafe
            {
                compresion_rle_bmp(imagen);
                ComprobarError();
            }
        }

        /// <summary>
        /// Cambia el formato de pixel de un mapa de bits que no tiene paleta de colores.
        /// <see cref="BPP"/> para más información sobre la profundidad de color.
        /// <see cref="MascarasBits"/> para más información sobre las máscaras de bits.
        /// </summary>
        /// <remarks>
        /// Solo se pueden transformar imágenes a 16, 24 y 32 bpp.
        /// Los mapas de bits cuya versión sea <seealso cref="VersionDIB.Windows200"/> solo soportan una profundidad de color de 24 bpp.
        /// Los mapas de bits de una profundidad de color de 24 bpp no soportan máscaras de bits por lo que siempre se tomará el
        /// formato <seealso cref="MascarasBits.RGB888"/> sin importar el indicado.
        /// La máscara del canal alpha no tendrá efecto si la versión del mapa de bits es <seealso cref="VersionDIB.WindowsNT"/>.
        /// </remarks>
        /// <param name="bpp">Profundidad de color en bits por pixel.</param>
        /// <param name="mascaras">Máscaras de bits.</param>
        public void CambiarFormatoPixel(int bpp, MascarasBits mascaras)
        {
            unsafe
            {
                cambiar_formato_pixel_bmp(imagen, (UInt16)bpp, mascaras);
                ComprobarError();
                ConstruirFormatoPixel();
            }
        }

        /// <summary>
        /// Quita la información del perfil de color ICC en caso de que esté presente en el mapa de bits.
        /// <see cref="EspacioColor"/> para más información sobre la información del espacio de color y
        /// los perfiles de color ICC.
        /// </summary>
        /// <remarks>
        /// Solamente los mapas de bits cuya versión sea <see cref="VersionDIB.Windows98"/> pueden contener
        /// un perfil de color ICC, por lo que usar esta función cuando haya una versión diferente resultará
        /// en un error.
        /// </remarks>
        public void QuitarPerfilICC()
        {
            unsafe
            {
                quitar_perfil_icc_bmp(imagen);
                ComprobarError();
            }
        }

        /// <summary>
        /// Establece la ruta de un archivo de perfil de color ICC para el mapa de bits.
        /// <see cref="EspacioColor"/> para más información sobre la información del espacio de color y
        /// los perfiles de color ICC.
        /// </summary>
        /// <remarks>
        /// Solamente los mapas de bits cuya versión sea <see cref="VersionDIB.Windows98"/> pueden contener
        /// un perfil de color ICC, por lo que usar esta función cuando haya una versión diferente resultará
        /// en un error.
        /// </remarks>
        /// <param name="rutaArchivo">Ruta que será almacenada para apuntar al perfil ICC.</param>
        public void EstablecerPerfilICCEnlazado(string rutaArchivo)
        {
            unsafe
            {
                establecer_ecl_archivo_bmp(imagen, rutaArchivo);
                ComprobarError();
            }
        }

        /// <summary>
        /// Establece un perfil de color ICC en el mapa de bits localizado en una dirección de memoria
        /// del tamaño especificado.
        /// </summary>
        /// <remarks>
        /// Solamente los mapas de bits cuya versión sea <see cref="VersionDIB.Windows98"/> pueden contener
        /// un perfil de color ICC, por lo que usar esta función cuando haya una versión diferente resultará
        /// en un error.
        /// </remarks>
        /// <param name="punteroPerfil">Puntero que indique la dirección de memoria donde se localize el perfil ICC.</param>
        /// <param name="tamPerfil">Cantidad de bytes a ser copiados de la dirección de memoria dada.</param>
        public void EstablecerPerfilICCEmbedido(IntPtr punteroPerfil, int tamPerfil)
        {
            unsafe
            {
                establecer_ecl_embedido_bmp(imagen, punteroPerfil, (UInt32)tamPerfil);
                ComprobarError();
            }
        }

        /// <summary>
        /// Establece un espacio de colo lógico calibrado para el mapa de bits especificando
        /// las coordenadas de los puntos finales en el espacio de color y la corrección gamma
        /// para cada componente de color.
        /// <see cref="CoordenadasColores"/> para más información sobre las coordenadas en el espacio de color.
        /// <see cref="GammaColores"/> para más información sobre la corrección gamma.
        /// </summary>
        /// <remarks>
        /// Solamente los mapas de bits cuya versión sea <see cref="VersionDIB.Windows95"/> o superior
        /// pueden contener información sobre el espacio de color, por lo que usar esta función cuando
        /// haya una versión diferente resultará en un error.
        /// </remarks>
        /// <param name="puntosFin">Coordenadas de los puntos finales en el espacio de color.</param>
        /// <param name="gamma">Corrección gamma para cada componente de color.</param>
        public void EstablecerECLCalibrado(CoordenadasColores puntosFin, GammaColores gamma)
        {
            unsafe
            {
                establecer_ecl_calibrado_bmp(imagen, puntosFin, gamma);
                ComprobarError();
            }
        }

        /// <summary>
        /// Establece uno de los espacios de color predeterminados indicados en <seealso cref="EspacioColor"/>
        /// para el mapa de bits.
        /// </summary>
        /// <remarks>
        /// Los únicos espacios de colos que se pueden asignar con esta función son <seealso cref="EspacioColor.sRGB"/>
        /// y <seealso cref="EspacioColor.Win"/> ya que no requieren información extra para ser asignadas.
        /// Para asignar algún otro elemento, utilice la función correspondiente.
        /// <see cref="EspacioColor"/> para más información sobre los espacios de color lógicos.
        /// Solamente los mapas de bits cuya versión sea <see cref="VersionDIB.Windows95"/> o superior
        /// pueden contener información sobre el espacio de color, por lo que usar esta función cuando
        /// haya una versión diferente resultará en un error.
        /// </remarks>
        /// <param name="ecl">Espacio de color lógico a aplicar.</param>
        public void EstablecerECLGenerico(EspacioColor ecl)
        {
            unsafe
            {
                establecer_ecl_generico_bmp(imagen, ecl);
                ComprobarError();
            }
        }

        /// <summary>
        /// Establece la intención de renderizado del mapa de bits, implementado en algunas aplicaciones de terceros.
        /// <see cref="IntencionRenderizado"/> para más información sobre la intención de renderizado.
        /// </summary>
        /// <remarks>
        /// Solamente los mapas de bits cuya versión sea <see cref="VersionDIB.Windows98"/>
        /// pueden contener información sobre la intención de renderizado, por lo que usar esta función cuando
        /// haya una versión diferente resultará en un error.
        /// </remarks>
        /// <param name="intencion">Intención de renderizado a aplicar.</param>
        public void EstablecerIntencionRenderizado(IntencionRenderizado intencion)
        {
            unsafe
            {
                establecer_intencion_renderizado_bmp(imagen, intencion);
                ComprobarError();
            }
        }

        #endregion

        #region Destructor

        /// <summary>Indica si el objecto ya ha sido destruido.</summary>
        private bool disposed = false;

        /// <summary>Libera los recursos utilizados por esta imagen BMP.</summary>
        /// <param name="disposing">Indica si se desean liberar también los recursos administrados (para ser omitidos por el recolector de basura después).</param>
        protected virtual void Dispose(bool disposing)
        {
            unsafe
            {
                if (disposed) return;
                if (disposing)
                {
                    //Libera los recursos administrados
                }

                //Libera los recursos no administrados
                destruir_puntero_bmp(imagen);
                imagen = null;
                disposed = true;
            }
        }

        /// <summary>Libera los recursos utilizados por esta imagen BMP.</summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>Libera los recursos utilizados por esta imagen BMP.</summary>
        ~ImagenBMP()
        {
            Dispose(false);
        }

        #endregion
    }
}
