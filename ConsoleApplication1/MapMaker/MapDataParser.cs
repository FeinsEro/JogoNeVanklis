using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;

namespace MapMaker
{
    /* Faz o parsing dos sprites de terreno do mapdata.png */
    public class MapDataParser
    {
        private String path;
        private Bitmap bmp = null;

        const int elemSize = 32;

        public int ItemCount { get; private set; }

        /// <summary>
        /// Abre o arquivo mapdata.png
        /// </summary>
        public void Open()
        {
            path = System.IO.Path.Combine(Properties.Settings.Default.demonsPath,
                @"game\mapdata.png");

            bmp = new Bitmap(path);
            
        }

        private Bitmap SliceImage(int x, int y)
        {
            if (bmp != null)
            {
                Bitmap newbmp = new Bitmap(bmp, new Size(elemSize, elemSize));
                using (Graphics gr = Graphics.FromImage(newbmp))
                {
                    gr.DrawImage(bmp, new Rectangle(0, 0, elemSize, elemSize),
                        new Rectangle(x, y, elemSize, elemSize),
                        GraphicsUnit.Pixel);
                    return newbmp;
                }
            }

            throw new NullReferenceException();
        }


        public Bitmap GetImageFromIndex(int index)
        {
            int yPos = (index / bmp.Width) * elemSize;
            int xPos = (index % bmp.Width) * elemSize;

            if (yPos >= bmp.Height) return null;

            Bitmap _bmp = this.SliceImage(xPos, yPos);
            
            return _bmp;
        }

    }
}
