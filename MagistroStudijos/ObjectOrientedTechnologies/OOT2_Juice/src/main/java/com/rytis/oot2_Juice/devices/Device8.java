/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2_Juice.devices;

import com.google.inject.Inject;
import com.google.inject.Provider;
import com.google.inject.name.Named;
import com.rytis.oot2_Juice.memories.Memory;
import com.rytis.oot2_Juice.processors.CPU;

/**
 *
 * @author rytis
 */
public abstract class Device8 implements Device {

    private final CPU cpu;
    private final String program;

    @Inject
    public Device8(CPU cpu, String program) {
        this.cpu = cpu;
        this.program = program;
    }

    @Override
    public void Boot() throws Throwable {
        System.out.println("Booting Device8:");
        cpu.Execute(program, getMemory());
        System.out.println();
    }
    
    protected abstract Memory getMemory() throws Throwable;
}

