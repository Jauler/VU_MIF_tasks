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
public class Decorator implements InvocationHandler {

    private final Object decoratee;
    private final Object decorator;
    private final Method before;
    private final Method after;

    public static Object newInstace(Object decoratee, Object decorator, Method before, Method after) {
        return Proxy.newProxyInstance(decoratee.getClass().getClassLoader(), decoratee.getClass().getInterfaces(), new Decorator(decoratee, decorator, before, after));
    }

    private Decorator(Object decoratee, Object decorator, Method before, Method after) {
        this.decoratee = decoratee;
        this.decorator = decorator;
        this.before = before;
        this.after = after;
    }

    @Override
    public Object invoke(Object proxy, Method m, Object[] args) throws Throwable {
        Object result;
        Object[] emptyArgs = {};
        try {
            before.invoke(decorator, emptyArgs);
            result = m.invoke(decoratee, args);
            after.invoke(decorator, emptyArgs);
        } catch (InvocationTargetException e) {
            throw e.getTargetException();
        } catch (Exception e) {
            throw new RuntimeException("Unknown invocation exception: " + e.getMessage());
        }
        return result;
    }
}
