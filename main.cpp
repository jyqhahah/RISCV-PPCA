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
    freopen("queens.data", "r" ,stdin);
    memset(mem, 0, sizeof(mem));
    _read.Read();
    Reg[0] = 0;
    while(true){
       // cout  <<"while pc " << pc << endl;
        uint32_t code=0;
        _read.fetch(code);
        if(pc == 4188) {
            int x;
            cin>>x;
        }
      //  cout <<"if " << hex <<' ' <<code << endl;
        if(code == 0x00c68223) break;
        //if(code == 0x000180a9) break;
        decoder _dec(code);
        instruction _in = _dec.decode();
        execute _exe(_in);
        _exe.exe();
        memory _mem(_in);
        _mem.memo();
        writeBack _write(_in);
        _write.write();
        Reg[0] = 0;
        //cout <<" end " << hex << Reg[_in.rs1] << ' ' << Reg[_in.rs2] << ' ' <<_in.imm << endl;
    }
    std::cout<<dec<<(Reg[10]&0xff)<<std::endl;
    return 0;
}