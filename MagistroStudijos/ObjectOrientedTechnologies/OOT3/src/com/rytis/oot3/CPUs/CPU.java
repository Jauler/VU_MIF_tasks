/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3.CPUs;

import com.rytis.oot3.memories.Memory;

/**
 *
 * @author rytis
 */
public interface CPU {
    
    public void Execute(String program, Memory memory) throws Throwable;
}
