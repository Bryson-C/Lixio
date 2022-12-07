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
    const std::vector<ParsePassRule> _rules = {
            {{TokenType::IntegerType, TokenType::StringType}, TokenType::Named},
    };
}

class Module {
private:
    std::string _moduleName;
    std::vector<std::string> _code;
    std::vector<Token> _tokens;


    void contextPass(const std::vector<ParsePassRule>& rules);
public:
    explicit Module(const std::string& string, Tokenizer& tokenizer);
    explicit Module(const std::filesystem::path& path, Tokenizer& tokenizer);
    explicit Module(const std::vector<std::string> &string, Tokenizer &tokenizer);

    inline void print() const {
        for (const auto& i : _tokens)
            //std::cout << i.asString() << '\n';
            i.print();
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
        if (str.empty()) return false;
        for (auto& chr : str)
            if (!isdigit(chr)) return false;
        return true;
    }
    inline Duo<bool, std::string> isString(std::string str) {
        if (str.empty()) return {false, ""};
        if (char stringType = str[0]; str[0] == '\"' || str[0] == '\'') {
            std::string buffer;
            int i = 1;
            while (str[i] != stringType) {
                buffer += str[i];
                i++;
            }
            return {true, buffer};
        }
        return {false, ""};
    }
    struct PushBuffer {
        std::vector<std::string> vec;
        std::string buffer;

        inline void push() {
            if (!buffer.empty()) {
                vec.push_back(buffer);
                buffer.clear();
            }
        }
        inline void push(std::string str) {
            vec.push_back(str);
        }
        inline void push(char chr) {
            vec.emplace_back(1, chr);
        }
        inline bool empty() {
            return buffer.empty();
        }
        inline void operator+=(char str) { buffer += str; }
        inline void operator+=(std::string str) { buffer += str; }
    };
};


#endif //COMPILERFEATURES_MODULE_HPP
