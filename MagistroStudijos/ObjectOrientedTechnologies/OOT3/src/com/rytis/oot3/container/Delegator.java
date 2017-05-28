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
public class Delegator implements InvocationHandler {
    
    private final Class delegatedInterface;
    private final Object delegatedObject;
    private final Object object;
    

    public static Object newInstace(Class delegatedInterface, Object delegatedObject, Object object) {
        Class interfaces[] = {object.getClass().getInterfaces()[0], delegatedInterface};
        return Proxy.newProxyInstance(object.getClass().getClassLoader(), interfaces, new Delegator(delegatedInterface, delegatedObject, object));
    }

    private Delegator(Class delegatedInterface, Object delegatedObject, Object object) {
        this.delegatedInterface = delegatedInterface;
        this.delegatedObject = delegatedObject;
        this.object = object;
    }

    @Override
    public Object invoke(Object proxy, Method m, Object[] args) throws Throwable {
        Object result;
        try {
            if (m.getDeclaringClass() == delegatedInterface)
                result = m.invoke(delegatedObject, args);
            else
                result = m.invoke(object, args);
        } catch (InvocationTargetException e) {
            throw e.getTargetException();
        } catch (Exception e) {
            throw new RuntimeException("Unknown invocation exception: " + e.getMessage());
        }
        return result;
    }
}
