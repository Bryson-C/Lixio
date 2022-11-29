//
// Created by Owner on 11/25/2022.
//

#ifndef COMPILERFEATURES_MODULE_HPP
#define COMPILERFEATURES_MODULE_HPP

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#include "../Tokenizer/Tokenizer.hpp"
#include "../Tokenizer/TokenType.hpp"


#define WARN_IF_UNHANDLED 1

class Module {
private:
    std::string _moduleName;
    std::vector<std::string> _code;
    std::vector<Token> _tokens;
public:
    explicit Module(const std::string& string, Tokenizer& tokenizer);
    explicit Module(const std::filesystem::path& path, Tokenizer& tokenizer);
};

// Fuck you external libraries; I Know It's My Fault But God Does It Have To Be That Difficult To Just Used Pre-made Code?

namespace Parser {
    enum class CharType {
        None,
        Alpha,
        Number,
        Symbol,
        Space,
    };
};


#endif //COMPILERFEATURES_MODULE_HPP
