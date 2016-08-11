package com.morpheus.doisdemonios.graphics;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL13;

/**
 *  Spritesheet manager.
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class SpriteManager {
    private static SpriteManager si = null;
    public static SpriteManager getInstance() {
        if (si == null) si = new SpriteManager();
        
        return si;
    }
    
    public void init() {
        GL11.glEnable(GL11.GL_TEXTURE_2D);

    }
    
    private List<SpriteSheet> sprites = new ArrayList<>();
    public void updateAll() {
        for (SpriteSheet s : sprites) {
            s.update();
        }
    }

    public SpriteSheet OpenFromFile(String path, int framew, int frameh) throws IOException {
        BufferedImage bi = ImageIO.read(new File(path));
        
        int bsize = bi.getWidth() * bi.getHeight() * 3;
        
        System.out.println("[SpriteManager] Opening image " + path + ", size " + bi.getWidth()
            + "x" + bi.getHeight() + ", " + bsize + " bytes");
        
        ByteBuffer dtest = BufferUtils.createByteBuffer(bsize);
        
        /* Copy the image from the BufferedImage to the texture buffer. */
        for (int y = bi.getHeight()-1; y >= 0; y--) {
            for (int x = 0; x < bi.getWidth(); x++) {
                int[] colors = new int[4];
                bi.getRaster().getPixel(x, y, colors);
                dtest.put((byte)(colors[0]));
                dtest.put((byte)(colors[1]));
                dtest.put((byte)(colors[2]));
            }
        }
               
        dtest.flip();        
        
        SpriteSheet s = new SpriteSheet(bi.getWidth(), bi.getHeight(), dtest, 
                framew, frameh);
        sprites.add(s);
        return s;
    }   
    
}
