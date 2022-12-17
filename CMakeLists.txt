cmake_minimum_required(VERSION 3.21)
project(frogl)

set(CMAKE_CXX_STANDARD 14)

add_executable(frogl main.cpp vm/lambda.cpp vm/lambda.h vm/vm.cpp vm/vm.h vm/util/fbc_buffer.cpp vm/util/fbc_buffer.h vm/util/const_table.cpp vm/util/const_table.h vm/util/retval_args_buffer.h vm/util/context.h vm/compiler/parser/token.cpp vm/compiler/parser/token.h vm/compiler/parser/parser.cpp vm/compiler/parser/parser.h vm/compiler/parser/source.cpp vm/compiler/parser/source.h vm/compiler/parser/string_source.cpp vm/compiler/parser/string_source.h vm/compiler/parser/tokenizer.cpp vm/compiler/parser/tokenizer.h)
