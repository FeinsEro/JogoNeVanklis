using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace MapMaker
{
    public class Map
    {
        public int[] Elements { get; private set; }
        private String path;

        private uint offData, offChars;

        public uint Width { get; private set; }
        public uint Height { get; private set; }

        public uint PlayerX { get; set; }
        public uint PlayerY { get; set; }

        public String Filename { get; set; }

        public List<Character> CharacterList { get; set; }

        public Map(String path)
        {
            this.Filename = path;
            this.CharacterList = new List<Character>();
        }

        public Map(uint width, uint height)
        {
            this.Width = width;
            this.Height = height;
            this.Elements = new int[width * height];
            this.Filename = String.Empty;

            this.CharacterList = new List<Character>();
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
            this.Elements = new int[this.Width * this.Height];
            bread.BaseStream.Seek(this.offData, SeekOrigin.Begin);

            for (uint y = 0; y < this.Height; y++)
            {
                for (uint x = 0; x < this.Width; x++)
                {
                    Elements[y * this.Width + x] = bread.ReadInt32();
                }
            }

            /* Lê os characters do mapa */
            bread.BaseStream.Seek(this.offChars, SeekOrigin.Begin);
            uint count = bread.ReadUInt32();

            for (int i = 0; i < count; i++)
            {
                uint elsize = bread.ReadUInt32();
                
                uint tid, objid, xpos, ypos, hp;

                if (elsize >= 20)
                {
                    tid = bread.ReadUInt32();
                    objid = bread.ReadUInt32();
                    xpos = bread.ReadUInt32();
                    ypos = bread.ReadUInt32();
                    hp = bread.ReadUInt32();
                    bread.BaseStream.Seek((elsize - 20), SeekOrigin.Current);
                } else
                {
                    /* Elementos com size < 20 não suportados */
                    throw new InvalidMapException();
                }

                Character ch = new Character((CharacterID)tid);
                ch.ID = objid;
                ch.Location = new System.Drawing.Point((int)xpos, (int)ypos);
                ch.HP = (int)hp;

                this.CharacterList.Add(ch);
            }
            

            bread.Close();


        }

        public void Save()
        {
            StreamWriter sw = new StreamWriter(this.Filename);
            BinaryWriter bw = new BinaryWriter(sw.BaseStream);

            
            /* Magic words */
            bw.Write('W'); bw.Write('E'); bw.Write('R'); bw.Write('L');


            /* Metadados */
            bw.Write(this.Width);       //Largura
            bw.Write(this.Height);      //Altura

            uint mapData = (uint) bw.BaseStream.Position + 16;
            uint charData = mapData + (sizeof(int) * this.Width * this.Height);
            bw.Write(mapData); //Posição para os dados do mapa.
            bw.Write(charData); //Posição para os dados do char (n implementado)
            bw.Write(this.PlayerX); //Pos. X do player
            bw.Write(this.PlayerY); //Pos. Y do player

            for (int i = 0; i < (this.Width * this.Height); i++)
            {
                bw.Write(this.Elements[i]);
            }

            /* Escreve os dados dos chars
                Eles estão nessa ordem:
                [quant. de chars: uint]
                
                E para cada char disponível
                [tamanho do campo: uint (geralmente 20 )]
                [Type][ID][XPos][YPos][HP] (todos uints)

            */
            bw.Write((uint)CharacterList.Count);
            
            foreach(Character c in this.CharacterList)
            {
                bw.Write((uint)20);
                bw.Write(c.TypeData.TypeID);
                bw.Write(c.ID);
                bw.Write((uint)c.Location.X);
                bw.Write((uint)c.Location.Y);
                bw.Write((uint)c.HP);
            }

            bw.Flush();                                   
            bw.Close();                                   
        }                                                

    }

    /// <summary>
    /// Thrown when you have a invalid map archive.
    /// </summary>
    class InvalidMapException : Exception
    {
        
    }
}
