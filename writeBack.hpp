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
    void write(MEM_WB &mem_wb){
        if(!mem_wb.avail || !mem_wb.isNext) return;
        switch (mem_wb.inst.type){
            case S_TYPE:case SB_TYPE:
                break;
            default: {
                Reg[mem_wb.inst.rd] = mem_wb.ALUOutput;
                break;
            }
        }
        mem_wb.isNext = 0;
    }
};
#endif //RISCV_WRITEBACK_HPP
