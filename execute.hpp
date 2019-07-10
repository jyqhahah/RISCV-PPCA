//
// Created by jiayuqi on 19-7-3.
//

#ifndef RISCV_EXECUTE_HPP
#define RISCV_EXECUTE_HPP

#include "parser.hpp"

using namespace std;
using namespace SJTU_JYQ;
class execute{
public:
    void JUMP_inst(IF_ID &if_id, ID_EX &id_ex, EX_MEM &ex_mem, predict &predictor){
        bool predict_result = predictor.getPredict(id_ex.inst.inst), willJump;
        switch(id_ex.inst.inst){
            case BEQ: {
                willJump = id_ex.reg_rs1 == id_ex.reg_rs2;
                if(predict_result == willJump) break;
                if (willJump && !predict_result){
                    pc = id_ex.NPC + id_ex.inst.imm;
                    if_id.predJump = false;
                }
                else if(!willJump && predict_result){
                    pc = id_ex.NPC + 4;
                    if_id.predJump = false;
                }
                if_id.isNext = 0;
                break;
            }
            case BNE:{
                willJump = id_ex.reg_rs1 != id_ex.reg_rs2;
                if(predict_result == willJump) break;
                if (willJump && !predict_result){
                    pc = id_ex.NPC + id_ex.inst.imm;
                    if_id.predJump = false;
                }
                else if(!willJump && predict_result){
                    pc = id_ex.NPC + 4;
                    if_id.predJump = false;
                }
                if_id.isNext = 0;
                break;
            }
            case BLT:{
                willJump = id_ex.reg_rs1 < id_ex.reg_rs2;
                if(predict_result == willJump) break;
                if (willJump && !predict_result){
                    pc = id_ex.NPC + id_ex.inst.imm;
                    if_id.predJump = false;
                }
                else if(!willJump && predict_result){
                    pc = id_ex.NPC + 4;
                    if_id.predJump = false;
                }
                if_id.isNext = 0;
                break;
            }
            case BGE:{
                willJump = id_ex.reg_rs1 >= id_ex.reg_rs2;
                if(predict_result == willJump) break;
                if (willJump && !predict_result){
                    pc = id_ex.NPC + id_ex.inst.imm;
                    if_id.predJump = false;
                }
                else if(!willJump && predict_result){
                    pc = id_ex.NPC + 4;
                    if_id.predJump = false;
                }
                if_id.isNext = 0;
                break;
            }
            case BLTU:{
                unsigned u_rs1 = Reg[id_ex.inst.rs1];
                unsigned u_rs2 = Reg[id_ex.inst.rs2];
                willJump = u_rs1 < u_rs2;
                if(predict_result == willJump) break;
                if (willJump && !predict_result){
                    pc = id_ex.NPC + id_ex.inst.imm;
                    if_id.predJump = false;
                }
                else if(!willJump && predict_result){
                    pc = id_ex.NPC + 4;
                    if_id.predJump = false;
                }
                if_id.isNext = 0;
                break;
            }
            case BGEU:{
                unsigned u_rs1 = Reg[id_ex.inst.rs1];
                unsigned u_rs2 = Reg[id_ex.inst.rs2];
                willJump = u_rs1 >= u_rs2;
                if(predict_result == willJump) break;
                if (willJump && !predict_result){
                    pc = id_ex.NPC + id_ex.inst.imm;
                    if_id.predJump = false;
                }
                else if(!willJump && predict_result){
                    pc = id_ex.NPC + 4;
                    if_id.predJump = false;
                }
                if_id.isNext = 0;
                break;
            }
            default:
                return;
        }
        predictor.updateTable(willJump, id_ex.NPC + id_ex.inst.imm, id_ex.inst.inst);
    }

