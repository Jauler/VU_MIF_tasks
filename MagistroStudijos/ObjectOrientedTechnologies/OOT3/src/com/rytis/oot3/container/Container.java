/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3.container;

/**
 *
 * @author rytis
 */
public interface Container {
    
    public void Register(Class interfaceClass, Class implementationClass);
    public Object Create(Class interfaceClass, boolean lazy) throws Throwable;
          
}
