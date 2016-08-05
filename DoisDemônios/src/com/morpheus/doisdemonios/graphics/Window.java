package com.morpheus.doisdemonios.graphics;

import org.lwjgl.glfw.GLFW;
import static org.lwjgl.system.MemoryUtil.NULL;

/**
 *  Window creation class
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class Window {
    
    private long windowHnd;
    private int width, height;

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }
    
    public Window(int w, int h) {
        
        if (!GLFW.glfwInit()) {
            throw new WindowException("Unable to start GLFW");
        }
        
        /* Create the window */
        windowHnd = GLFW.glfwCreateWindow(w, h, "Dois Demônios", 0, 0);
        if (windowHnd == NULL) {
            throw new WindowException("Window creation error");
        }
        
        /* Set the opengl context to this window */
        GLFW.glfwMakeContextCurrent(windowHnd);
        GLFW.glfwSwapInterval(1);
        
        GLFW.glfwSetKeyCallback(windowHnd, (window, key, scancode, action, mods) -> {
			if ( key == GLFW.GLFW_KEY_ESCAPE && action == GLFW.GLFW_RELEASE )
				GLFW.glfwSetWindowShouldClose(window, true); // We will detect this in our rendering loop
		});
        
        width = w;
        height = h;
    }
    
    public void show() {
        if (windowHnd != NULL) {
            GLFW.glfwShowWindow(windowHnd);
        }
    }
    
    /***
     * Close the window
     */
    public void close() {
        GLFW.glfwDestroyWindow(windowHnd);
        GLFW.glfwTerminate();
    }
    
    /***
     * Update the window with the rendered content
     */
    public void update() {
        
        GLFW.glfwSwapBuffers(windowHnd);
    }
    
    /***
     * Check if the user has ordened the window closing
     * @return True if yes, false if no
     */
    public boolean checkIfShouldClose() {
        return GLFW.glfwWindowShouldClose(windowHnd);
    }
    
    public class WindowException extends RuntimeException
    {
        public WindowException(String message) {
            super(message);
        }   
    }
}
