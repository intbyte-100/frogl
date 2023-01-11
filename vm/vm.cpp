#include "vm.h"
#include "util/retval_args_buffer.h"
#include "util/context.h"

template<typename T>
inline T get_table_value(const frogl::context *context, unsigned char address) {
    return *(T *) ((address & 0b10000000) ?
                   &context->const_table[(address & 0b01111111) * sizeof(T)] :
                   &context->table[address * sizeof(T)]);
}

template<typename T>
inline void write_value_to_table(frogl::context *context, unsigned char address, T value) {
    *((T *) &context->table[address * sizeof(T)]) = value;
}

void frogl_ret(unsigned char *&codePointer, frogl::context *context) {
    context->status = 0;
}

void frogl_reti32(unsigned char *&codePointer, frogl::context *context) {
    *((int *) context->retval_args_buffer->retval) = get_table_value<int>(context, codePointer[0]);
    context->status = 0;
    codePointer++;
}

void frogl_getai32(unsigned char *&codePointer, frogl::context *context) {
    write_value_to_table<int>(context, codePointer[0], *(int *) context->retval_args_buffer->args[codePointer[1]]);
    codePointer += 2;
}

void frogl_addi32(unsigned char *&codePointer, frogl::context *context) {
    write_value_to_table(context, codePointer[0],
                         get_table_value<int>(context, codePointer[1]) +
                         get_table_value<int>(context, codePointer[2]));
    codePointer += 3;
}

void frogl_subi32(unsigned char *&codePointer, frogl::context *context) {
    write_value_to_table(context, codePointer[0],
                         get_table_value<int>(context, codePointer[1]) -
                         get_table_value<int>(context, codePointer[2]));
    codePointer += 3;
}


void frogl_muli32(unsigned char *&codePointer, frogl::context *context) {
    write_value_to_table(context, codePointer[0],
                         get_table_value<int>(context, codePointer[1]) +
                         get_table_value<int>(context, codePointer[2]));
    codePointer += 3;
}


void frogl_movi32(unsigned char *&codePointer, frogl::context *context) {
    write_value_to_table(context, codePointer[0], get_table_value<int>(context, codePointer[1]));
    codePointer += 2;
}


void frogl_tpmovi32(unsigned char *&codePointer, frogl::context *context) {
    write_value_to_table(context, codePointer[0], *(get_table_value<int *>(context, codePointer[1]) + 4));
    codePointer += 2;
}

void frogl_ptmovi32(unsigned char *&codePointer, frogl::context *context) {
    *(get_table_value<int *>(context, codePointer[0]) + 4) = get_table_value<int>(context, codePointer[1]);
    codePointer += 2;
}


void frogl_malloc(unsigned char *&codePointer, frogl::context *context) {
    write_value_to_table<frogl::byte *>(context, codePointer[0],
                                        new frogl::byte[get_table_value<int>(context, codePointer[1])]);
    codePointer += 2;
}

void frogl_muse(unsigned char *&codePointer, frogl::context *context) {
    *get_table_value<int *>(context, codePointer[0]) += 1;
    codePointer++;
}

void frogl_mfree(unsigned char *&codePointer, frogl::context *context) {
    auto ptr = get_table_value<int *>(context, codePointer[0]);
    *ptr -= 1;

    if (*ptr < 1)
        delete[] ptr;
}

void (*instr_interpreters[])(unsigned char *&codePointer, frogl::context *context){
        &frogl_ret,
        &frogl_reti32,
        &frogl_malloc,
        &frogl_muse,
        &frogl_mfree,
        &frogl_getai32,
        &frogl_movi32,
        &frogl_ptmovi32,
        &frogl_tpmovi32,
        &frogl_addi32,
        &frogl_subi32,
        &frogl_muli32,

};

void *frogl::interpret(unsigned char *function_start, unsigned short frame_size, unsigned char *const_table,
                       frogl::retval_args_buffer *retval_args_buffer) {
    unsigned char frameMemory[frame_size];

    unsigned char *&codePointer = function_start;

    frogl::context context(retval_args_buffer, const_table, &frameMemory[0]);

    while (context.status) {
        instr_interpreters[codePointer++[0]](codePointer, &context);
    }
}
