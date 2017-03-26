/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package factories;

import java.lang.reflect.Constructor;
import locations.Location;
import roads.Road;
import vechicles.Vechicle;

/**
 *
 * @author rytis
 */
public class ClassAbstractFactory implements Factory {

    final private Class<? extends Location> locationClass;
    final private Object[] locationCreationArgs;
    final private Class<? extends Road> roadClass;
    final private Object[] roadCreationArgs;
    final private Class<? extends Vechicle> vechicleClass;
    final private Object[] vechicleCreationArgs;

    public ClassAbstractFactory(
            Class<? extends Location> _locationClass, Object[] _locationCreationArgs,
            Class<? extends Road> _roadClass, Object[] _roadCreationArgs,
            Class<? extends Vechicle> _vechicleClass, Object[] _vechicleCreationArgs) {
        locationClass = _locationClass;
        locationCreationArgs = _locationCreationArgs;
        roadClass = _roadClass;
        roadCreationArgs = _roadCreationArgs;
        vechicleClass = _vechicleClass;
        vechicleCreationArgs = _vechicleCreationArgs;
    }

    private Constructor GetCompatibleConstructor(Class target, Class[] ctorArgTypes) throws NoSuchMethodException {
        Constructor[] constructors = target.getDeclaredConstructors();

        Constructor compatibleConstructor = null;
        for (Constructor constructor : constructors) {
            Class[] params = constructor.getParameterTypes();

            Boolean isAllParametersCompatible = true;
            for (int i = 0; i < params.length; i++) {
                if (!params[i].isAssignableFrom(ctorArgTypes[i])) {
                    isAllParametersCompatible = false;
                    break;
                }
            }

            if (isAllParametersCompatible) {
                compatibleConstructor = constructor;
                break;
            }
        }

        if (compatibleConstructor == null) {
            throw new NoSuchMethodException();
        }

        return compatibleConstructor;
    }

    @Override
    public Location CreateLocation(String description) throws Exception {
        Class[] ctorTypes = new Class[locationCreationArgs.length + 1];
        Object[] ctorArgs = new Object[locationCreationArgs.length + 1];
        ctorTypes[0] = description.getClass();
        ctorArgs[0] = description;
        for (int i = 0; i < locationCreationArgs.length; i++) {
            ctorTypes[i + 1] = locationCreationArgs[i].getClass();
            ctorArgs[i + 1] = locationCreationArgs[i];
        }

        Constructor ctor = GetCompatibleConstructor(locationClass, ctorTypes);
        return (Location) ctor.newInstance(ctorArgs);
    }

    @Override
    public Road CreateRoad(Location destination) throws Exception {
        Class[] ctorTypes = new Class[roadCreationArgs.length + 1];
        Object[] ctorArgs = new Object[roadCreationArgs.length + 1];
        ctorTypes[0] = destination.getClass();
        ctorArgs[0] = destination;
        for (int i = 0; i < roadCreationArgs.length; i++) {
            ctorTypes[i + 1] = roadCreationArgs[i].getClass();
            ctorArgs[i + 1] = roadCreationArgs[i];
        }

        Constructor ctor = GetCompatibleConstructor(roadClass, ctorTypes);
        return (Road) ctor.newInstance(ctorArgs);
    }

    @Override
    public Vechicle CreateVechicle(String color) throws Exception {
        Class[] ctorTypes = new Class[vechicleCreationArgs.length + 1];
        Object[] ctorArgs = new Object[vechicleCreationArgs.length + 1];
        ctorTypes[0] = color.getClass();
        ctorArgs[0] = color;
        for (int i = 0; i < vechicleCreationArgs.length; i++) {
            ctorTypes[i + 1] = vechicleCreationArgs[i].getClass();
            ctorArgs[i + 1] = vechicleCreationArgs[i];
        }

        Constructor ctor = GetCompatibleConstructor(vechicleClass, ctorTypes);
        return (Vechicle) ctor.newInstance(ctorArgs);
    }
}
