/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2_Juice.devices;

import com.google.inject.Inject;
import com.google.inject.name.Named;
import com.rytis.oot2_Juice.memories.Memory;
import com.rytis.oot2_Juice.processors.CPU;

/**
 *
 * @author rytis
 */
public class Device5 implements Device {

    private final CPU cpu;
    private final Memory memory;
    private final String program;

    @Inject
    public Device5(CPU cpu, Memory memory, @Named("Program") String program) {
        this.cpu = cpu;
        this.memory = memory;
        this.program = program;
    }

    @Override
    public void Boot() throws Throwable {
        System.out.println("Booting Device5:");
        cpu.Execute(program, memory);
        System.out.println();
    }
}
