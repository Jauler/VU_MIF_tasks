/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package trader;

import java.lang.reflect.Constructor;

/**
 *
 * @author rytis
 */
public class AbstractCreator implements Creator {

    public final Class classObj;
    public final Object[] additionalArgs;

    public AbstractCreator(Class _classObj, Object[] _ctorArgs) {
        classObj = _classObj;
        additionalArgs = _ctorArgs;
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
    public Object Create(Object[] args) throws Exception {
        Class[] ctorTypes = new Class[args.length + additionalArgs.length];
        Object[] ctorArgs = new Object[args.length + additionalArgs.length];
        for (int i = 0; i < args.length; i++) {
            ctorTypes[i] = args[i].getClass();
            ctorArgs[i] = args[i];
        }
        for (int j = 0; j < additionalArgs.length; j++) {
            ctorTypes[args.length + j] = additionalArgs[j].getClass();
            ctorArgs[args.length + j] = additionalArgs[j];
        }

        Constructor constructor = GetCompatibleConstructor(classObj, ctorTypes);
        return constructor.newInstance(ctorArgs);
    }
}
