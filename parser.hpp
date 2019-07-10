#ifndef RISCV_PARSER_HPP
#define RISCV_PARSER_HPP
namespace SJTU_JYQ{
    enum INST{
        LUI = 0,
        AUIPC = 1,
        JAL = 2,
        JALR = 3,
        BEQ = 4,
        BNE = 5,
        BLT = 6,
        BGE = 7,
        BLTU = 8,
        BGEU = 9,
        LB = 10,
        LH = 11,
        LW = 12,
        LBU = 13,
        LHU = 14,
        SB = 15,
        SH = 16,
        SW = 17,
        ADDI = 18,
        SLTI = 19,
        SLTIU = 20,
        XORI = 21,
        ORI = 22,
        ANDI = 23,
        SLLI = 24,
        SRLI = 25,
        SRAI = 26,
        ADD = 27,
        SUB = 28,
        SLL = 29,
        SLT =30,
        SLTU = 31,
        XOR = 32,
        SRL = 33,
        SRA = 34,
        OR = 35,
        AND = 36,
    };
    enum InstType {
        R_TYPE,
        I_TYPE,
        S_TYPE,
        SB_TYPE,
        U_TYPE,
        UJ_TYPE,
    };
    struct instruction{
        INST inst;
        unsigned int inst_32;
        InstType type;
        int imm;
        int rs1;
        int rs2;
        int rd;
        instruction(){}
        instruction(INST i, InstType t):inst(i),type(t){}
    };
    unsigned char mem[0x20100];
    int Reg[32],pc = 0x00000000;
    struct IF_ID{
        instruction inst;
        int NPC;
        int avail, isNext, free;
        bool predJump;
        int jump_pc;
    };
    struct ID_EX{
        instruction inst;
        int NPC;
        int avail, isNext, free;
        int reg_rs1, reg_rs2;
        bool predJump;
        int jump_pc;
    };
    struct EX_MEM{
        instruction inst;
        int avail, isNext, free;
        int ALUOutput;
        int reg_rs2;
    };
    struct MEM_WB{
        instruction inst;
        int ALUOutput;
        int avail, isNext, free;
    };
    struct predictor{
        bool pred1, pred2;
    };
    predictor caseTable[20];
}
using namespace SJTU_JYQ;
#include <cstring>
class predict{
public:
    predict(){
        memset(caseTable, 0, sizeof(caseTable));
    }
    bool getPredict(uint32_t _inst){
        int _pc = (_inst>>2) & 0xf;
        predictor pred = caseTable[_pc];
        if(pred.pred1 &&pred.pred2)   return true;
        if(!pred.pred1&&pred.pred2)   return false;
        if(!pred.pred1&&!pred.pred2)  return true;
        if(pred.pred1 &&!pred.pred2)  return false;
    }

    void updateTable(bool predCorrect, int addr, uint32_t _inst){
        int _pc = (_inst>>3) & 0xf;
        predictor pred = caseTable[_pc];
        if(predCorrect){
            if(!pred.pred1&&pred.pred2)  pred.pred1 = true;
            if(!pred.pred1&&!pred.pred2) pred.pred2 = true;
            if(pred.pred1 &&!pred.pred2) pred.pred2 = true;
        }
        else{
            if(pred.pred1&&pred.pred2)   pred.pred2 = false;
            if(!pred.pred1&&pred.pred2)  pred.pred2 = false;
            if(pred.pred1 &&!pred.pred2) pred.pred1 = false;
        }
        caseTable[_pc] = pred;
    }
};
#endif //RISCV_PARSER_HPP
