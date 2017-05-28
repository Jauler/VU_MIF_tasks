/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2_juice;

import com.google.inject.AbstractModule;
import com.google.inject.Guice;
import com.google.inject.Injector;
import com.google.inject.Key;
import com.google.inject.Provides;
import com.google.inject.name.Named;
import com.google.inject.name.Names;
import com.rytis.oot2_Juice.devices.Device;
import com.rytis.oot2_Juice.devices.Device1;
import com.rytis.oot2_Juice.devices.Device2;
import com.rytis.oot2_Juice.devices.Device3;
import com.rytis.oot2_Juice.devices.Device4;
import com.rytis.oot2_Juice.devices.Device5;
import com.rytis.oot2_Juice.devices.Device4Provider;
import com.rytis.oot2_Juice.devices.Device8;
import com.rytis.oot2_Juice.memories.Disk;
import com.rytis.oot2_Juice.memories.Memory;
import com.rytis.oot2_Juice.memories.RAM;
import com.rytis.oot2_Juice.processors.BrainfuckCPU;
import com.rytis.oot2_Juice.processors.CPU;
import javax.inject.Singleton;

/**
 *
 * @author rytis
 */
public class SimpleApp {

    public static void run() throws Throwable {
        Injector injector1 = Guice.createInjector(
                new AbstractModule() {
            @Override
            protected void configure() {
                bind(CPU.class).to(BrainfuckCPU.class).in(Singleton.class);
                bind(Memory.class).to(RAM.class);
                bind(Memory.class).annotatedWith(Names.named("Disk")).to(Disk.class);
                bind(String.class).annotatedWith(Names.named("Program")).toInstance("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++");
                bind(Device4.class).toProvider(Device4Provider.class);
                bind(Device5.class).annotatedWith(Names.named("RAM")).to(Device5.class);
                bind(Device5.class).annotatedWith(Names.named("Disk")).to(Device5.class);
            }

            // Device1 -> JIT provider
            // Device2 -> JIT provider
            @Provides
            Device3 ProvideDevice3(CPU cpu, Memory memory, @Named("Program") String program) {
                return Device3.CreateInstance(cpu, memory, program);
            }

            @Provides
            Device8 ProvideDevice8(CPU cpu, @Named("Program") String program) {
                Device8 device = new Device8(cpu, "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++") {
                    @Override
                    protected Memory getMemory() throws Throwable {
                        return new RAM(1024);
                    }
                };
                return device;
            }
        });

        Device device;
        device = injector1.getInstance(Device1.class);
        device.Boot();
        device = injector1.getInstance(Device2.class);
        device.Boot();
        device = injector1.getInstance(Device3.class);
        device.Boot();
        device = injector1.getInstance(Device4.class);
        device.Boot();
        device = injector1.getInstance(Key.get(Device5.class, Names.named("RAM")));
        device.Boot();
        device = injector1.getInstance(Key.get(Device5.class, Names.named("Disk")));
        device.Boot();
        device = injector1.getInstance(Device8.class);
        device.Boot();
    }
}
