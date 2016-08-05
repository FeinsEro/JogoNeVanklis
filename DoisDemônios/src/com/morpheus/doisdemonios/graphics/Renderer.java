package com.morpheus.doisdemonios.graphics;

import org.lwjgl.opengl.GL;
import static org.lwjgl.opengl.GL11.*;

/**
 * Rendering class
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class Renderer {
    
    private Window _win;
    public Renderer(Window win) {
        _win = win;
        
        GL.createCapabilities();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        glViewport(0, 0, win.getWidth(), win.getHeight());
        
        /* Set projection matrix */
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,1,0,1,0,1);                   
    }
    
    /***
     * Render the scene
     * @return True if all rendered ok, false otherwise
     */
    public boolean Render() {
        if (_win.checkIfShouldClose()) return false;
                
        _win.update();
        return true;        
    }
    
}
