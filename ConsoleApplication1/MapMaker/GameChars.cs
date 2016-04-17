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
    public partial class GameChars : Form
    {
        List<Character> _chars;
        public GameChars()
        {
            InitializeComponent();
            _chars = new List<Character>();
        }

        public GameChars(List<Character> chars)
        {
            InitializeComponent();
            _chars = chars;
        }

        public List<Character> GetCharacters()
        {
            return this._chars;
        }

        private void GameChars_Load(object sender, EventArgs e)
        {

        }

        void AddGameCharToList(Character character)
        {
            ListViewItem lvi = new ListViewItem(((CharacterID)character.TypeData.TypeID).ToString());
            lvi.Tag = character;
            lvi.SubItems.Add(new ListViewItem.ListViewSubItem(lvi, character.ID.ToString()));
            lvi.SubItems.Add(new ListViewItem.ListViewSubItem(lvi, character.Location.X.ToString()));
            lvi.SubItems.Add(new ListViewItem.ListViewSubItem(lvi, character.Location.Y.ToString()));

            lvwChars.Items.Add(lvi);
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            using (GameCharAdd gca = new GameCharAdd(this._chars.Count)) { 
                if (gca.ShowDialog() == DialogResult.OK)
                {
                    Character c = gca.GetCharacter();
                    this._chars.Add(c);
                    AddGameCharToList(c);
                }

            }
        }

        private void btnRemove_Click(object sender, EventArgs e)
        {
            var selItems = lvwChars.SelectedItems;
            foreach (ListViewItem lviSel in selItems)
            {
                _chars.Remove((Character)lviSel.Tag);
                lvwChars.Items.Remove(lviSel);

            }

        }
    }
}
