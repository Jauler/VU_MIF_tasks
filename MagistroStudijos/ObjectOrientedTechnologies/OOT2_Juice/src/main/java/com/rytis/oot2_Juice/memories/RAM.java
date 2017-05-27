/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2_Juice.memories;


/**
 *
 * @author rytis
 */
public class RAM implements Memory {
    
    private final byte[] memoryCells;
    
    public RAM()
    {
        memoryCells = new byte[1024];
    }
    

    public RAM(int memorySize)
    {
        memoryCells = new byte[memorySize];
    }
    
    @Override
    public void Store(int address, byte value) throws Throwable
    {
       if (address < 0 || address >= memoryCells.length)
            throw new Exception("Memory access violation");
       
       memoryCells[address] = value;
    }
    
    @Override
    public byte Load(int address) throws Throwable
    {
        if (address < 0 || address >= memoryCells.length)
            throw new Exception("Memory access violation");
            
        return memoryCells[address];
    }
}
