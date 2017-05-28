/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3.container;

import java.lang.reflect.Method;

/**
 *
 * @author rytis
 */
public class Dependency {

    private Method setter;
    private Class type;
    private Object instance;

    Dependency() {
    }

    Dependency(Method setter, Class type) {
        this.setter = setter;
        this.type = type;
    }
    
    Dependency(Method setter, Class type, Object instance) {
        this.setter = setter;
        this.type = type;
        this.instance = instance;
    }
    
    void setSetter(Method setter) {
        this.setter = setter;
    }
    
    void setType(Class type) {
        this.type = type;
    }
    
    void setInstance(Object instance) {
        this.instance = instance;
    }
    
    Method getSetter() {
        return this.setter;
    }
    
    Class getType() {
        return this.type;
    }
    
    Object getInstance() {
        return this.instance;
    }
}
