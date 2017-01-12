using System;
using System.Windows.Forms;
using LibEDS.Net;

namespace Prueba_CS
{
    public partial class FrmFormatoPixel : Form
    {
        private MascarasBits mascaras;
        private FrmBMP frmOrigen;

        public FrmFormatoPixel(FrmBMP frmOrigen)
        {
            InitializeComponent();

            this.frmOrigen = frmOrigen;
            mascaras = frmOrigen.nuevoFormatoPixel;
            numRojo.Value = mascaras.BitsRojo;
            numVerde.Value = mascaras.BitsVerde;
            numAzul.Value = mascaras.BitsAzul;
            numAlpha.Value = mascaras.BitsAlpha;

            txtRojo.Text = mascaras.Rojo.ToString("X8");
            txtVerde.Text = mascaras.Verde.ToString("X8");
            txtAzul.Text = mascaras.Azul.ToString("X8");
            txtAlpha.Text = mascaras.Alpha.ToString("X8");
        }

        private void btnAceptar_Click(object sender, EventArgs e)
        {
            try
            {
                if (rdbNumBits.Checked)
                    mascaras = MascarasBits.CrearDesdeNumeroBits((int)numRojo.Value, (int)numVerde.Value, (int)numAzul.Value, (int)numAlpha.Value);
                else
                    mascaras = new MascarasBits(
                        UInt32.Parse(txtRojo.Text, System.Globalization.NumberStyles.HexNumber),
                        UInt32.Parse(txtVerde.Text, System.Globalization.NumberStyles.HexNumber),
                        UInt32.Parse(txtAzul.Text, System.Globalization.NumberStyles.HexNumber),
                        UInt32.Parse(txtAlpha.Text, System.Globalization.NumberStyles.HexNumber)
                    );
            }
            catch (Exception ex)
            {
                if (ex is FormatException || ex is ExcepcionMascarasBits)
                {
                    if (MessageBox.Show("Ocurrió un error al intentar generar el nuevo formato de pixel:\n" +
                        ex.Message + "\nPor favor, revise los valores. Haga clic en Reintentar para corregirlos.", "Error en formato de pixel",
                        MessageBoxButtons.RetryCancel, MessageBoxIcon.Warning) == DialogResult.Retry)
                        return;
                    else Close();
                }
                else throw ex;
            }

            if (mascaras.BitsRojo > 8 || mascaras.BitsVerde > 8 || mascaras.BitsAzul > 8 || mascaras.BitsAlpha > 8)
            {
                if (MessageBox.Show("Advertencia: Si el número de bits de la máscara de un componente de color excede los 8 bits\n" +
                    "es posible que no sea reconocida por algunas aplicaciones,\n" +
                    "incluyendo el propio visor de imágenes popular de Windows.\n" +
                    "¿Desea continuar de todas maneras?", "Advertencia en formato de pixel",
                    MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) == DialogResult.Cancel)
                    return;
            }

            if(mascaras.SumaBits > frmOrigen.bppViejo)
            {
                if (MessageBox.Show("Ocurrió un error al intentar generar el nuevo formato de pixel:\n" +
                    "La suma de bits de las máscaras excede los " + frmOrigen.bppViejo + " bpp.\n" +
                    "\nPor favor, revise los valores. Haga clic en Reintentar para corregirlos.", "Error en formato de pixel",
                    MessageBoxButtons.RetryCancel, MessageBoxIcon.Warning) == DialogResult.Retry)
                    return;
                else Close();
            }

            frmOrigen.nuevoFormatoPixel = mascaras;
            Close();
        }

        private void btnCancelar_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void cambiarModo(object sender, EventArgs e)
        {
            grpMascaras.Enabled = rdbMascaras.Checked;
            grpNumBits.Enabled = rdbNumBits.Checked;
        }
    }
}
