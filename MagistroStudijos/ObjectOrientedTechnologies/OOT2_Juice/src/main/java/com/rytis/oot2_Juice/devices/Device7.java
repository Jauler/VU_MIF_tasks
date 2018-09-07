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
public class Device7 implements Device {

    private final CPU cpu;
    private final Memory ram;
    private final Memory disk;
    private final String program;

    @Inject
    public Device7(CPU cpu, @Named("RAM") Memory ram, @Named("Disk") Memory disk, @Named("Program") String program) {
        this.cpu = cpu;
        this.ram = ram;
        this.disk = disk;
        this.program = program;
    }

    @Override
    public void Boot() throws Throwable {
        System.out.println("Booting Device7:");
        cpu.Execute(program, ram);
        System.out.println("");
        System.out.println("Booting Device7:");
        cpu.Execute(program, disk);
        System.out.println();
    }
}
