/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3.devices;

import com.rytis.oot3.CPUs.CPU;
import com.rytis.oot3.container.Delegate;
import com.rytis.oot3.memories.Memory;



/**
 *
 * @author rytis
 */

@Delegate(on="com.rytis.oot3.devices.DeviceSelfCheck", by="com.rytis.oot3.devices.DeviceSelfChecker")
public class Device3 implements Device {

    private CPU cpu;
    private Memory memory;
    private String program;
    
    public Device3()
    {
        program = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++";
    }

    public void setCPU(CPU cpu) {
        this.cpu = cpu;
    }

    public void setMemory(Memory memory) {
        this.memory = memory;
    }

    @Override
    public void Boot() throws Throwable {
        System.out.println("Booting Device3:");
        cpu.Execute(program, memory);
        System.out.println();
    }
}
