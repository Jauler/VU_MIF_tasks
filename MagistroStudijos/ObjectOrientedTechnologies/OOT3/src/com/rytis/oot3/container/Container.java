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
    
    public<T> void Register(Class<T> interfaceClass, Class<? extends T> implementationClass);
    public<T> T Create(Class<T> interfaceClass, boolean lazy) throws Throwable;
          
}
