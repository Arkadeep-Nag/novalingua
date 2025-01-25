#include "parser.hpp"

Parser::Parser(Lexer& lex) : lexer(lex) {
    advance();
}

void Parser::advance() {
    currentToken = lexer.getNextToken();
}

void Parser::expect(TokenType type) {
    if (currentToken.type != type) {
        throw std::runtime_error("Unexpected token: " + currentToken.value);
    }
    advance();
}

std::unique_ptr<ASTNode> Parser::parseFunction() {
    expect(KEYWORD); // 'func'
    std::string name = currentToken.value;
    expect(IDENTIFIER);
    expect(SYMBOL); // '('

    std::vector<std::string> params;
    while (currentToken.type == IDENTIFIER) {
        params.push_back(currentToken.value);
        advance();
        if (currentToken.value == ",") advance();
    }

    expect(SYMBOL); // ')'
    expect(SYMBOL); // '{'

    auto funcNode = std::make_unique<FunctionNode>(name, params);

    while (currentToken.value != "}") {
        funcNode->addBodyNode(std::make_unique<VariableNode>("temp", "42"));
        advance();
    }

    expect(SYMBOL); // '}'
    return funcNode;
}

std::unique_ptr<ASTNode> Parser::parseClass() {
    expect(KEYWORD); // 'class'
    std::string name = currentToken.value;
    expect(IDENTIFIER);

    std::string parentClass;
    if (currentToken.value == "extends") {
        advance();
        parentClass = currentToken.value;
        expect(IDENTIFIER);
    }

    expect(SYMBOL); // '{'

    auto classNode = std::make_unique<ClassNode>(name, parentClass);

    while (currentToken.value != "}") {
        if (currentToken.value == "func") {
            classNode->addMember(parseFunction());
        }
        advance();
    }

    expect(SYMBOL); // '}'
    return classNode;
}
