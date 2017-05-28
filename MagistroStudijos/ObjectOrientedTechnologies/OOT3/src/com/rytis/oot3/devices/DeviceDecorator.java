/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3.devices;

/**
 *
 * @author rytis
 */
public class DeviceDecorator {

    public void PreBoot() {
        System.out.println("Prebooting");
    }

    public void PostBoot() {
        System.out.println("postBooting");
    }
}
