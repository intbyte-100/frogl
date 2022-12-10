#pragma once

#include "util/retval_args_buffer.h"

namespace frogl {
    void* interpret(unsigned char* function_start, unsigned short frame_size, unsigned char *const_table, frogl::retval_args_buffer *retval_args_buffer);
}