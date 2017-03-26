/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package locations;

/**
 *
 * @author rytis
 */
public class City implements Location {
    
    public final String name;
    
    public City(String _name)
    {
        name = _name;
    }
    
    @Override
    public String GetDescription()
    {
        return name + " city";
    }
}
