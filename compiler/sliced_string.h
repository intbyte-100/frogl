#pragma once

#include <string>
#include <cstring>

namespace frogl {
    class sliced_string {
    private:
        const char *string;
        int string_size;

    public:

        inline sliced_string() = default;

        inline char operator [](int index){
            return string[index];
        }

        inline sliced_string(std::string *source, int position, int size){
            string = &source->c_str()[position];
            this->string_size = size;
        }

        inline sliced_string(sliced_string *source, int position, int size){
            string = &source->c_str()[position];
            this->string_size = size;
        }


        inline std::string to_string() {
            return {string, (unsigned long) string_size};
        }

        inline std::string* to_string_pointer(){
            return new std::string(string, string_size);
        }

        inline const char* c_str(){
            return string;
        }

        inline bool operator ==(const std::string* str){
            return string_size == str->size() && !memcmp(string, str->c_str(), string_size);
        }

        inline bool operator ==(const std::string& str){
            return operator==(&str);
        }

        inline int size(){
            return string_size;
        }
    };
}

