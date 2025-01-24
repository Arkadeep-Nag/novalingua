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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./nova_compiler <file.nol>\n";
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

    // Proceed with Lexer and Parser
    Lexer lexer(sourceCode);  // Assuming Lexer is properly defined in lexer.hpp
    Parser parser(lexer);     // Assuming Parser is properly defined in parser.hpp

    try {
        std::cout << "Parsing " << filename << "...\n";
        auto ast = parser.parseClass();  // Assuming parseClass() returns a pointer to an AST
        std::cout << "Parsed successfully!\n";

        std::cout << "Abstract Syntax Tree (AST):\n";
        ast->print();  // Ensure AST class has a print method
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
