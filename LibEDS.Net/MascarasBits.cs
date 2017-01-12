using System;
using System.Runtime.InteropServices;
using LibEDS.Net.LibBMP;

namespace LibEDS.Net
{
    /// <summary>
    /// Contiene las máscaras de bits para cada componente de color utilizadas
    /// para establecer el formato de pixel de un mapa de bits.
    /// </summary>
    [StructLayout(LayoutKind.Sequential, Pack = 2)]
    public struct MascarasBits
    {
        #region Variables

        private UInt32 rojo;
        private UInt32 verde;
        private UInt32 azul;
        private UInt32 alpha;

        #endregion

        #region Funciones importadas de C

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private extern static MascarasBits crear_mascaras(UInt32 rojo, UInt32 verde, UInt32 azul, UInt32 alpha);

        [DllImport(ImagenBMP.rutaDll, CallingConvention = ImagenBMP.convencionLlamado)]
        private extern static bool mascaras_validas(MascarasBits mascaras);

        #endregion

        #region Constructores

        /// <summary>
        /// Crea una instancia de esta estructura dando los valores.
        /// </summary>
        /// <remarks>
        /// Para que las máscaras de bits sean válidas, todos los bits deben de ser contigüos
        /// y no debe de existir el mismo bit en más de un componente.
        /// </remarks>
        /// <param name="rojo">Máscara del componente rojo.</param>
        /// <param name="verde">Máscara del componente verde.</param>
        /// <param name="azul">Máscara del componente azul.</param>
        /// <param name="alpha">Máscara del canal alpha.</param>
        public MascarasBits(UInt32 rojo, UInt32 verde, UInt32 azul, UInt32 alpha = 0)
        {
            this.rojo = rojo;
            this.verde = verde;
            this.azul = azul;
            this.alpha = alpha;

            if (!mascaras_validas(this)) throw new ExcepcionMascarasBits("Algunas máscaras tienen bits cruzados o se dejaron huecos entre ellas.");
        }

        /// <summary>
        /// Construye unas máscaras de bits especifiando el número de bits que se usarán
        /// para cada componente de color.
        /// </summary>
        /// <remarks>
        /// La suma de todos los bits no debe de exceder los 32 bits.
        /// </remarks>
        /// <param name="bitsRojo">Número de bits para la máscara del componente rojo.</param>
        /// <param name="bitsVerde">Número de bits para la máscara del componente verde.</param>
        /// <param name="bitsAzul">Número de bits para la máscara del componente azul.</param>
        /// <param name="bitsAlpha">Número de bits para la máscara del canal alpha.</param>
        /// <returns>Máscaras de bits de las cantidades de bits especificadas.</returns>
        public static MascarasBits CrearDesdeNumeroBits(int bitsRojo, int bitsVerde, int bitsAzul, int bitsAlpha = 0)
        {
            MascarasBits salida = crear_mascaras((UInt32)bitsRojo, (UInt32)bitsVerde, (UInt32)bitsAzul, (UInt32)bitsAlpha);
            if (!mascaras_validas(salida)) throw new ExcepcionMascarasBits("La suma de bits excede 32.");
            return salida;
        }

        #endregion

        #region Propiedades

        /// <summary>
        /// Devuelve la máscara de bits del componente de color rojo.
        /// </summary>
        public UInt32 Rojo
        {
            get { return rojo; }
        }

        /// <summary>
        /// Devuelve la máscara de bits del componente de color verde.
        /// </summary>
        public UInt32 Verde
        {
            get { return verde; }
        }

        /// <summary>
        /// Devuelve la máscara de bits del componente de color azul.
        /// </summary>
        public UInt32 Azul
        {
            get { return azul; }
        }

        /// <summary>
        /// Devuelve la máscara de bits del canal alpha.
        /// </summary>
        public UInt32 Alpha
        {
            get { return alpha; }
        }

        /// <summary>
        /// Deveulve la suma de bits que contiene la máscara del componente de color rojo.
        /// </summary>
        public int BitsRojo
        {
            get
            {
                int c, r;
                for (c = r = 0; c < 32; c++) if (((rojo >> c) & 1) == 1) r++;
                return r;
            }
        }

        /// <summary>
        /// Deveulve la suma de bits que contiene la máscara del componente de color verde.
        /// </summary>
        public int BitsVerde
        {
            get
            {
                int c, r;
                for (c = r = 0; c < 32; c++) if (((verde >> c) & 1) == 1) r++;
                return r;
            }
        }

        /// <summary>
        /// Deveulve la suma de bits que contiene la máscara del componente de color azul.
        /// </summary>
        public int BitsAzul
        {
            get
            {
                int c, r;
                for (c = r = 0; c < 32; c++) if (((azul >> c) & 1) == 1) r++;
                return r;
            }
        }

        /// <summary>
        /// Deveulve la suma de bits que contiene la máscara del canal alpha.
        /// </summary>
        public int BitsAlpha
        {
            get
            {
                int c, r;
                for (c = r = 0; c < 32; c++) if (((alpha >> c) & 1) == 1) r++;
                return r;
            }
        }

        /// <summary>
        /// Deveulve la suma de bits de todas las máscaras.
        /// </summary>
        public int SumaBits
        {
            get { return BitsRojo + BitsVerde + BitsAzul + BitsAlpha; }
        }

        #endregion

        #region Métodos invalidados

        /// <summary>
        /// Devuelve una cadena donde se especifiquen los valores de las máscaras de bits
        /// en formato hexadecimal.
        /// </summary>
        /// <returns>Cadena que represente los valores de las máscaras de bits.</returns>
        public override string ToString()
        {
            return "Rojo  = 0x" + Rojo.ToString("X8") + " (" + BitsRojo.ToString() + " bits)\n" +
                "Verde = 0x" + Verde.ToString("X8") + " (" + BitsVerde.ToString() + " bits)\n" +
                "Azul  = 0x" + Azul.ToString("X8") + " (" + BitsAzul.ToString() + " bits)\n" +
                "Alpha = 0x" + Alpha.ToString("X8") + " (" + BitsAlpha.ToString() + " bits)\n";
        }

