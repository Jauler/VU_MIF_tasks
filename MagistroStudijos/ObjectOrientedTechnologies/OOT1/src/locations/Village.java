/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package locations;

import Utils.Clone;

/**
 *
 * @author rytis
 */
public class Village implements ClonableLocation {
    
    @Override
    public String GetDescription()
    {
        return " village";
    }
    
    @Override
    public ClonableLocation Clone() throws Exception
    {
        Village clonedVillage = (Village)Clone.CloneObject(this);
        return clonedVillage;
    }

    @Override
    public void Init(String description)
    {
    }
}
