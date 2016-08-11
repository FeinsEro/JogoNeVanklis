package com.morpheus.doisdemonios.graphics;

/**
 * Interface for all classes that can receive input
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public interface InputReceivable {
    
    public void ReceiveInput(int glfwKey, int glfwScanCode, 
            int action, int mods, float frameTime);
    
}
