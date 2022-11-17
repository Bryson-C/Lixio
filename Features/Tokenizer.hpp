//
// Created by Owner on 11/10/2022.
//

#ifndef COMPILERFEATURES_TOKENIZER_HPP
#define COMPILERFEATURES_TOKENIZER_HPP

#include <map>
#include <string>

enum class TokenType {
    None,
    Named,
    Equals,
    Integer,
    Semicolon,
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
    std::string data;
    TokenType token;
};

class Tokenizer {
private:
    std::map<std::string, TokenType> _tokenTable;
    friend class Parser;
    friend class Token;
public:
    Tokenizer(const std::map<std::string, TokenType>& tokenTable) {
        _tokenTable = tokenTable;
    }
    inline Token parseNextFromCurrent(TokenType current, int& iteration) {
        iteration++;
    }
    inline void parseCurrent(TokenType current, int& iteration) {
        iteration++;
    }
};


#endif //COMPILERFEATURES_TOKENIZER_HPP
