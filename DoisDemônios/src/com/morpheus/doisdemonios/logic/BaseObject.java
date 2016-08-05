package com.morpheus.doisdemonios.logic;

import com.morpheus.doisdemonios.util.Vector2f;

/**
 *  This class will host the BaseObjec type
 * 
 *  The base object is the most basic type object in the game.
 *  It will have only enough information to render it and to
 *  kill it, such as life, image and position.
 * 
 *  This is primarily used for basic scenario objects (trees, tables, peaceful
 *  animals)
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class BaseObject implements IBaseObject {
    
    protected Vector2f position;
    protected double life;
    protected ObjectType type;

    protected final int ID;
    protected String name;
    
    protected Vector2f size;

    public BaseObject(Vector2f position, double life, String name,
            Vector2f size) {
        this.position = position;
        this.life = life;
        this.ID = ObjectManager.getInstance().count();
        this.name = name;
        this.size = size;
        
        ObjectManager.getInstance().add(this);
    }
    
    public BaseObject(Vector2f position, double life, int ID, String name,
            Vector2f size) {
        this.position = position;
        this.life = life;
        this.ID = ID;
        this.name = name;
        this.size = size;
        
        ObjectManager.getInstance().add(this);
    }

    @Override
    public Vector2f getPosition() {
        return position;
    }

    @Override
    public double getLife() {
        return life;
    }

    @Override
    public int getID() {
        return ID;
    }

    @Override
    public String getName() {
        return name;
    }
    
    @Override
    public ObjectType getType() {
        return type;
    }
    
    @Override
    public Vector2f getSize() {
        return this.size;
    }
    
    @Override
    public void setPosition(Vector2f position) {
        this.position = position;
    }

    @Override
    public void setLife(double life) {
        this.life = life;
    }

    @Override
    public void setName(String name) {
        this.name = name;
    } 
    
    @Override
    public void run() {}

    @Override
    protected void finalize() throws Throwable {
        ObjectManager.getInstance().remove(this);
        super.finalize(); 
    }

    
}
