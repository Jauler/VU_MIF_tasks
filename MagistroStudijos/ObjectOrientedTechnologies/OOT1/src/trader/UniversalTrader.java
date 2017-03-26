/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package trader;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author rytis
 */
public class UniversalTrader implements AbstracterFactory {

    private final Map<String, Creator> creators = new HashMap();
        
    @Override
    public Object Create(String product, Object[] args) throws Exception
    {
        return creators.get(product).Create(args);
    }
    
    public void AddCreator(String product, Creator creator)
    {
        creators.put(product, creator);
    }
}
