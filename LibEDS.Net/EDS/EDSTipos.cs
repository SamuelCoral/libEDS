using System;
using System.Drawing;

namespace LibEDS.Net
{
    /// <summary>
    /// Estructura que almacena todos los componentes de color
    /// utilizada en esta librería en el formato BGRA8888.
    /// </summary>
    public struct p32
    {
        /// <summary>8 bits del componente rojo del color.</summary>
        public Byte B;
        /// <summary>8 bits del componente verde del color.</summary>
        public Byte G;
        /// <summary>8 bits del componente azul del color.</summary>
        public Byte R;
        /// <summary>8 bits del canal alpha.</summary>
        public Byte A;

        /// <summary>
        /// Construye una instancia de esta estructura a partir de los valores de color.
        /// </summary>
        /// <param name="rojo">8 bits del componente rojo del color.</param>
        /// <param name="verde">8 bits del componente verde del color.</param>
        /// <param name="azul">8 bits del componente azul del color.</param>
        /// <param name="alpha">8 bits del canal alpha.</param>
        public p32(int rojo, int verde, int azul, int alpha = 255)
        {
            R = (Byte)rojo;
            G = (Byte)verde;
            B = (Byte)azul;
            A = (Byte)alpha;
        }

        /// <summary>
        /// Construye una instancia de esta estructura a partir de una estructura de
        /// color de .Net <seealso cref="Color"/>.
        /// </summary>
        /// <param name="color">Estructura de color de .Net</param>
        public p32(Color color)
        {
            R = color.R;
            G = color.G;
            B = color.B;
            A = color.A;
        }

        /// <summary>
        /// Convierte esta estructura de color en una de .Net <seealso cref="Color"/>.
        /// </summary>
        /// <returns>Estructura de color <seealso cref="Color"/> equivalente.</returns>
        public Color ConvertirAColor()
        {
            return Color.FromArgb(A, R, G, B);
        }

        /// <summary>
        /// Convierte esta estructura de color en una de .Net <seealso cref="Color"/>.
        /// </summary>
        /// <param name="color">Estructura de color <seealso cref="Color"/> equivalente.</param>
        public static implicit operator Color(p32 color)
        {
            return color.ConvertirAColor();
        }

        /// <summary>
        /// Convierte una estructura de color de .Net <seealso cref="Color"/> en una estructura <seealso cref="p32"/>.
        /// </summary>
        /// <param name="color">Estructura de color <seealso cref="p32"/> equivalente.</param>
        public static implicit operator p32(Color color)
        {
            return new p32(color);
        }
    }

    /// <summary>Estructura que contiene toda la información de un lienzo de dibujo que maneja esta librería.</summary>
    /// <remarks>Esta estructura es inútil para el usuario final, ya que viene encapsulada dentro de la clase.</remarks>
    public struct eDibujoEDS
    {
        /// <summary>Ancho del mapa de bits en pixeles.</summary>
        public UInt32 ancho;
        /// <summary>Alto del mapa de bits en pixeles.</summary>
        public UInt32 alto;
        /// <summary>Profundidad de color del mapa de bits en bits por pixel.</summary>
        /// <remarks>Solo las profundidades de 1, 4, 8 y 32 bpp son válidas.</remarks>
        public byte bpp;
        /// <summary>Arreglo de colores en el formato XRGB en caso de que la profundidad de color sea igual o menor a 8 bpp.</summary>
        public unsafe UInt32* paleta;
        /// <summary>Mapa de bits.</summary>
        public unsafe p32* bitmap;
        /// <summary>Mapa de bits que contiene las entradas de la paleta cuando esta exista.</summary>
        public unsafe byte* bitmap_p;
    }
}
