//
// Created by Owner on 11/25/2022.
//

#include "Module.hpp"


static std::vector<std::string> splitString(const std::string& string) {
    Parser::PushBuffer buffer;

    bool isString = false;
    char strType;
    for (Parser::CharType currentType, lastType = Parser::CharType::None; const auto& chr : string) {

        if (isString) {
            buffer += chr;
            if (chr == strType) {
                buffer.push();
                isString = false;
            }
            continue;
        }
        if (chr == '\'' || chr == '\"') {
            buffer.push();
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

        if (currentType == Parser::CharType::Symbol) {
            buffer.push();
            buffer.push(chr);
            continue;
        }
        if (currentType != lastType && lastType != Parser::CharType::None) {
            buffer.push();
        }
        if (currentType != Parser::CharType::Space)
            buffer += chr;

        lastType = currentType;
    }
    buffer.push();

    return buffer.vec;
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
                    _tokens[i]._type = rule.two;
                    leave = true;
                    break;
                }
            }
            if (leave) break;
            else {
                if (ruleIter >= rule.one.size()-1 && !leave)
                    #ifdef WARN_IF_UNHANDLED
                        std::cerr << "Unhandled Case: (TokenCode) " << _tokens[i].asString() << "\n";
                    #endif
            }
            ruleIter++;
        }
    }
}

Module::Module(const std::vector<std::string> &string, Tokenizer &tokenizer) {
    _code = string;
    Token* parent = nullptr;
    for (int i = 0; i < _code.size(); i++) {
        Token token;
        token._type = TokenType::None;
        token._str = _code[i];
        token._parent = parent;

        if (tokenizer._dictionary[_code[i]] == TokenType::CloseBlock) {
            if (parent != nullptr)
                parent = parent->_parent;
        }
        ((parent != nullptr) ? (*parent)._children : _tokens).push_back(token);
        if (tokenizer._dictionary[_code[i]] == TokenType::OpenBlock) {
            parent = (parent == nullptr) ? &_tokens.back() : &parent->_children.back();
            continue;
        }

    }

    contextPass(_rules);
}
Module::Module(const std::string &string, Tokenizer& tokenizer) {
    _code = splitString(string);
    *this = Module(_code, tokenizer);
}

Module::Module(const std::filesystem::path &path, Tokenizer& tokenizer) {
    _code = splitString(fileToString(path.string()));
    *this = Module(_code, tokenizer);
}
