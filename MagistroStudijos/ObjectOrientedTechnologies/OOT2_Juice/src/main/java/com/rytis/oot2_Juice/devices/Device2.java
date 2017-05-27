/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2_Juice.devices;

import com.google.inject.Inject;
import com.rytis.oot2_Juice.memories.Memory;
import com.rytis.oot2_Juice.processors.CPU;

/**
 *
 * @author rytis
 */
public class Device2 implements Device {

    private CPU cpu;
    private Memory memory;
    private final String program;
    
    public Device2()
    {
        program = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++";
    }

    @Inject
    public void setCPU(CPU cpu) {
        this.cpu = cpu;
    }

    @Inject
    public void setMemory(Memory memory) {
        this.memory = memory;
    }

    @Override
    public void Boot() throws Throwable {
        System.out.println("Booting Device2:");
        cpu.Execute(program, memory);
        System.out.println();
    }

    public void PostConstruct() {
        System.out.println("Device constructed");
    }

    public void PreDestruct() {
        System.out.println("Device will be destructed soon");
    }
}
