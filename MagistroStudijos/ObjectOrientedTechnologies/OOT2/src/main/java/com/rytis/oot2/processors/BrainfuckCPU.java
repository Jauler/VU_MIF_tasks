/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.rytis.oot2.processors;

import com.rytis.oot2.memories.Memory;

/**
 *
 * @author rytis
 */
public class BrainfuckCPU implements CPU {

    private Integer IP = 0;
    private Integer pointer = 0;

    private Integer FindMatchingClosingParanthesis(Integer pos, String program) {
        int count = 1;

        do {
            pos++;
            char instruction = program.charAt(pos);
            if (instruction == '[') {
                count++;
            } else if (instruction == ']') {
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
            if (instruction == ']') {
                count++;
            } else if (instruction == '[') {
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
                case '>':
                    pointer++;
                    break;

                case '<':
                    pointer--;
                    break;

                case '+':
                    byte incByte = memory.Load(pointer);
                    incByte++;
                    memory.Store(pointer, incByte);
                    break;

                case '-':
                    byte decByte = memory.Load(pointer);
                    decByte--;
                    memory.Store(pointer, decByte);
                    break;

                case '.':
                    byte outByte = memory.Load(pointer);
                    System.out.print((char) outByte);
                    break;

                case ',':
                    byte inByte = (byte) System.in.read();
                    memory.Store(pointer, inByte);
                    break;

                case '[':
                    byte branchStartByte = memory.Load(pointer);
                    if (branchStartByte == 0) {
                        IP = FindMatchingClosingParanthesis(IP, program);
                    }
                    break;

                case ']':
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
