/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package vechicles;

import locations.Location;

/**
 *
 * @author rytis
 */
public class DoubleDecaBus extends Bus {
    
    private final Integer passengerCount;
    
    public DoubleDecaBus(Integer _passengerCount, Location _location)
    {
        super(2 * _passengerCount, "Red", "AEC", _location);
        passengerCount = _passengerCount;
        
    } 
    
    @Override
    public ClonableVechicle Clone()
    {
        DoubleDecaBus clonedDoubleDecaBus = new DoubleDecaBus(2 * passengerCount, this.GetCurrentLocation());
        clonedDoubleDecaBus.Setup(this);
        return clonedDoubleDecaBus;
    }
    
    @Override
    public String toString()
    {
        String str = super.toString();
        str = str.replaceFirst("(?s)Bus(?!.*?Bus)", "DoubleDecaBus");
        return str;
    }
}
