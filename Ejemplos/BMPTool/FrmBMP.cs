using System;
using System.Drawing;
using System.Windows.Forms;
using LibEDS.Net;
using LibEDS.Net.LibBMP;

namespace Prueba_CS
{
    public partial class FrmBMP : Form
    {
        public FrmBMP()
        {
            InitializeComponent();
        }

        private void FrmBMP_Load(object sender, EventArgs e)
        {
            numResHorizontal.Maximum =
            numResVertical.Maximum =
            numAncho.Maximum =
            numAlto.Maximum =
            numRecortarX1.Maximum =
            numRecortarY1.Maximum =
            numRecortarX2.Maximum =
            numRecortarY2.Maximum =
                Int32.MaxValue;

            numRecortarX1.Minimum =
            numRecortarY1.Minimum =
            numRecortarX2.Minimum =
            numRecortarY2.Minimum =
                Int32.MinValue;

            btnAbrir_Click(null, null);
            BringToFront();
            if (imagen == null) Close();
        }

        const string FiltroArchivoBMP = "Archivos BMP (*.bmp)|*.bmp";
        public ImagenBMP imagen;
        public MascarasBits nuevoFormatoPixel;
        int versionVieja;
        public int bppViejo;
        public Color[] paletaVieja;

        decimal anchoAnterior, altoAnterior;
        bool rotadoAnterior;

