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
public interface AbstracterFactory {
    
    public Object Create(String product, Object[] args) throws Exception;
}
