#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "ast_node.hpp"

class Parser {
    Lexer& lexer;
    Token currentToken;

    void advance();
    void expect(TokenType type);

public:
    explicit Parser(Lexer& lex);
    std::unique_ptr<ASTNode> parseFunction();
    std::unique_ptr<ASTNode> parseClass();
};

#endif // PARSER_HPP
