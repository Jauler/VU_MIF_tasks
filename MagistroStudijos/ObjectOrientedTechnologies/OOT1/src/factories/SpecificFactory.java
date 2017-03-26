/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package factories;

import locations.City;
import locations.Location;
import roads.Highway;
import roads.Road;
import vechicles.Car;
import vechicles.Vechicle;

/**
 *
 * @author rytis
 */
public class SpecificFactory implements Factory {
    
    private final Integer defaultHighwayLanesCount;
    private final Location carManufacturingLocation;
    
    public SpecificFactory(Integer _DefaultHighwayLanesCount, Location _carManufactoryLocation)
    {
        defaultHighwayLanesCount = _DefaultHighwayLanesCount;
        carManufacturingLocation = _carManufactoryLocation;   
    }
    
    @Override
    public Location CreateLocation(String description)
    {
        return new City(description);
    }
    
    @Override
    public Road CreateRoad(Location destination)
    {
        return new Highway(destination, defaultHighwayLanesCount);
    }

    @Override
    public Vechicle CreateVechicle(String color)
    {
        return new Car(color, carManufacturingLocation);
    }
}
