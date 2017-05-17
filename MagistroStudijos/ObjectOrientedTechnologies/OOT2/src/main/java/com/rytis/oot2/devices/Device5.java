package com.rytis.oot2.devices;

import com.rytis.oot2.memories.Memory;
import com.rytis.oot2.processors.CPU;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author rytis
 */
public class Device5 implements Device {

    private CPU cpu;
    private Memory memory;
    private String program;

    public void setCPU(CPU cpu) {
        this.cpu = cpu;
    }

    public void setMemory(Memory memory) {
        this.memory = memory;
    }

    public void setProgram(String program) {
        this.program = program;
    }

    @Override
    public void Boot() throws Throwable {
        System.out.println("Booting Device5:");
        cpu.Execute(program, memory);
        System.out.println();
    }
}