        private void btnAbrir_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog dialogoAbrirArchivo = new OpenFileDialog())
            {
                dialogoAbrirArchivo.Filter = FiltroArchivoBMP;
                if (dialogoAbrirArchivo.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        if (imagen != null) imagen.Dispose();
                        imagen = new ImagenBMP(dialogoAbrirArchivo.FileName);

                        versionVieja = 0;
                        bppViejo = 0;
                        cmbBPP.SelectedIndex = -1;

                        numResHorizontal.Value = imagen.Resolucion.Width;
                        numResVertical.Value = imagen.Resolucion.Height;

                        anchoAnterior = altoAnterior = 0;
                        rotadoAnterior = false;
                        rdbRotarNo.Checked = true;

                        rdbEspejoNo.Checked = rdbRotarNo.Checked = true;
                        chkInvertir.Checked = chkGrises.Checked = false;

                        numRecortarX1.Value =
                        numRecortarY1.Value =
                        numRecortarX2.Value =
                        numRecortarY2.Value =
                        numSaturarRojo.Value =
                        numSaturarVerde.Value =
                        numSaturarAzul.Value =
                        numSaturarAlpha.Value =
                        numCambiarRojo.Value =
                        numCambiarVerde.Value =
                        numCambiarAzul.Value =
                        numCambiarAlpha.Value =
                            0;

                        numExtraerRojo.Value =
                        numExtraerVerde.Value =
                        numExtraerAzul.Value =
                        numExtraerAlpha.Value =
                            255;
                        
                        numAncho.Value = imagen.Ancho;
                        numAlto.Value = imagen.Alto;

                        cmbVersion.SelectedIndex = versionVieja =
                            imagen.Version == VersionDIB.Windows200 ? 0 :
                            imagen.Version == VersionDIB.WindowsNT ||
                            imagen.Version == VersionDIB.WindowsNTMascaras ||
                            imagen.Version == VersionDIB.WindowsNTMascarasAlpha ? 1 :
                            imagen.Version == VersionDIB.Windows95 ? 2 :
                            imagen.Version == VersionDIB.Windows98 ? 3 : -1;
                        cmbBPP.SelectedItem = imagen.BPP.ToString();
                        bppViejo = imagen.BPP;
                    }
                    catch (ExcepcionBMP ex)
                    {
                        MessageBox.Show(ex.Message, "Error al cargar el archivo BMP", MessageBoxButtons.OK);
                    }
                }
            }
        }
        
        private ImagenBMP generarBMP()
        {
            DibujoEDS dibujo = (DibujoEDS)imagen;
            dibujo.BPP = bppViejo;
            if (bppViejo <= 8) for (int c = 0; c < paletaVieja.Length; c++) dibujo.Paleta[c] = paletaVieja[c];
            else
            {
                foreach (string opColor in lstOrdenEfectos.Items)
                {
                    switch (opColor)
                    {
                        case "Invertir":
                            if (chkInvertir.Checked) dibujo.InvertirColores();
                            break;

                        case "Grises":
                            if (chkGrises.Checked) dibujo.EscalaGrises();
                            break;

                        case "Saturar":
                            dibujo.SaturarColores(Color.FromArgb(
                                (int)numSaturarAlpha.Value,
                                (int)numSaturarRojo.Value,
                                (int)numSaturarVerde.Value,
                                (int)numSaturarAzul.Value
                            ));
                            break;

                        case "Extraer":
                            dibujo.ExtraerColores(Color.FromArgb(
                                (int)numExtraerAlpha.Value,
                                (int)numExtraerRojo.Value,
                                (int)numExtraerVerde.Value,
                                (int)numExtraerAzul.Value
                            ));
                            break;

                        case "Incrementar":
                            dibujo.CambiarRojo((int)numCambiarRojo.Value);
                            dibujo.CambiarVerde((int)numCambiarVerde.Value);
                            dibujo.CambiarAzul((int)numCambiarAzul.Value);
                            break;
                    }
                }
            }

            foreach (string opGeometria in lstOrdenGeometria.Items)
            {
                switch (opGeometria)
                {
                    case "Reescalar":
                        dibujo.Reescalar((int)numAncho.Value, (int)numAlto.Value);
                        break;

                    case "Recortar":
                        dibujo.Recortar(
                            (int)numRecortarX1.Value,
                            (int)numRecortarY1.Value,
                            (int)numRecortarX2.Value,
                            (int)numRecortarY2.Value
                        );
                        break;

                    case "Espejo":
                        if (rdbEspejoX.Checked) dibujo.EspejoX();
                        if (rdbEspejoY.Checked) dibujo.EspejoY();
                        break;

                    case "Rotar":
                        if (rdbRotarDerecha.Checked) dibujo.RotarDerecha();
                        if (rdbRotarIzquierda.Checked) dibujo.RotarIzquierda();
                        if (rdbRotarVoltear.Checked) dibujo.Voltear();
                        break;
                }
            }

            ImagenBMP salida = dibujo.ConvertirAImagenBMP(bppViejo == 32, chkRLE.Checked);
            if (bppViejo == 16 || bppViejo == 32) salida.CambiarFormatoPixel(bppViejo, nuevoFormatoPixel);
            salida.Resolucion = new Size((int)numResHorizontal.Value, (int)numResVertical.Value);
            salida.Version = cmbVersion.SelectedIndex == 0 ? VersionDIB.Windows200 :
                cmbVersion.SelectedIndex == 1 ? VersionDIB.WindowsNT :
                cmbVersion.SelectedIndex == 2 ? VersionDIB.Windows95 :
                cmbVersion.SelectedIndex == 3 ? VersionDIB.Windows98 : VersionDIB.WindowsNT;

            return salida;
        }

        private void btnGuardar_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog dialogoGuardarArchivo = new SaveFileDialog())
            {
                dialogoGuardarArchivo.Filter = FiltroArchivoBMP;
                if (dialogoGuardarArchivo.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        using (ImagenBMP imagenGuardar = generarBMP())
                        {
                            imagenGuardar.Guardar(dialogoGuardarArchivo.FileName);
                        }
                    }
                    catch (ExcepcionBMP ex)
                    {
                        MessageBox.Show(ex.Message, "Error al guardar el archivo BMP", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    }
                    catch (FormatException ex)
                    {
                        MessageBox.Show(ex.Message, "Error de formato de cadena", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    }
                    catch (ExcepcionMascarasBits ex)
                    {
                        MessageBox.Show(ex.Message, "Error de máscaras de bits", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    }
                }
            }
        }

        private void acomodarFormatoPixel()
        {
            lblFormatoPixel.Text = "RGB" +
                (nuevoFormatoPixel.Alpha != 0 ? "A" : "") +
                nuevoFormatoPixel.BitsRojo +
                nuevoFormatoPixel.BitsVerde +
                nuevoFormatoPixel.BitsAzul +
                (nuevoFormatoPixel.Alpha != 0 ? nuevoFormatoPixel.BitsAlpha.ToString() : "");
        }

        private void cmbVersion_SelectedIndexChanged(object sender, EventArgs e)
        {
            int nuevaVersion = cmbVersion.SelectedIndex;
            if (nuevaVersion < versionVieja)
                if (MessageBox.Show("Cambiar la versión del archivo a una inferior puede provocar pérdida de algunos datos\n" +
                    "¿Aún desea cambiar a la version seleccionada?", "Cambiar versión", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) == DialogResult.No)
                {
                    cmbVersion.SelectedIndex = versionVieja;
                    return;
                }
            
            versionVieja = cmbVersion.SelectedIndex;
            int bppNuevo = bppViejo;

            if (versionVieja == 0)
            {
                if (bppViejo == 16 || bppViejo == 32) bppNuevo = 24;
                chkRLE.Enabled = grpResolucion.Enabled = false;
                if (!chkRLE.Enabled) chkRLE.Checked = false;

                if (cmbBPP.Items.Count == 6)
                {
                    cmbBPP.Items.Remove("16");
                    cmbBPP.Items.Remove("32");
                    cmbBPP.SelectedItem = bppNuevo.ToString();
                }
            }
            else
            {
                chkRLE.Enabled = bppViejo == 4 || bppViejo == 8;
                if (!chkRLE.Enabled) chkRLE.Checked = false;

                if (cmbBPP.Items.Count == 4)
                {
                    cmbBPP.Items.Insert(3, "16");
                    cmbBPP.Items.Insert(5, "32");
                    cmbBPP.SelectedItem = bppNuevo.ToString();
                }
            }
        }

        private void lstOrdenGeometria_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnPrimeroGeometria.Enabled = lstOrdenGeometria.SelectedIndex > 0;
            btnDespuesGeometria.Enabled = lstOrdenGeometria.SelectedIndex < lstOrdenGeometria.Items.Count - 1;
        }

        private void lstOrdenEfectos_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnPrimeroEfectos.Enabled = lstOrdenEfectos.SelectedIndex > 0;
            btnDespuesEfectos.Enabled = lstOrdenEfectos.SelectedIndex < lstOrdenEfectos.Items.Count - 1;
        }

        public static void moverElementoListBox(ListBox lista, int elemento, bool subir)
        {
            lista.Items.Insert(elemento + (subir ? -1 : 2), lista.Items[elemento]);
            lista.Items.RemoveAt(elemento + (subir ? 1 : 0));
            lista.SelectedIndex = elemento + (subir ? -1 : 1);
        }

        public static void moverElementoListBox(ListBox lista, bool subir) { moverElementoListBox(lista, lista.SelectedIndex, subir); }

        private void btnPrimeroGeometria_Click(object sender, EventArgs e)
        {
            moverElementoListBox(lstOrdenGeometria, true);
        }

        private void btnDespuesGeometria_Click(object sender, EventArgs e)
        {
            moverElementoListBox(lstOrdenGeometria, false);
        }

        private void btnPrimeroEfectos_Click(object sender, EventArgs e)
        {
            moverElementoListBox(lstOrdenEfectos, true);
        }

        private void btnDespuesEfectos_Click(object sender, EventArgs e)
        {
            moverElementoListBox(lstOrdenEfectos, false);
        }

        private void cmbBPP_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbBPP.SelectedItem == null) return;
            int bppNuevo = int.Parse(cmbBPP.SelectedItem.ToString());
            if (bppNuevo == bppViejo) return;
            bppViejo = bppNuevo;
            nuevoFormatoPixel = bppViejo == imagen.BPP ? imagen.FormatoPixel : MascarasBits.MascarasPorDefecto(bppViejo);
            
            chkRLE.Enabled = (bppViejo == 4 || bppViejo == 8) && cmbVersion.SelectedIndex != 0;
            if (!chkRLE.Enabled) chkRLE.Checked = false;
            else chkRLE.Checked = imagen.Compresion == MetodoCompresion.RLE4 || imagen.Compresion == MetodoCompresion.RLE8;
            btnFormatoPixel.Enabled = bppViejo > 8 && bppViejo != 24;
            grpEfectos.Enabled = bppViejo > 8;
            btnPaletaColores.Enabled = bppViejo <= 8;
            if (bppViejo <= 8)
            {
                paletaVieja = new Color[1 << bppViejo];
                if(bppViejo == imagen.BPP)
                {
                    for (int c = 0; c < paletaVieja.Length; c++) paletaVieja[c] = imagen.Paleta[c];
                }
                else
                {
                    for (int c = 0; c < paletaVieja.Length; c++) paletaVieja[c] = PaletaColores.PaletaPorDefecto(bppViejo)[c];
                }
            }

            acomodarFormatoPixel();
        }

        private void btnFormatoPixel_Click(object sender, EventArgs e)
        {
            FrmFormatoPixel form = new FrmFormatoPixel(this);
            form.ShowDialog();
            acomodarFormatoPixel();
        }

        private void btnPaletaColores_Click(object sender, EventArgs e)
        {
            FrmPaleta form = new FrmPaleta(this);
            form.ShowDialog();
        }

        private void btnBrilloMas_Click(object sender, EventArgs e)
        {
            numCambiarRojo.Value += 25;
            numCambiarVerde.Value += 25;
            numCambiarAzul.Value += 25;
        }

        private void btnBrilloMenos_Click(object sender, EventArgs e)
        {
            numCambiarRojo.Value -= 25;
            numCambiarVerde.Value -= 25;
            numCambiarAzul.Value -= 25;
        }

        private void btnPrevisualizar_Click(object sender, EventArgs e)
        {
            Form ventana = new Form();
            ImagenBMP imagen = generarBMP();
            ventana.FormBorderStyle = FormBorderStyle.None;
            ventana.KeyDown += CerrarVentanaPrevisualizacion;
            ventana.MouseClick += CerrarVentanaPrevisualizacion;
            ventana.Size = imagen.Dimensiones;
            ventana.BackgroundImage = (DibujoEDS)imagen;
            ventana.StartPosition = FormStartPosition.CenterScreen;
            ventana.ShowDialog();
            ventana.Dispose();
            imagen.Dispose();
        }

        private void CerrarVentanaPrevisualizacion(object sender, EventArgs e)
        {
            ((Form)sender).Close();
        }

        private void numAncho_ValueChanged(object sender, EventArgs e)
        {
            numRecortarX2.Value += numAncho.Value - anchoAnterior;
            anchoAnterior = numAncho.Value;
        }

        private void numAlto_ValueChanged(object sender, EventArgs e)
        {
            numRecortarY2.Value += numAlto.Value - altoAnterior;
            altoAnterior = numAlto.Value;
        }

        private void cambiarRotado(bool nuevoRotado)
        {
            if(nuevoRotado != rotadoAnterior)
            {
                decimal temp = numAlto.Value;
                numAlto.Value = numAncho.Value;
                numAncho.Value = temp;

                temp = numRecortarX1.Value;
                numRecortarX1.Value = numRecortarY1.Value;
                numRecortarY1.Value = temp;

                temp = numRecortarX2.Value - numAncho.Value;
                numRecortarX2.Value = numAncho.Value + numRecortarY2.Value - numAlto.Value;
                numRecortarY2.Value = numAlto.Value + temp;
            }
        }

        private void rdbRotarDerecha_CheckedChanged(object sender, EventArgs e)
        {
            cambiarRotado(true);
        }

        private void rdbRotarIzquierda_CheckedChanged(object sender, EventArgs e)
        {
            cambiarRotado(true);
        }

        private void rdbRotarVoltear_CheckedChanged(object sender, EventArgs e)
        {
            cambiarRotado(false);
        }

        private void rdbRotarNo_CheckedChanged(object sender, EventArgs e)
        {
            cambiarRotado(false);
        }
    }
}
