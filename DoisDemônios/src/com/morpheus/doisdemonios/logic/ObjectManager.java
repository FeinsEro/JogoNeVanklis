package com.morpheus.doisdemonios.logic;

import java.util.ArrayList;
import java.util.List;

/**
 * The object manager iterates and cares for every object.
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class ObjectManager {
    
    private final List<IBaseObject> objects;
    
    public ObjectManager() {
        objects = new ArrayList<>();
    }    
     
    public void add(IBaseObject o) {
        objects.add(o);
        System.out.println("[ObjectManager] Added object " + o.getName() + ", "
                + "ID " + o.getID() + ", life " + o.getLife()
                + ", pos" + o.getPosition());
    }
    
    public void remove(IBaseObject o) {
        objects.remove(o);
        System.out.println("[ObjectManager] Removed object " + o.getName() + ", "
                + "ID " + o.getID() + ", life " + o.getLife()
                + ", pos" + o.getPosition());
    }
    
    public int count() {
        return objects.size();
    }
    
    public void runAll() {
        
    }   
    
    private static ObjectManager oInstance = null;
    public static ObjectManager getInstance() {
        if (oInstance == null) oInstance = new ObjectManager();
        
        return oInstance;
    }
}
