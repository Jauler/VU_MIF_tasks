/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Utils;

import java.lang.reflect.Field;

/**
 *
 * @author rytis
 */
public class Clone {

    public static Object CloneObject(Object o) throws Exception {
        Object clone = null;

        clone = o.getClass().newInstance();

        // Walk up the superclass hierarchy
        for (Class obj = o.getClass();
                !obj.equals(Object.class);
                obj = obj.getSuperclass()) {
            Field[] fields = obj.getDeclaredFields();
            for (int i = 0; i < fields.length; i++) {
                fields[i].setAccessible(true);
                try {
                    // for each class/suerclass, copy all fields
                    // from this object to the clone
                    fields[i].set(clone, fields[i].get(o));
                } catch (Exception e) {
                }
            }
        }
        return clone;
    }
}
