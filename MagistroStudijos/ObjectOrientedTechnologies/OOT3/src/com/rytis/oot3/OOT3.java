/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3;

import com.rytis.oot3.CPUs.BrainfuckCPU;
import com.rytis.oot3.CPUs.CPU;
import com.rytis.oot3.container.Container;
import com.rytis.oot3.container.MyContainer;
import com.rytis.oot3.devices.Device;
import com.rytis.oot3.devices.Device1;
import com.rytis.oot3.devices.Device2;
import com.rytis.oot3.devices.DeviceDecorator;
import com.rytis.oot3.devices.Device3;
import com.rytis.oot3.devices.Device4;
import com.rytis.oot3.devices.DeviceSelfCheck;
import com.rytis.oot3.devices.DeviceSelfChecker;
import com.rytis.oot3.memories.Memory;
import com.rytis.oot3.memories.RAM;

/**
 *
 * @author rytis
 */
public class OOT3 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Throwable {

        Container container = new MyContainer();

        container.Register(Memory.class, RAM.class);
        container.Register(CPU.class, BrainfuckCPU.class);
        container.Register(Device.class, Device1.class);
        container.Register(Device2.class, Device2.class);
        container.Register(DeviceDecorator.class, DeviceDecorator.class);
        container.Register(Device3.class, Device3.class);
        container.Register(DeviceSelfCheck.class, DeviceSelfChecker.class);
        container.Register(Device4.class, Device4.class);

        Device device;
        System.out.println("====== Simple Example ======");
        device = (Device) container.Create(Device.class, false);
        device.Boot();
        
        System.out.println("====== Decorated Example ======");
        device = (Device) container.Create(Device2.class, false);
        device.Boot();
        
        System.out.println("====== Delegated Example ======");
        Object device3 = container.Create(Device3.class, false);
        ((DeviceSelfCheck)device3).PerformSelfCheck();
        ((Device)device3).Boot();
        
        System.out.println("====== Lazy Decorated Delegated Example ======");
        Object device4 = container.Create(Device4.class, true);
        System.out.println("Device 4 created lazily");
        ((DeviceSelfCheck) device4).PerformSelfCheck();
        ((Device) device4).Boot();
    }
}
