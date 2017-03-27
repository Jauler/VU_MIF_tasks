/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package factories;

import locations.Location;
import roads.Road;
import vechicles.Vechicle;

/**
 *
 * @author rytis
 */
public interface Factory {

    public Location CreateLocation(String description) throws Throwable;
    
    public Road CreateRoad(Location destination) throws Throwable;

    public Vechicle CreateVechicle(String color) throws Throwable;
}
