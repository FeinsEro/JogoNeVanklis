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
        BufferedImage im = null;
        im = ImageIO.read(new File(path));
        
        System.out.println("[SpriteManager] Opening file " + path + ", "
                + "size " + im.getWidth() + "x" + im.getHeight());
        
        ByteBuffer dtest = BufferUtils.createByteBuffer(64*64);
                                
        for (int i = 0; i < 64*64; i++) {
            dtest.put((byte)0x30);
        }
        
        dtest.flip();        
        
        SpriteSheet s = new SpriteSheet(64, 64, dtest, 16, 16);
        sprites.add(s);
        return s;
    }   
    
}
