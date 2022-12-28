cmake_minimum_required(VERSION 3.21)
project(frogl)

set(CMAKE_CXX_STANDARD 14)

add_executable(frogl main.cpp
        vm/lambda.cpp vm/lambda.h
        vm/vm.cpp vm/vm.h
        compiler/translator/fbc_buffer.cpp compiler/translator/fbc_buffer.h
        vm/util/const_table.cpp vm/util/const_table.h
        vm/util/retval_args_buffer.h
        vm/util/context.h
        compiler/parser/token.cpp compiler/parser/token.h
        compiler/parser/parser.cpp compiler/parser/parser.h
        compiler/source.cpp compiler/source.h
        compiler/string_source.cpp compiler/string_source.h
        compiler/parser/tokenizer.cpp compiler/parser/tokenizer.h
        compiler/sliced_string.h compiler/compiler.cpp compiler/compiler.h)
