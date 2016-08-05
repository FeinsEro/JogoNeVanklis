/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.morpheus.doisdemonios.graphics;

import com.morpheus.doisdemonios.logic.IBaseObject;
import com.morpheus.doisdemonios.util.Vector2f;

/**
 * Base data needed for object rendering.
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class ObjectRenderData {
    /* OpenGL coordinates:
                1.0
            -----------------
            |               |
            |               |
        -1.0|               | 1.0
            |               |
            |               |
            |               |
            -----------------
                -1.0
        
    */
    
    /* index 0: x, index 1: y, in OpenGL coordinates */
    private float[] position;
    
    /* index 0: width, index 1: height, proportionally, between 0 and 1. */
    private float[] size;
    
    /* OpenGL texture for the object */
    private SpriteSheet sprite;
    
    /* Base object, for mere identification */
    private IBaseObject object;

    public ObjectRenderData(Vector2f pos, Vector2f size, IBaseObject object, 
            SpriteSheet sprite) {
        this.position = pos.getNative();
        this.size = size.getNative();
        this.sprite = sprite;
        this.object = object;
    }

    public float[] getPosition() {
        return position;
    }

    public float[] getSize() {
        return size;
    }

    public SpriteSheet getSprite() {
        return sprite;
    }

    public IBaseObject getObject() {
        return object;
    }

    public void setPosition(float[] position) {
        this.position = position;
    }

    public void setSize(float[] size) {
        this.size = size;
    }

    public void setSprite(SpriteSheet s) {
        this.sprite = s;
    }
    
}
