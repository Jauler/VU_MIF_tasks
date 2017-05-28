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
public class Device4Provider implements Provider<Device4> {

    private final CPU cpu;
    private final Memory memory;
    private final String program;

    @Inject
    public Device4Provider(CPU cpu, Memory memory, @Named("Program") String program) {
        this.cpu = cpu;
        this.memory = memory;
        this.program = program;
    }

    @Override
    public Device4 get() {
        return new Device4(cpu, memory, program);
    }
}
