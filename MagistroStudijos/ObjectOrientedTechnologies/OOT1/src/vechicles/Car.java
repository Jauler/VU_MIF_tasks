/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vechicles;

import locations.Location;
import roads.Road;

/**
 *
 * @author rytis
 */
public class Car implements Vechicle {
    
    private final String color;
    private Location currentLocation;
    
    public Car(String _color, Location _currentLocation)
    {
        color = _color;
        currentLocation = _currentLocation;  
    }
        
    @Override
    public void Drive(Road road)
    {
        currentLocation = road.GetDestination();
    }

    @Override
    public Location GetCurrentLocation()
    {
        return currentLocation;
    }
    
    @Override
    public String toString()
    {
        return color + " car";
    }
}
