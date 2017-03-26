/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package factories;

/**
 *
 * @author rytis
 */
public class FactoryHolder {
 
    private static Factory factory;
    
    public static void SetFactory(Factory _factory)
    {
        factory = _factory;
    }
    
    public static Factory GetFactory()
    {
        return factory;
    }
}
