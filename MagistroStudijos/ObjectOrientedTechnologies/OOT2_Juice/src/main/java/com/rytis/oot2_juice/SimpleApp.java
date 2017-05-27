/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2_juice;

import com.google.inject.AbstractModule;
import com.google.inject.Guice;
import com.google.inject.Injector;
import com.rytis.oot2_Juice.devices.Device;
import com.rytis.oot2_Juice.devices.Device1;
import com.rytis.oot2_Juice.devices.Device2;
import com.rytis.oot2_Juice.memories.Memory;
import com.rytis.oot2_Juice.memories.RAM;
import com.rytis.oot2_Juice.processors.BrainfuckCPU;
import com.rytis.oot2_Juice.processors.CPU;

/**
 *
 * @author rytis
 */
public class SimpleApp {
 
    public static void run() throws Throwable {
                Injector injector = Guice.createInjector(
            new AbstractModule() {
                @Override
                protected void configure() {
                    bind(CPU.class).to(BrainfuckCPU.class);
                    bind(Memory.class).to(RAM.class);
                }
            });
        
        Device device;
        device = injector.getInstance(Device1.class);
        device.Boot();
        device = injector.getInstance(Device2.class);
        device.Boot();
    }
}
