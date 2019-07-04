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
        //std::cout << "Read" << std::endl;
        int p = 0;
        char buffer[20];
        while (scanf("%s", buffer) != EOF) {
            if (buffer[0] == '@') {
                sscanf(buffer + 1, "%x", &p);
                //printf("pc : %x\n", p);
            }
            else {
                uint32_t a1, a2, a3, a4;
                sscanf(buffer, "%x", &a1);
                scanf("%x%x%x", &a2, &a3, &a4);
                unsigned int tmp = (a4 << 24) | (a3 << 16) | (a2 << 8) | a1;
                memcpy(mem + p, &tmp, sizeof(tmp));
                //printf("mem : %x %x %x %x\n", mem[p], mem[p + 1], mem[p + 2], mem[p + 3]);
                p += 4;
            }
        }
    }

    void fetch(uint32_t &code) {
        memcpy(&code, mem + pc, 4);
        //std::cout<<pc << ' ' <<std::hex<< code<<' '   << std::endl;
    }
};
#endif //RISCV_READ_HPP
