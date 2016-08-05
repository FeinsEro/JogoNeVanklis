package com.morpheus.doisdemonios.logic;

import com.morpheus.doisdemonios.util.Vector2f;

/**
 * This is the dynamic object class
 * 
 * A dynamic object implement things such as attack (magical or pure), defense
 * (magical or pure), spells... dialog and a function to be runned every loop
 * 
 * This is primarily used for mobs and NPCs
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class DynamicObject implements IBaseObject {
    
    // Base values (for the IBaseObject)
    protected Vector2f position;
    protected double life;
    protected ObjectType type;
    protected Vector2f size;

    protected final int ID;
    protected String name;

    // Complex values
    protected double magicalAttack, pureAttack;
    protected double magicalDefense, pureDefense;
      
    public DynamicObject(Vector2f position, double life, ObjectType type, 
            String name, Vector2f size) {
        this.position = position;
        this.life = life;
        this.type = type;
        this.name = name;
        this.size = size;
        this.ID = ObjectManager.getInstance().count();
        ObjectManager.getInstance().add(this);

    }
    
    public DynamicObject(Vector2f position, double life, ObjectType type, 
            int ID, String name, Vector2f size) {
        this.position = position;
        this.life = life;
        this.type = type;
        this.ID = ID;
        this.name = name;
        this.size = size;
        ObjectManager.getInstance().add(this);
        
    }
    
    
    public DynamicObject(Vector2f position, double life, ObjectType type, 
            String name, Vector2f size, double magicalAttack, double pureAttack, 
            double magicalDefense, double pureDefense) {
        this.position = position;
        this.life = life;
        this.type = type;
        this.ID = ObjectManager.getInstance().count();
        this.name = name;
        this.size = size;
        this.magicalAttack = magicalAttack;
        this.pureAttack = pureAttack;
        this.magicalDefense = magicalDefense;
        this.pureDefense = pureDefense;
        ObjectManager.getInstance().add(this);

    }
    
    public DynamicObject(Vector2f position, double life, ObjectType type, 
            int ID, String name, Vector2f size, double magicalAttack, 
            double pureAttack, double magicalDefense, double pureDefense) {
        this.position = position;
        this.life = life;
        this.type = type;
        this.ID = ID;
        this.name = name;
        this.size = size;
        this.magicalAttack = magicalAttack;
        this.pureAttack = pureAttack;
        this.magicalDefense = magicalDefense;
        this.pureDefense = pureDefense;
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
    public ObjectType getType() {
        return type;
    }

    @Override
    public int getID() {
        return ID;
    }

    @Override
    public String getName() {
        return name;
    }

    public double getMagicalAttack() {
        return magicalAttack;
    }

    public double getPureAttack() {
        return pureAttack;
    }

    public double getMagicalDefense() {
        return magicalDefense;
    }

    public double getPureDefense() {
        return pureDefense;
    }   

    @Override
    public Vector2f getSize() {
        return size;
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
    public void run() {
        
    }

    @Override
    protected void finalize() throws Throwable {
        ObjectManager.getInstance().remove(this);
        super.finalize(); 
    }
    
}
