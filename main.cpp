#include <iostream>
#include "parser.hpp"
#include "decoder.hpp"
#include "execute.hpp"
#include "memory.hpp"
#include "read.hpp"
#include "writeBack.hpp"

using namespace std;
int main() {
    read _read;
    freopen("pi.data", "r" ,stdin);
    memset(mem, 0, sizeof(mem));
    _read.Read();
    decoder _dec;
    execute _exe;
    memory _mem;
    writeBack _write;
    Reg[0] = 0;
    IF_ID if_id;if_id.avail = if_id.free = 1;if_id.isNext = 0;
    ID_EX id_ex;id_ex.avail = id_ex.free = 1;id_ex.isNext = 0;
    EX_MEM ex_mem;ex_mem.avail = ex_mem.free = 1;ex_mem.isNext = 0;
    MEM_WB mem_wb;mem_wb.avail = mem_wb.free = 1;mem_wb.isNext = 0;
    while(if_id.inst.inst_32 != 0x00c68223){
        _write.write(mem_wb);
        Reg[0] = 0;
        _mem.memo(if_id, id_ex, ex_mem, mem_wb);
        Reg[0] = 0;
        _exe.exe(if_id, id_ex, ex_mem);
        Reg[0] = 0;
        _dec.decode(if_id, id_ex, ex_mem, mem_wb);
        Reg[0] = 0;
        _read.fetch(if_id);
        Reg[0] = 0;
    }
    while(mem_wb.isNext || ex_mem.isNext){
        _write.write(mem_wb);
        Reg[0] = 0;
        _mem.memo(if_id, id_ex, ex_mem, mem_wb);
        Reg[0] = 0;
        _exe.exe(if_id, id_ex, ex_mem);
        Reg[0] = 0;
    }
    std::cout<<dec<<(Reg[10]&0xff)<<std::endl;
    return 0;
}