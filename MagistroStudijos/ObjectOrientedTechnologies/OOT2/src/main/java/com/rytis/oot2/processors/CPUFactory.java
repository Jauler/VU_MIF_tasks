/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2.processors;

import com.rytis.oot2.processors.BrainfuckCPU;
import com.rytis.oot2.processors.CPU;
import com.rytis.oot2.processors.Fuck4CPU;
import org.springframework.beans.factory.FactoryBean;

/**
 *
 * @author rytis
 */
public class CPUFactory implements FactoryBean<CPU> {

    private final String model;

    public CPUFactory(String model) {
        this.model = model;
    }

    @Override
    public CPU getObject() throws Exception {
        CPU cpu;
        if (this.model.equals("model1"))
            cpu = new BrainfuckCPU();
        else if (this.model.equals("model2"))
            cpu = new Fuck4CPU();
        else
            throw new UnsupportedOperationException("Could not recognize instruction set");
        
        return cpu;
    }
    
    @Override
    public Class<CPU> getObjectType() {
        return CPU.class;
    }
    
    @Override
    public boolean isSingleton() {
        return false;
    }
}
