/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot3.memories;

import java.io.RandomAccessFile;

/**
 *
 * @author rytis
 */
public class Disk implements Memory {

    public RandomAccessFile disk;

    public Disk() throws Throwable {
        this.disk = new RandomAccessFile("/tmp/disk", "rw");
        disk.setLength(0);
    }

    @Override
    public void Store(int address, byte value) throws Throwable {
        disk.seek(address);
        disk.writeByte(value);
    }

    @Override
    public byte Load(int address) throws Throwable {
        if (address < 0 || address >= disk.length()) {
            return 0;
        }

        disk.seek(address);
        return disk.readByte();
    }
}
