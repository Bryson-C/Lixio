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

    Token* _parent;
    std::vector<Token> _children;

    friend class Module;
public:
    Token() = default;
    Token(TokenType type, std::string str = "") : _type(type), _str(str), _parent(nullptr) {}

    inline std::string asString() const { return ((!_str.empty()) ? "\'" + _str + "\'" : "") + "  --  [" + tokenToString(_type) + "]"; }
    inline void print() const {
        std::cout << asString() << "\n";
        for (auto& i : _children) {
            std::cout << "\t" << i.asString() << "\n";
            for (auto& j : i._children) {
                std::cout << "\t\t" << j.asString() << "\n";
            }
        }
    }
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
