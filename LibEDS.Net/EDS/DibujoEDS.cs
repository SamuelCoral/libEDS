using System;
using System.Runtime.InteropServices;
using System.Drawing;
using LibEDS.Net.LibBMP;

namespace LibEDS.Net
{
    /// <summary>Clase que encapsula todos los métodos y propiedades de un lienzo de dibujo simple.</summary>
    public partial class DibujoEDS : IDisposable, ICloneable
    {
        #region Variables

        private unsafe eDibujoEDS* dibujo;
        private PaletaColores _paleta;
        private MapaBitsEDS _bitmap;
        private MapaBitsPaletaEDS _bitmap_p;
        //// <summary>Posición actual del cursor utilizado en operaciones de dibujo con coordenadas relativas.</summary>
        //public Point Posicion;

        #endregion

        #region Propiedades

        /// <summary>Paleta de colores en caso de que el dibujo sea de una profundidad de color de 8 bpp o menor.</summary>
        /// <remarks>El número de entradas se determina por la fórmula 2^bpp.</remarks>
        public PaletaColores Paleta
        {
            get { return _paleta; }
        }

        /// <summary>Mapa de bits del dibujo con el que se pueden obtener o ajustar los pixeles en un arreglo.</summary>
        public MapaBitsEDS MapaDeBits
        {
            get { return _bitmap; }
        }

        /// <summary>Mapa de bits del dibujo con paleta de colores con el que se pueden obtener o ajustar los pixeles en un arreglo.</summary>
        public MapaBitsPaletaEDS MapaDeBitsPaleta
        {
            get { return _bitmap_p; }
        }

