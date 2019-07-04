//
// Created by jiayuqi on 19-7-3.
//

#ifndef RISCV_MEMORY_HPP
#define RISCV_MEMORY_HPP

#include <cstring>
#include <iostream>
#include "parser.hpp"
#include <cstring>
using namespace SJTU_JYQ;
class memory{
public:
    instruction in;
    memory (instruction in) : in(in){}
    void memo(){
        int check = 1;
        switch(in.inst){
            case LB:{
                int8_t tmp;
                memcpy(&tmp, mem + Reg[in.rs1] + in.imm, 1);
                Reg[in.rd] = tmp;
                break;
            }
            case LH:{
                int16_t tmp;
                memcpy(&tmp, mem + Reg[in.rs1] + in.imm, 2);
                Reg[in.rd] = tmp;
                break;
            }
            case LW:{
                int tmp;
                memcpy(&tmp, mem + Reg[in.rs1] + in.imm, 4);
                Reg[in.rd] = tmp;
                break;
            }
            case LBU:{
                uint8_t tmp;
                memcpy(&tmp, mem + Reg[in.rs1] + in.imm, 1);
                Reg[in.rd] = tmp;
                break;
            }
            case LHU:{
                uint16_t tmp;
                memcpy(&tmp, mem + Reg[in.rs1] + in.imm, 2);
                Reg[in.rd] = tmp;
                break;
            }
            default: check = 0;
        }
        if(check) pc = pc + 4;
    }
};
#endif //RISCV_MEMORY_HPP
