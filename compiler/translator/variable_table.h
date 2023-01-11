#pragma once


#include <string>
#include <map>

namespace frogl {

    struct type {
        int type_id;
        int size;
    };

    struct variable {
        int type_id;
        int address;
    };

    class variable_table {
        int next_id = 0;
        int next_address;
        std::map<std::string, variable> map;

    public:
        void define(type type, std::string name);
    };
}

