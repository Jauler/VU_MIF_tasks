/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2.devices;

import com.rytis.oot2.memories.Memory;
import com.rytis.oot2.processors.CPU;

/**
 *
 * @author rytis
 */
public class Device1 implements Device {

    private final CPU cpu;
    private final Memory memory;
    private final String program;

    public Device1(CPU cpu, Memory memory, String program) {
        this.cpu = cpu;
        this.memory = memory;
        this.program = program;
    }

    @Override
    public void Boot() throws Throwable {
        System.out.println("Booting Device1:");
        cpu.Execute(program, memory);
        System.out.println();
    }
}
