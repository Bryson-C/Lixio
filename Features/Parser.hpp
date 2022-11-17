//
// Created by Owner on 11/10/2022.
//

#ifndef COMPILERFEATURES_PARSER_HPP
#define COMPILERFEATURES_PARSER_HPP

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <ctype.h>


#include "Tokenizer.hpp"

class Parser {
private:
    enum class CharType {
        None,
        Alpha,
        Number,
        Symbol,
        Space,
    };

    std::vector<std::string> _wordBuffer;
public:
    Parser(const std::string& string, Tokenizer tokenizer);
    inline explicit Parser(const std::filesystem::path& path, Tokenizer tokenizer) {
        std::ifstream file(path);
        std::string buffer, result;
        while (std::getline(file, buffer)) {
            result += buffer;
        }
        *this = Parser(result, tokenizer);
    }
};


#endif //COMPILERFEATURES_PARSER_HPP
