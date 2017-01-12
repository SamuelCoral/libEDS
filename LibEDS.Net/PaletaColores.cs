using System;
using System.Collections.Generic;
using System.Drawing;
using System.Collections;

namespace LibEDS.Net
{
    /// <summary>
    /// Clase que enumera todos los colores de una paleta.
    /// </summary>
    public class PaletaColores : IEnumerable<Color>
    {
        internal unsafe UInt32* paleta;
        internal UInt16 colores;
        private bool soloLectura;

        internal unsafe PaletaColores(byte bpp, UInt32* paleta, bool soloLectura = false)
        {
            colores = bpp <= 8 ? (UInt16)(1 << bpp) : (UInt16)0;
            this.paleta = paleta;
            this.soloLectura = soloLectura;
        }

        /// <summary>
        /// Obtiene la cantidad de colores encontrados en esta paleta.
        /// </summary>
        public int Colores
        {
            get { return colores; }
        }

        /// <summary>
        /// Obtiene o cambia un color el el índice especificado de la paleta.
        /// </summary>
        /// <param name="index">Índice del color a obtener o cambiar.</param>
        /// <returns>Color en el índice especificado.</returns>
        public Color this[int index]
        {
            get
            {
                if (colores == 0) throw new ExcepcionPaletaColores("La imagen no tiene una paleta de colores.");
                if (index >= colores || index < 0) throw new IndexOutOfRangeException("El color especificado no existe en la paleta de colores.");
                unsafe
                {
                    return Color.FromArgb((Int32)(paleta[index] | 0xFF000000));
                }
            }

            set
            {
                if (soloLectura) return;
                if (colores == 0) throw new ExcepcionPaletaColores("La imagen no tiene una paleta de colores.");
                if (index >= colores || index < 0) throw new IndexOutOfRangeException("El color especificado no existe en la paleta de colores.");
                unsafe
                {
                    paleta[index] = (UInt32)value.ToArgb() & 0x00FFFFFF;
                }
            }
        }

        /// <summary>
        /// Deveulve una cadena donde se enlistan los valores de cada componente de color
        /// de todos los colores en la paleta.
        /// </summary>
        /// <returns>Cadena con todos los colores de la paleta.</returns>
        public override string ToString()
        {
            string r = "";
            foreach (Color item in this)
                r += item.ToString() + "\n";

            return r;
        }

        [System.Runtime.InteropServices.DllImport(LibBMP.ImagenBMP.rutaDll, CallingConvention = LibBMP.ImagenBMP.convencionLlamado)]
        private unsafe extern static UInt32* paleta_std(UInt16 bpp);

        /// <summary>
        /// Devuelve la paleta de colores usada por defecto para la profundidad de color especificada.
        /// </summary>
        /// <remarks>
        /// Si se especifica una profundidad de color no válida, la paleta se creará de todos modos, pero
        /// fallará al quere acceder a sus elementos como si se tratara de una paleta de colores incrustada
        /// en una imagen o un dibujo.
        /// La paleta devuelta es de sólo lectura, por lo que si se intenta modificar una entrada, simplemente
        /// no ocurrirá nada.
        /// </remarks>
        /// <param name="bpp">Profundidad de color en bits por pixel.</param>
        /// <returns>Paleta de colores asociada a la profundidad de color especificada.</returns>
        public static PaletaColores PaletaPorDefecto(int bpp)
        {
            unsafe { return new PaletaColores((byte)bpp, paleta_std((UInt16)bpp), true); }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        /// <summary>
        /// Deveulve un enumerador para iterar a través de todos los colores en la paleta.
        /// </summary>
        /// <returns>Enumerador de los colres en la paleta.</returns>
        public IEnumerator<Color> GetEnumerator()
        {
            return new EnumeradorPaleta(this);
        }

        /// <summary>
        /// Clase que enumera los colores en una paleta.
        /// </summary>
        public class EnumeradorPaleta : IEnumerator<Color>
        {
            private PaletaColores paleta;
            private int index;

            /// <summary>
            /// Crea un enumerador de una paleta de colores dada.
            /// </summary>
            /// <param name="paleta">Paleta de colores a usar para cread enumerador.</param>
            public EnumeradorPaleta(PaletaColores paleta)
            {
                this.paleta = paleta;
                index = -1;
            }

            /// <summary>Reinicia el iterador.</summary>
            public void Reset()
            {
                index = -1;
            }

            /// <summary>
            /// Mueve el índice del iterador al siguiente elemento.
            /// </summary>
            /// <returns>Valor booleano que indica si se puede seguir iterando.</returns>
            public bool MoveNext()
            {
                index++;
                if (paleta.colores == 0) return false;
                return index < paleta.colores;
            }

            object IEnumerator.Current
            {
                get { return Current; }
            }

            /// <summary>Devuelve el color apuntado por el índice actual del iterador.</summary>
            public Color Current
            {
                get { return paleta[index]; }
            }

            /// <summary>Destruye este objeto.</summary>
            public void Dispose()
            {
                paleta = null;
            }
        }
    }
}
