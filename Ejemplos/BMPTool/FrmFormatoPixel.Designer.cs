namespace Prueba_CS
{
    partial class FrmFormatoPixel
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
            this.label1 = new System.Windows.Forms.Label();
            this.rdbMascaras = new System.Windows.Forms.RadioButton();
            this.rdbNumBits = new System.Windows.Forms.RadioButton();
            this.grpNumBits = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.numAlpha = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.numAzul = new System.Windows.Forms.NumericUpDown();
            this.numVerde = new System.Windows.Forms.NumericUpDown();
            this.numRojo = new System.Windows.Forms.NumericUpDown();
            this.grpMascaras = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.txtAlpha = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.txtAzul = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtVerde = new System.Windows.Forms.TextBox();
            this.txtRojo = new System.Windows.Forms.TextBox();
            this.btnCancelar = new System.Windows.Forms.Button();
            this.btnAceptar = new System.Windows.Forms.Button();
            this.grpNumBits.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numAlpha)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAzul)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numVerde)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRojo)).BeginInit();
            this.grpMascaras.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(112, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Editar especificando...";
            // 
            // rdbMascaras
            // 
            this.rdbMascaras.AutoSize = true;
            this.rdbMascaras.Location = new System.Drawing.Point(11, 61);
            this.rdbMascaras.Name = "rdbMascaras";
            this.rdbMascaras.Size = new System.Drawing.Size(71, 17);
            this.rdbMascaras.TabIndex = 7;
            this.rdbMascaras.Text = "Máscaras";
            this.rdbMascaras.UseVisualStyleBackColor = true;
            this.rdbMascaras.CheckedChanged += new System.EventHandler(this.cambiarModo);
            // 
            // rdbNumBits
            // 
            this.rdbNumBits.AutoSize = true;
            this.rdbNumBits.Checked = true;
            this.rdbNumBits.Location = new System.Drawing.Point(11, 38);
            this.rdbNumBits.Name = "rdbNumBits";
            this.rdbNumBits.Size = new System.Drawing.Size(96, 17);
            this.rdbNumBits.TabIndex = 8;
            this.rdbNumBits.TabStop = true;
            this.rdbNumBits.Text = "Número de bits";
            this.rdbNumBits.UseVisualStyleBackColor = true;
            this.rdbNumBits.CheckedChanged += new System.EventHandler(this.cambiarModo);
            // 
            // grpNumBits
            // 
            this.grpNumBits.Controls.Add(this.label8);
            this.grpNumBits.Controls.Add(this.numAlpha);
            this.grpNumBits.Controls.Add(this.label4);
            this.grpNumBits.Controls.Add(this.label3);
            this.grpNumBits.Controls.Add(this.label2);
            this.grpNumBits.Controls.Add(this.numAzul);
            this.grpNumBits.Controls.Add(this.numVerde);
            this.grpNumBits.Controls.Add(this.numRojo);
            this.grpNumBits.Location = new System.Drawing.Point(151, 9);
            this.grpNumBits.Name = "grpNumBits";
            this.grpNumBits.Size = new System.Drawing.Size(176, 130);
            this.grpNumBits.TabIndex = 10;
            this.grpNumBits.TabStop = false;
            this.grpNumBits.Text = "Número de bits";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(55, 102);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(34, 13);
            this.label8.TabIndex = 7;
            this.label8.Text = "Alpha";
            // 
            // numAlpha
            // 
            this.numAlpha.Location = new System.Drawing.Point(7, 100);
            this.numAlpha.Name = "numAlpha";
            this.numAlpha.Size = new System.Drawing.Size(40, 20);
            this.numAlpha.TabIndex = 6;
            this.numAlpha.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(53, 76);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(27, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "Azul";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(53, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Verde";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(53, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Rojo";
            // 
            // numAzul
            // 
            this.numAzul.Location = new System.Drawing.Point(7, 74);
            this.numAzul.Name = "numAzul";
            this.numAzul.Size = new System.Drawing.Size(40, 20);
            this.numAzul.TabIndex = 2;
            this.numAzul.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // numVerde
            // 
            this.numVerde.Location = new System.Drawing.Point(7, 47);
            this.numVerde.Name = "numVerde";
            this.numVerde.Size = new System.Drawing.Size(40, 20);
            this.numVerde.TabIndex = 1;
            this.numVerde.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // numRojo
            // 
            this.numRojo.Location = new System.Drawing.Point(7, 20);
            this.numRojo.Maximum = new decimal(new int[] {
            32,
            0,
            0,
            0});
            this.numRojo.Name = "numRojo";
            this.numRojo.Size = new System.Drawing.Size(40, 20);
            this.numRojo.TabIndex = 0;
            this.numRojo.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            // 
            // grpMascaras
            // 
            this.grpMascaras.Controls.Add(this.label9);
            this.grpMascaras.Controls.Add(this.txtAlpha);
            this.grpMascaras.Controls.Add(this.label5);
            this.grpMascaras.Controls.Add(this.label6);
            this.grpMascaras.Controls.Add(this.txtAzul);
            this.grpMascaras.Controls.Add(this.label7);
            this.grpMascaras.Controls.Add(this.txtVerde);
            this.grpMascaras.Controls.Add(this.txtRojo);
            this.grpMascaras.Enabled = false;
            this.grpMascaras.Location = new System.Drawing.Point(151, 145);
            this.grpMascaras.Name = "grpMascaras";
            this.grpMascaras.Size = new System.Drawing.Size(176, 125);
            this.grpMascaras.TabIndex = 11;
            this.grpMascaras.TabStop = false;
            this.grpMascaras.Text = "Máscaras";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(113, 101);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(34, 13);
            this.label9.TabIndex = 8;
            this.label9.Text = "Alpha";
            // 
            // txtAlpha
            // 
            this.txtAlpha.Location = new System.Drawing.Point(7, 98);
            this.txtAlpha.Name = "txtAlpha";
            this.txtAlpha.Size = new System.Drawing.Size(100, 20);
            this.txtAlpha.TabIndex = 9;
            this.txtAlpha.Text = "0xFF000000";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(113, 75);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(27, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Azul";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(113, 49);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(35, 13);
            this.label6.TabIndex = 7;
            this.label6.Text = "Verde";
            // 
            // txtAzul
            // 
            this.txtAzul.Location = new System.Drawing.Point(7, 72);
            this.txtAzul.Name = "txtAzul";
            this.txtAzul.Size = new System.Drawing.Size(100, 20);
            this.txtAzul.TabIndex = 2;
            this.txtAzul.Text = "0x000000FF";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(113, 23);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(29, 13);
            this.label7.TabIndex = 6;
            this.label7.Text = "Rojo";
            // 
            // txtVerde
            // 
            this.txtVerde.Location = new System.Drawing.Point(7, 46);
            this.txtVerde.Name = "txtVerde";
            this.txtVerde.Size = new System.Drawing.Size(100, 20);
            this.txtVerde.TabIndex = 1;
            this.txtVerde.Text = "0x0000FF00";
            // 
            // txtRojo
            // 
            this.txtRojo.Location = new System.Drawing.Point(7, 20);
            this.txtRojo.Name = "txtRojo";
            this.txtRojo.Size = new System.Drawing.Size(100, 20);
            this.txtRojo.TabIndex = 0;
            this.txtRojo.Text = "0x00FF0000";
            // 
            // btnCancelar
            // 
            this.btnCancelar.Location = new System.Drawing.Point(252, 276);
            this.btnCancelar.Name = "btnCancelar";
            this.btnCancelar.Size = new System.Drawing.Size(75, 23);
            this.btnCancelar.TabIndex = 12;
            this.btnCancelar.Text = "Cancelar";
            this.btnCancelar.UseVisualStyleBackColor = true;
            this.btnCancelar.Click += new System.EventHandler(this.btnCancelar_Click);
            // 
            // btnAceptar
            // 
            this.btnAceptar.Location = new System.Drawing.Point(171, 276);
            this.btnAceptar.Name = "btnAceptar";
            this.btnAceptar.Size = new System.Drawing.Size(75, 23);
            this.btnAceptar.TabIndex = 13;
            this.btnAceptar.Text = "Aceptar";
            this.btnAceptar.UseVisualStyleBackColor = true;
            this.btnAceptar.Click += new System.EventHandler(this.btnAceptar_Click);
            // 
            // FrmFormatoPixel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(339, 311);
            this.Controls.Add(this.btnAceptar);
            this.Controls.Add(this.btnCancelar);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.rdbMascaras);
            this.Controls.Add(this.rdbNumBits);
            this.Controls.Add(this.grpNumBits);
            this.Controls.Add(this.grpMascaras);
            this.Name = "FrmFormatoPixel";
            this.Text = "Formato de Pixel";
            this.grpNumBits.ResumeLayout(false);
            this.grpNumBits.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numAlpha)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAzul)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numVerde)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRojo)).EndInit();
            this.grpMascaras.ResumeLayout(false);
            this.grpMascaras.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RadioButton rdbMascaras;
        private System.Windows.Forms.RadioButton rdbNumBits;
        private System.Windows.Forms.GroupBox grpNumBits;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown numAlpha;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numAzul;
        private System.Windows.Forms.NumericUpDown numVerde;
        private System.Windows.Forms.NumericUpDown numRojo;
        private System.Windows.Forms.GroupBox grpMascaras;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox txtAlpha;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtAzul;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtVerde;
        private System.Windows.Forms.TextBox txtRojo;
        private System.Windows.Forms.Button btnCancelar;
        private System.Windows.Forms.Button btnAceptar;
    }
}