/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2_Juice.processors;

import com.google.inject.Singleton;
import com.rytis.oot2_Juice.memories.Memory;

/**
 *
 * @author rytis
 */
@Singleton
public class Fuck4CPU implements CPU {

    private Integer IP = 0;
    private Integer pointer = 0;

    private Integer FindMatchingClosingParanthesis(Integer pos, String program) {
        int count = 1;

        do {
            pos++;
            char instruction = program.charAt(pos);
            if (instruction == 'u') {
                count++;
            } else if (instruction == 'k') {
                count--;
            }
        } while (count != 0);

        return pos;
    }

    private Integer FindMatchingOpeningParanthesis(Integer pos, String program) {
        int count = 1;

        do {
            pos--;
            char instruction = program.charAt(pos);
            if (instruction == 'k') {
                count++;
            } else if (instruction == 'u') {
                count--;
            }
        } while (count != 0);

        return pos;
    }

    @Override
    public void Execute(String program, Memory memory) throws Throwable {
        
        IP = 0;
        pointer = 0;

        while (IP < program.length()) {

            switch (program.charAt(IP)) {
                case 'c':
                    pointer = (pointer + 1) & 7;

                    byte moveByte = memory.Load(1);
                    if (pointer == 2 && moveByte == 2) {
                        byte inByte = (byte) System.in.read();
                        memory.Store(0, inByte);
                    }

                    if (pointer == 2 && moveByte == 1) {
                        byte outByte = memory.Load(0);
                        System.out.print((char)outByte);
                    }
                    
                    if (pointer == 2)
                        memory.Store(1, (byte)0);
                    break;

                case 'f':
                    byte incByte = memory.Load(pointer);
                    incByte = (byte)((incByte + 1) & 127);
                    memory.Store(pointer, incByte);
                    break;

                case 'u':
                    byte branchStartByte = memory.Load(pointer);
                    if (branchStartByte == 0) {
                        IP = FindMatchingClosingParanthesis(IP, program);
                    }
                    break;

                case 'k':
                    byte branchEndByte = memory.Load(pointer);
                    if (branchEndByte != 0) {
                        IP = FindMatchingOpeningParanthesis(IP, program);
                    }
                    break;

                default:
                    break;
            }

            IP++;
        }
    }
}
