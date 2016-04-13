using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace MapMaker
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        MapDataParser mdp;
        Map map = null;

        struct _GFXDATA {
            public Graphics gfx;
            public int xoff, yoff;
            public int elWidth, elHeight;
        }

        _GFXDATA gfxData;

        private void Form1_Load(object sender, EventArgs e)
        {
#if DEBUG
            Properties.Settings.Default.Reset();
#endif


            /* Verifica se a pasta é valida */
            if (Properties.Settings.Default.demonsPath == String.Empty)
            {
                bool validFolder = false;

                while (!validFolder) { 
                    FolderBrowserDialog fbd = new FolderBrowserDialog();
                    fbd.Description = "Não foi possível encontrar a pasta de instalação do jogo Dois Demônios. \n" +
                         "Informe-nos onde você o instalou";
                    fbd.SelectedPath = Application.StartupPath;
                
                    if (fbd.ShowDialog() == DialogResult.OK)
                    {
                        /* Verifica a existência de três subpastas: game, characters e maps */
                        bool isChar = false, isGame = false, isMaps = false;
                        foreach (String dir in Directory.EnumerateDirectories(fbd.SelectedPath))
                        {
                            
                            if (dir.EndsWith("game"))
                                isGame = true;

                            if (dir.EndsWith("characters"))
                                isChar = true;

                            if (dir.EndsWith("maps"))
                                isMaps = true;


                        }

                        
                        validFolder = (isGame && isChar && isMaps);
                        if (!validFolder)
                        {
                            MessageBox.Show(this, "Pasta inválida!", "Criador de Mapas", MessageBoxButtons.OK, 
                                MessageBoxIcon.Error);
                        } else
                        {
                            
                        }


                        Properties.Settings.Default.demonsPath = fbd.SelectedPath;
                    }
                    else
                    {
                        Application.Exit();
                    }
                }

                Properties.Settings.Default.Save();
                


            }

            mdp = new MapDataParser();
            mdp.Open();

            if (map == null)
            {
                pnlMapInfo.Visible = false;
            }


        }

        private void sobreToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Criador de mapas para o jogo Dois Demônios \n" +
                "\n" +
                "\n");
        }

        private void abrirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            String file = String.Empty;
            using (OpenFileDialog ofd = new OpenFileDialog())
            {
                ofd.AddExtension = true;
                ofd.Title = "Abrir mapa";
                ofd.CheckFileExists = true;
                ofd.AutoUpgradeEnabled = true;
                ofd.Filter = "Tribalia map files (*.map)|*.map|All files|*.*";
                ofd.FilterIndex = 0;
                ofd.Multiselect = false;
                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    file = ofd.FileName;

                } else
                {
                    return;
                }
            }

            try { 
                map = new Map(file);
                map.Open();
                lblSize.Text = map.Width + " x " + map.Height;
                lblPlayerPos.Text = "(" + map.PlayerX + ", " + map.PlayerY + ")";
                pnlMapInfo.Visible = true;
                this.Text = map.Filename + " - Criador de Mapas";

                gfxData.gfx = this.pnlMapDraw.CreateGraphics();
                gfxData.gfx.Clear(SystemColors.Control);
                gfxData.xoff = 0;
                gfxData.yoff = 0;
                gfxData.elWidth = (pnlMapDraw.Width / 32) + 1;
                gfxData.elHeight = (pnlMapDraw.Width / 32) + 1;


            } catch (InvalidMapException ex)
            {
                MessageBox.Show(this, "Mapa inválido", "Criador de mapas", MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        private void pnlMapDraw_Paint(object sender, PaintEventArgs e)
        {
            if (map != null)
            {

                for (int y = gfxData.yoff; y < (gfxData.elHeight + gfxData.yoff); y++){
                    for (int x = gfxData.xoff; x < (gfxData.elWidth + gfxData.xoff); x++)
                    {
                        if (x > map.Width)
                            break;

                        Bitmap bmp = mdp.GetImageFromIndex(map.Elements[y * map.Width + x]);

                        if (bmp == null)
                            break;

                        gfxData.gfx.DrawImage(bmp, new Point(x * 32, y * 32));
                    }

                    if (y > map.Height)
                        break;
                }
            }
        }
    }
}
