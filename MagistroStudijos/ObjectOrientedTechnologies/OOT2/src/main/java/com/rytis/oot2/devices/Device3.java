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
public class Device3 implements Device {

    private final CPU cpu;
    private final Memory memory;
    private final String program;

    public static Device3 CreateInstance(CPU cpu, Memory memory, String program) {
        return new Device3(cpu, memory, program);
    }

    private Device3(CPU cpu, Memory memory, String program) {
        this.cpu = cpu;
        this.memory = memory;
        this.program = program;
    }

    @Override
    public void Boot() throws Throwable {
        System.out.println("Booting Device3:");
        cpu.Execute(program, memory);
        System.out.println();
    }
}
