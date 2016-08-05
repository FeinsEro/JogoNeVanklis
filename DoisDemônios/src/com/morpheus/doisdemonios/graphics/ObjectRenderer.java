/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.morpheus.doisdemonios.graphics;

import com.morpheus.doisdemonios.logic.IBaseObject;
import com.morpheus.doisdemonios.util.Vector2f;
import java.util.ArrayList;
import java.util.List;
import org.lwjgl.opengl.GL11;
import static org.lwjgl.opengl.GL11.GL_COLOR_BUFFER_BIT;
import static org.lwjgl.opengl.GL11.GL_TEXTURE_2D;
import static org.lwjgl.opengl.GL11.glClear;
import static org.lwjgl.opengl.GL11.glEnable;

/**
 * Object rendering class.
 * This class will take care only of rendering part.
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class ObjectRenderer {
    private List<ObjectRenderData> objs;
    
    private Vector2f cameraPos;
    public final int SCREEN_TILE_WIDTH = 30;
    public final int SCREEN_TILE_HEIGHT = 20;
    
    public ObjectRenderer(Vector2f initialPos) {
        objs = new ArrayList<>();
        this.cameraPos = initialPos;
    }  
    
    public void addToRender(IBaseObject o) {
        Vector2f pos, size;
        pos = new Vector2f(o.getPosition().getX(), o.getPosition().getY());
        size = new Vector2f(o.getSize().getX(), o.getSize().getY());
        
        pos.subtract(cameraPos, null);
        size = new Vector2f(size.getX() / SCREEN_TILE_WIDTH, 
                size.getY() / SCREEN_TILE_HEIGHT);
        
        ObjectRenderData ord = new ObjectRenderData(pos, size, o, o.getSprite());
        objs.add(ord);
    }
    
    public void update() {
         for (ObjectRenderData ord : objs) {  
             IBaseObject ibo = ord.getObject();
             ord.getPosition()[0] = ibo.getPosition().getX() - cameraPos.getX();
             ord.getPosition()[1] = ibo.getPosition().getY() - cameraPos.getY();
             
         }
    }
    
    public void setCameraPos(Vector2f cam) {
        this.cameraPos = cam;
    }
    
    public Vector2f getCameraPos() {
        return this.cameraPos;
    }
    
    public void render() {
        GL11.glMatrixMode(GL11.GL_MODELVIEW);
        GL11.glLoadIdentity();
        
        glClear(GL_COLOR_BUFFER_BIT);

        for (ObjectRenderData ord : objs) {
            ord.getSprite().bindTexture();
            float[] frame = ord.getSprite().getCoordinates();
            float[] pos = ord.getPosition();
            float[] size = ord.getSize();
            
            GL11.glBegin(GL11.GL_QUADS);
                GL11.glTexCoord2f(frame[0], frame[1]);
                GL11.glVertex2f(pos[0], pos[1]);
                
                GL11.glTexCoord2f(frame[0]+frame[2], frame[1]);                
                GL11.glVertex2f(pos[0]+size[0], pos[1]);
                
                GL11.glTexCoord2f(frame[0]+frame[2], frame[1]+frame[3]);                                
                GL11.glVertex2f(pos[0]+size[0], pos[1]+size[1]);
                
                GL11.glTexCoord2f(frame[0]+frame[2], frame[1]);                
                GL11.glVertex2f(pos[0], pos[1]+size[1]);
            GL11.glEnd();
        }
        
        GL11.glFlush();
    }
}