        /// <summary>
        /// Compara un objecto con las máscaras de bits y determina si son iguales.
        /// </summary>
        /// <param name="obj">Objecto a comparar igualdad con las máscaras de bits.</param>
        /// <returns>Resultado de la evaluación de igualdad.</returns>
        public override bool Equals(object obj)
        {
            if (obj == null) return false;

            MascarasBits? comparar = obj as MascarasBits?;
            if (comparar == null) return false;
            return rojo == ((MascarasBits)comparar).rojo &&
                verde == ((MascarasBits)comparar).verde &&
                azul == ((MascarasBits)comparar).azul &&
                alpha == ((MascarasBits)comparar).alpha;
        }

        /// <summary>
        /// Determina si unas máscaras de bits son iguales a las actuales.
        /// </summary>
        /// <param name="comparar">Máscaras de bits a comprobar igualdad.</param>
        /// <returns>Resultado de la evaluación de igualdad.</returns>
        public bool Equals(MascarasBits comparar)
        {
            return rojo == comparar.rojo &&
                verde == comparar.verde &&
                azul == comparar.azul &&
                alpha == comparar.alpha;
        }

        /// <summary>
        /// Calcula un código Hash para estas máscaras de bits.
        /// </summary>
        /// <returns>Código Hash.</returns>
        public override int GetHashCode()
        {
            return (int)(rojo ^ verde ^ azul ^ alpha);
        }

        #endregion

        #region Operadores sobrecargados

        /// <summary>
        /// Determina si 2 máscaras de bits son iguales entre sí.
        /// </summary>
        /// <param name="m1">Primeras máscaras a comprobar.</param>
        /// <param name="m2">Segundas máscaras a comprobar.</param>
        /// <returns>Resultado de la evaluación de igualdad.</returns>
        public static bool operator ==(MascarasBits m1, MascarasBits m2)
        {
            return m1.rojo == m2.rojo &&
                m1.verde == m2.verde &&
                m1.azul == m2.azul &&
                m1.alpha == m2.alpha;
        }

        /// <summary>
        /// Determina si 2 máscaras de bits son diferentes.
        /// </summary>
        /// <param name="m1">Primeras máscaras a comprobar.</param>
        /// <param name="m2">Segundas máscaras a comprobar.</param>
        /// <returns>Resultado de la evaluación de desigualdad.</returns>
        public static bool operator !=(MascarasBits m1, MascarasBits m2)
        {
            return m1.rojo != m2.rojo ||
                m1.verde != m2.verde ||
                m1.azul != m2.azul ||
                m1.alpha != m2.alpha;
        }

        #endregion

        #region Instancias predefinidas

        /// <summary>
        /// Devuelve las máscaras de bits del formato de pixel por defecto de una imagen BMP
        /// dada su profundidad de color en bits por pixel.
        /// </summary>
        /// <param name="bpp">Profundidad de color en bits por pixel</param>
        /// <returns>Máscaras de bits por default.</returns>
        public static MascarasBits MascarasPorDefecto(int bpp)
        {
            return bpp == 1 || bpp == 4 || bpp == 8 || bpp == 24 || bpp == 32 ? MascarasBits.RGB888 :
                bpp == 16 ? MascarasBits.RGB555 : MascarasBits.MascarasBitsVacias;
        }

        /// <summary>
        /// Representan unas máscaras de bits vacías, pueden ser usadas para especificar el
        /// formato de pixel por defecto para cada profundidad de color cuando se utiliza con <seealso cref="ImagenBMP.CambiarFormatoPixel(int, MascarasBits)"/>.
        /// </summary>
        public static MascarasBits MascarasBitsVacias
        {
            get { return CrearDesdeNumeroBits(0, 0, 0); }
        }

        /// <summary>
        /// Representan unas máscaras de bits que se conforman de 8 bits para el componente Rojo,
        /// 8 bits para el componente verde y 8 bits para el componente azul.
        /// </summary>
        public static MascarasBits RGB888
        {
            get { return CrearDesdeNumeroBits(8, 8, 8); }
        }

        /// <summary>
        /// Representan unas máscaras de bits que se conforman de 8 bits para el componente Rojo,
        /// 8 bits para el componente verde, 8 bits para el componente azul y 8 bits para el canal alpha.
        /// </summary>
        public static MascarasBits RGBA8888
        {
            get { return CrearDesdeNumeroBits(8, 8, 8, 8); }
        }

        /// <summary>
        /// Representan unas máscaras de bits que se conforman de 5 bits para el componente Rojo,
        /// 5 bits para el componente verde y 5 bits para el componente azul.
        /// </summary>
        public static MascarasBits RGB555
        {
            get { return CrearDesdeNumeroBits(5, 5, 5); }
        }

        /// <summary>
        /// Representan unas máscaras de bits que se conforman de 5 bits para el componente Rojo,
        /// 5 bits para el componente verde, 5 bits para el componente azul y un bit para el canal alpha.
        /// </summary>
        public static MascarasBits RGBA5551
        {
            get { return CrearDesdeNumeroBits(5, 5, 5, 1); }
        }

        /// <summary>
        /// Representan unas máscaras de bits que se conforman de 5 bits para el componente Rojo,
        /// 6 bits para el componente verde y 5 bits para el componente azul.
        /// </summary>
        public static MascarasBits RGB565
        {
            get { return CrearDesdeNumeroBits(5, 6, 5); }
        }

        #endregion
    }
}
