#include "lexer.hpp"
#include <stdexcept>
#include <cctype>

Lexer::Lexer(const std::string& src) : source(src), index(0) {}

Token Lexer::getNextToken() {
    while (index < source.length() && isspace(source[index])) index++;

    if (index >= source.length()) {
        return {END_OF_FILE, ""};
    }

    char current = source[index];

    if (isalpha(current)) {
        size_t start = index;
        while (index < source.length() && isalnum(source[index])) index++;
        std::string word = source.substr(start, index - start);
        if (word == "class" || word == "func" || word == "return" || word == "let" || word == "import" || word == "extends") {
            return {KEYWORD, word};
        }
        return {IDENTIFIER, word};
    }

    if (isdigit(current)) {
        size_t start = index;
        while (index < source.length() && isdigit(source[index])) index++;
        return {NUMBER, source.substr(start, index - start)};
    }

    if (current == '\"') {
        index++; // Skip opening quote
        size_t start = index;
        while (index < source.length() && source[index] != '\"') index++;
        std::string str = source.substr(start, index - start);
        index++; // Skip closing quote
        return {STRING, str};
    }

    if (ispunct(current)) {
        index++;
        return {SYMBOL, std::string(1, current)};
    }

    throw std::runtime_error("Unknown character: " + std::string(1, current));
}
