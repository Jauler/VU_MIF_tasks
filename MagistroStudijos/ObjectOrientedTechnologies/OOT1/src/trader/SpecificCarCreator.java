/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package trader;

import locations.Location;
import vechicles.Car;

/**
 *
 * @author rytis
 */
public class SpecificCarCreator implements Creator {
    
    private final Location initialLocation;
    
    public SpecificCarCreator(Location _initialLocation)
    {
        initialLocation = _initialLocation;
    }
    
    @Override
    public Object Create(Object[] args)
    {
        return new Car((String)args[0], initialLocation);
    }
}
