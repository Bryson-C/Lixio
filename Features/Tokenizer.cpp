//
// Created by Owner on 11/10/2022.
//

#include "Tokenizer.hpp"


Token Tokenizer::parseCurrent(std::string str) {
    if  (_tokenTable.contains(str)) {
        Token token(_tokenTable[str].two, str);
        return token;
    }
    return Token(TokenType::None);
}