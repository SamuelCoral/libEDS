namespace Prueba_CS
{
    partial class FrmPaleta
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.picPaleta = new System.Windows.Forms.PictureBox();
            this.picColorActual = new System.Windows.Forms.PictureBox();
            this.picColorNuevo = new System.Windows.Forms.PictureBox();
            this.lblActual = new System.Windows.Forms.Label();
            this.lblNuevo = new System.Windows.Forms.Label();
            this.btnCancelar = new System.Windows.Forms.Button();
            this.btnAceptar = new System.Windows.Forms.Button();
            this.lblSeleccionado = new System.Windows.Forms.Label();
            this.lblDecimal = new System.Windows.Forms.Label();
            this.lblHexadecimal = new System.Windows.Forms.Label();
            this.lblOctal = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rdbPaletaAnterior = new System.Windows.Forms.RadioButton();
            this.rdbPaletaNueva = new System.Windows.Forms.RadioButton();
            this.btnResstablecer = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.picPaleta)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorActual)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorNuevo)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // picPaleta
            // 
            this.picPaleta.Location = new System.Drawing.Point(60, 36);
            this.picPaleta.Name = "picPaleta";
            this.picPaleta.Size = new System.Drawing.Size(512, 512);
            this.picPaleta.TabIndex = 0;
            this.picPaleta.TabStop = false;
            this.picPaleta.Click += new System.EventHandler(this.picPaleta_Click);
            // 
            // picColorActual
            // 
            this.picColorActual.Location = new System.Drawing.Point(663, 58);
            this.picColorActual.Name = "picColorActual";
            this.picColorActual.Size = new System.Drawing.Size(100, 50);
            this.picColorActual.TabIndex = 1;
            this.picColorActual.TabStop = false;
            this.picColorActual.BackColorChanged += new System.EventHandler(this.picColorActual_BackColorChanged);
            // 
            // picColorNuevo
            // 
            this.picColorNuevo.Location = new System.Drawing.Point(663, 107);
            this.picColorNuevo.Name = "picColorNuevo";
            this.picColorNuevo.Size = new System.Drawing.Size(100, 50);
            this.picColorNuevo.TabIndex = 2;
            this.picColorNuevo.TabStop = false;
            this.picColorNuevo.BackColorChanged += new System.EventHandler(this.picColorNuevo_BackColorChanged);
            this.picColorNuevo.Click += new System.EventHandler(this.picColorNuevo_Click);
            // 
            // lblActual
            // 
            this.lblActual.AutoSize = true;
            this.lblActual.Location = new System.Drawing.Point(660, 42);
            this.lblActual.Name = "lblActual";
            this.lblActual.Size = new System.Drawing.Size(37, 13);
            this.lblActual.TabIndex = 3;
            this.lblActual.Text = "Actual";
            // 
            // lblNuevo
            // 
            this.lblNuevo.AutoSize = true;
            this.lblNuevo.Location = new System.Drawing.Point(663, 164);
            this.lblNuevo.Name = "lblNuevo";
            this.lblNuevo.Size = new System.Drawing.Size(39, 13);
            this.lblNuevo.TabIndex = 4;
            this.lblNuevo.Text = "Nuevo";
            // 
            // btnCancelar
            // 
            this.btnCancelar.Location = new System.Drawing.Point(698, 528);
            this.btnCancelar.Name = "btnCancelar";
            this.btnCancelar.Size = new System.Drawing.Size(75, 23);
            this.btnCancelar.TabIndex = 5;
            this.btnCancelar.Text = "Cancelar";
            this.btnCancelar.UseVisualStyleBackColor = true;
            this.btnCancelar.Click += new System.EventHandler(this.btnCancelar_Click);
            // 
            // btnAceptar
            // 
            this.btnAceptar.Location = new System.Drawing.Point(698, 499);
            this.btnAceptar.Name = "btnAceptar";
            this.btnAceptar.Size = new System.Drawing.Size(75, 23);
            this.btnAceptar.TabIndex = 6;
            this.btnAceptar.Text = "Aceptar";
            this.btnAceptar.UseVisualStyleBackColor = true;
            this.btnAceptar.Click += new System.EventHandler(this.btnAceptar_Click);
            // 
            // lblSeleccionado
            // 
            this.lblSeleccionado.AutoSize = true;
            this.lblSeleccionado.Location = new System.Drawing.Point(663, 269);
            this.lblSeleccionado.Name = "lblSeleccionado";
            this.lblSeleccionado.Size = new System.Drawing.Size(72, 13);
            this.lblSeleccionado.TabIndex = 7;
            this.lblSeleccionado.Text = "Seleccionado";
            // 
            // lblDecimal
            // 
            this.lblDecimal.AutoSize = true;
            this.lblDecimal.Location = new System.Drawing.Point(666, 286);
            this.lblDecimal.Name = "lblDecimal";
            this.lblDecimal.Size = new System.Drawing.Size(31, 13);
            this.lblDecimal.TabIndex = 8;
            this.lblDecimal.Text = "000d";
            // 
            // lblHexadecimal
            // 
            this.lblHexadecimal.AutoSize = true;
            this.lblHexadecimal.Location = new System.Drawing.Point(666, 299);
            this.lblHexadecimal.Name = "lblHexadecimal";
            this.lblHexadecimal.Size = new System.Drawing.Size(25, 13);
            this.lblHexadecimal.TabIndex = 9;
            this.lblHexadecimal.Text = "00h";
            // 
            // lblOctal
            // 
            this.lblOctal.AutoSize = true;
            this.lblOctal.Location = new System.Drawing.Point(666, 312);
            this.lblOctal.Name = "lblOctal";
            this.lblOctal.Size = new System.Drawing.Size(31, 13);
            this.lblOctal.TabIndex = 10;
            this.lblOctal.Text = "0000";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rdbPaletaAnterior);
            this.groupBox1.Controls.Add(this.rdbPaletaNueva);
            this.groupBox1.Location = new System.Drawing.Point(662, 357);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(101, 71);
            this.groupBox1.TabIndex = 11;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Mostrar paleta";
            // 
            // rdbPaletaAnterior
            // 
            this.rdbPaletaAnterior.AutoSize = true;
            this.rdbPaletaAnterior.Location = new System.Drawing.Point(7, 44);
            this.rdbPaletaAnterior.Name = "rdbPaletaAnterior";
            this.rdbPaletaAnterior.Size = new System.Drawing.Size(61, 17);
            this.rdbPaletaAnterior.TabIndex = 1;
            this.rdbPaletaAnterior.Text = "Anterior";
            this.rdbPaletaAnterior.UseVisualStyleBackColor = true;
            this.rdbPaletaAnterior.CheckedChanged += new System.EventHandler(this.rdbPaletaAnterior_CheckedChanged);
            // 
            // rdbPaletaNueva
            // 
            this.rdbPaletaNueva.AutoSize = true;
            this.rdbPaletaNueva.Checked = true;
            this.rdbPaletaNueva.Location = new System.Drawing.Point(7, 20);
            this.rdbPaletaNueva.Name = "rdbPaletaNueva";
            this.rdbPaletaNueva.Size = new System.Drawing.Size(57, 17);
            this.rdbPaletaNueva.TabIndex = 0;
            this.rdbPaletaNueva.TabStop = true;
            this.rdbPaletaNueva.Text = "Nueva";
            this.rdbPaletaNueva.UseVisualStyleBackColor = true;
            this.rdbPaletaNueva.CheckedChanged += new System.EventHandler(this.rdbPaletaNueva_CheckedChanged);
            // 
            // btnResstablecer
            // 
            this.btnResstablecer.Location = new System.Drawing.Point(663, 190);
            this.btnResstablecer.Name = "btnResstablecer";
            this.btnResstablecer.Size = new System.Drawing.Size(83, 23);
            this.btnResstablecer.TabIndex = 12;
            this.btnResstablecer.Text = "Reestablecer";
            this.btnResstablecer.UseVisualStyleBackColor = true;
            this.btnResstablecer.Click += new System.EventHandler(this.btnResstablecer_Click);
            // 
            // FrmPaleta
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(785, 568);
            this.Controls.Add(this.btnResstablecer);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.lblOctal);
            this.Controls.Add(this.lblHexadecimal);
            this.Controls.Add(this.lblDecimal);
            this.Controls.Add(this.lblSeleccionado);
            this.Controls.Add(this.btnAceptar);
            this.Controls.Add(this.btnCancelar);
            this.Controls.Add(this.lblNuevo);
            this.Controls.Add(this.lblActual);
            this.Controls.Add(this.picColorNuevo);
            this.Controls.Add(this.picColorActual);
            this.Controls.Add(this.picPaleta);
            this.Name = "FrmPaleta";
            this.Text = "Editor de paleta de colores";
            ((System.ComponentModel.ISupportInitialize)(this.picPaleta)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorActual)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picColorNuevo)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox picPaleta;
        private System.Windows.Forms.PictureBox picColorActual;
        private System.Windows.Forms.PictureBox picColorNuevo;
        private System.Windows.Forms.Label lblActual;
        private System.Windows.Forms.Label lblNuevo;
        private System.Windows.Forms.Button btnCancelar;
        private System.Windows.Forms.Button btnAceptar;
        private System.Windows.Forms.Label lblSeleccionado;
        private System.Windows.Forms.Label lblDecimal;
        private System.Windows.Forms.Label lblHexadecimal;
        private System.Windows.Forms.Label lblOctal;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rdbPaletaAnterior;
        private System.Windows.Forms.RadioButton rdbPaletaNueva;
        private System.Windows.Forms.Button btnResstablecer;
    }
}