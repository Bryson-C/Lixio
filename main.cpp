#include <iostream>
#include <map>

#include "Features/Parser.hpp"

int main() {

    std::map<std::string, TokenType> tokens = {
            {"=", TokenType::Equals},
            {";", TokenType::Semicolon},
    };

    Tokenizer tokenizer(tokens);
    Parser parser(std::filesystem::path("D:\\CompilerFeatures\\Language\\default.lang"), tokenizer);

    
    return 0;
}
