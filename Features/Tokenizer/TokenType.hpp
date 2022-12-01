//
// Created by Owner on 11/28/2022.
//

#ifndef COMPILERFEATURES_TOKENTYPE_HPP
#define COMPILERFEATURES_TOKENTYPE_HPP

#include "stdint.h"

enum class TokenType {
    None,           // Cannot Be Directly Used
    IntegerType,
    Integer,        // Cannot Be Directly Used
    StringType,
    String,         // Cannot Be Directly Used
    Named,          // Cannot Be Directly Used
    Equals,
    Semicolon,
};

inline std::string tokenToString(const TokenType type) {
    switch (type) {
        case TokenType::None: return "None";
        case TokenType::IntegerType: return "Integer_Type";
        case TokenType::Integer: return "Integer";
        case TokenType::StringType: return "String_Type";
        case TokenType::String: return "String";
        case TokenType::Named: return "Named";
        case TokenType::Equals: return "Equals";
        case TokenType::Semicolon: return "Semicolon";
    }
}


inline std::map<std::string, TokenType> GetTokenTable() {
    std::map<std::string, TokenType> TokenTable {
            {"Int", TokenType::IntegerType},
            {"String", TokenType::StringType},
            {"=", TokenType::Equals},
            {";", TokenType::Semicolon},
    };
    return TokenTable;
};


#endif //COMPILERFEATURES_TOKENTYPE_HPP
