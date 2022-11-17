//
// Created by Owner on 11/10/2022.
//

#include "Parser.hpp"


Parser::Parser(const std::string &string, Tokenizer tokenizer) {
    std::vector<std::string> split;

    std::string buffer;
    for (CharType currentType, lastType = CharType::None; const auto& chr : string) {

        if (std::isdigit(chr))
            currentType = CharType::Number;
        else if (std::isalpha(chr))
            currentType = CharType::Alpha;
        else if (std::isspace(chr))
            currentType = CharType::Space;
        else if (!std::isalpha(chr) && !std::isspace(chr))
            currentType = CharType::Symbol;


        if (currentType != lastType && lastType != CharType::None && !buffer.empty()) {
            split.push_back(buffer);
            buffer.clear();
        }
        buffer += chr;

        lastType = currentType;
    }
    if (!buffer.empty())
        split.push_back(buffer);

    _wordBuffer = split;

    for (const auto& i : split) {
        std::cout << i << "\n";
    }

    for (auto & i : _wordBuffer) {
        std::cout << tokenTypeToString(tokenizer._tokenTable[i]) << '\n';
    }
}