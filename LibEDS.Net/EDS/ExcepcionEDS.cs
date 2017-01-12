using System;

namespace LibEDS.Net
{
    /// <summary>
    /// Excepción arrojada cuando ocurre un arror al realizar una operación
    /// relacionada con algún dibujo.
    /// </summary>
    [Serializable]
    public class ExcepcionEDS : Exception
    {
        /// <summary>
        /// Crea una instancia de esta excepción sin especificar el motivo que la disparó.
        /// </summary>
        public ExcepcionEDS() { }

        /// <summary>
        /// Crea una instancia de esta excepción especificando el motivo que la disparó.
        /// </summary>
        /// <param name="mensaje">Motivo por el cual se arroja la excepción.</param>
        public ExcepcionEDS(string mensaje) : base(mensaje) { }

        /// <summary>
        /// Crea una instancia de esta excepción especificando el motivo y una excepción padre.
        /// </summary>
        /// <param name="mensaje">Motivo por el cual se arroja la excepción.</param>
        /// <param name="causa">Excepción padre que provoca que se arroje esta nueva excepción.</param>
        public ExcepcionEDS(string mensaje, ExcepcionEDS causa) : base(mensaje, causa) { }
    }
}
