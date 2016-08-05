/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.morpheus.doisdemonios;

import com.morpheus.doisdemonios.graphics.InputManager;
import com.morpheus.doisdemonios.graphics.ObjectRenderer;
import com.morpheus.doisdemonios.graphics.Window;
import com.morpheus.doisdemonios.graphics.Renderer;
import com.morpheus.doisdemonios.graphics.SpriteManager;
import com.morpheus.doisdemonios.logic.ObjectManager;
import com.morpheus.doisdemonios.logic.objects.Dann;
import com.morpheus.doisdemonios.util.Vector2f;
import java.io.IOException;
import org.lwjgl.glfw.GLFW;

/**
 *
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class DoisDemonios {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
       System.out.println("== [DOIS DEMONIOS] == ");
       System.out.println("--> Creating window...");
       Window win = null;
       Renderer renderer = null;
       ObjectRenderer or = null;
          
       try {
            win = new Window(640, 480);
            renderer = new Renderer(win);
            or = new ObjectRenderer(new Vector2f(0.6f, 0.0f));
       } catch (Window.WindowException e) {
            System.err.println("Graphical error while starting: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
       } catch (Exception e) {
            System.err.println("Error while starting: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
       }
       
       win.show();
       SpriteManager.getInstance().init();
       ObjectManager.getInstance().setObjectRenderer(or);
       InputManager.getInstance().setObjectRenderer(or);
       
       try {
       Dann d = new Dann(new Vector2f(0.8f, 0.6f));
       } catch (IOException ex) {
           System.err.println("Error: I/O error: " + ex.getMessage());
           ex.printStackTrace();
           System.exit(1);
       } catch (Exception ex) {
           System.err.println("Error" + ex.getMessage());
           ex.printStackTrace();
           System.exit(1);
       }
       boolean do_render = false;
       
       float begin = 0.0f;       
       float end = 0.0f;       
       do {           
           ObjectManager.getInstance().runAll();
           
           SpriteManager.getInstance().updateAll();
           or.update();           
           or.render();
           do_render = renderer.Render();
           GLFW.glfwPollEvents();
           
           end = (float)GLFW.glfwGetTime();

           System.out.println("Frame time: " + (end-begin) + " ms");           
           InputManager.getInstance().setFrameTime(end-begin);

           begin = end;
           
       } while (do_render);
       
       win.close();   
             
    }
    
}
