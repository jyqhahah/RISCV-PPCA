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
}
#endif //RISCV_PARSER_HPP
