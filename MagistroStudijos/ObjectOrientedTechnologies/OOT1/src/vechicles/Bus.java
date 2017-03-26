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
public class Bus implements ClonableVechicle {

    private Integer passengerCount;
    private String color;
    private String manufacturer;
    private Location location;

    public Bus(Integer _passengerCount, String _color, String _manufacturer, Location _location) {
        passengerCount = _passengerCount;
        color = _color;
        manufacturer = _manufacturer;
        location = _location;
    }

    protected void Setup(Bus bus) {
        bus.passengerCount = passengerCount;
        bus.color = color;
        bus.manufacturer = manufacturer;
        bus.location = location;
    }

    @Override
    public void Drive(Road r) {
        location = r.GetDestination();
    }

    @Override
    public Location GetCurrentLocation() {
        return location;
    }

    @Override
    public ClonableVechicle Clone() {
        Bus clonedBus = new Bus(passengerCount, color, manufacturer, location);
        return clonedBus;
    }

    @Override
    public void Init(String _color) {
        color = _color;
    }
    
    @Override
    public String toString()
    {
        return color + " " + manufacturer + " Bus";
    }
}
