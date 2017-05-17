/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2.memories;

/**
 *
 * @author rytis
 */
public interface Memory {

    public void Store(int address, byte value) throws Throwable;
    public byte Load(int address) throws Throwable;
}
