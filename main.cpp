#include <iostream>
#include <map>

#include "Features/Module/Module.hpp"

int main() {

    std::map<std::string, TokenType> TokenTable = GetTokenTable();
    Tokenizer tokenizer(TokenTable);

    std::filesystem::path file(R"(D:\CompilerFeatures\Language\default.lang)");
    Module mod(file, tokenizer);



    return 0;
}
