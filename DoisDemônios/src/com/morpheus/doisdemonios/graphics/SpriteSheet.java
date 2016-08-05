package com.morpheus.doisdemonios.graphics;

import com.morpheus.doisdemonios.util.Vector2f;
import java.nio.ByteBuffer;
import org.lwjgl.opengl.GL11;;

/**
 * Spritesheet representant
 * 
 * This represents a complete spritesheet.
 * 
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class SpriteSheet {
    private Vector2f uv;
    private Vector2f frame_size;
    
    private int frame = 0, lastframe = 0;
    private int loopend = 0, loopstart, frame_count;
    private int frame_width, frame_height;
    private int tex_handler = 0;
    
    /***
     * Creates the spritesheet
     * @param imagew The sheet width
     * @param imageh The sheet height
     * @param GLformat The image format (GL_RGB for rgb, GL_BGR for bgr)
     * @param data The image binary data
     * @param framew The sprite/frame width
     * @param frameh The sprite/frame height
     */
    public SpriteSheet(int imagew, int imageh, ByteBuffer data, int framew, int frameh) {
        /* Setup a texture for the spritesheet */
        tex_handler = GL11.glGenTextures();
        GL11.glBindTexture(GL11.GL_TEXTURE_2D, tex_handler);
        
        GL11.glPixelStorei(GL11.GL_UNPACK_ALIGNMENT, 1);
        GL11.glTexImage2D(GL11.GL_TEXTURE_2D, 0, GL11.GL_RGB, imagew, imageh, 0, 
            GL11.GL_RGB, GL11.GL_UNSIGNED_BYTE, data);
                
        GL11.glTexParameteri(GL11.GL_TEXTURE_2D, GL11.GL_TEXTURE_MAG_FILTER, GL11.GL_LINEAR);
        GL11.glTexParameteri(GL11.GL_TEXTURE_2D, GL11.GL_TEXTURE_MIN_FILTER, GL11.GL_LINEAR);
        
        System.out.println("[SpriteSheet] Added spritesheet " + imagew + "x" + imageh + ","
                + "id " + tex_handler);
        
        /* Ensure proper frame count conversion */
        
        // Set frame size for OpenGL
        frame_size = new Vector2f((float)framew / (float)imagew, 
                (float)frameh / (float)imageh);
        
        // Set it for the engine
        frame_width = (int) Math.ceil(imagew / (double)framew);
        frame_height = (int) Math.ceil(imageh / (double)frameh);
        
        System.out.println("[SpriteSheet] Sheet " + tex_handler + "has " +
                frame_width + "x" + frame_height + " textures");
        
        // Set the loop points
        loopstart = 0;
        loopend = frame_width * frame_height;
        
        lastframe = frame;
        frame_count = loopend;
    }
    
    public int getFrame() { return frame; }
    public void nextFrame() {
        if (frame > loopend) {
            frame = loopstart;
        } else {
            frame++;
        }
    }
    public void prevFrame() {
        if (frame < loopstart) {
            frame = loopend-1;
        } else {
            frame = loopstart;
        }
    }
    
    public void setLoopPoints(int start, int end) {
        this.loopstart = start;
        this.loopend = end;
    }
    
    public int getLoopStart() { return loopstart; }
    public int getLoopEnd() { return loopend; }
    
    /***
     * Update UV frame coordinates
     */
    public void update() {
        if (lastframe != frame || frame == 0) {
            int y = frame / frame_width;
            int x = frame % frame_width;
        
            this.uv = new Vector2f(frame_size.getX() * x, this.frame_size.getY() * y);
            lastframe = frame;
        }
    }
    
    /***
     * Get all coordinates for the frame
     * @return An array, where indices 0 and 1 contain the UV coords for the frame
     * and indices 2 and 3 contain the frame size, in normalized device coord space
     */
    public float[] getCoordinates() {
        
        //fb.put(uv.getNative());
        //fb.put(frame_size.getNative());
        return new float[]{uv.getX(), uv.getY(), frame_size.getX(), frame_size.getY()};
    }
    
    
    public void bindTexture() {
        GL11.glBindTexture(GL11.GL_TEXTURE_2D, tex_handler);
    }
    
}
