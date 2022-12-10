#pragma once

#include <cstddef>

namespace frogl {
    typedef unsigned char byte;

    class const_table {

    public:
        byte* table;
        const_table(size_t size);

        template<typename T>
        inline T& at(int index){
            return ((T*)(&table[index*4]))[0];
        }
    };
}
