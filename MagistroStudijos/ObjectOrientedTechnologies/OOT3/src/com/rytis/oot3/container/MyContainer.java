/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3.container;

import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.NoSuchElementException;

/**
 *
 * @author rytis
 */
public class MyContainer implements Container {

    private final Map<Class, Class> implementations;

    public MyContainer() {
        implementations = new HashMap<>();
    }

    @Override
    public void Register(Class interfaceClass, Class implementationClass) {
        implementations.put(interfaceClass, implementationClass);
    }

    protected Dependency[] findDependencies(Class type) {
        ArrayList<Dependency> dependencies = new ArrayList<>();
        Method[] allMethods = type.getDeclaredMethods();
        for (Method method : allMethods) {
            if (!Modifier.isPublic(method.getModifiers())) {
                continue;
            }

            if (!method.getName().startsWith("set")) {
                continue;
            }

            if (method.getParameters().length != 1) {
                continue;
            }

            dependencies.add(new Dependency(method, method.getParameters()[0].getType()));
        }

        return dependencies.toArray(new Dependency[0]);
    }

    private Object CreateEagerObject(Class implementation) throws Throwable {
        Dependency[] dependencies = findDependencies(implementation);
        for (Dependency dependency : dependencies) {
            dependency.setInstance(Create(dependency.getType(), false));
        }

        Object obj = implementation.newInstance();
        for (Dependency dependency : dependencies) {
            dependency.getSetter().invoke(obj, dependency.getInstance());
        }

        return obj;
    }

    private Object CreateLazyObject(Class implementation) throws Throwable {
        Class additionalInterfaces[];
        Delegate delegate[] = (Delegate[]) implementation.getAnnotationsByType(Delegate.class);
        if (delegate.length == 1) {
            additionalInterfaces = new Class[1];
            additionalInterfaces[0] = Class.forName(delegate[0].on());
        } else if (delegate.length > 1) {
            throw new Exception("@Delegate cannot be specified more than once");
        } else {
            additionalInterfaces = new Class[0];
        }

         return LazyCreationProxy.newInstace(this, implementation, additionalInterfaces);
    }

    private Object DecorateObject(Object object, String decoratorClass, String decoratorBeforeMethod, String decoratorAfterMethod) throws Throwable {
        Class emptyArgTypes[] = {};
        Object decorator = CreateEagerObject(Class.forName(decoratorClass));
        Method before = decorator.getClass().getDeclaredMethod(decoratorBeforeMethod, emptyArgTypes);
        Method after = decorator.getClass().getDeclaredMethod(decoratorAfterMethod, emptyArgTypes);
        return Decorator.newInstace(object, decorator, before, after);
    }

    private Object DelegateObject(Object object, String delegatedInterface, String delegatedClass) throws Throwable {
        Class delegatedInterfaceClass = Class.forName(delegatedInterface);
        Object delegatedObject = CreateEagerObject(Class.forName(delegatedClass));
        return Delegator.newInstace(delegatedInterfaceClass, delegatedObject, object);
    }

    @Override
    public Object Create(Class interfaceClass, boolean lazy) throws Throwable {
        if (!implementations.containsKey(interfaceClass)) {
            throw new NoSuchElementException("No implementation was found for requested interface class");
        }

        Class implementation = implementations.get(interfaceClass);

        if (lazy) {
            return CreateLazyObject(implementation);
        }

        Object object = CreateEagerObject(implementation);

        Decorate decorate[] = (Decorate[]) implementation.getAnnotationsByType(Decorate.class);
        if (decorate.length == 1) {
            object = DecorateObject(object, decorate[0].classType(), decorate[0].before(), decorate[0].after());
        } else if (decorate.length > 1) {
            throw new Exception("@Decorate cannot be specified more than once");
        }

        Delegate delegate[] = (Delegate[]) implementation.getAnnotationsByType(Delegate.class);
        if (delegate.length == 1) {
            object = DelegateObject(object, delegate[0].on(), delegate[0].by());
        } else if (delegate.length > 1) {
            throw new Exception("@Delegate cannot be specified more than once");
        }

        return object;
    }
}
