/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.morpheus.doisdemonios.util;

/**
 * 2D vector class
 * @author Arthur Mendes <arthurmco@gmail.com>
 */
public class Vector2f {
    private float x, y;
    
    public Vector2f(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public float getX() {
        return x;
    }

    public float getY() {
        return y;
    }
        
    /***
     * Add two vectors
     * @param v The other vector
     * @param res Where to store the result, if you wish
     */
    public void add(Vector2f v, Vector2f res) {
        if (res != null) {
            res.x = (this.x + v.x);
            res.y = (this.y + v.y);
        } else {
            this.x += v.x;
            this.y += v.y;
        }
    }
    
     
    /***
     * Subtract two vectors
     * @param v The other vector
     * @param res Where to store the result, if you wish
     */
    public void subtract(Vector2f v, Vector2f res) {
        if (res != null) {
            res.x = (this.x - v.x);
            res.y = (this.y - v.y);
        } else {
            this.x -= v.x;
            this.y -= v.y;
        }
    }
    
     
    /***
     * Multiply a vector by a scalar value
     * @param s The scalar
     * @param res Where to store the result, if you wish
     */
    public void multiplyScalar(float s, Vector2f res) {
        if (res != null) {
            res.x = (this.x * s);
            res.y = (this.y * s);
        } else {
            this.x *= s;
            this.y *= s;
        }
    }
    
     /***
     * Do the scalar/dot product between vectors
     * @param v The other vector
     * @return The dot product
     */
    public float dot(Vector2f v) {
        float r = (this.x * v.x) + (this.y * v.y);
        return r;
    }
    
    /***
     * Get the vector length
     * @return The vector length
     */
    public float length() {
        float l = (float)Math.sqrt((this.x*this.x)+(this.y*this.y));
        return l;
    }
    
    /***
     * Normalize the vector. This means "set the length to 1"
     * Together with dot product, this is useful to find the angle between
     * two vectors.
     */
    public void normalize() {
        float l = this.length();
        this.x = this.x / l;
        this.y = this.y / l;
    }
        
    /***
     * Returns a float array, that you can use with OpenGL.
     * @return The array
     */
    public float[] getNative() {
        return new float[]{x,y};
    }

    @Override
    public String toString() {
        return "( "+this.x+" , "+this.y+" )";
    }

    @Override
    public boolean equals(Object obj) {
        if (obj.getClass() == Vector2f.class) {
            Vector2f v = (Vector2f)obj;
            return (v.x == this.x && v.y == this.y);            
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 59 * hash + Float.floatToIntBits(this.x);
        hash = 59 * hash + Float.floatToIntBits(this.y);
        return hash;
    }
    
    
    
        
}
