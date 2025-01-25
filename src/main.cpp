#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./novalingua <file.nol>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return 1;
    }

    std::string sourceCode((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    file.close();

    Lexer lexer(sourceCode);
    Parser parser(lexer);
    Interpreter interpreter;

    try {
        auto ast = parser.parseClass(); // Parse the program
        std::cout << "Parsing successful.\n\n";

        // Interpret the program
        std::cout << "Executing...\n";
        interpreter.interpret(*ast);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
