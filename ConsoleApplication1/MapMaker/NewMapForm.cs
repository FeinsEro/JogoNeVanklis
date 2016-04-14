using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MapMaker
{
    public partial class NewMapForm : Form
    {
        public NewMapForm()
        {
            InitializeComponent();
            this.DialogResult = DialogResult.Cancel;
        }

        uint height, width;

        private void btnCreate_Click(object sender, EventArgs e)
        {
            height = Convert.ToUInt32(numHeight.Value);
            width = Convert.ToUInt32(numWidth.Value);
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        public Size GetMapSize()
        {
            return new Size((int)width, (int)height);
        }
    }
}
