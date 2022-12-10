#include "fbc_buffer.h"

void frogl::fbc_buffer::three_argument_opcode(frogl::opcodes opcode, frogl::byte a, frogl::byte b, frogl::byte c) {
    code.resize(code.size() + 4);
    byte *instruction = &code[code.size() - 4];
    instruction[0] = static_cast<byte>(opcode);
    instruction[1] = a;
    instruction[2] = b;
    instruction[3] = c;
}

void frogl::fbc_buffer::two_argument_opcode(frogl::opcodes opcode, frogl::byte a, frogl::byte b) {
    code.resize(code.size() + 3);
    byte *instruction = &code[code.size() - 3];
    instruction[0] = static_cast<byte>(opcode);
    instruction[1] = a;
    instruction[2] = b;
}

void frogl::fbc_buffer::addi32(frogl::byte direction, frogl::byte a, frogl::byte b) {
    three_argument_opcode(opcodes::addi32, direction, a, b);
}


void frogl::fbc_buffer::subi32(frogl::byte direction, frogl::byte a, frogl::byte b) {
    three_argument_opcode(opcodes::subi32, direction, a, b);
}

void frogl::fbc_buffer::muli32(frogl::byte direction, frogl::byte a, frogl::byte b) {
    three_argument_opcode(opcodes::muli32, direction, a, b);
}

void frogl::fbc_buffer::movi32(frogl::byte direction, frogl::byte source) {
    two_argument_opcode(opcodes::movi32, direction, source);
}

void frogl::fbc_buffer::ptmovi32(frogl::byte direction, frogl::byte source) {
    two_argument_opcode(opcodes::ptmovi32, direction, source);
}

void frogl::fbc_buffer::tpmovi32(frogl::byte direction, frogl::byte source) {
    two_argument_opcode(opcodes::tpmovi32, direction, source);
}

frogl::byte *frogl::fbc_buffer::pointer() {
    return &code[0];
}

void frogl::fbc_buffer::ret() {
    code.push_back(0);
}

void frogl::fbc_buffer::reti32(frogl::byte val) {
    code.push_back(opcodes::reti32);
    code.push_back(val);
}

void frogl::fbc_buffer::getai32(frogl::byte address, frogl::byte argument) {
    two_argument_opcode(opcodes::getai32, address, argument);
    return;
}
