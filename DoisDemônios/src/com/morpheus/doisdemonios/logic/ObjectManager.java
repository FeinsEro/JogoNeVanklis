package com.morpheus.doisdemonios.logic;

import com.morpheus.doisdemonios.graphics.ObjectRenderer;
import java.util.ArrayList;
import java.util.List;

/**
 * The object manager iterates and cares for every object.
 * 
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class ObjectManager {
    
    private final List<IBaseObject> objects;
    private ObjectRenderer or;

    public ObjectRenderer getOr() {
        return or;
    }

    public void setObjectRenderer(ObjectRenderer or) {
        this.or = or;
    }
    
    public ObjectManager() {
        objects = new ArrayList<>();
    }    
     
    public void add(IBaseObject o) {
        objects.add(o);
        this.or.addToRender(o);
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
    
    public List<IBaseObject> getObjects() {
        return this.objects;
    }
    
    /***
     * Gets an object by its name
     * @param name The name
     * @return The first object found
     */
    public IBaseObject getObjectByName(String name) {
        for (IBaseObject o : objects) {
            if (o.getName().equals(name)) {
                return o;
            }
        }
        
        return null;
    }
    
    public int count() {
        return objects.size();
    }
   
    
    public void runAll() {
        for (IBaseObject o : objects) {
            o.run();
        }
    }   
    
    private static ObjectManager oInstance = null;
    public static ObjectManager getInstance() {
        if (oInstance == null) oInstance = new ObjectManager();
        
        return oInstance;
    }
}
