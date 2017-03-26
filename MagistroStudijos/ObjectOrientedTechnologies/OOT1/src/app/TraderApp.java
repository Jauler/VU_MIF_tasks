/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package app;

import factories.Factory;
import factories.FactoryHolder;
import locations.City;
import locations.Location;
import roads.Road;
import trader.AbstracterFactory;
import trader.AbstracterFactoryHolder;
import vechicles.Vechicle;

/**
 *
 * @author rytis
 */
public class TraderApp {

    public void Run() throws Exception {

        AbstracterFactory factory = AbstracterFactoryHolder.GetFactory(); //TODO: assign

        Object[] locationArgs = {"Vilnius"};
        Location destination = (Location) factory.Create("Location", locationArgs);

        Object[] roadArgs = {destination};
        Road road = (Road) factory.Create("Road", roadArgs);

        Object[] vechicleArgs = {"green"};
        Vechicle vechicle = (Vechicle)factory.Create("Vechicle", vechicleArgs);

        Location initialVechicleLocation = vechicle.GetCurrentLocation();
        vechicle.Drive(road);
        Location finalVechicleLocation = vechicle.GetCurrentLocation();

        System.out.println(vechicle
                + " starts in " + initialVechicleLocation.GetDescription()
                + " and arrives at " + finalVechicleLocation.GetDescription()
                + " over " + road);
    }
}
