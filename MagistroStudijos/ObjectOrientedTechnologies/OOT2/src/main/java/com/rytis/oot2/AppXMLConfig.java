/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2;

import com.rytis.oot2.devices.Device;
import org.springframework.boot.*;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.AbstractApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 *
 * @author rytis
 */
@EnableAutoConfiguration
public class AppXMLConfig {

    public static void run(String[] args) throws Throwable {
        SpringApplication.run(AppXMLConfig.class, args);
        ClassPathXmlApplicationContext applicationContext = new ClassPathXmlApplicationContext("configuration.xml");

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
        device = applicationContext.getBean("device6", Device.class);
        device.Boot();
        device = applicationContext.getBean("device7", Device.class);
        device.Boot();
        device = applicationContext.getBean("device8", Device.class);
        device.Boot();

        ((AbstractApplicationContext)applicationContext).close();
    }
}
