//
// Created by jiayuqi on 19-7-3.
//

#ifndef RISCV_INST_HPP
#define RISCV_INST_HPP
#include <cstring>
#include <iostream>
using namespace SJTU_JYQ;
class decoder{
public:
    instruction get_inst(uint32_t _inst) {
        int funct = (_inst >> 12) & 0x7, opcode = _inst & 0x7f;
        int rd = (_inst >> 7) & 0x1f;
        int rs1 = (_inst >> 15) & 0x1f;
        int rs2 = (_inst >> 20) & 0x1f;
        switch (opcode) {
            case 0x37:
                return instruction(LUI, U_TYPE);
            case 0x17:
                return instruction(AUIPC, U_TYPE);
            case 0x6f:
                return instruction(JAL, UJ_TYPE);
            case 0x67:
                return instruction(JALR, I_TYPE);
            case 0x63:
                switch (funct) {
                    case 0x0:
                        return instruction(BEQ, SB_TYPE);
                    case 0x1:
                        return instruction(BNE, SB_TYPE);
                    case 0x4:
                        return instruction(BLT, SB_TYPE);
                    case 0x5:
                        return instruction(BGE, SB_TYPE);
                    case 0x6:
                        return instruction(BLTU, SB_TYPE);
                    case 0x7:
                        return instruction(BGEU, SB_TYPE);
                }
                break;
            case 0x3:
                switch (funct) {
                    case 0x0:
                        return instruction(LB, I_TYPE);
                    case 0x1:
                        return instruction(LH, I_TYPE);
                    case 0x2:
                        return instruction(LW, I_TYPE);
                    case 0x4:
                        return instruction(LBU, I_TYPE);
                    case 0x5:
                        return instruction(LHU, I_TYPE);
                }
                break;
            case 0x23:
                switch (funct) {
                    case 0x0:
                        return instruction(SB, S_TYPE);
                    case 0x1:
                        return instruction(SH, S_TYPE);
                    case 0x2:
                        return instruction(SW, S_TYPE);
                }
                break;
            case 0x13:
                switch (funct) {
                    case 0x0:
                        return instruction(ADDI, I_TYPE);
                    case 0x2:
                        return instruction(SLTI, I_TYPE);
                    case 0x3:
                        return instruction(SLTIU, I_TYPE);
                    case 0x4:
                        return instruction(XORI, I_TYPE);
                    case 0x6:
                        return instruction(ORI, I_TYPE);
                    case 0x7:
                        return instruction(ANDI, I_TYPE);
                    case 0x1:
                        return instruction(SLLI, I_TYPE);
                    case 0x5:
                        if ((_inst >> 30) & 1)
                            return instruction(SRAI, I_TYPE);
                        else
                            return instruction(SRLI, I_TYPE);
                }
                break;
            case 0x33:
                switch (funct) {
                    case 0x0:
                        if ((_inst >> 30) & 1)
                            return instruction(SUB, R_TYPE);
                        else
                            return instruction(ADD, R_TYPE);
                    case 0x1:
                        return instruction(SLL, R_TYPE);
                    case 0x2:
                        return instruction(SLT, R_TYPE);
                    case 0x3:
                        return instruction(SLTU, R_TYPE);
                    case 0x4:
                        return instruction(XOR, R_TYPE);
                    case 0x5:
                        if ((_inst >> 30) & 1)
                            return instruction(SRA, R_TYPE);
                        else
                            return instruction(SRL, R_TYPE);
                    case 0x6:
                        return instruction(OR, R_TYPE);
                    case 0x7:
                        return instruction(AND, R_TYPE);
                }
        }
    }

    int get_imm(InstType t, uint32_t _inst){
        switch(t){
            case U_TYPE: {
                int tmp = _inst;
                return (tmp >> 12) << 12;
            }
            case UJ_TYPE:{
                int imm;
                imm = -(_inst >> 31) << 20;
                imm += ((_inst << 1) >> 22) << 1;
                imm += ((_inst << 11) >> 31) << 11;
                imm += ((_inst << 12) >> 24) << 12;
                return imm;
            }
            case S_TYPE: {
                int tmp = _inst;
                int imm = (tmp >> 25) << 5;
                imm += (_inst << 20) >> 27;
                return imm;
            }
            case SB_TYPE: {
                int imm_11 = ((_inst >> 7) & (0x1)) << 11;
                int imm_1_4 = ((_inst >> 8) & (0xf)) << 1;
                int imm_12 = -(_inst >> 31) << 12;
                int imm_5_10 = ((_inst >> 25) & (0x3f)) << 5;
                int imm = imm_1_4 | imm_5_10 | imm_11 | imm_12;
                return imm;
            }
            case I_TYPE: {
                int tmp  = _inst;
                return (tmp >> 20);
            }
            default:return 0;
        }
    }

