//
// Created by Owner on 11/25/2022.
//

#ifndef COMPILERFEATURES_MODULE_HPP
#define COMPILERFEATURES_MODULE_HPP

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <ranges>

#include "../Tokenizer/Tokenizer.hpp"
#include "../Tokenizer/TokenType.hpp"


#define WARN_IF_UNHANDLED 1

namespace {
    // Takes Previous Tokens And If It Matches One Of The Types Converts Current To Type 2
    using ParsePassRule = Duo<std::vector<TokenType>, TokenType>;
}

class Module {
private:
    std::string _moduleName;
    std::vector<std::string> _code;
    std::vector<Token> _tokens;

    const std::vector<ParsePassRule> _rules = {
            {{TokenType::IntegerType, TokenType::StringType}, TokenType::Named},

    };

    void contextPass(const std::vector<ParsePassRule>& rules);
public:
    explicit Module(const std::string& string, Tokenizer& tokenizer);
    explicit Module(const std::filesystem::path& path, Tokenizer& tokenizer);
    inline void print() const {
        for (const auto& i : _tokens) {
            std::cout << i.asString() << '\n';
        }
    }
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
    inline bool isDigit(std::string str) {
        for (auto& chr : str)
            if (!isdigit(chr)) return false;
        return true;
    }
};


#endif //COMPILERFEATURES_MODULE_HPP
