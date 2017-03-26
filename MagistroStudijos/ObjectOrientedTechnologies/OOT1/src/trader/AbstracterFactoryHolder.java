/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package trader;

/**
 *
 * @author rytis
 */
public class AbstracterFactoryHolder {
    private static AbstracterFactory factory;
    
    public static void SetFactory(AbstracterFactory _factory)
    {
        factory = _factory;
    }
    
    public static AbstracterFactory GetFactory()
    {
        return factory;
    }
}
