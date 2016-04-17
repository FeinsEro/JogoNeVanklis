using System;
using System.Collections.Generic;
using System.Linq;
using System.Drawing;
using System.Runtime.Serialization;

namespace MapMaker
{
    public enum CharacterID {
       Player = 0,
       Tree = 1,
    }


    public class Character
    {

        public CharacterType TypeData { get; set; }
        public uint ID { get; set; }
        public Point Location { get; set; }
        public int HP { get; set; }

        public Character(CharacterType typeData)
        {
            this.TypeData = typeData;
        }

        public Character(CharacterID id)
        {
            this.TypeData = CharacterType.GetTypeByID(id);
        }
    }



    public struct CharacterType
    {
        public uint TypeID;
        public string SpritePath;
        public Size SpriteElementSize;
        public float SpriteScale;
        public Image CharacterBitmap;

        public CharacterType(uint tid, String path, float scale = 1.0f, int spritew = 32, int spriteh = 32)
        {
            this.TypeID = tid;
            this.SpritePath = path;
            this.SpriteScale = scale;
            this.SpriteElementSize = new Size(spritew, spriteh);

            /* Desenha o primeiro frame do sprite */
            Image img = Image.FromFile(this.SpritePath);

            this.CharacterBitmap = new Bitmap((int)(spritew * scale), (int)(spriteh * scale));
            Graphics gfx = Graphics.FromImage(this.CharacterBitmap);
            gfx.DrawImage(img, new Rectangle(0, 0, (int)(spritew * scale), (int)(spriteh * scale)), 
                new Rectangle(0, 0, spritew, spriteh), GraphicsUnit.Pixel);
            
        }

        public static CharacterType GetTypeByID(CharacterID typeid)
        {
            String path = Properties.Settings.Default.demonsPath;
            switch (typeid)
            {
                case CharacterID.Player:
                    return new CharacterType((int)CharacterID.Player,
                        System.IO.Path.Combine(path, @"characters\dann.png"), 1.5f);

                case CharacterID.Tree:
                    return new CharacterType((int)CharacterID.Tree,
                        System.IO.Path.Combine(path, @"characters\arvore1.png"), 1, 60, 80);

                default:
                    throw new InvalidCharacterTypeException();
                        
            }
        }

    };


    [Serializable]
    public class InvalidCharacterTypeException : Exception
    {
        public InvalidCharacterTypeException()
        {
        }

        public InvalidCharacterTypeException(string message) : base(message)
        {
        }

        public InvalidCharacterTypeException(string message, Exception innerException) : base(message, innerException)
        {
        }

        protected InvalidCharacterTypeException(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }
    }
}
