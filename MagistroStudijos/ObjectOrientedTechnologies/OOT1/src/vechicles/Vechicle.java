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
public interface Vechicle {

    public void Drive(Road r);

    public Location GetCurrentLocation();
}
