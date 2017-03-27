/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package factories;

import locations.ClonableLocation;
import locations.Location;
import roads.ClonableRoad;
import roads.Road;
import vechicles.ClonableVechicle;
import vechicles.Vechicle;

/**
 *
 * @author rytis
 */
public class PrototypeAbstractFactory implements Factory {
    
    public ClonableLocation locationPrototype;
    public ClonableRoad roadPrototype;
    public ClonableVechicle vechiclePrototype;
    
    public PrototypeAbstractFactory(ClonableLocation _locationPrototype, ClonableRoad _roadPrototype, ClonableVechicle _vechiclePrototype)
    {
        locationPrototype = _locationPrototype;
        roadPrototype = _roadPrototype;
        vechiclePrototype = _vechiclePrototype;
    }
    
    @Override
    public Location CreateLocation(String description) throws Throwable
    {
        ClonableLocation location = locationPrototype.Clone();
        location.Init(description);
        return location;
    }
    
    @Override
    public Road CreateRoad(Location destination) throws Throwable
    {
        ClonableRoad road = roadPrototype.Clone();
        road.Init(destination);
        return road;
    }

    @Override
    public Vechicle CreateVechicle(String color) throws Throwable
    {
        ClonableVechicle vechicle = vechiclePrototype.Clone();
        vechicle.Init(color);
        return vechicle;
    }
}
