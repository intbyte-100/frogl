cmake_minimum_required(VERSION 3.21)
project(frogl)

set(CMAKE_CXX_STANDARD 14)

add_executable(frogl main.cpp
        vm/lambda.cpp vm/lambda.h
        vm/vm.cpp vm/vm.h
        compiler/translator/fbc_buffer.cpp compiler/translator/fbc_buffer.h
        compiler/translator/const_table.cpp compiler/translator/const_table.h
        vm/util/retval_args_buffer.h
        vm/util/context.h
        compiler/token.cpp compiler/token.h
        compiler/parser/parser.cpp compiler/parser/parser.h
        compiler/source.cpp compiler/source.h
        compiler/string_source.cpp compiler/string_source.h
        compiler/parser/tokenizer.cpp compiler/parser/tokenizer.h
        compiler/sliced_string.h compiler/compiler.cpp compiler/compiler.h compiler/translator/translator.cpp compiler/translator/translator.h compiler/translator/variable_table.cpp compiler/translator/variable_table.h)
