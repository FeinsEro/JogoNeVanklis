/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.morpheus.doisdemonios.graphics;

import com.morpheus.doisdemonios.Player;
import com.morpheus.doisdemonios.util.Vector2f;
import java.util.ArrayList;
import java.util.List;
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
    private List<InputReceivable> input_receivers = new ArrayList<>();
    public void setObjectRenderer(ObjectRenderer or) {
        this.or = or;
    }
    
    public void AddInputReceiver(InputReceivable r) {
        input_receivers.add(r);
    }
    
    public void RemoveInputReceiver(InputReceivable r) {
        input_receivers.remove(r);
    }
    
    private float frameTime;
    public void setFrameTime(float delta) {
        this.frameTime = delta;
    }
    
    public void ProcessInput(int glfwKey, int glfwScanCode, int action, int mods) {
        
        for (InputReceivable r : input_receivers) {
            r.ReceiveInput(glfwKey, glfwScanCode, action, mods, frameTime);
        }
        
    }

    public boolean ExistsInputReceiver(InputReceivable r) {
        if (input_receivers.stream().anyMatch((i) -> (i.equals(r)))) {
            return true;
        }
        
        return false;
    }
}
