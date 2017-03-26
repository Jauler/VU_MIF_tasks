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
public class CarManufacturerBuilding implements Location {
    
    public String brand;
    
    public CarManufacturerBuilding(String _brand)
    {
        brand = _brand;
    }
    
    @Override
    public String GetDescription()
    {
        return brand + " factory";
    }
}
