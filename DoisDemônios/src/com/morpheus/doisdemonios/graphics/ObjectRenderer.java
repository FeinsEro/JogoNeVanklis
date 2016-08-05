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
import static org.lwjgl.opengl.GL11.glClear;

/**
 * Object rendering class.
 * This class will take care only of rendering part.
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class ObjectRenderer {
    private List<ObjectRenderData> objs;
    
    private Vector2f initialPos;
    public final int SCREEN_TILE_WIDTH = 30;
    public final int SCREEN_TILE_HEIGHT = 20;
    
    public ObjectRenderer(Vector2f initialPos) {
        objs = new ArrayList<>();
        this.initialPos = initialPos;
    }  
    
    public void addToRender(IBaseObject o) {
        Vector2f pos, size;
        pos = new Vector2f(o.getPosition().getX(), o.getPosition().getY());
        size = new Vector2f(o.getSize().getX(), o.getSize().getY());
        
        pos.subtract(initialPos, null);
        size = new Vector2f(size.getX() / SCREEN_TILE_WIDTH, 
                size.getY() / SCREEN_TILE_WIDTH);
        
        ObjectRenderData ord = new ObjectRenderData(pos, size, o, 0);
        objs.add(ord);
    }
    
    public void render() {
        GL11.glMatrixMode(GL11.GL_MODELVIEW);
        GL11.glLoadIdentity();

        glClear(GL_COLOR_BUFFER_BIT);

        GL11.glColor3f(1.0f, 1.0f, 1.0f);
        for (ObjectRenderData ord : objs) {
            GL11.glBegin(GL11.GL_QUADS);
                GL11.glVertex2f(ord.getPosition()[0], ord.getPosition()[1] + ord.getSize()[1]);
                GL11.glVertex2f(ord.getPosition()[0], ord.getPosition()[1]);
                GL11.glVertex2f(ord.getPosition()[0] + ord.getSize()[0], ord.getPosition()[1]);
                GL11.glVertex2f(ord.getPosition()[0] + ord.getSize()[0], ord.getPosition()[1] + ord.getSize()[1]);
            GL11.glEnd();
        }
        
        GL11.glFlush();
    }
}
