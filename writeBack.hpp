//
// Created by jiayuqi on 19-7-4.
//

#ifndef RISCV_WRITEBACK_HPP
#define RISCV_WRITEBACK_HPP
#include <cstring>
#include <iostream>
#include "parser.hpp"
#include <cstring>
using namespace SJTU_JYQ;
class writeBack{
public:
    instruction in;
    writeBack (instruction in) : in(in){}
    void write(){
        int check = 1;
        switch(in.inst){
            case SB:{
                uint8_t tmp = Reg[in.rs2];
                memcpy(mem + Reg[in.rs1] + in.imm, &tmp, 1);
                break;
            }
            case SH:{
                uint16_t tmp = Reg[in.rs2];
                memcpy(mem + Reg[in.rs1] + in.imm, &tmp, 2);
                break;
            }
            case SW:{
                memcpy(mem + Reg[in.rs1] + in.imm, &Reg[in.rs2], 4);
                //
                break;
            }
            default:
                check = 0;
                break;
        }
        if(check) pc = pc + 4;
    }
};
#endif //RISCV_WRITEBACK_HPP
