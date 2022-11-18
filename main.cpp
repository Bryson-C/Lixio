#include <iostream>
#include <map>

#include "Features/Parser.hpp"

int main() {

    std::map<std::string, Duo<TokenPosition, TokenType>> tokens = {
            {"=", Duo(TokenPosition::Current, TokenType::Equals)},
            {";", Duo(TokenPosition::Current, TokenType::Semicolon)},
            {"$", Duo(TokenPosition::Next, TokenType::Named)},
    };

    Tokenizer tokenizer(tokens);
    Parser parser(std::filesystem::path(R"(D:\CompilerFeatures\Language\default.lang)"), tokenizer);

    for (const auto& i : parser._tokens) {
        i.print();
    }
    
    return 0;
}
