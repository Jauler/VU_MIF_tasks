/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2;

import com.rytis.oot2.devices.Device;
import com.rytis.oot2.devices.Device1;
import com.rytis.oot2.devices.Device2;
import com.rytis.oot2.devices.Device3;
import com.rytis.oot2.devices.Device5;
import com.rytis.oot2.devices.Device7;
import com.rytis.oot2.memories.Disk;
import com.rytis.oot2.memories.Memory;
import com.rytis.oot2.memories.RAM;
import com.rytis.oot2.processors.BrainfuckCPU;
import com.rytis.oot2.processors.CPU;
import com.rytis.oot2.processors.CPUFactory;
import com.rytis.oot2.processors.Fuck4CPU;
import org.springframework.beans.factory.FactoryBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;
import org.springframework.context.annotation.Scope;

/**
 *
 * @author rytis
 */
@Configuration
public class AppConfig {

    @Bean
    @Scope("prototype")
    @Qualifier("default")
    public RAM memory() throws Throwable {
        return new RAM(1024);
    }

    @Bean
    @Scope("prototype")
    public Disk disk() throws Throwable {
        return new Disk("/tmp/disk");
    }

    @Bean
    @Qualifier("default")
    public CPU cpu() {
        return new BrainfuckCPU();
    }

    @Bean
    @Primary
    public CPU brainfuckCPU() {
        return new BrainfuckCPU();
    }

    @Bean
    public CPU fuck4CPU() {
        return new Fuck4CPU();
    }

    @Bean
    public FactoryBean<CPU> cpuFactory() {
        return new CPUFactory("model1");
    }

    @Bean
    public Device device1() throws Throwable {
        return new Device1(brainfuckCPU(), memory(), "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++");
    }

    @Bean
    public Device device2() throws Throwable {
        Device2 device = new Device2();

        device.setCPU(fuck4CPU());
        device.setMemory(disk());
        device.setProgram("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffcfcccccccfffffffffffffffffffffffffffffcfcccccccfffffffcfccccccccfcccccccfffcfcccccccufkffffffffffffffffffffffffffffffffffffffffffffcfcccccccufkffffffffffffffffffffffffffffffffcfcccccccfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffcfcccccccufkfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffcfcccccccfffcfcccccccufkffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffcfcccccccufkffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffcfcccccccufkfffffffffffffffffffffffffffffffffcfc");

        return device;
    }

    @Bean
    public Device device3() throws Throwable {
        return Device3.CreateInstance(brainfuckCPU(), memory(), "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++");
    }

    @Bean
    public Device device4() throws Throwable {
        return new Device1(cpuFactory().getObject(), memory(), "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++");
    }

    @Bean
    public Device device5(CPU cpu, Memory memory) {
        Device5 device = new Device5();
        device.setCPU(cpu);
        device.setMemory(memory);
        device.setProgram("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++");
        return device;
    }
    
    @Bean
    public Device device7(@Qualifier("default") CPU cpu, @Qualifier("default") Memory memory) {
        Device1 device = new Device1(cpu, memory, "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++");
        return device;
    }

}
