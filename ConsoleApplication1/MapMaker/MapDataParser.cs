using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Threading.Tasks;

namespace MapMaker
{
    /* Faz o parsing dos sprites de terreno do mapdata.png */
    public class MapDataParser
    {
        public enum MapTiles
        {
            TILE_GRASS = 0,
            TILE_WATER = 1,
            TILE_DIRT = 2,
                
        }

        private String path;
        private Bitmap bmp = null;

        const int elemSize = 32;
        private Bitmap[] bmpCache;

        public int ItemCount { get; private set; }

        /// <summary>
        /// Abre o arquivo mapdata.png
        /// </summary>
        public void Open()
        {
            path = System.IO.Path.Combine(Properties.Settings.Default.demonsPath,
                @"game\mapdata.png");

            bmp = new Bitmap(path);

            int cachesize = Enum.GetValues(typeof(MapTiles)).Length;
            bmpCache = new Bitmap[cachesize];

            //Coloca os blocos em cache.
            for (int i = 0; i < cachesize; i++) 
            {
                bmpCache[i] = GetImageFromIndex(i);
            }
            
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
            if (bmpCache[index] != null)
            {
                return bmpCache[index];
            }

            int yPos = (index / bmp.Width) * elemSize;
            int xPos = (index % bmp.Width) * elemSize;

            if (yPos >= bmp.Height) return null;

           Bitmap _bmp = this.SliceImage(xPos, yPos);
            
            return _bmp;
        }

    }
}
