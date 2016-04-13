using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace MapMaker
{
    public class Map
    {
        private int[] elements;
        private String path;

        private uint offData, offChars;

        public uint Width { get; private set; }
        public uint Height { get; private set; }

        public uint PlayerX { get; set; }
        public uint PlayerY { get; set; }

        public String Filename { get; private set; }

        public Map(String path)
        {
            this.Filename = path;
        }

        public void Open()
        {
            StreamReader sr = new StreamReader(this.Filename);
            BinaryReader bread = new BinaryReader(sr.BaseStream);

            /* Verifica o magic number */
           


            byte[] magic = bread.ReadBytes(4);
            if (magic[0] != 'W' || magic[1] != 'E' ||
                magic[2] != 'R' || magic[3] != 'L')
            {
                throw new InvalidMapException();
            }

            /* Lê os metadados */

            this.Width = bread.ReadUInt32();
            this.Height = bread.ReadUInt32();
            this.offData = bread.ReadUInt32();
            this.offChars = bread.ReadUInt32();
            this.PlayerX = bread.ReadUInt32();
            this.PlayerY = bread.ReadUInt32();

            if (this.Width == 0)
                throw new InvalidMapException();

            if (this.Height == 0)
                throw new InvalidMapException();
            
            /* Lê os dados do mapa */
            this.elements = new int[this.Width * this.Height];
            bread.BaseStream.Seek(this.offData, SeekOrigin.Begin);

            for (uint y = 0; y < this.Height; y++)
            {
                for (uint x = 0; x < this.Width; x++)
                {
                    elements[y * this.Width + x] = bread.ReadInt32();
                }
            }


        }

    }

    /// <summary>
    /// Thrown when you have a invalid map archive.
    /// </summary>
    class InvalidMapException : Exception
    {
        
    }
}