    void decode(IF_ID &if_id, ID_EX &id_ex, EX_MEM &ex_mem, MEM_WB &mem_wb){
        static bool pause = false;
        if(pause && !ex_mem.isNext && !mem_wb.isNext){
            if_id.avail = if_id.isNext = 1;
            id_ex.avail = id_ex.isNext = 1;
            pause = false;
        }
        if(!if_id.isNext || !id_ex.avail || !id_ex.free) return;
        //std::cout<<"decoder "<<std::dec<<if_id.inst.inst_32<<std::endl;
        if_id.isNext = 0;
        uint32_t _inst = if_id.inst.inst_32;
        instruction tmp;
        tmp = get_inst(_inst);
        tmp.inst_32 = _inst;
        id_ex.inst.type = tmp.type;
        id_ex.inst.inst = tmp.inst;
        id_ex.inst.inst_32 = tmp.inst_32;
        int funct = (_inst >> 12) & 0x7, opcode = _inst & 0x7f;
        int rd = (_inst >> 7) & 0x1f;
        int rs1 = (_inst >> 15) & 0x1f;
        int rs2 = (_inst >> 20) & 0x1f;
        id_ex.NPC = if_id.NPC;
        switch(id_ex.inst.type){
            case U_TYPE:
            case UJ_TYPE:id_ex.inst.rd = rd;id_ex.inst.imm = get_imm(id_ex.inst.type,_inst);break;
            case R_TYPE:{
                id_ex.inst.rs1 = rs1;
                id_ex.inst.rs2 = rs2;
                if((ex_mem.isNext&&(ex_mem.inst.rd == id_ex.inst.rs1 || ex_mem.inst.rd == id_ex.inst.rs2))||
                   (mem_wb.isNext&&(mem_wb.inst.rd == id_ex.inst.rs1 || mem_wb.inst.rd == id_ex.inst.rs2))){
                    if_id.avail = id_ex.avail = 0;
                    pause = true;
                    return;
                }
                id_ex.reg_rs1 = Reg[id_ex.inst.rs1];
                id_ex.reg_rs2 = Reg[id_ex.inst.rs2];
                id_ex.inst.rd = rd;
                if_id.avail = id_ex.avail = 1;
                pause = false;
                break;
            }
            case S_TYPE:{
                id_ex.inst.rs1 = rs1;
                id_ex.inst.rs2 = rs2;
                if((ex_mem.isNext&&(ex_mem.inst.rd == id_ex.inst.rs1 || ex_mem.inst.rd == id_ex.inst.rs2))||
                   (mem_wb.isNext&&(mem_wb.inst.rd == id_ex.inst.rs1 || mem_wb.inst.rd == id_ex.inst.rs2))){
                    if_id.avail = id_ex.avail = 0;
                    pause = true;
                    return;
                }
                id_ex.reg_rs1 = Reg[id_ex.inst.rs1];
                id_ex.reg_rs2 = Reg[id_ex.inst.rs2];
                id_ex.inst.imm = get_imm(id_ex.inst.type,_inst);
                if_id.avail = id_ex.avail = 1;
                pause = false;
                break;
            }
            case SB_TYPE:{
                id_ex.inst.rs1 = rs1;
                id_ex.inst.rs2 = rs2;
                id_ex.inst.imm = get_imm(id_ex.inst.type,_inst);
                if((ex_mem.isNext&&(ex_mem.inst.rd == id_ex.inst.rs1 || ex_mem.inst.rd == id_ex.inst.rs2))||
                   (mem_wb.isNext&&(mem_wb.inst.rd == id_ex.inst.rs1 || mem_wb.inst.rd == id_ex.inst.rs2))){
                    if_id.avail = id_ex.avail = 0;
                    pause = true;
                    return;
                }
                id_ex.reg_rs1 = Reg[id_ex.inst.rs1];
                id_ex.reg_rs2 = Reg[id_ex.inst.rs2];
                if_id.avail = id_ex.avail = 1;
                pause = false;
                break;
            }
            default:{
                id_ex.inst.rs1 = rs1;
                id_ex.inst.imm = get_imm(id_ex.inst.type,_inst);
                if((ex_mem.isNext&&ex_mem.inst.rd == id_ex.inst.rs1)||
                   (mem_wb.isNext&&mem_wb.inst.rd == id_ex.inst.rs1)){
                    if_id.avail = id_ex.avail = 0;
                    pause = true;
                    return;
                }
                id_ex.reg_rs1 = Reg[id_ex.inst.rs1];
                id_ex.inst.rd = rd;
                if_id.avail = id_ex.avail = 1;
                pause = false;
                break;
            }
        }
        id_ex.isNext = 1;
    }
};
#endif //RISCV_INST_HPP
