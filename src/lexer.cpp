#include "lexer.hpp"

Lexer::Lexer(const std::string& src) : source(src), index(0) {}

void Lexer::skipWhitespace() {
    while (index < source.length() && isspace(source[index])) {
        index++;
    }
}

void Lexer::skipComments() {
    if (source[index] == '/' && source[index + 1] == '/') {
        while (index < source.length() && source[index] != '\n') index++;
    } else if (source[index] == '/' && source[index + 1] == '*') {
        index += 2; // Skip /*
        while (index < source.length() && (source[index] != '*' || source[index + 1] != '/')) index++;
        index += 2; // Skip */
    }
}

Token Lexer::getNextToken() {
    skipWhitespace();
    if (index >= source.length()) return {END_OF_FILE, ""};

    char current = source[index];

    if (current == '/' && (source[index + 1] == '/' || source[index + 1] == '*')) {
        skipComments();
        return getNextToken();
    }

    if (isalpha(current)) {
        size_t start = index;
        while (index < source.length() && isalnum(source[index])) index++;
        std::string word = source.substr(start, index - start);
        if (word == "class" || word == "func" || word == "if" || word == "else" ||
            word == "let" || word == "return" || word == "for" || word == "while") {
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
        index++;
        size_t start = index;
        while (index < source.length() && source[index] != '\"') index++;
        std::string str = source.substr(start, index - start);
        index++;
        return {STRING, str};
    }

    if (ispunct(current)) {
        index++;
        return {SYMBOL, std::string(1, current)};
    }

    throw std::runtime_error("Unknown character: " + std::string(1, current));
}