    void CALC_inst(IF_ID &if_id, ID_EX &id_ex, EX_MEM &ex_mem){
        int check = 1;
        switch(id_ex.inst.inst){
            case JAL:{
                ex_mem.ALUOutput = id_ex.NPC + 4;
                pc = id_ex.NPC + id_ex.inst.imm;
                if_id.isNext = 0;
                break;
            }
            case JALR:{
                ex_mem.ALUOutput = id_ex.NPC + 4;
                pc = (id_ex.reg_rs1 + id_ex.inst.imm) & (-2);
                if_id.isNext = 0;
                break;
            }
            case LUI:   {
                ex_mem.ALUOutput = id_ex.inst.imm;
                break;
            }
            case AUIPC: {
                if_id.isNext = 0;
                pc = id_ex.NPC + id_ex.inst.imm;
                ex_mem.ALUOutput = id_ex.NPC + id_ex.inst.imm;
                break;
            }
            case ADDI:{
                ex_mem.ALUOutput = id_ex.reg_rs1 + id_ex.inst.imm;
                break;
            }
            case SLTI:{
                ex_mem.ALUOutput = id_ex.reg_rs1 < id_ex.inst.imm;
                break;
            }
            case SLTIU:{
                unsigned imm = id_ex.inst.imm;
                unsigned tmp = Reg[id_ex.inst.rs2];
                ex_mem.ALUOutput = (tmp < imm);
                break;
            }
            case XORI:{
                ex_mem.ALUOutput = id_ex.reg_rs1 ^ id_ex.inst.imm;
                break;
            }
            case ORI:{
                ex_mem.ALUOutput = id_ex.reg_rs1 | id_ex.inst.imm;
                break;
            }
            case ANDI:{
                ex_mem.ALUOutput = id_ex.reg_rs1 & id_ex.inst.imm;
                break;
            }
            case SLLI:{
                unsigned imm = id_ex.inst.imm;
                ex_mem.ALUOutput = id_ex.reg_rs1 << (int)((imm<<27)>>27);
                break;
            }
            case SRLI:{
                unsigned imm = id_ex.inst.imm;
                unsigned u_rs1 = id_ex.reg_rs1;
                ex_mem.ALUOutput = u_rs1 >> (int)((imm<<27)>>27);
                break;
            }
            case SRAI:{
                unsigned imm = id_ex.inst.imm;
                ex_mem.ALUOutput = id_ex.reg_rs1 >> (int)((imm<<27)>>27);
                break;
            }
            case ADD:{
                ex_mem.ALUOutput = id_ex.reg_rs1 + id_ex.reg_rs2;
                break;
            }
            case SUB:{
                ex_mem.ALUOutput = id_ex.reg_rs1 - id_ex.reg_rs2;
                break;
            }
            case SLL:{
                ex_mem.ALUOutput = id_ex.reg_rs1 << id_ex.reg_rs2;
                break;
            }
            case SLT:{
                ex_mem.ALUOutput = id_ex.reg_rs1 < id_ex.reg_rs2;
                break;
            }
            case SLTU:{
                unsigned u_rs1 = id_ex.reg_rs1;
                unsigned u_rs2 = id_ex.reg_rs2;
                ex_mem.ALUOutput = u_rs1 < u_rs2;
                break;
            }
            case XOR:{
                ex_mem.ALUOutput = id_ex.reg_rs1 ^ id_ex.reg_rs2;
                break;
            }
            case SRL:{
                unsigned u_rs1 = id_ex.reg_rs1;
                unsigned u_rs2 = id_ex.reg_rs2;
                ex_mem.ALUOutput = u_rs1 >> u_rs2;
                break;
            }
            case SRA:{
                ex_mem.ALUOutput = id_ex.reg_rs1 >> id_ex.reg_rs2;
                break;
            }
            case OR:{
                ex_mem.ALUOutput = id_ex.reg_rs1 | id_ex.reg_rs2;
                break;
            }
            case AND:{
                ex_mem.ALUOutput = id_ex.reg_rs1 & id_ex.reg_rs2;
                break;
            }
            default:check = 0;
                break;
        }
        if(check == 1) ex_mem.inst.rd = id_ex.inst.rd;
    }

    void L_S_inst(IF_ID &if_id, ID_EX &id_ex, EX_MEM &ex_mem){
        switch(id_ex.inst.inst) {
            case LB:
            case LH:
            case LW:
            case LBU:
            case LHU:
            {
                ex_mem.inst.rd = id_ex.inst.rd;
                ex_mem.ALUOutput = id_ex.reg_rs1 + id_ex.inst.imm;
                break;
            }
            case SB:
            case SH:
            case SW:
            {
                ex_mem.inst.rd = id_ex.inst.rd;
                ex_mem.reg_rs2 = id_ex.reg_rs2;
                ex_mem.ALUOutput = id_ex.reg_rs1 + id_ex.inst.imm;
                break;
            }
            default:
                break;
        }
    }

    void exe(IF_ID &if_id, ID_EX &id_ex, EX_MEM &ex_mem, predict &predictor){
        if(!id_ex.isNext || !id_ex.avail || !ex_mem.free) return;
        //std::cout<<"exe "<<dec<<id_ex.inst.inst_32<<endl;
        ex_mem.inst.inst = id_ex.inst.inst;
        ex_mem.inst.type = id_ex.inst.type;
        ex_mem.inst.inst_32 = id_ex.inst.inst_32;
        JUMP_inst(if_id, id_ex, ex_mem, predictor);
        CALC_inst(if_id, id_ex, ex_mem);
        L_S_inst(if_id, id_ex, ex_mem);
        id_ex.isNext = 0;
        ex_mem.isNext = 1;
    }

};

#endif //RISCV_EXECUTE_HPP
