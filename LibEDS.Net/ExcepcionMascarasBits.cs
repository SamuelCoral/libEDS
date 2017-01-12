using System;

namespace LibEDS.Net
{
    /// <summary>
    /// Excepción producida cuando ocurre un error al realizar una operación
    /// a una <seealso cref="MascarasBits"/>.
    /// </summary>
    [Serializable]
    public class ExcepcionMascarasBits : Exception
    {
        /// <summary>
        /// Crea una instancia de esta excepción sin especificar el motivo que la disparó.
        /// </summary>
        public ExcepcionMascarasBits() { }
        
        /// <summary>
        /// Crea una instancia de esta excepción especificando el motivo que la disparó.
        /// </summary>
        /// <param name="mensaje">Motivo por el cual se arroja la excepción.</param>
        public ExcepcionMascarasBits(string mensaje) : base(mensaje) { }

        /// <summary>
        /// Crea una instancia de esta excepción especificando el motivo y una excepción padre.
        /// </summary>
        /// <param name="mensaje">Motivo por el cual se arroja la excepción.</param>
        /// <param name="causa">Excepción padre que provoca que se arroje esta nueva excepción.</param>
        public ExcepcionMascarasBits(string mensaje, Exception causa) : base(mensaje, causa) { }
    }
}
