/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2;

import com.rytis.oot2.devices.Device;
import org.springframework.boot.SpringApplication;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.support.AbstractApplicationContext;

/**
 *
 * @author rytis
 */
public class AppJavaConfig {

    public static void run(String[] args) throws Throwable {
        SpringApplication.run(AppJavaConfig.class, args);
        AnnotationConfigApplicationContext applicationContext = new AnnotationConfigApplicationContext();
        applicationContext.scan("com.rytis.oot2");
        applicationContext.refresh();

        Device device;
        device = applicationContext.getBean("device1", Device.class);
        device.Boot();
        device = applicationContext.getBean("device2", Device.class);
        device.Boot();
        device = applicationContext.getBean("device3", Device.class);
        device.Boot();
        device = applicationContext.getBean("device4", Device.class);
        device.Boot();
        device = applicationContext.getBean("device5", Device.class);
        device.Boot();
        device = applicationContext.getBean("device7", Device.class);
        device.Boot();
        device = applicationContext.getBean("device8", Device.class);
        device.Boot();

        ((AbstractApplicationContext) applicationContext).close();

    }

}
