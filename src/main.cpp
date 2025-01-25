#include "lexer.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <string>

// Function to check if the file has the correct extension
bool hasCorrectExtension(const std::string& filename, const std::string& extension) {
    size_t extPos = filename.find_last_of('.');
    return extPos != std::string::npos && filename.substr(extPos) == extension;
}

// Function to print tokens (for debugging)
void printTokens(const std::string& sourceCode) {
    Lexer lexer(sourceCode);
    std::cout << "Tokens:\n";
    try {
        Token token;
        while ((token = lexer.getNextToken()).type != END_OF_FILE) {
            std::cout << "Type: " << token.type << ", Value: " << token.value << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Lexer error: " << e.what() << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./novalingua <file.nol>\n";
        return 1;
    }

    std::string filename = argv[1];
    if (!hasCorrectExtension(filename, ".nol")) {
        std::cerr << "Error: File must have a .nol extension (Nova Lingua source file).\n";
        return 1;
    }

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 1;
    }

    // Read the file content
    std::string sourceCode((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    file.close();

    // Debugging: Print tokens
    std::cout << "\n--- Tokenization ---\n";
    printTokens(sourceCode);

    // Proceed with Lexer and Parser
    Lexer lexer(sourceCode);
    Parser parser(lexer);

    try {
        std::cout << "\n--- Parsing ---\n";
        auto ast = parser.parseClass(); // Assuming main file defines a class
        std::cout << "Parsed successfully!\n";

        std::cout << "\n--- Abstract Syntax Tree (AST) ---\n";
        ast->print();
    } catch (const std::exception& e) {
        std::cerr << "Error during parsing: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
