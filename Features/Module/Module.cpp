//
// Created by Owner on 11/25/2022.
//

#include "Module.hpp"


static std::vector<std::string> splitString(const std::string& string) {
    std::vector<std::string> split;

    std::string buffer;
    bool isString = false;
    char strType;
    for (Parser::CharType currentType, lastType = Parser::CharType::None; const auto& chr : string) {

        if (isString) {
            buffer += chr;
            if (chr == strType) {
                split.push_back(buffer);
                buffer.clear();
                isString = false;
            }
            continue;
        }
        if (chr == '\'' || chr == '\"') {
            split.push_back(buffer);
            buffer.clear();
            isString = true;
            buffer += strType = chr;
            continue;
        }

        if (std::isdigit(chr))
        {
            currentType = Parser::CharType::Number;
        }
        else if (std::isalpha(chr))
        {
            currentType = Parser::CharType::Alpha;
        }
        else if (std::isspace(chr))
        {
            currentType = Parser::CharType::Space;
        }
        else if (!std::isalpha(chr) && !std::isspace(chr))
        {
            currentType = Parser::CharType::Symbol;
        }


        if (currentType != lastType && lastType != Parser::CharType::None && !buffer.empty()) {
            split.push_back(buffer);
            buffer.clear();
        }
        if (currentType != Parser::CharType::Space)
            buffer += chr;

        lastType = currentType;
    }
    if (!buffer.empty())
        split.push_back(buffer);

    return split;
}
static std::string fileToString(const std::filesystem::path& path) {
    std::ifstream file(path);
    std::string buffer, result;
    while (std::getline(file, buffer)) {
        if (!buffer.empty())
            result += buffer;
    }
    return result;
}

void Module::contextPass(const std::vector<ParsePassRule> &rules) {
    for (int i = 1; i < _tokens.size(); i++) {
        int ruleIter = 0;
        for (bool leave = false; auto& rule : rules) {
            for (auto& token : rule.one) {
                if (_tokens[i-1]._type == token && _tokens[i]._type == TokenType::None) {
                    _tokens[i] = rule.two;
                    leave = true;
                    break;
                }
            }
            if (leave) break;
            else {
                if (ruleIter >= rule.one.size()-1 && !leave)
                    #ifdef WARN_IF_UNHANDLED
                        std::cerr << "Unhandled Case: (TokenCode) " << _tokens[i].asString() << "\n";
                    #else
                        ;
                    #endif
            }
            ruleIter++;
        }
    }
}

Module::Module(const std::string &string, Tokenizer& tokenizer) {
    _code = splitString(string);
    for (int i = 0; i < _code.size(); i++) {
        if (!tokenizer._dictionary.contains(_code[i])) {
            if (auto isNum = Parser::isDigit(_code[i]); isNum)
                _tokens.emplace_back(TokenType::Integer, _code[i]);
            else if (auto isString = Parser::isString(_code[i]); isString.one)
                _tokens.emplace_back(TokenType::String, isString.two);
            else
                _tokens.emplace_back(TokenType::None, _code[i]);
        } else {
            _tokens.emplace_back(tokenizer._dictionary[_code[i]], _code[i]);
        }
    }
    contextPass(_rules);
}



Module::Module(const std::filesystem::path &path, Tokenizer& tokenizer) {
    _code = splitString(fileToString(path.string()));
    for (int i = 0; i < _code.size(); i++) {
        if (!tokenizer._dictionary.contains(_code[i])) {
            if (auto isNum = Parser::isDigit(_code[i]); isNum)
                _tokens.emplace_back(TokenType::Integer, _code[i]);
            else if (auto isString = Parser::isString(_code[i]); isString.one)
                _tokens.emplace_back(TokenType::String, isString.two);
            else
                _tokens.emplace_back(TokenType::None, _code[i]);
        } else {
            _tokens.emplace_back(tokenizer._dictionary[_code[i]], _code[i]);
        }
    }
    contextPass(_rules);
}
