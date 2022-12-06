//
// Created by Owner on 11/10/2022.
//

#ifndef COMPILERFEATURES_TOKENIZER_HPP
#define COMPILERFEATURES_TOKENIZER_HPP

#include <map>
#include <string>
#include <iostream>
#include <vector>

#include "../Util.hpp"
#include "TokenType.hpp"

class Token {
private:
    TokenType _type;
    std::string _str;
    friend class Module;
public:
    Token() = default;
    Token(TokenType type, std::string str = "") : _type(type), _str(str) {}

    inline std::string asString() const { return ((!_str.empty()) ? "\"" + _str + "\" " : "") + tokenToString(_type); }
};

class Tokenizer {
private:
    std::vector<Token> _tokens;
    std::map<std::string, TokenType> _dictionary;
    friend class Module;
public:
    inline explicit Tokenizer(const std::map<std::string, TokenType>& tokens) : _dictionary(tokens) {}
};


#endif //COMPILERFEATURES_TOKENIZER_HPP
