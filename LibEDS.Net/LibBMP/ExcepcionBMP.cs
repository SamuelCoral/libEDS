using System;

namespace LibEDS.Net.LibBMP
{
    /// <summary>
    /// Excepción producida cuando ocurre un error al realizar una operación
    /// realcionada con una <seealso cref="ImagenBMP"/>.
    /// </summary>
    [Serializable]
    public class ExcepcionBMP : Exception
    {
        /// <summary>
        /// Crea una instancia de esta excepción sin especificar el motivo que la disparó.
        /// </summary>
        public ExcepcionBMP() { }

        /// <summary>
        /// Crea una instancia de esta excepción especificando el motivo que la disparó.
        /// </summary>
        /// <param name="mensaje">Motivo por el cual se arroja la excepción.</param>
        public ExcepcionBMP(string mensaje) : base(mensaje) { }

        /// <summary>
        /// Crea una instancia de esta excepción especificando el motivo y una excepción padre.
        /// </summary>
        /// <param name="mensaje">Motivo por el cual se arroja la excepción.</param>
        /// <param name="causa">Excepción padre que provoca que se arroje esta nueva excepción.</param>
        public ExcepcionBMP(string mensaje, Exception causa) : base(mensaje, causa) { }
    }
}
