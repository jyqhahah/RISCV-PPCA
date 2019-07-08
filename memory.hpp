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
    void memo(IF_ID &if_id, ID_EX &id_ex, EX_MEM &ex_mem, MEM_WB &mem_wb){
        static int loop_num = 1;
        if(!ex_mem.avail||!ex_mem.isNext) return;
        if(loop_num == 3){
            if_id.free = id_ex.free = ex_mem.free = 1;
            loop_num = 1;
        }
        else{
            if_id.free = id_ex.free = ex_mem.free = 0;
            loop_num++;
            return;
        }
        mem_wb.inst = ex_mem.inst;
        mem_wb.ALUOutput = ex_mem.ALUOutput;
        switch(ex_mem.inst.inst){
            case LB:{
                int8_t tmp;
                memcpy(&tmp, mem + ex_mem.ALUOutput, 1);
                mem_wb.ALUOutput = tmp;
                break;
            }
            case LH:{
                int16_t tmp;
                memcpy(&tmp, mem + ex_mem.ALUOutput, 2);
                mem_wb.ALUOutput = tmp;
                break;
            }
            case LW:{
                int tmp;
                memcpy(&tmp, mem + ex_mem.ALUOutput, 4);
                mem_wb.ALUOutput = tmp;
                break;
            }
            case LBU:{
                uint8_t tmp;
                memcpy(&tmp, mem + ex_mem.ALUOutput, 1);
                mem_wb.ALUOutput = tmp;
                break;
            }
            case LHU:{
                uint16_t tmp;
                memcpy(&tmp, mem + ex_mem.ALUOutput, 2);
                mem_wb.ALUOutput = tmp;
                break;
            }
            case SB:{
                uint8_t tmp = ex_mem.reg_rs2;
                memcpy(mem + ex_mem.ALUOutput, &tmp, 1);
                break;
            }
            case SH:{
                uint16_t tmp = ex_mem.reg_rs2;
                memcpy(mem + ex_mem.ALUOutput, &tmp, 2);
                break;
            }
            case SW:{
                memcpy(mem + ex_mem.ALUOutput, &ex_mem.reg_rs2, 4);
                break;
            }
            default:{
                if(ex_mem.inst.type == U_TYPE || ex_mem.inst.type == R_TYPE || ex_mem.inst.type == I_TYPE) {
                    mem_wb.ALUOutput = ex_mem.ALUOutput;
                }
                break;
            }
        }
        ex_mem.isNext = 0;
        mem_wb.isNext = 1;
    }
};
#endif //RISCV_MEMORY_HPP
