//
// Created by Owner on 11/10/2022.
//

#ifndef COMPILERFEATURES_TOKENIZER_HPP
#define COMPILERFEATURES_TOKENIZER_HPP

#include <map>
#include <string>
#include <iostream>

#include "Util.hpp"

enum class TokenType {
    None,
    Named,
    Equals,
    Integer,
    Semicolon,
};
enum class TokenPosition {
    Current,
    Previous,
    Next,
};

inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::None: return "None";
        case TokenType::Named: return "Named";
        case TokenType::Equals: return "Equals";
        case TokenType::Integer: return "Integer";
        case TokenType::Semicolon: return "Semicolon";
    }
}

class Token {
private:
public:
    Token(TokenType type, std::string str = "") : token(type), data(str) {}
    std::string data;
    TokenType token;


    void print() const {
        std::cout << data << "\t|  " << tokenTypeToString(token) << "\n";
    }
};

class Tokenizer {
private:
    std::map<std::string, Duo<TokenPosition, TokenType>> _tokenTable;
    friend class Parser;
    friend class Token;
public:
    explicit Tokenizer(const std::map<std::string, Duo<TokenPosition,TokenType>>& tokenTable) {
        _tokenTable = tokenTable;
    }
    Token parseCurrent(std::string str);
};


#endif //COMPILERFEATURES_TOKENIZER_HPP
