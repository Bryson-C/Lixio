//
// Created by Owner on 11/25/2022.
//

#include "Module.hpp"


static std::vector<std::string> splitString(const std::string& string) {
    std::vector<std::string> split;

    std::string buffer;
    for (Parser::CharType currentType, lastType = Parser::CharType::None; const auto& chr : string) {

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

Module::Module(const std::string &string, Tokenizer& tokenizer) {
    _code = splitString(string);
}
Module::Module(const std::filesystem::path &path, Tokenizer& tokenizer) {
    _code = splitString(fileToString(path.string()));
    for (const auto& str : _code) {
        if (!tokenizer._dictionary.contains(str)) {
            #ifdef WARN_IF_UNHANDLED
                std::cerr << "Unhandled Case: (TokenCode) " << str << "\n";
            #endif
        } else {
            _tokens.push_back(Token(tokenizer._dictionary[str]));
        }
    }
}
