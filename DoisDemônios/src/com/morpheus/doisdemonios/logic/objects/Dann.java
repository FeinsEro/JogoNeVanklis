/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.morpheus.doisdemonios.logic.objects;

import com.morpheus.doisdemonios.graphics.SpriteManager;
import com.morpheus.doisdemonios.logic.DynamicObject;
import com.morpheus.doisdemonios.logic.ObjectType;
import com.morpheus.doisdemonios.util.Vector2f;
import java.io.IOException;

/**
 * Base class for Dann, the main char of the game
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class Dann extends DynamicObject {
        
    public Dann(Vector2f position) throws IOException {
        super(position, 1000, ObjectType.TDann, "Dann", new Vector2f(2,2), 
                1.0, 0.8, 1.2, 0.9, 
                SpriteManager.getInstance().OpenFromFile("assets/dann.png", 32, 32));
        
    }
    
    public Dann(Vector2f position, int ID) throws IOException {
        super(position, 1000, ObjectType.TDann, ID, "Dann", new Vector2f(2,2), 
                1.0, 0.8, 1.2, 0.9,
                SpriteManager.getInstance().OpenFromFile("assets/dann.png", 32, 32));

    }

    @Override
    public void run() {
        super.run(); //To change body of generated methods, choose Tools | Templates.
    }
    
    
    
}
