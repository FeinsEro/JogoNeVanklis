using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Reflection;
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

        struct _GFXDATA
        {
            public Graphics gfx;
            public int xoff, yoff;
            public int elWidth, elHeight;
        }

        _GFXDATA gfxData;

        private void Form1_Load(object sender, EventArgs e)
        {
            gfxData.elHeight = 0;
            gfxData.elWidth = 0;
            gfxData.gfx = null;
#if DEBUG
            Properties.Settings.Default.Reset();
#endif


            /* Verifica se a pasta é valida */
            if (Properties.Settings.Default.demonsPath == String.Empty)
            {
                bool validFolder = false;

                while (!validFolder)
                {
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
                        }
                        else
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

            contextMenuStrip1.Enabled = false;
            int tcount = Enum.GetValues(typeof(MapDataParser.MapTiles)).Length;
            /* Adiciona novos itens de acordo com a pos. de mapa deles */
            for (int i = 0; i < tcount; i++)
            {
                ToolStripMenuItem itTile = new ToolStripMenuItem(
                    Enum.GetName(typeof(MapDataParser.MapTiles), i),
                    mdp.GetImageFromIndex(i));
                itTile.Tag = i;
                itTile.Click += ItTile_Click;
                mudarItemParaToolStripMenuItem.DropDownItems.Add(itTile);
            }

            if (map == null)
            {
                pnlMapInfo.Visible = false;
            }

            if (gfxData.elHeight > 0)
            {
                vScrollBar1.Maximum = 100; // gfxData.elHeight;
                vScrollBar1.Minimum = 0;


                contextMenuStrip1.Enabled = true;

            }
            else
            {
                vScrollBar1.Enabled = false;
            }
        }

        private void ItTile_Click(object sender, EventArgs e)
        {
            //Pega o ID do tile modificado.
            int tileid = (int)((ToolStripMenuItem)sender).Tag;

            foreach (Point pt in selectedTiles)
            {
                map.Elements[pt.Y * map.Width + pt.X] = tileid;
            }

            selectedTiles.Clear();
            pnlMapDraw.Refresh();
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

                }
                else
                {
                    return;
                }
            }

            try
            {
                map = new Map(file);
                map.Open();
                lblSize.Text = map.Width + " x " + map.Height;
                lblPlayerPos.Text = "(" + map.PlayerX + ", " + map.PlayerY + ")";
                pnlMapInfo.Visible = true;
                this.Text = map.Filename + " - Criador de Mapas";

                gfxData.xoff = 0;
                gfxData.yoff = 0;
                gfxData.elWidth = (pnlMapDraw.Width / 32) + 1;
                gfxData.elHeight = (pnlMapDraw.Height / 32) + 1;

                //habilita o double buffering *apenas* no painel de desenho de mapa
                typeof(Panel).InvokeMember("DoubleBuffered", BindingFlags.SetProperty
                    | BindingFlags.Instance | BindingFlags.NonPublic, null,
                    pnlMapDraw, new object[] { true });

                if (gfxData.elHeight > 0)
                {
                    //   vScrollBar1.Maximum = gfxData.elHeight;
                    vScrollBar1.Minimum = 0;
                    vScrollBar1.Enabled = true;
                    contextMenuStrip1.Enabled = true;
                    pnlMapDraw.Refresh();
                }
            }
            catch (InvalidMapException ex)
            {
                MessageBox.Show(this, "Mapa inválido", "Criador de mapas", MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }

        List<Point> selectedTiles = new List<Point>();

        private void pnlMapDraw_Paint(object sender, PaintEventArgs e)
        {
            if (map != null)
            {

                if (e != null)
                {
                    e.Graphics.FillRectangle(Brushes.Black, e.ClipRectangle);
                }
                else
                {
                    e.Graphics.Clear(Color.Black);
                }

                for (int y = gfxData.yoff; y < (gfxData.elHeight + gfxData.yoff); y++)
                {
                    if (y >= map.Height)
                        break;

                    for (int x = gfxData.xoff; x < (gfxData.elWidth + gfxData.xoff); x++)
                    {
                        if (x >= map.Width)
                            break;


                        Bitmap bmp = mdp.GetImageFromIndex(map.Elements[y * map.Width + x]);

                        if (bmp == null)
                            break;

                        e.Graphics.DrawImage(bmp,
                            new Point((x - gfxData.xoff) * 32, (y - gfxData.yoff) * 32));
                    }
                }

                Pen pn = new Pen(Brushes.Black, 2);

                foreach (Point pt in selectedTiles)
                {
                    int pixelX, pixelY;
                    pixelX = ((pt.X - gfxData.xoff) * 32);
                    pixelY = ((pt.Y - gfxData.yoff) * 32);

                    e.Graphics.DrawRectangle(pn, new Rectangle(pixelX, pixelY, 32, 32));
                }

                int playerPixelX = ((int) (map.PlayerX - gfxData.xoff) * 32);
                int playerPixelY = ((int)(map.PlayerY - gfxData.yoff) * 32);

                e.Graphics.DrawEllipse(Pens.White, new Rectangle(playerPixelX, playerPixelY, 32, 32));

                e.Graphics.DrawString("P", new Font(FontFamily.GenericMonospace, 12, GraphicsUnit.Point),
                    Brushes.Black, new Point(playerPixelX + 12, playerPixelY + 12));
            }
        }

        bool sizeChanged = false;
        private void pnlMapDraw_Resize(object sender, EventArgs e)
        {
            gfxData.elWidth = (pnlMapDraw.Width / 32) + 1;
            gfxData.elHeight = (pnlMapDraw.Height / 32) + 1;
            pnlMapDraw.Refresh();
            sizeChanged = true;
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            gfxData.yoff = e.NewValue;
            pnlMapDraw.Refresh();

        }

        bool multiple = false;
        private void pnlMapDraw_Click(object sender, EventArgs e)
        {


        }

        private void pnlMapDraw_MouseClick(object sender, MouseEventArgs e)
        {
            if (map != null)
            {
                if (!multiple)
                {
                    selectedTiles.Clear();
                    
                }



                int gameX, gameY;
                gameX = (e.X / 32) + gfxData.xoff;
                gameY = (e.Y / 32) + gfxData.yoff;
                selectedTiles.Add(new Point(gameX, gameY));
            }

            pnlMapDraw.Refresh();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Shift)
                multiple = true;


        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {

            if (e.Shift)
                multiple = false;
        }

        private void salvarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (map != null)
            {
                if (map.Filename == String.Empty)
                    salvarComoToolStripMenuItem_Click(sender, e);
                else
                    map.Save();
            }
        }

        private void novoToolStripMenuItem_Click(object sender, EventArgs e)
        {

            Size mapSize;
            using (NewMapForm frmNew = new NewMapForm())
            {
                if (frmNew.ShowDialog() != DialogResult.OK)
                    return;

                mapSize = frmNew.GetMapSize();
            }

            this.Text = "Criador de Mapas - Criando...";

            map = new Map((uint)mapSize.Width, (uint)mapSize.Height);
            lblSize.Text = map.Width + " x " + map.Height;
            lblPlayerPos.Text = "(" + map.PlayerX + ", " + map.PlayerY + ")";
            pnlMapInfo.Visible = true;

            if (gfxData.gfx == null)
                gfxData.gfx = this.pnlMapDraw.CreateGraphics();

            gfxData.gfx.Clear(Color.Black);
            gfxData.xoff = 0;
            gfxData.yoff = 0;
            gfxData.elWidth = (pnlMapDraw.Width / 32) + 1;
            gfxData.elHeight = (pnlMapDraw.Height / 32) + 1;

            //habilita o double buffering *apenas* no painel de desenho de mapa
            typeof(Panel).InvokeMember("DoubleBuffered", BindingFlags.SetProperty
                | BindingFlags.Instance | BindingFlags.NonPublic, null,
                pnlMapDraw, new object[] { true });
            vScrollBar1.Maximum = 100; // gfxData.elHeight;
            vScrollBar1.Minimum = 0;

            this.Text = "Sem Título - Criador de Mapas";

            contextMenuStrip1.Enabled = true;

            pnlMapDraw.Refresh();
        }

        private void salvarComoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (SaveFileDialog sfd = new SaveFileDialog())
            {
                sfd.AddExtension = true;
                sfd.Title = "Salvar mapa";
                sfd.CheckPathExists = true;
                sfd.AutoUpgradeEnabled = true;
                sfd.Filter = "Tribalia map files (*.map)|*.map|All files|*.*";
                sfd.FilterIndex = 0;

                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    map.Filename = sfd.FileName;
                }
                else
                {
                    return;
                }
            }

            map.Save();
            this.Text = map.Filename + " - Criador de mapas";
        }

        private void alterarPosDoPlayerParaCáToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int gameX, gameY;
            gameX = ((contextMenuStrip1.Left - pnlMapDraw.Location.X) / 32) + gfxData.xoff;
            gameY = ((contextMenuStrip1.Top - pnlMapDraw.Location.Y) / 32) + gfxData.yoff;

            gameX = (int) Math.Min(gameX, map.Width - 1);
            gameY = (int) Math.Min(gameY, map.Height - 1);

            map.PlayerX = (uint) gameX;
            map.PlayerY = (uint) gameY;

            lblPlayerPos.Text = "(" + map.PlayerX + ", " + map.PlayerY + ")";

            pnlMapDraw.Refresh();

        }

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {
            
        }
    }
}
