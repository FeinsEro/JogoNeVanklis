package com.morpheus.doisdemonios;

import com.morpheus.doisdemonios.graphics.InputManager;
import com.morpheus.doisdemonios.graphics.InputReceivable;
import com.morpheus.doisdemonios.logic.DynamicObject;
import com.morpheus.doisdemonios.util.Vector2f;
import org.lwjgl.glfw.GLFW;

/**
 * Player support class
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class Player implements InputReceivable {
   
    private DynamicObject defaultObject;

    public DynamicObject getDefaultObject() {
        return defaultObject;
    }

    public void setDefaultObject(DynamicObject defaultObject) {
        this.defaultObject = defaultObject;
    }
    
    /***
     * Creates a new player
     * @param playerDefaultObject The object that the player will control
     */
    public Player(DynamicObject playerDefaultObject) {
        this.defaultObject = playerDefaultObject;
        if (!InputManager.getInstance().ExistsInputReceiver(this)) {
            InputManager.getInstance().AddInputReceiver(this);
        }
    }
    
    private static Player p = null;
    public static Player GetInstance() {
        if (p == null) p = new Player(null);
        
        return p;
    }

    @Override
    public void ReceiveInput(int glfwKey, int glfwScanCode, int action, int mods, float frameTime) {
        Vector2f moveVector = new Vector2f(0, 0);
        if (action != GLFW.GLFW_RELEASE) {
            switch (glfwKey) {
                case GLFW.GLFW_KEY_W:
                    moveVector = new Vector2f(0.0f, 0.1f*frameTime);
                    break;
                case GLFW.GLFW_KEY_S:
                    moveVector = new Vector2f(0.0f, -0.1f*frameTime);                    
                    break;
                case GLFW.GLFW_KEY_A:
                    moveVector = new Vector2f(-0.1f*frameTime, 0.0f);                                        
                    break;
                case GLFW.GLFW_KEY_D:
                    moveVector = new Vector2f(0.1f*frameTime, 0.0f);                                                            
                    break;
            }
        }
        moveVector.add(defaultObject.getPosition(), null);
        defaultObject.setPosition(moveVector);

    }
       
    
}
