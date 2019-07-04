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
    instruction in;
    int _inst;
    execute(instruction in) : in(in){}
    void JUMP_inst(){
        switch(in.inst){
            case JAL:{
                Reg[in.rd] = pc+4;
                pc = pc + in.imm;
                break;
            }
            case JALR:{
                Reg[in.rd] = pc+4;
                pc = (Reg[in.rs1] + in.imm)&(-2);
                break;
            }
            case BEQ: {
                if (Reg[in.rs1] == Reg[in.rs2]){
                    pc = pc + in.imm;
                }
                else pc = pc + 4;
                break;
            }
            case BNE:{
                if(Reg[in.rs1] != Reg[in.rs2]) {
                    pc = pc + in.imm;
                }
                else pc = pc + 4;
                break;
            }
            case BLT:{
                if(Reg[in.rs1] < Reg[in.rs2]) {
                    pc = pc + in.imm;
                }
                else pc = pc + 4;
                break;
            }
            case BGE:{
                if(Reg[in.rs1] >= Reg[in.rs2]) {
                    pc = pc + in.imm;
                }
                else pc = pc + 4;
                break;
            }
            case BLTU:{
                unsigned u_rs1 = Reg[in.rs1];
                unsigned u_rs2 = Reg[in.rs2];
                if(u_rs1 < u_rs2) {
                    pc = pc + in.imm;
                }
                else pc = pc + 4;
                break;
            }
            case BGEU:{
                unsigned u_rs1 = Reg[in.rs1];
                unsigned u_rs2 = Reg[in.rs2];
                if(u_rs1 >= u_rs2) {
                    pc = pc + in.imm;
                }
                else pc = pc + 4;
                break;
            }
            default:
                break;
        }
    }

    void CALC_inst(){
        int check = 1;
        switch(in.inst){
            case LUI:   Reg[in.rd] = in.imm;break;
            case AUIPC: Reg[in.rd] = pc + in.imm;break;
            case ADDI:{
                Reg[in.rd] = Reg[in.rs1] + in.imm;
                break;
            }
            case SLTI:{
                Reg[in.rd] = Reg[in.rs1] < in.imm;
                break;
            }
            case SLTIU:{
                unsigned imm = in.imm;
                unsigned tmp = Reg[in.rs2];
                Reg[in.rd] = (tmp < imm);
                break;
            }
            case XORI:{
                Reg[in.rd] = Reg[in.rs1] ^ in.imm;
                break;
            }
            case ORI:{
                Reg[in.rd] = Reg[in.rs1] | in.imm;
                break;
            }
            case ANDI:{
                Reg[in.rd] = Reg[in.rs1] & in.imm;
                break;
            }
            case SLLI:{
                unsigned imm = in.imm;
                Reg[in.rd] = Reg[in.rs1] << (int)((imm<<27)>>27);
                break;
            }
            case SRLI:{
                unsigned imm = in.imm;
                unsigned u_rs1 = Reg[in.rs1];
                Reg[in.rd] = u_rs1 >> (int)((imm<<27)>>27);
                break;
            }
            case SRAI:{
                unsigned imm = in.imm;
                Reg[in.rd] = Reg[in.rs1] >> (int)((imm<<27)>>27);
                break;
            }
            case ADD:{
                Reg[in.rd] = Reg[in.rs1] + Reg[in.rs2];
                break;
            }
            case SUB:{
                Reg[in.rd] = Reg[in.rs1] - Reg[in.rs2];
                break;
            }
            case SLL:{
                Reg[in.rd] = Reg[in.rs1] << Reg[in.rs2];
                break;
            }
            case SLT:{
                Reg[in.rd] = Reg[in.rs1] < Reg[in.rs2];
                break;
            }
            case SLTU:{
                unsigned u_rs1 = Reg[in.rs1];
                unsigned u_rs2 = Reg[in.rs2];
                Reg[in.rd] = u_rs1 < u_rs2;
                break;
            }
            case XOR:{
                Reg[in.rd] = Reg[in.rs1] ^ Reg[in.rs2];
                break;
            }
            case SRL:{
                unsigned u_rs1 = Reg[in.rs1];
                unsigned u_rs2 = Reg[in.rs2];
                Reg[in.rd] = u_rs1 >> u_rs2;
                break;
            }
            case SRA:{
                Reg[in.rd] = Reg[in.rs1] >> Reg[in.rs2];
                break;
            }
            case OR:{
                Reg[in.rd] = Reg[in.rs1] | Reg[in.rs2];
                break;
            }
            case AND:{
                Reg[in.rd] = Reg[in.rs1] & Reg[in.rs2];
                break;
            }
            default: check = 0;
        }
        if(check) pc = pc + 4;
    }

    void exe(){
        JUMP_inst();
        CALC_inst();
    }
};

#endif //RISCV_EXECUTE_HPP
