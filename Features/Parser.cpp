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

    int iteration = 0;
    while (iteration < split.size()) {
        Token token = tokenizer.parseCurrent(split[iteration]);
        switch (tokenizer._tokenTable[split[iteration]].one) {
            case TokenPosition::Current:
                _tokens.push_back(token);
                break;
            case TokenPosition::Next:
                _tokens.emplace_back(TokenType::None);
                _tokens.push_back(token);
                break;
            case TokenPosition::Previous:
                _tokens[_tokens.size()-1] = token;
                break;
        }
        iteration++;
    }
}