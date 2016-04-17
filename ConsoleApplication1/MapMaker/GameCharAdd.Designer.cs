namespace MapMaker
{
    partial class GameCharAdd
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
            this.cboCharTypes = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.numID = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.numXPos = new System.Windows.Forms.NumericUpDown();
            this.numYPos = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numID)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numXPos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numYPos)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(31, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Tipo:";
            // 
            // cboCharTypes
            // 
            this.cboCharTypes.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboCharTypes.FormattingEnabled = true;
            this.cboCharTypes.Location = new System.Drawing.Point(49, 6);
            this.cboCharTypes.Name = "cboCharTypes";
            this.cboCharTypes.Size = new System.Drawing.Size(325, 21);
            this.cboCharTypes.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(21, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "ID:";
            // 
            // numID
            // 
            this.numID.Location = new System.Drawing.Point(49, 43);
            this.numID.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numID.Name = "numID";
            this.numID.Size = new System.Drawing.Size(120, 20);
            this.numID.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 86);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Posição X:";
            // 
            // numXPos
            // 
            this.numXPos.Location = new System.Drawing.Point(76, 84);
            this.numXPos.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numXPos.Name = "numXPos";
            this.numXPos.Size = new System.Drawing.Size(69, 20);
            this.numXPos.TabIndex = 5;
            // 
            // numYPos
            // 
            this.numYPos.Location = new System.Drawing.Point(228, 84);
            this.numYPos.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numYPos.Name = "numYPos";
            this.numYPos.Size = new System.Drawing.Size(69, 20);
            this.numYPos.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(164, 86);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(58, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Posição Y:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(299, 150);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 8;
            this.button1.Text = "&OK";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // GameCharAdd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(389, 185);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.numYPos);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.numXPos);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.numID);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cboCharTypes);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "GameCharAdd";
            this.ShowIcon = false;
            this.Text = "Adicionar caractere";
            this.Load += new System.EventHandler(this.GameCharAdd_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numID)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numXPos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numYPos)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cboCharTypes;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numID;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown numXPos;
        private System.Windows.Forms.NumericUpDown numYPos;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button1;
    }
}