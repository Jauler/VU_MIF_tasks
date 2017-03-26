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
public interface ClonableRoad extends Road {

    public ClonableRoad Clone() throws Exception;

    public void Init(Location destination);
}
