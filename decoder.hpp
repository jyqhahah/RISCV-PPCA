//
// Created by jiayuqi on 19-7-3.
//

#ifndef RISCV_INST_HPP
#define RISCV_INST_HPP
#include <cstring>
#include <iostream>
using namespace SJTU_JYQ;
//inst A(reg, &pc);
class decoder{
public:
    uint32_t _inst;
    decoder(uint32_t _inst):_inst(_inst){}
    int funct = (_inst >> 12) & 0x7, opcode = _inst & 0x7f;
    int rd = (_inst >> 7) & 0x1f;
    int rs1 = (_inst >> 15) & 0x1f;
    int rs2 = (_inst >> 20) & 0x1f;

    //inst(int *x, int *y) : ptr_reg(x), ptr_pc(y) {}

    instruction get_inst() {
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

/*    int get_imm1(InstType t) {
        switch (t) {
            case R_TYPE:
                break;
            case I_TYPE: {
                int tmp_31 = _inst >> 31, tmp_30_20 = (_inst >> 20) & 0x7ff;
                if (tmp_31 == 1) return ((-1) << 11) | tmp_30_20;
                else return tmp_30_20;
            }
            case S_TYPE: {
                int tmp_31 = _inst >> 31, tmp_30_25 = (_inst >> 25) & 0x3f, tmp_11_7 = (_inst >> 7) & 0x1f;
                if (tmp_31 == 1) return ((-1) << 11) | (tmp_30_25 << 5) | tmp_11_7;
                else return (tmp_30_25 << 5) | tmp_11_7;
            }
            case SB_TYPE: {
                int tmp_31 = _inst >> 31, tmp_30_25 = (_inst >> 25) & 0x3f, tmp_11_8 = (_inst >> 8) & 0xf, tmp_7 =
                        (_inst >> 7) & 0x1;
                if (tmp_31 == 1) return ((-1) << 12) | (tmp_7 << 11) | (tmp_30_25 << 5) | (tmp_11_8 << 1) | 0x0;
                else return (tmp_7 << 11) | (tmp_30_25 << 5) | (tmp_11_8 << 1) | 0x0;
            }
            case U_TYPE:
                return (_inst >> 12) << 12;
            case UJ_TYPE: {
                int imm;
                int tmp_31 = _inst >> 31, tmp_30_21 = (_inst >> 21) & 0x3ff, tmp_20 = (_inst >> 20) & 0x1, tmp_19_12 =
                        (_inst >> 12) & 0xff;
                if (tmp_31 == 1) return (((-1) << 20) | (tmp_19_12 << 12) | (tmp_20 << 11) | (tmp_30_21 << 1))<<1;
                else return (tmp_19_12 << 12) | (tmp_20 << 11) | (tmp_30_21 << 1);
            }
        }
    }
    */

    int get_imm(InstType t){
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

    instruction decode() {
        instruction tmp;
        tmp = get_inst();
        tmp.imm = get_imm(tmp.type);
        tmp.rd = rd;
        tmp.rs1 = rs1;
        tmp.rs2 = rs2;
        return tmp;
    }
};
#endif //RISCV_INST_HPP
