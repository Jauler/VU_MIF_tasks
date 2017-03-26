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
public interface ClonableLocation extends Location {

    public ClonableLocation Clone() throws Exception;

    public void Init(String description);
}
