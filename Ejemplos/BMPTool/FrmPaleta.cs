using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace Prueba_CS
{
    public partial class FrmPaleta : Form
    {
        private FrmBMP frmOrigen;
        private Color[] paletaNueva;
        private Size tamCuadro;
        private Label[] etiquetasColores;
        private int colorSeleccionado;

        public FrmPaleta(FrmBMP frmOrigen)
        {
            InitializeComponent();

            this.frmOrigen = frmOrigen;
            paletaNueva = new Color[1 << frmOrigen.bppViejo];
            for (int c = 0; c < paletaNueva.Length; c++) paletaNueva[c] = frmOrigen.paletaVieja[c];
            tamCuadro = new Size(picPaleta.Width / 16, picPaleta.Height / 16);
            picPaleta.Image = new Bitmap(picPaleta.Width, picPaleta.Height);
            llenarPaleta(paletaNueva);
            
            Image fondo = new Bitmap(Width, Height);
            Graphics g = Graphics.FromImage(fondo);
            g.FillRectangle(new LinearGradientBrush(Point.Empty, new Point(Size), Color.Red, Color.Blue), new Rectangle(Point.Empty, Size));
            BackgroundImage = fondo;

            etiquetasColores = new Label[48];
            for(int i = 0; i < 3; i++)
            {
                for (int c = 0; c < 16; c++)
                {
                    Label etiqueta = new Label();
                    etiquetasColores[c + i * 16] = etiqueta;
                    etiqueta.Font = new Font(FontFamily.GenericSansSerif, 9, FontStyle.Bold);
                    etiqueta.ForeColor = Color.Gold;
                    etiqueta.BackColor = Color.Transparent;
                    etiqueta.TextAlign = ContentAlignment.MiddleCenter;
                    etiqueta.Text = Convert.ToString(i == 0 ? (c % 8) : (i == 2 ? c | 0x10 : c) << 3, 8).PadLeft(i == 0 ? 2 : 4, '0');
                    etiqueta.Size = new Size(i == 0 ? 28 : 42, 14);
                    etiqueta.Location = new Point(
                        picPaleta.Location.X +
                        (i == 0 ? tamCuadro.Width * c + (tamCuadro.Width - etiqueta.Width) / 2 : i == 1 ? -etiqueta.Width - 4 : picPaleta.Width + 4),
                        picPaleta.Location.Y +
                        (i == 0 ? -etiqueta.Height - 4 : tamCuadro.Height * c + (tamCuadro.Height - etiqueta.Height) / 2)
                    );
                    Controls.Add(etiqueta);
                }
            }

            colorSeleccionado = 0;
            etiquetasColores[0].ForeColor = etiquetasColores[16].ForeColor = Color.White;
            picColorActual.BackColor = picColorNuevo.BackColor = paletaNueva[0];
        }

        private void llenarPaleta(Color[] paleta)
        {
            Image coloresPaleta = picPaleta.Image;
            Graphics g = Graphics.FromImage(coloresPaleta);
            g.FillRectangle(new HatchBrush(HatchStyle.Percent05, Color.DarkGray), new Rectangle(Point.Empty, coloresPaleta.Size));
            for (int c = 0; c < paleta.Length; c++)
            {
                g.FillRectangle(
                    new SolidBrush(paleta[c]),
                    ((c % 8) + 8 * (c >> 7)) * tamCuadro.Width,
                    ((c % 128) >> 3) * tamCuadro.Height,
                    tamCuadro.Width,
                    tamCuadro.Height
                );
            }
            picPaleta.Image = coloresPaleta;
        }

        private void picPaleta_Click(object sender, EventArgs e)
        {
            Point puntoClickeado = picPaleta.PointToClient(MousePosition);
            puntoClickeado.X /= tamCuadro.Width;
            puntoClickeado.Y /= tamCuadro.Height;
            int colorClicado = (puntoClickeado.X > 7 ? 128 : 0) + 8 * puntoClickeado.Y + (puntoClickeado.X % 8);
            if (colorClicado >= paletaNueva.Length) return;

            etiquetasColores[(colorSeleccionado % 8) + (colorSeleccionado > 128 ? 8 : 0)].ForeColor =
                etiquetasColores[(colorSeleccionado >> 3) + 16].ForeColor = Color.Gold;
            etiquetasColores[(colorClicado % 8) + (colorClicado > 128 ? 8 : 0)].ForeColor =
                etiquetasColores[(colorClicado >> 3) + 16].ForeColor = Color.White;

            lblDecimal.Text = colorClicado.ToString("D3") + 'd';
            lblOctal.Text = Convert.ToString(colorClicado, 8).PadLeft(4, '0');
            lblHexadecimal.Text = colorClicado.ToString("X2") + 'h';

            picColorActual.BackColor = frmOrigen.paletaVieja[colorClicado];
            picColorNuevo.BackColor = paletaNueva[colorClicado];

            colorSeleccionado = colorClicado;
        }

        private void btnCancelar_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void picColorNuevo_Click(object sender, EventArgs e)
        {
            ColorDialog formColores = new ColorDialog();
            formColores.Color = picColorNuevo.BackColor;
            if (formColores.ShowDialog() != DialogResult.OK) return;
            paletaNueva[colorSeleccionado] = picColorNuevo.BackColor = formColores.Color;
            if (rdbPaletaNueva.Checked)
            {
                Image nuevaImagen = picPaleta.Image;
                Graphics g = Graphics.FromImage(nuevaImagen);
                g.FillRectangle(
                    new SolidBrush(formColores.Color),
                    ((colorSeleccionado % 8) + 8 * (colorSeleccionado >> 7)) * tamCuadro.Width,
                    ((colorSeleccionado % 128) >> 3) * tamCuadro.Height,
                    tamCuadro.Width,
                    tamCuadro.Height
                );
                picPaleta.Image = nuevaImagen;
            }
        }

        private void rdbPaletaNueva_CheckedChanged(object sender, EventArgs e)
        {
            llenarPaleta(paletaNueva);
        }

        private void rdbPaletaAnterior_CheckedChanged(object sender, EventArgs e)
        {
            llenarPaleta(frmOrigen.paletaVieja);
        }

        private void btnResstablecer_Click(object sender, EventArgs e)
        {
            paletaNueva[colorSeleccionado] = picColorNuevo.BackColor = picColorActual.BackColor;
            if (rdbPaletaNueva.Checked)
            {
                Image nuevaImagen = picPaleta.Image;
                Graphics g = Graphics.FromImage(nuevaImagen);
                g.FillRectangle(
                    new SolidBrush(picColorActual.BackColor),
                    ((colorSeleccionado % 8) + 8 * (colorSeleccionado >> 7)) * tamCuadro.Width,
                    ((colorSeleccionado % 128) >> 3) * tamCuadro.Height,
                    tamCuadro.Width,
                    tamCuadro.Height
                );
                picPaleta.Image = nuevaImagen;
            }
        }

        private void picColorNuevo_BackColorChanged(object sender, EventArgs e)
        {
            lblNuevo.Text = "Nuevo - #" + (picColorNuevo.BackColor.ToArgb() & 0x00FFFFFF).ToString("X6");
        }

        private void picColorActual_BackColorChanged(object sender, EventArgs e)
        {
            lblActual.Text = "Actual - #" + (picColorActual.BackColor.ToArgb() & 0x00FFFFFF).ToString("X6");
        }

        private void btnAceptar_Click(object sender, EventArgs e)
        {
            for (int c = 0; c < paletaNueva.Length; c++) frmOrigen.paletaVieja[c] = paletaNueva[c];
            Close();
        }
    }
}
