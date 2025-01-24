// lexer.hpp
#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    STRING,
    SYMBOL,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& src);
    Token getNextToken();

private:
    std::string source;
    size_t index;
};

#endif
