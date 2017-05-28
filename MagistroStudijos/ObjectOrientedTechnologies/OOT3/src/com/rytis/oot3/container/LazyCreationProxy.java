/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3.container;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

/**
 *
 * @author rytis
 */
public class LazyCreationProxy implements InvocationHandler {
    
    private final Container container;
    private final Class implementationClass;
    private Object object;
    

    public static Object newInstace(Container container, Class implementationClass, Class additionalInterfaces[]) {
        
        Class interfaces[] = new Class[1 + additionalInterfaces.length];
        interfaces[0] = implementationClass.getInterfaces()[0];
        for (int i = 0; i < additionalInterfaces.length; i++)
            interfaces[i+1] = additionalInterfaces[i];
                
        return Proxy.newProxyInstance(interfaces[0].getClassLoader(), interfaces, new LazyCreationProxy(container, implementationClass));
    }

    private LazyCreationProxy(Container container, Class implementationClass) {
        this.container = container;
        this.implementationClass = implementationClass;
    }

    @Override
    public Object invoke(Object proxy, Method m, Object[] args) throws Throwable {
        Object result;
        try {
            if (object == null) {
                object = container.Create(implementationClass, false);
            }
            result = m.invoke(object, args);
        } catch (InvocationTargetException e) {
            throw e.getTargetException();
        } catch (Exception e) {
            throw new RuntimeException("Unknown invocation exception: " + e.getMessage());
        }
        return result;
    }
}
