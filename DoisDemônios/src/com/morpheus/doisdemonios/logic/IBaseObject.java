package com.morpheus.doisdemonios.logic;

import com.morpheus.doisdemonios.util.Vector2f;

/**
 * Interface for base objects.
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public interface IBaseObject {
    
    public Vector2f getPosition();
    public double getLife();
    public int getID();
    public String getName();
    public ObjectType getType();
    
    
    /*  Size, in tiles. Check SCREEN_TILE_WIDTH and SCREEN_TILE_HEIGHT to
        see how much tiles you'll have in the screen */
    public Vector2f getSize();

    public void setPosition(Vector2f position);
    public void setLife(double life);
    public void setName(String name);
    
    public void run();
    
}
