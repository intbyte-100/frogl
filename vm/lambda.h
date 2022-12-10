#pragma once

#include <utility>
#include "vm.h"
#include "util/const_table.h"

namespace frogl {

    class void_return {};



    template<typename R, class... T>
    class lambda {
        unsigned short frame_size;
        unsigned char *function_start;
        unsigned char* const_table;

    public:
        lambda(unsigned char* const_table, unsigned short frame_size, unsigned char *function_start)  {
            this->frame_size = frame_size;
            this->function_start = function_start;
            this->const_table = const_table;
        };


        inline R execute(T*... args){
            R retval;
            void * arguments[] {&retval, args...};

            interpret(function_start, frame_size, const_table, (frogl::retval_args_buffer*) &arguments);
            return retval;
        }

        inline R operator ()(T&&... args){
            return execute(&args...);
        }
    };

}

