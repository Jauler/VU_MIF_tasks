/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package roads;

import Utils.Clone;
import java.util.Random;
import locations.City;
import locations.Location;

/**
 *
 * @author rytis
 */
public class Magic implements ClonableRoad {

    private final Random random;
    private final Location availableLocations[];

    public Magic() {
        random = new Random(0);
        Location[] defaultLocations = {new City("Vilnius")};
        availableLocations = defaultLocations;
    }
    
    public Magic(int seed, Location _availableLocations[]) {
        random = new Random(seed);
        availableLocations = _availableLocations;
    }

    @Override
    public Location GetDestination() {
        int selectedLocationIdx = random.nextInt(availableLocations.length);

        return availableLocations[selectedLocationIdx];
    }
    
    public ClonableRoad Clone() throws Exception
    {
        ClonableRoad road = (ClonableRoad)Clone.CloneObject(this);
        return road;        
    }

    public void Init(Location destination)
    {
    }
    
        @Override
    public String toString()
    {
        return "magic road";
    }
}