        /// <summary>Obtiene o reescala el ancho del dibujo en pixeles.</summary>
        public int Ancho
        {
            get { unsafe { return (int)dibujo->ancho; } }
            set
            {
                unsafe
                {
                    if (value < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                    reescalar_d(dibujo, (UInt32)value, dibujo->alto);
                    ComprobarErrorEDS();
                }
            }
        }

        /// <summary>Obtiene o redimensiona el alto del dibujo en pixeles.</summary>
        public int Alto
        {
            get { unsafe { return (int)dibujo->alto; } }
            set
            {
                unsafe
                {
                    if (value < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                    reescalar_d(dibujo, dibujo->ancho, (UInt32)value);
                    ComprobarErrorEDS();
                }
            }
        }

        /// <summary>Obtiene o cambia la profundidad de color del dibujo en bits por pixel.</summary>
        /// <remarks>Solo las profundidades de color 1, 4, 8 y 32 bpp son válidas.</remarks>
        public int BPP
        {
            get { unsafe { return dibujo->bpp; } }
            set
            {
                unsafe
                {
                    if (value < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                    if (value > 8) aumentar_bpp_d(dibujo);
                    else reducir_bpp_d(dibujo, (byte)value);
                    ConstruirFormatoPixel();
                    ComprobarErrorEDS();
                }
            }
        }

        /// <summary>Obtiene o cambia las dimensiones del dibujo.</summary>
        public Size Dimensiones
        {
            get { return new Size(Ancho, Alto); }
            set
            {
                unsafe
                {
                    if(value.Width < 0 || value.Height < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                    reescalar_d(dibujo, (UInt32)value.Width, (UInt32)value.Height);
                    ComprobarErrorEDS();
                }
            }
        }

        #endregion

        #region Funciones Auxiliares

        private void ComprobarErrorEDS()
        {
            string error = Marshal.PtrToStringAnsi(error_EDS());
            if (error != string.Empty) throw new ExcepcionEDS(error);
        }

        private void ConstruirFormatoPixel()
        {
            unsafe
            {
                _paleta = new PaletaColores((byte)BPP, dibujo->paleta);
                _bitmap = new MapaBitsEDS(this);
                _bitmap_p = new MapaBitsPaletaEDS(this);
            }
        }

        #endregion

        #region Constructores

        private unsafe DibujoEDS(eDibujoEDS* nuevo)
        {
            dibujo = nuevo;
            ConstruirFormatoPixel();
        }

        /// <summary>
        /// Construye un dibujo vacío de las dimensiones y la profundidad de color especificadas.
        /// </summary>
        /// <param name="ancho">Ancho del dibujo en pixeles.</param>
        /// <param name="alto">Alto del dibujo en pixeles.</param>
        /// <param name="bpp">Profundidad de color del dibujo en bits por pixel.</param>
        public DibujoEDS(int ancho, int alto, int bpp = 32)
        {
            unsafe
            {
                if (ancho < 0 || alto < 0 || bpp < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                dibujo = crear_dibujo_vacio((UInt32)ancho, (UInt32)alto, (byte)bpp);
                ComprobarErrorEDS();
                ConstruirFormatoPixel();
            }
        }

        /// <summary>
        /// Construye un dibujo vacío de las dimensiones y la profundidad de color especificadas.
        /// </summary>
        /// <param name="dimensiones">Dimensiones del dibujo.</param>
        /// <param name="bpp">Profundidad de color del dibujo en bits por pixel.</param>
        public DibujoEDS(Size dimensiones, int bpp = 32) : this(dimensiones.Width, dimensiones.Height, bpp) { }

        /// <summary>
        /// Construye un dibujo a partir de una imagen BMP.
        /// <see cref="ImagenBMP"/> para más información sobre las imágenes BMP.
        /// </summary>
        /// <param name="imagen">Imagen a copiar para crear el dibujo.</param>
        /// <param name="paleta">Indica si se desea conservar la paleta de colores en caso de que exista.</param>
        public DibujoEDS(ImagenBMP imagen, bool paleta = true)
        {
            unsafe
            {
                dibujo = convertir_bmp_dibujo(imagen.imagen, paleta);
                ComprobarErrorEDS();
                ConstruirFormatoPixel();
            }
        }

        /// <summary>
        /// Construye un dibujo a partir de un archivo de imagen BMP en la ruta dada.
        /// </summary>
        /// <param name="rutaArchivo">Ruta del archivo BMP a copiar para crear el dibujo.</param>
        /// <param name="paleta">Indica si se desea conservar la paleta de colores en caso de que exista.</param>
        public DibujoEDS(string rutaArchivo, bool paleta = true)
        {
            unsafe
            {
                dibujo = cargar_dibujo_archivo_bmp(rutaArchivo, paleta);
                ComprobarErrorEDS();
                ConstruirFormatoPixel();
            }
        }

        /// <summary>
        /// Construye un dibujo a partir de otro, copiándolo.
        /// </summary>
        /// <param name="copia">Dibujo a copiar.</param>
        public DibujoEDS(DibujoEDS copia)
        {
            unsafe
            {
                dibujo = copiar_dibujo(copia.dibujo);
                ComprobarErrorEDS();
                ConstruirFormatoPixel();
            }
        }

        /// <summary>
        /// Construye un dibujo a partir de un mapa de bits de .Net <seealso cref="Bitmap"/>.
        /// </summary>
        /// <param name="imagen">Mapa de bits de .Net a convertir.</param>
        public DibujoEDS(Bitmap imagen) : this(imagen.Width, imagen.Height, 32)
        {
            for (int Y = 0; Y < Alto; Y++) for (int X = 0; X < Ancho; X++)
                    MapaDeBits[X, Y] = imagen.GetPixel(X, Y);
        }

        #endregion

        #region Métodos Comunes y Conversiones

        /// <summary>
        /// Almacena el dibujo en una Imagen BMP sin cambiar sus propiedades.
        /// </summary>
        /// <param name="imagen">Imagen BMP donde se almacenará el dibujo.</param>
        /// <param name="alpha">Indica si también se desea conservar el canal alpha de cada pixel.</param>
        public void InyectarAImagenBMP(ImagenBMP imagen, bool alpha = false)
        {
            unsafe
            {
                inyectar_dibujo_bmp(dibujo, imagen.imagen, alpha);
                ComprobarErrorEDS();
                imagen.ConstruirFormatoPixel();
            }
        }

        /// <summary>
        /// Convierte el dibujo actual en una Imagen BMP.
        /// </summary>
        /// <param name="alpha">Indica si se desea conservar el canal alpha de cada pixel.</param>
        /// <param name="rle">Intenta aplicar la compresión RLE al mapa de bits después de convertirlo.</param>
        /// <returns></returns>
        public ImagenBMP ConvertirAImagenBMP(bool alpha = false, bool rle = false)
        {
            unsafe
            {
                eImagenBMP* imagen = convertir_dibujo_bmp(dibujo, alpha, rle);
                ComprobarErrorEDS();
                return new ImagenBMP(imagen);
            }
        }

        /// <summary>
        /// Convierte el dibujo en un mapa de bits de .Net <seealso cref="Bitmap"/>.
        /// </summary>
        /// <returns>Mapa de bits de .Net.</returns>
        public Bitmap ConvertirABitmap()
        {
            Bitmap salida = new Bitmap(Ancho, Alto);
            for (int Y = 0; Y < Alto; Y++) for (int X = 0; X < Ancho; X++)
                    salida.SetPixel(X, Y, MapaDeBits[X, Y]);
            return salida;
        }

        /// <summary>
        /// Convierte un dibujo en una Imagen BMP con un formato de pixel <seealso cref="MascarasBits.RGB888"/>.
        /// </summary>
        /// <param name="dibujo">Dibujo a convertir a Imagen BMP.</param>
        public static implicit operator ImagenBMP(DibujoEDS dibujo)
        {
            return dibujo.ConvertirAImagenBMP();
        }

        /// <summary>
        /// Convierte una Imagen BMP en una estructura de dibujo.
        /// </summary>
        /// <param name="imagen">Imagen BMP a convertir.</param>
        public static explicit operator DibujoEDS(ImagenBMP imagen)
        {
            return new DibujoEDS(imagen);
        }

        /// <summary>
        /// Convierte un dibujo en un Mapa de bits de .Net <seealso cref="Bitmap"/>.
        /// </summary>
        /// <param name="dibujo">Dibujo a convertir.</param>
        public static implicit operator Bitmap(DibujoEDS dibujo)
        {
            return dibujo.ConvertirABitmap();
        }

        /// <summary>
        /// Convierte un mapa de bits de .Net <seealso cref="Bitmap"/> en un dibujo.
        /// </summary>
        /// <param name="imagen">Mapa de bits de .Net a convertir.</param>
        public static explicit operator DibujoEDS(Bitmap imagen)
        {
            return new DibujoEDS(imagen);
        }

        /// <summary>Copia este dibujo.</summary>
        /// <returns>Copia del dibujo.</returns>
        public DibujoEDS Copiar()
        {
            unsafe
            {
                eDibujoEDS* copia = copiar_dibujo(dibujo);
                ComprobarErrorEDS();
                return new DibujoEDS(copia);
            }
        }

        /// <summary>Copia este dibujo.</summary>
        /// <returns>Copia del dibujo.</returns>
        public object Clone()
        {
            return Copiar();
        }

        /// <summary>
        /// Guarda este dibujo en un archivo BMP en la ruta especificada.
        /// </summary>
        /// <param name="rutaArchivo">Ruta del archivo a guardar.</param>
        /// <param name="alpha">Indica si se desea conservar el canal alpha de cada pixel.</param>
        /// <param name="rle">Intenta aplicar la compresión RLE al mapa de bits antes de guardarlo.</param>
        public void GuardarImagenBMP(string rutaArchivo, bool alpha = false, bool rle = false)
        {
            unsafe
            {
                guardar_dibujo_bmp(dibujo, rutaArchivo, alpha, rle);
                ComprobarErrorEDS();
                ImagenBMP.ComprobarError();
            }
        }

        #endregion

        #region Funciones de Color

        /// <summary>Mapa de bits de un dibujo que no tiene paleta de colores.</summary>
        public class MapaBitsEDS
        {
            private DibujoEDS dibujo;

            internal MapaBitsEDS(DibujoEDS dibujo)
            {
                this.dibujo = dibujo;
            }

            /// <summary>Deveulve o ajusta el color de un pixel del dibujo en las posiciones indicadas.</summary>
            /// <remarks>
            /// Si se utiliza en un dibujo con paleta de colores, se devolverá el color al que apunta el índice de
            /// la paleta para el pixel solicitado y no podrá cambiarse ningún pixel, para ello utilice <seealso cref="DibujoEDS.MapaDeBitsPaleta"/>.
            /// </remarks>
            /// <param name="X">Coordenada en X del pixel solicitado.</param>
            /// <param name="Y">Coordenada en X del pixel solicitado.</param>
            /// <returns>Color del pixel en las coordenadas solicitadas.</returns>
            public Color this[int X, int Y]
            {
                get { unsafe { return dibujo.BPP > 8 ? Color.FromArgb((Int32)v_pixel(dibujo.dibujo, (UInt32)X, (UInt32)Y, false)) : dibujo.Paleta[(Int32)v_pixel(dibujo.dibujo, (UInt32)X, (UInt32)Y, false)]; } }
                set { unsafe { if (dibujo.BPP > 8) d_pixel(dibujo.dibujo, (UInt32)X, (UInt32)Y, (UInt32)value.ToArgb(), false); } }
            }
        }

        /// <summary>Mapa de bits de un dibujo que tiene paleta de colores.</summary>
        public class MapaBitsPaletaEDS
        {
            private DibujoEDS dibujo;

            internal MapaBitsPaletaEDS(DibujoEDS dibujo)
            {
                this.dibujo = dibujo;
            }

            /// <summary>Devuelve o ajusta la entrada de la paleta de colores del pixel en las coordenadas indicadas del dibujo.</summary>
            /// <remarks>
            /// Si el dibujo no poseé una paleta de colores no ocurrirá ninguna acción al intentar ajustar
            /// algún valor y devolverá 0 en cualquier pixel solicitado.
            /// </remarks>
            /// <param name="X">Coordenada en X del pixel solicitado.</param>
            /// <param name="Y">Coordenada en Y del pixel solicitado.</param>
            /// <returns>Entrada de la paleta de colores del pixel en las coordenadas solicitadas.</returns>
            public int this[int X, int Y]
            {
                get { unsafe { return dibujo.BPP <= 8 ? (byte)v_pixel(dibujo.dibujo, (UInt32)X, (UInt32)Y, false) : 0; } }
                set { unsafe { if (dibujo.BPP <= 8) d_pixel(dibujo.dibujo, (UInt32)X, (UInt32)Y, (UInt32)value, false); } }
            }
        }

        /// <summary>Invierte un color dado.</summary>
        /// <param name="color">Color a invertir.</param>
        /// <returns>Color invertido.</returns>
        public static Color InvertirColor(Color color)
        {
            return Color.FromArgb((Int32)invertir_color((UInt32)color.ToArgb()));
        }

        /// <summary>
        /// Convierte un color dado a su equivalente en escala de grises siguiendo
        /// los términos de la iluminación linear del espacio de color CIE 1931.
        /// </summary>
        /// <param name="color">Color a convertir en escala de grises.</param>
        /// <returns>Color en escala de grises equivalente.</returns>
        public static Color ColorEscalaGrises(Color color)
        {
            return Color.FromArgb((Int32)color_escala_grises((UInt32)color.ToArgb()));
        }

        /// <summary>Busca el color más cercano en una paleta de colores a un color dado.</summary>
        /// <param name="paleta">Paleta de colores a buscar el color más cercano.</param>
        /// <param name="color">Color a buscar en la paleta de colores.</param>
        /// <returns>Color mas cercano.</returns>
        public static int ColorMasCercano(PaletaColores paleta, Color color)
        {
            unsafe { return color_mas_cercano(paleta.colores, paleta.paleta, (UInt32)color.ToArgb()); }
        }

        /// <summary>Invierte los colores de todo el dibujo.</summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        public void InvertirColores()
        {
            unsafe
            {
                invertir_colores_d(dibujo);
                ComprobarErrorEDS();
            }
        }

        /// <summary>Convierte todo el dibujo en escala de grises.</summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        public void EscalaGrises()
        {
            unsafe
            {
                escala_grises_d(dibujo);
                ComprobarErrorEDS();
            }
        }

        /// <summary>Realiza la operación binaria OR a cada pixel con el color dado.</summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        /// <param name="color">Color a saturar en el dibujo.</param>
        public void SaturarColores(Color color)
        {
            unsafe
            {
                saturar_colores_d(dibujo, (UInt32)color.ToArgb());
                ComprobarErrorEDS();
            }
        }

        /// <summary>Realiza la operación binaria AND a cada pixel con el color dado.</summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        /// <param name="color">Color a extrar del dibujo.</param>
        public void ExtraerColores(Color color)
        {
            unsafe
            {
                extraer_colores_d(dibujo, (UInt32)color.ToArgb());
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Aplica un incremento o decremento en la transparencia (canal alpha) del dibujo
        /// que vaya entre -255 y 255.
        /// </summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        /// <param name="incremento">Incremento de transparencia.</param>
        public void CambiarTransparencia(int incremento)
        {
            unsafe
            {
                cambiar_transparencia_d(dibujo, (Int16)incremento);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Aplica un incremento o decremento en el componente rojo del color del dibujo
        /// que vaya entre -255 y 255.
        /// </summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        /// <param name="incremento">Incremento de color rojo.</param>
        public void CambiarRojo(int incremento)
        {
            unsafe
            {
                cambiar_rojo_d(dibujo, (Int16)incremento);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Aplica un incremento o decremento en el componente verde del color del dibujo
        /// que vaya entre -255 y 255.
        /// </summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        /// <param name="incremento">Incremento de color verde.</param>
        public void CambiarVerde(int incremento)
        {
            unsafe
            {
                cambiar_verde_d(dibujo, (Int16)incremento);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Aplica un incremento o decremento en el componente azul del color del dibujo
        /// que vaya entre -255 y 255.
        /// </summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        /// <param name="incremento">Incremento de color azul.</param>
        public void CambiarAzul(int incremento)
        {
            unsafe
            {
                cambiar_azul_d(dibujo, (Int16)incremento);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Aplica un incremento o decremento en el brillo de todo el dibujo
        /// que vaya entre -255 y 255.
        /// </summary>
        /// <remarks>Solo funciona en dibujos sin paleta de colores.</remarks>
        /// <param name="incremento">Incremento de brillo.</param>
        public void CambiarBrillo(int incremento)
        {
            unsafe
            {
                cambiar_brillo_d(dibujo, (Int16)incremento);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Convierte el dibujo actual en un dibujo a colores reales (con una profundidad de color
        /// de 32 bpp) eliminando la paleta de colores.
        /// </summary>
        public void AumentarBPP()
        {
            unsafe
            {
                aumentar_bpp_d(dibujo);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Convierte el dibujo actual en un dibujo de paleta de colores, reduciendo su profundidad
        /// de color a la especificada buscando los colores mas cercanos a la paleta de colores
        /// estándar para cada profundidad de color (8, 4 o 1 bpp).
        /// </summary>
        /// <param name="bpp">Nueva profundidad de color a usar</param>
        public void ReducirBPP(int bpp)
        {
            unsafe
            {
                reducir_bpp_d(dibujo, (byte)bpp);
                ComprobarErrorEDS();
            }
        }

        #endregion

        #region Funciones de Dibujo

        /// <summary>
        /// Limpia todo el dibujo y lo colorea del color especificado.
        /// </summary>
        /// <param name="color">Color que rellenará el dibujo entero.</param>
        public void Limpiar(Color color)
        {
            unsafe { limpiar_d(dibujo, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja una línea recta en el dibujo dadas las coordenadas de 2 puntos.
        /// </summary>
        /// <param name="x1">Coordenada en X del punto 1.</param>
        /// <param name="y1">Coordenada en Y del punto 1.</param>
        /// <param name="x2">Coordenada en X del punto 2.</param>
        /// <param name="y2">Coordenada en Y del punto 2.</param>
        /// <param name="color">Color de la recta.</param>
        public void DibujarLinea(int x1, int y1, int x2, int y2, Color color)
        {
            unsafe { d_linea(dibujo, x1, y1, x2, y2, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja una línea recta en el dibujo dados sus 2 puntos finales.
        /// </summary>
        /// <param name="p1">Primer punto.</param>
        /// <param name="p2">Segundo punto.</param>
        /// <param name="color">Color de la recta.</param>
        public void DibujarLinea(Point p1, Point p2, Color color)
        {
            DibujarLinea(p1.X, p1.Y, p2.X, p2.Y, color);
        }

        /// <summary>
        /// Dibuja el contorno de un rectángulo en el dibujo dadas las coordenadas
        /// de los puntos de sus 2 aristas opuestas.
        /// </summary>
        /// <param name="x1">Coordenada en X del punto de la primera arista.</param>
        /// <param name="y1">Coordenada en Y del punto de la primera arista.</param>
        /// <param name="x2">Coordenada en X del punto de la segunda arista.</param>
        /// <param name="y2">Coordenada en Y del punto de la segunda arista.</param>
        /// <param name="color">Color del rectángulo.</param>
        public void DibujarRectangulo(int x1, int y1, int x2, int y2, Color color)
        {
            unsafe { d_rect(dibujo, x1, y1, x2, y2, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja el contorno de un rectángulo en el dibujo dados los puntos de
        /// sus 2 aristas opuestas.
        /// </summary>
        /// <param name="p1">Punto de la primera arista.</param>
        /// <param name="p2">Punto de la segunda arista.</param>
        /// <param name="color">Color del rectángulo.</param>
        public void DibujarRectangulo(Point p1, Point p2, Color color)
        {
            DibujarRectangulo(p1.X, p1.Y, p2.X, p2.Y, color);
        }

        /// <summary>
        /// Dibuja el contorno de un rectángulo dado en el dibujo.
        /// </summary>
        /// <param name="r">Rectángulo a dibujar.</param>
        /// <param name="color">Color del rectángulo.</param>
        public void DibujarRectangulo(Rectangle r, Color color)
        {
            DibujarRectangulo(r.Left, r.Top, r.Right, r.Bottom, color);
        }

        /// <summary>
        /// Dibuja y rellena un rectángulo en el dibujo dadas las coordenadas
        /// de los puntos de sus 2 aristas opuestas.
        /// </summary>
        /// <param name="x1">Coordenada en X del punto de la primera arista.</param>
        /// <param name="y1">Coordenada en Y del punto de la primera arista.</param>
        /// <param name="x2">Coordenada en X del punto de la segunda arista.</param>
        /// <param name="y2">Coordenada en Y del punto de la segunda arista.</param>
        /// <param name="color">Color del rectángulo.</param>
        public void DibujarRectanguloLleno(int x1, int y1, int x2, int y2, Color color)
        {
            unsafe { d_rect_lleno(dibujo, x1, y1, x2, y2, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja y rellena un rectángulo en el dibujo dados los puntos de
        /// sus 2 aristas opuestas.
        /// </summary>
        /// <param name="p1">Punto de la primera arista.</param>
        /// <param name="p2">Punto de la segunda arista.</param>
        /// <param name="color">Color del rectángulo.</param>
        public void DibujarRectanguloLleno(Point p1, Point p2, Color color)
        {
            DibujarRectanguloLleno(p1.X, p1.Y, p2.X, p2.Y, color);
        }

        /// <summary>
        /// Dibuja y rellena un rectángulo dado en el dibujo.
        /// </summary>
        /// <param name="r">Rectángulo a dibujar.</param>
        /// <param name="color">Color del rectángulo.</param>
        public void DibujarRectanguloLleno(Rectangle r, Color color)
        {
            DibujarRectanguloLleno(r.Left, r.Top, r.Right, r.Bottom, color);
        }

        /// <summary>
        /// Dibuja una circunferencia en el dibujo dadas las coordenadas de su centro
        /// y su radio.
        /// </summary>
        /// <param name="x1">Coordenada en X del centro de la circunferencia.</param>
        /// <param name="y1">Coordenada en Y del centro de la circunferencia.</param>
        /// <param name="radio">Radio de la circunferencia.</param>
        /// <param name="color">Color de la circunferencia.</param>
        public void DibujarCirculo(int x1, int y1, int radio, Color color)
        {
            unsafe { d_circ(dibujo, x1, y1, (UInt32)radio, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja una circunferencia en el dibujo dado su centro y su radio.
        /// </summary>
        /// <param name="p1">Punto del centro de la circunferencia.</param>
        /// <param name="radio">Radio de la circunferencia.</param>
        /// <param name="color">Color de la circunferencia.</param>
        public void DibujarCirculo(Point p1, int radio, Color color)
        {
            DibujarCirculo(p1.X, p1.Y, radio, color);
        }

        /// <summary>
        /// Dibuja un círculo en el dibujo dadas las coordenadas de su centro
        /// y su radio.
        /// </summary>
        /// <param name="x1">Coordenada en X del centro del círculo.</param>
        /// <param name="y1">Coordenada en Y del centro del círculo.</param>
        /// <param name="radio">Radio del círculo.</param>
        /// <param name="color">Color del círculo.</param>
        public void DibujarCirculoLleno(int x1, int y1, int radio, Color color)
        {
            unsafe { d_circ_lleno(dibujo, x1, y1, (UInt32)radio, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja un círculo en el dibujo dado su centro y su radio.
        /// </summary>
        /// <param name="p1">Punto del centro del círculo.</param>
        /// <param name="radio">Radio del círculo.</param>
        /// <param name="color">Color del círculo.</param>
        public void DibujarCirculoLleno(Point p1, int radio, Color color)
        {
            DibujarCirculoLleno(p1.X, p1.Y, radio, color);
        }

        /// <summary>
        /// Dibuja una semicircunferencia en el dibujo dadas las coordenadas de su centro,
        /// su radio y sus ángulos de inicio y fin.
        /// </summary>
        /// <param name="x1">Coordenada en X del centro de la semicircunferencia.</param>
        /// <param name="y1">Coordenada en Y del centro de la semicircunferencia.</param>
        /// <param name="radio">Radio de la semicircunferencia.</param>
        /// <param name="anguloInicio">Ángulo de inicio de la semicircunferencia con origen sobre la abscisa positiva.</param>
        /// <param name="anguloFinal">Ángulo de fin de la semicircunferencia con origen sobre la abscisa positiva.</param>
        /// <param name="color">Color de la semicircunferencia.</param>
        public void DibujarSemiCirculo(int x1, int y1, int radio, double anguloInicio, double anguloFinal, Color color)
        {
            unsafe { d_semi_circ(dibujo, x1, y1, (UInt32)radio, anguloInicio, anguloFinal, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja una semicircunferencia en el dibujo dados su centro, su radio y
        /// sus ángulos de inicio y fin.
        /// </summary>
        /// <param name="p1">Punto del centro de la semicircunferencia.</param>
        /// <param name="radio">Radio de la semicircunferencia.</param>
        /// <param name="anguloInicio">Ángulo de inicio de la semicircunferencia con origen sobre la abscisa positiva.</param>
        /// <param name="anguloFinal">Ángulo de fin de la semicircunferencia con origen sobre la abscisa positiva.</param>
        /// <param name="color">Color de la semicircunferencia.</param>
        public void DibujarSemiCirculo(Point p1, int radio, double anguloInicio, double anguloFinal, Color color)
        {
            DibujarSemiCirculo(p1.X, p1.Y, radio, anguloInicio, anguloFinal, color);
        }

        /// <summary>
        /// Dibuja el contorno de una elipse en el dibujo dadas las coordenadas de su centro y
        /// sus radios horizontal y vertical.
        /// </summary>
        /// <param name="x1">Coordenada en X del centro de la elipse.</param>
        /// <param name="y1">Coordenada en Y del centro de la elipse.</param>
        /// <param name="radioHorizontal">Radio horizontal de la elipse.</param>
        /// <param name="radioVertical">Radio vertical de la elipse.</param>
        /// <param name="color">Color de la elipse.</param>
        public void DibujarElipse(int x1, int y1, int radioHorizontal, int radioVertical, Color color)
        {
            unsafe { d_elipse(dibujo, x1, y1, (UInt32)radioHorizontal, (UInt32)radioVertical, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja el contorno de una elipse en el dibujo dados su centro y sus
        /// radios horizontal y vertical.
        /// </summary>
        /// <param name="p1">Punto del centro de la elipse.</param>
        /// <param name="radioHorizontal">Radio horizontal de la elipse.</param>
        /// <param name="radioVertical">Radio vertical de la elipse.</param>
        /// <param name="color">Color de la elipse.</param>
        public void DibujarElipse(Point p1, int radioHorizontal, int radioVertical, Color color)
        {
            DibujarElipse(p1.X, p1.Y, radioHorizontal, radioVertical, color);
        }

        /// <summary>
        /// Dibuja el controno de una elipse en el dibujo que se encuentra inscrita en
        /// un rectángulo dados su punto de la arista superior izquierda y su tamaño.
        /// </summary>
        /// <param name="p1">Punto de la arista superior izquierda del rectángulo.</param>
        /// <param name="tam">Tamaño del rectángulo.</param>
        /// <param name="color">Color de la elipse.</param>
        public void DibujarElipse(Point p1, Size tam, Color color)
        {
            int radioHorizontal = tam.Width / 2;
            int radioVertical = tam.Height / 2;
            DibujarElipse(p1.X + radioHorizontal, p1.Y + radioVertical, radioHorizontal, radioVertical, color);
        }

        /// <summary>
        /// Dibuja el contorno de una elipse en el dibujo que se encuentre inscrita en un
        /// rectángulo dado.
        /// </summary>
        /// <param name="r">Rectángulo donde se encuentra incrita la elipse.</param>
        /// <param name="color">Color de la elipse.</param>
        public void DibujarElipse(Rectangle r, Color color)
        {
            int radioHorizontal = r.Width / 2;
            int radioVertical = r.Height / 2;
            DibujarElipse(r.X + radioHorizontal, r.Y + radioVertical, radioHorizontal, radioVertical, color);
        }

        /// <summary>
        /// Dibuja y rellena una elipse en el dibujo dadas las coordenadas de su centro y
        /// sus radios horizontal y vertical.
        /// </summary>
        /// <param name="x1">Coordenada en X del centro de la elipse.</param>
        /// <param name="y1">Coordenada en Y del centro de la elipse.</param>
        /// <param name="radioHorizontal">Radio horizontal de la elipse.</param>
        /// <param name="radioVertical">Radio vertical de la elipse.</param>
        /// <param name="color">Color de la elipse.</param>
        public void DibujarElipseLlena(int x1, int y1, int radioHorizontal, int radioVertical, Color color)
        {
            unsafe { d_elipse_llena(dibujo, x1, y1, (UInt32)radioHorizontal, (UInt32)radioVertical, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja y rellena una elipse en el dibujo dados su centro y sus
        /// radios horizontal y vertical.
        /// </summary>
        /// <param name="p1">Punto del centro de la elipse.</param>
        /// <param name="radioHorizontal">Radio horizontal de la elipse.</param>
        /// <param name="radioVertical">Radio vertical de la elipse.</param>
        /// <param name="color">Color de la elipse.</param>
        public void DibujarElipseLlena(Point p1, int radioHorizontal, int radioVertical, Color color)
        {
            DibujarElipseLlena(p1.X, p1.Y, radioHorizontal, radioVertical, color);
        }

        /// <summary>
        /// Dibuja y rellena una elipse en el dibujo que se encuentra inscrita en
        /// un rectángulo dados su punto de la arista superior izquierda y su tamaño.
        /// </summary>
        /// <param name="p1">Punto de la arista superior izquierda del rectángulo.</param>
        /// <param name="tam">Tamaño del rectángulo.</param>
        /// <param name="color">Color de la elipse.</param>
        public void DibujarElipseLlena(Point p1, Size tam, Color color)
        {
            int radioHorizontal = tam.Width / 2;
            int radioVertical = tam.Height / 2;
            DibujarElipseLlena(p1.X + radioHorizontal, p1.Y + radioVertical, radioHorizontal, radioVertical, color);
        }

        /// <summary>
        /// Dibuja y rellena una elipse en el dibujo que se encuentre inscrita en un
        /// rectángulo dado.
        /// </summary>
        /// <param name="r">Rectángulo donde se encuentra incrita la elipse.</param>
        /// <param name="color">Color de la elipse.</param>
        public void DibujarElipseLleana(Rectangle r, Color color)
        {
            int radioHorizontal = r.Width / 2;
            int radioVertical = r.Height / 2;
            DibujarElipseLlena(r.X + radioHorizontal, r.Y + radioVertical, radioHorizontal, radioVertical, color);
        }

        /// <summary>
        /// Dibuja el contorno de una semielipse en el dibujo dadas las coordenadas de su centro,
        /// sus radios horizontal y vertical y sus ángulos de inicio y fin.
        /// </summary>
        /// <param name="x1">Coordenada en X del centro de la semielipse.</param>
        /// <param name="y1">Coordenada en Y del centro de la semielipse.</param>
        /// <param name="radioHorizontal">Radio horizontal de la semielipse.</param>
        /// <param name="radioVertical">Radio vertical de la semielipse.</param>
        /// <param name="anguloInicio">Ángulo de inicio de la semielipse con origen sobre la abscisa positiva.</param>
        /// <param name="anguloFinal">Ángulo de fin de la semielipse con origen sobre la abscisa positiva.</param>
        /// <param name="color">Color de la semielipse.</param>
        public void DibujarSemiElipse(int x1, int y1, int radioHorizontal, int radioVertical, double anguloInicio, double anguloFinal, Color color)
        {
            unsafe { d_semi_elipse(dibujo, x1, y1, (UInt32)radioHorizontal, (UInt32)radioVertical, anguloInicio, anguloFinal, (UInt32)color.ToArgb()); }
        }

        /// <summary>
        /// Dibuja el contorno de una semielipse en el dibujo dados su centro, sus
        /// radios horizontal y vertical y sus ángulos de inicio y fin.
        /// </summary>
        /// <param name="p1">Punto del centro de la semielipse.</param>
        /// <param name="radioHorizontal">Radio horizontal de la semielipse.</param>
        /// <param name="radioVertical">Radio vertical de la semielipse.</param>
        /// <param name="anguloInicio">Ángulo de inicio de la semielipse con origen sobre la abscisa positiva.</param>
        /// <param name="anguloFinal">Ángulo de fin de la semielipse con origen sobre la abscisa positiva.</param>
        /// <param name="color">Color de la semielipse.</param>
        public void DibujarSemiElipse(Point p1, int radioHorizontal, int radioVertical, double anguloInicio, double anguloFinal, Color color)
        {
            DibujarSemiElipse(p1.X, p1.Y, radioHorizontal, radioVertical, anguloInicio, anguloFinal, color);
        }

        /// <summary>
        /// Dibuja el contorno de una semielipse en el dibujo que se encuentra inscrita en
        /// un rectángulo dados su punto de la arista superior izquierda y su tamaño y
        /// especificando sus ángulos de inicio y fin.
        /// </summary>
        /// <param name="p1">Punto de la arista superior izquierda del rectángulo.</param>
        /// <param name="tam">Tamaño del rectángulo.</param>
        /// <param name="anguloInicio">Ángulo de inicio de la semielipse con origen sobre la abscisa positiva.</param>
        /// <param name="anguloFinal">Ángulo de fin de la semielipse con origen sobre la abscisa positiva.</param>
        /// <param name="color">Color de la semielipse.</param>
        public void DibujarSemiElipse(Point p1, Size tam, double anguloInicio, double anguloFinal, Color color)
        {
            int radioHorizontal = tam.Width / 2;
            int radioVertical = tam.Height / 2;
            DibujarSemiElipse(p1.X + radioHorizontal, p1.Y + radioVertical, radioHorizontal, radioVertical, anguloInicio, anguloFinal, color);
        }

        /// <summary>
        /// Dibuja el contorno de una semielipse en el dibujo que se encuentre inscrita en un
        /// rectángulo dado, especificando sus ángulos de inicio y fin.
        /// </summary>
        /// <param name="r">Rectángulo donde se encuentra incrita la semielipse.</param>
        /// <param name="anguloInicio">Ángulo de inicio de la semielipse con origen sobre la abscisa positiva.</param>
        /// <param name="anguloFinal">Ángulo de fin de la semielipse con origen sobre la abscisa positiva.</param>
        /// <param name="color">Color de la semielipse.</param>
        public void DibujarSemiElipse(Rectangle r, double anguloInicio, double anguloFinal, Color color)
        {
            int radioHorizontal = r.Width / 2;
            int radioVertical = r.Height / 2;
            DibujarSemiElipse(r.X + radioHorizontal, r.Y + radioVertical, radioHorizontal, radioVertical, anguloInicio, anguloFinal, color);
        }

        #endregion

        #region Funciones de Geometría

        /// <summary>
        /// Cambia las dimensiones del dibujo sin alterar la calidad de la imagen original
        /// dadas sus nuevas dimensiones.
        /// </summary>
        /// <param name="x2">Nuevo ancho del dibujo.</param>
        /// <param name="y2">Nuevo alto del dibujo.</param>
        public void Reescalar(int x2, int y2)
        {
            Dimensiones = new Size(x2, y2);
        }

        /// <summary>
        /// Cambia las dimensiones del dibujo sin alterar la calidad de la imagen original
        /// dadas sus nuevas dimensiones.
        /// </summary>
        /// <param name="tam">Nuevas dimensiones del dibujo.</param>
        public void Reescalar(Size tam)
        {
            Dimensiones = tam;
        }

        /// <summary>
        /// Cambia las dimensiones del dibujo sin alterar la calidad de la imagen original
        /// dadas sus nuevas dimensiones y entrega el resultado en un nuevo dibujo.
        /// </summary>
        /// <param name="x2">Nuevo ancho del dibujo.</param>
        /// <param name="y2">Nuevo alto del dibujo.</param>
        /// <returns>Dibujo a escala.</returns>
        public DibujoEDS Escalar(int x2, int y2)
        {
            unsafe
            {
                if (x2 < 0 || y2 < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                eDibujoEDS* salida = escalar_d(dibujo, (UInt32)x2, (UInt32)y2);
                ComprobarErrorEDS();
                return new DibujoEDS(salida);
            }
        }

        /// <summary>
        /// Cambia las dimensiones del dibujo sin alterar la calidad de la imagen original
        /// dadas sus nuevas dimensiones y entrega el resultado en un nuevo dibujo.
        /// </summary>
        /// <param name="tam">Nuevas dimensiones del dibujo.</param>
        /// <returns>Dibujo a escala.</returns>
        public DibujoEDS Escalar(Size tam)
        {
            return Escalar(tam.Width, tam.Height);
        }

        /// <summary>
        /// Recorta el dibujo que está dentro de un rectángulo dadas las coordenadas de
        /// los puntos de sus aristas opuestas.
        /// </summary>
        /// <param name="x1">Coordenada en X de la primera arista.</param>
        /// <param name="y1">Coordenada en Y de la primera arista.</param>
        /// <param name="x2">Coordenada en X de la segunda arista.</param>
        /// <param name="y2">Coordenada en Y de la segunda arista.</param>
        public void Recortar(int x1, int y1, int x2, int y2)
        {
            unsafe
            {
                recortar_d(dibujo, x1, y1, x2, y2);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Recorta el dibujo que está dentro de un rectángulo dados los puntos de
        /// sus aristas opuestas.
        /// </summary>
        /// <param name="p1">Punto de la primera arista.</param>
        /// <param name="p2">Punto de la segunda arista.</param>
        public void Recortar(Point p1, Point p2)
        {
            Recortar(p1.X, p1.Y, p2.X, p2.Y);
        }

        /// <summary>
        /// Recorta el dibujo que está dentro de un rectángulo dado.
        /// </summary>
        /// <param name="r">Área del dibujo a recortar.</param>
        public void Recortar(Rectangle r)
        {
            Recortar(r.Left, r.Top, r.Right, r.Bottom);
        }

        /// <summary>
        /// Recorta el dibujo que está dentro de un rectángulo dadas las coordenadas de
        /// los puntos de sus aristas opuestas y entrega el resultado en un nuevo dibujo.
        /// </summary>
        /// <param name="x1">Coordenada en X de la primera arista.</param>
        /// <param name="y1">Coordenada en Y de la primera arista.</param>
        /// <param name="x2">Coordenada en X de la segunda arista.</param>
        /// <param name="y2">Coordenada en Y de la segunda arista.</param>
        /// <returns>Área recortada del dibujo original.</returns>
        public DibujoEDS Cortar(int x1, int y1, int x2, int y2)
        {
            unsafe
            {
                if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                eDibujoEDS* salida = cortar_d(dibujo, x1, y1, x2, y2);
                ComprobarErrorEDS();
                return new DibujoEDS(salida);
            }
        }

        /// <summary>
        /// Recorta el dibujo que está dentro de un rectángulo dados los puntos de
        /// sus aristas opuestas y entrega el resultado en un nuevo dibujo.
        /// </summary>
        /// <param name="p1">Punto de la primera arista.</param>
        /// <param name="p2">Punto de la segunda arista.</param>
        /// <returns>Área recortada del dibujo original.</returns>
        public DibujoEDS Cortar(Point p1, Point p2)
        {
            return Cortar(p1.X, p1.Y, p2.X, p2.Y);
        }

        /// <summary>
        /// Recorta el dibujo que está dentro de un rectángulo dado y entrega el resultado en
        /// un nuevo dibujo.
        /// </summary>
        /// <param name="r">Área del dibujo a recortar.</param>
        /// <returns>Área recortada del dibujo original.</returns>
        public DibujoEDS Cortar(Rectangle r)
        {
            return Cortar(r.Left, r.Top, r.Right, r.Bottom);
        }

        /// <summary>
        /// Copia todo el dibujo dado y lo pega en este dibujo en las coordenadas especificadas.
        /// </summary>
        /// <param name="origen">Dibujo a copiar.</param>
        /// <param name="x1">Coordenada en X del punto a pegar.</param>
        /// <param name="y1">Coordenada en Y del punto a pegar.</param>
        public void PegarDibujo(DibujoEDS origen, int x1, int y1)
        {
            unsafe
            {
                if (x1 < 0 || y1 < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                pegar_d(origen.dibujo, dibujo, x1, y1);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Copia todo el dibujo dado y lo pega en este dibujo en el punto especificado.
        /// </summary>
        /// <param name="origen">Dibujo a copiar.</param>
        /// <param name="p1">Punto en el que se pegará.</param>
        public void PegarDibujo(DibujoEDS origen, Point p1)
        {
            PegarDibujo(origen, p1.X, p1.Y);
        }

        /// <summary>
        /// Copia y reescala todo el dibujo dado sin alterarlo y lo pega en este dibujo en
        /// el área de un rectángulo dadas las coordenadas de los puntos de sus aristas opuestas.
        /// </summary>
        /// <param name="origen">Dibujo a copiar.</param>
        /// <param name="x1">Coordenada en X del punto de la primera arista.</param>
        /// <param name="y1">Coordenada en Y del punto de la primera arista.</param>
        /// <param name="x2">Coordenada en X del punto de la segunda arista.</param>
        /// <param name="y2">Coordenada en Y del punto de la segunda arista.</param>
        public void PegarDibujo(DibujoEDS origen, int x1, int y1, int x2, int y2)
        {
            unsafe
            {
                if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) throw new ArgumentException("Solo puede introducir valores positivos.");
                pegar_escalar_d(origen.dibujo, dibujo, x1, y1, x2, y2);
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Copia y reescala todo el dibujo dado sin alterarlo y lo pega en este dibujo en
        /// el área de un rectángulo dados los puntos de sus aristas opuestas.
        /// </summary>
        /// <param name="origen">Dibujo a copiar.</param>
        /// <param name="p1">Punto de la primera arista.</param>
        /// <param name="p2">Punto de la segunda arista.</param>
        public void PegarDibujo(DibujoEDS origen, Point p1, Point p2)
        {
            PegarDibujo(origen, p1.X, p1.Y, p2.X, p2.Y);
        }

        /// <summary>
        /// Copia y reescala todo el dibujo dado sin alterarlo y lo pega en este dibujo en
        /// el área de un rectángulo dado.
        /// </summary>
        /// <param name="origen">Dibujo a copiar.</param>
        /// <param name="r">Área de pegado.</param>
        public void PegarDibujo(DibujoEDS origen, Rectangle r)
        {
            PegarDibujo(origen, r.Left, r.Top, r.Right, r.Bottom);
        }

        /// <summary>
        /// Rota o aplica un efecto espejo deseado en el dibujo.
        /// </summary>
        /// <param name="modoRotadoEspejo">Sentido de giro o espejo.</param>
        public void RotarEspejo(RotateFlipType modoRotadoEspejo)
        {
            unsafe
            {
                switch (modoRotadoEspejo)
                {
                    case RotateFlipType.RotateNoneFlipX:
                        espejo_x_d(dibujo);
                        break;
                    case RotateFlipType.RotateNoneFlipY:
                        espejo_y_d(dibujo);
                        break;
                    case RotateFlipType.RotateNoneFlipXY:
                        voltear_d(dibujo);
                        break;
                    case RotateFlipType.Rotate90FlipNone:
                        rotar_derecha_d(dibujo);
                        break;
                    case RotateFlipType.Rotate90FlipX:
                        rotar_derecha_d(dibujo);
                        espejo_x_d(dibujo);
                        break;
                    case RotateFlipType.Rotate270FlipNone:
                        rotar_izquierda_d(dibujo);
                        break;
                    case RotateFlipType.Rotate270FlipX:
                        rotar_izquierda_d(dibujo);
                        espejo_x_d(dibujo);
                        break;
                }

                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Rota toda la imagen 90º en sentido de las manecillas del reloj.
        /// </summary>
        public void RotarDerecha()
        {
            unsafe { rotar_derecha_d(dibujo); }
        }

        /// <summary>
        /// Rota toda la imagen 90º en sentido contrario de las manecillas del reloj.
        /// </summary>
        public void RotarIzquierda()
        {
            unsafe { rotar_izquierda_d(dibujo); }
        }

        /// <summary>
        /// Voltea todo el dibujo de cabeza.
        /// </summary>
        public void Voltear()
        {
            unsafe { voltear_d(dibujo); }
        }

        /// <summary>
        /// Realiza un efecto espejo sobre toda la imagen en el eje X,
        /// recolocando los pixeles de la derecha del dibujo en la izquierda y viceversa.
        /// </summary>
        public void EspejoX()
        {
            unsafe { espejo_x_d(dibujo); }
        }

        /// <summary>
        /// Realiza un efecto espejo sobre toda la imagen en el eje Y,
        /// recolocando los pixeles de la parte superior del dibujo en la inferior y viceversa.
        /// </summary>
        public void EspejoY()
        {
            unsafe { espejo_y_d(dibujo); }
        }

        #endregion

        #region Funciones de Texto

        /// <summary>
        /// Calcula la el ancho de la cadena dada en pixeles.
        /// </summary>
        /// <param name="cadena">Cadena a medir.</param>
        /// <returns>Longitud de la cadena en pixeles.</returns>
        public static int LongitudCadenaPixeles(string cadena)
        {
            return (int)longitud_cadena(cadena);
        }

        /// <summary>
        /// Dibuja un caracter en el dibujo dadas las coordenadas del punto en donde se dibujará.
        /// </summary>
        /// <param name="caracter">Caracter a dibujar.</param>
        /// <param name="x1">Coordenada en X del punto a dibujar.</param>
        /// <param name="y1">Coordenada en Y del punto a dibujar.</param>
        /// <param name="color">Color del caracter.</param>
        public void DibujarCaracter(char caracter, int x1, int y1, Color color)
        {
            unsafe
            {
                d_letra(dibujo, Convert.ToByte(caracter), x1, y1, (UInt32)color.ToArgb());
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Dibuja un caracter en el dibujo dado el punto en donde se dibujará.
        /// </summary>
        /// <param name="caracter">Caracter a dibujar.</param>
        /// <param name="p1">Punto a dibujar.</param>
        /// <param name="color">Color del caracter.</param>
        public void DibujarCaracter(char caracter, Point p1, Color color)
        {
            DibujarCaracter(caracter, p1.X, p1.Y, color);
        }

        /// <summary>
        /// Dibuja una cadena en el dibujo dadas las coordenadas del punto en donde se dibujará.
        /// </summary>
        /// <param name="cadena">Cadena a dibujar.</param>
        /// <param name="x1">Coordenada en X del punto a dibujar.</param>
        /// <param name="y1">Coordenada en Y del punto a dibujar.</param>
        /// <param name="color">Color de la cadena.</param>
        public void DibujarCadena(string cadena, int x1, int y1, Color color)
        {
            unsafe
            {
                d_cadena(dibujo, cadena, x1, y1, (UInt32)color.ToArgb());
                ComprobarErrorEDS();
            }
        }

        /// <summary>
        /// Dibuja una cadena en el dibujo dado el punto en donde se dibujará.
        /// </summary>
        /// <param name="cadena">Cadena a dibujar.</param>
        /// <param name="p1">Punto a dibujar.</param>
        /// <param name="color">Color de la cadena.</param>
        public void DibujarCadena(string cadena, Point p1, Color color)
        {
            DibujarCadena(cadena, p1.X, p1.Y, color);
        }

        #endregion

        #region Destructor

        /// <summary>Indica si el objecto ya ha sido destruido.</summary>
        private bool disposed = false;

        /// <summary>Destruye el objeto.</summary>
        /// <param name="disposing">Indica si se desean borrar los recursos administrados (para omitirse el recolector de basura después).</param>
        protected virtual void Dispose(bool disposing)
        {
            unsafe
            {
                if (disposed) return;
                if (disposing)
                {
                    //Deshecha los recursos administrados
                }

                //Deshecha los recursos no administrados
                destruir_puntero_dibujo(dibujo);
                dibujo = null;
                disposed = true;
            }
        }

        /// <summary>Destruye este objecto.</summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>Destruye este objeto.</summary>
        ~DibujoEDS()
        {
            Dispose(false);
        }

        #endregion
    }
}
