//
// Created by jiayuqi on 19-7-3.
//

#ifndef RISCV_READ_HPP
#define RISCV_READ_HPP
#include <cstdio>
#include "parser.hpp"
#include <cstring>
using namespace SJTU_JYQ;
class read{
public:
    void Read() {
        int p = 0;
        char buffer[20];
        while (scanf("%s", buffer) != EOF) {
            if (buffer[0] == '@') {
                sscanf(buffer + 1, "%x", &p);
            }
            else {
                uint32_t a1, a2, a3, a4;
                sscanf(buffer, "%x", &a1);
                scanf("%x%x%x", &a2, &a3, &a4);
                unsigned int tmp = (a4 << 24) | (a3 << 16) | (a2 << 8) | a1;
                memcpy(mem + p, &tmp, sizeof(tmp));
                p += 4;
            }
        }
    }

    void fetch(IF_ID &if_id) {
        if(!if_id.free||!if_id.avail) return;
        uint32_t code;
        if(!if_id.predJump) {
            memcpy(&code, mem + pc, 4);
            if_id.NPC = pc;
            if_id.isNext = 1;
            if_id.inst.inst_32 = code;
            pc += 4;
        }
        else{
            memcpy(&code, mem + if_id.jump_pc, 4);
            if_id.NPC = if_id.jump_pc;
            if_id.isNext = 1;
            if_id.inst.inst_32 = code;
            pc = if_id.jump_pc + 4;
            if_id.predJump = false;
            if_id.jump_pc = 0;
        }
    }
};
#endif //RISCV_READ_HPP
