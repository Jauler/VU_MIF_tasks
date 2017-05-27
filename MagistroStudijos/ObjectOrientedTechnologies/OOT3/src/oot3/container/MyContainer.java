/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oot3.container;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author rytis
 */
public class MyContainer implements Container {
    
    private final Map<Class, Class> implementations;
    
    public MyContainer() {
        implementations = new HashMap();
    }
    
    @Override
    public void Register(Class interfaceClass, Class implementationClass)
    {
        implementations.put(interfaceClass, implementationClass);
    }
    
    @Override
    public Object Create(Class interfaceClass, boolean lazy) throws Throwable
    {
        Class implementation = implementations.get(interfaceClass);
        
        
        
        
        Object obj = implementation.newInstance();
        //TODO: search for public set...() methods in class
        //TODO: check for @Decorate method
     
        return obj;
    }
}
