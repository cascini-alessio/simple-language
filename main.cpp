#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "include/Interpreter.hpp"
#include "include/Lexer.hpp"
#include "include/Parser.hpp"

// Converts TokenType to a string representation for easy display.
std::string toString(Lexer::TokenType type);

// Displays a list of tokens with their type and value.
void showTokens(const std::vector<Lexer::Token> &tokens);

// Reads the content of a file into a string.
std::string readFile(const std::string &filePath);

int main() {
  try {
    // Read the source code from the input file.
    std::string sourceCode = readFile("input.txt");

    // Create a lexer object and tokenize the source code.
    Lexer lexer(sourceCode);
    showTokens(lexer.tokenize());  // Display the tokens.
    std::cout << std::endl;

    // Parse the tokens into an abstract syntax tree (AST).
    Parser parser(lexer.tokenize());
    auto nodes = parser.parse();

    // Perform semantic analysis on the AST.
    SemanticAnalysisVisitor semanticAnalysisVisitor;
    for (const auto &node : nodes) node->accept(semanticAnalysisVisitor);

    // Perform optimization on the AST.
    OptimizationVisitor optimizationVisitor;
    for (const auto &node : nodes) node->accept(optimizationVisitor);

    // Execute the AST (i.e., interpret the program).
    ExecuteVisitor interpreter;
    for (const auto &node : nodes) node->accept(interpreter);
  } catch (const std::runtime_error &e) {
    // Catch any runtime errors and display the message.
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}

// Converts a Lexer TokenType to its string representation.
std::string toString(Lexer::TokenType type) {
  switch (type) {
    case Lexer::TokenType::PRINT:
      return "PRINT";

    case Lexer::TokenType::LPAR:
      return "LPAR";

    case Lexer::TokenType::STRING:
      return "STRING";

    case Lexer::TokenType::RPAR:
      return "RPAR";

    case Lexer::TokenType::END:
      return "END";

    default:
      return "UNKNOWN";
  }
}

// Displays each token type and its associated value.
void showTokens(const std::vector<Lexer::Token> &tokens) {
  try {
    for (const Lexer::Token &token : tokens)
      std::cout << toString(token.type) << ' ' << token.value << std::endl;
  } catch (const std::runtime_error &e) {
    // Catch any Lexer-specific errors and display them.
    std::cerr << "Lexer error: " << e.what() << std::endl;
  }
}

// Reads the contents of a file and returns it as a string.
std::string readFile(const std::string &filePath) {
  std::ifstream file(filePath);

  // If the file cannot be opened, throw an error.
  if (!file.is_open())
    throw std::runtime_error("Could not open file: " + filePath);

  std::stringstream oss;
  oss << file.rdbuf();  // Read the entire file into the stringstream.
  return oss.str();     // Return the contents as a string.
}
