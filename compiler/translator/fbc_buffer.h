#pragma once

#include <vector>
#include "opcodes.h"

namespace frogl {

    typedef unsigned char byte;
    class fbc_buffer {
    private:
        std::vector<byte> code;


    public:
        byte* pointer();
        void three_argument_opcode(opcodes opcode, byte a, byte b, byte c);
        void two_argument_opcode(opcodes opcode, byte a, byte b);
        void addi32(byte direction, byte a, byte b);
        void subi32(byte direction, byte a, byte b);
        void muli32(byte direction, byte a, byte b);
        void movi32(byte direction, byte source);
        void ptmovi32(byte direction, byte source);
        void tpmovi32(byte direction, byte source);
        void ret();
        void reti32(byte val);
        void getai32(byte address, byte argument);
    };

    static constexpr byte const_val(byte val) {
        return val | 0b10000000;
    }
}


