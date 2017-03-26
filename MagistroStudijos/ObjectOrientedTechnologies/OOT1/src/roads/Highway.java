/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package roads;

import locations.Location;

/**
 *
 * @author rytis
 */
public class Highway implements Road {

    public final Integer lanesCnt;
    public final Location destination;
    
    public Highway(Location _destination, Integer _lanesCnt)
    {
        lanesCnt = _lanesCnt;
        destination = _destination;
    }
    
    @Override
    public Location GetDestination()
    {
        return destination;
    }
    
    @Override
    public String toString()
    {
        return lanesCnt + " Lanes Highway";
    }
}
