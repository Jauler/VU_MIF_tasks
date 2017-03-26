/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package app;

import factories.ClassAbstractFactory;
import factories.FactoryHolder;
import factories.PrototypeAbstractFactory;
import factories.SpecificFactory;
import locations.CarManufacturerBuilding;
import locations.City;
import locations.Location;
import locations.Village;
import roads.Highway;
import roads.Magic;
import trader.AbstractCreator;
import trader.AbstracterFactoryHolder;
import trader.SpecificCarCreator;
import trader.UniversalTrader;
import vechicles.Car;
import vechicles.DoubleDecaBus;

/**
 *
 * @author rytis
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        try {
            FactoryHolder.SetFactory(new SpecificFactory(3, new CarManufacturerBuilding("Ford")));
            App app = new App();
            app.Run();

            FactoryHolder.SetFactory(new ClassAbstractFactory(
                    City.class, new Object[]{},
                    Highway.class, new Object[]{4},
                    Car.class, new Object[]{new CarManufacturerBuilding("Audi")}));
            app = new App();
            app.Run();

            Location[] magicRoadLocations = {new City("Vilnius"), new City("Kaunas")};
            FactoryHolder.SetFactory(new PrototypeAbstractFactory(
                    new Village(),
                    new Magic(1, magicRoadLocations),
                    new DoubleDecaBus(20, new CarManufacturerBuilding("AEC"))
            ));
            app = new App();
            app.Run();
            
            UniversalTrader trader = new UniversalTrader();
            Object[] locationArgs = {};
            trader.AddCreator("Location", new AbstractCreator(City.class, locationArgs));
            Object[] roadArgs = {5};
            trader.AddCreator("Road", new AbstractCreator(Highway.class, roadArgs));
            trader.AddCreator("Vechicle", new SpecificCarCreator(new CarManufacturerBuilding("Toyota")));
            AbstracterFactoryHolder.SetFactory(trader);
            TraderApp traderApp = new TraderApp();
            traderApp.Run();
            

        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }
}
