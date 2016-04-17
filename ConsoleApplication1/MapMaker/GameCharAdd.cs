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
    public partial class GameCharAdd : Form
    {
        int maxID = 0;

        public GameCharAdd()
        {
            InitializeComponent();
            this.DialogResult = DialogResult.Cancel;
        }

        public GameCharAdd(int maxid)
        {
            InitializeComponent();
            maxID = maxid;
            this.DialogResult = DialogResult.Cancel;
        }

        private void GameCharAdd_Load(object sender, EventArgs e)
        {
            String[] itemnames = Enum.GetNames(typeof(CharacterID));

            foreach (String s in itemnames)
            {
                cboCharTypes.Items.Add(s);
            }

            numID.Value = maxID;

        }

        Character c;
        private void button1_Click(object sender, EventArgs e)
        {
            c = new Character((CharacterID)cboCharTypes.SelectedIndex);
            c.ID = (uint)numID.Value;
            c.Location = new Point((int)this.numXPos.Value, (int)this.numYPos.Value);

            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        public Character GetCharacter()
        {
            return c;
        }
    }
}
