/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.morpheus.doisdemonios.graphics;

import com.morpheus.doisdemonios.util.Vector2f;
import static org.lwjgl.glfw.GLFW.*;

/**
 *
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class InputManager {
    private static InputManager im = null;
    public static InputManager getInstance() {
        if (im == null) im = new InputManager();
        
        return im;
    }
    
    private ObjectRenderer or;
    public void setObjectRenderer(ObjectRenderer or) {
        this.or = or;
    }
    
    private float frameTime;
    public void setFrameTime(float delta) {
        this.frameTime = delta;
    }
    
    public void ProcessInput(int glfwKey, int glfwScanCode, int action, int mods) {
        if (action != GLFW_RELEASE) {
            switch (glfwKey) {
                case GLFW_KEY_W:
                    or.getCameraPos().add(new Vector2f(0, 0.25f * frameTime), null);
                    break;
                case GLFW_KEY_S:
                    or.getCameraPos().add(new Vector2f(0, -0.25f * frameTime ), null);                    
                    break;
                case GLFW_KEY_A:
                    or.getCameraPos().add(new Vector2f(-0.25f * frameTime, 0), null);
                    break;
                case GLFW_KEY_D:
                    or.getCameraPos().add(new Vector2f(0.25f * frameTime, 0), null);                    
                    break;
            }
        }
        
    }
}
