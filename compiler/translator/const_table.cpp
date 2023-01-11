//
// Created by intbyte on 12/8/22.
//

#include "const_table.h"

frogl::const_table::const_table(size_t size) {
    table = new byte[size * 4];
}
