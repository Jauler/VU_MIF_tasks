/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package app;

import factories.FactoryHolder;
import factories.Factory;
import locations.Location;
import roads.Road;
import vechicles.Vechicle;

/**
 *
 * @author rytis
 */
public class App {

    public void Run() throws Exception {
        Factory factory = FactoryHolder.GetFactory();

        Location destination = factory.CreateLocation("Vilnius");
        Road road = factory.CreateRoad(destination);

        Vechicle vechicle = factory.CreateVechicle("Green");
        
        Location initialVechicleLocation = vechicle.GetCurrentLocation();
        vechicle.Drive(road);
        Location finalVechicleLocation = vechicle.GetCurrentLocation();
        
        System.out.println(vechicle +
                " starts in " + initialVechicleLocation.GetDescription() +
                " and arrives at " + finalVechicleLocation.GetDescription() +
                " over " + road);
    }
}
