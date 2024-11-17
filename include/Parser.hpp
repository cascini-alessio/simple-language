#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "ASTNode.hpp"
#include "Lexer.hpp"

class Parser {
 public:
  // Constructor that initializes the parser with a list of tokens.
  Parser(const std::vector<Lexer::Token> &tokens) : tokens(tokens) {}

  // Main parsing function that returns a list of AST nodes.
  std::vector<std::unique_ptr<ASTNode>> parse();

 private:
  std::vector<Lexer::Token> tokens;             // List of tokens to parse.
  std::vector<std::unique_ptr<ASTNode>> nodes;  // List of generated AST nodes.
  int tokenIndex = 0;  // Current position in the token list.

  // Enum class to define the different states during parsing.
  enum class ParserState { DEFAULT, PRINT };

  // Mapping from token types to parsing states.
  std::unordered_map<Lexer::TokenType, ParserState> stateMap = {
      {Lexer::TokenType::PRINT, ParserState::PRINT}};

  ParserState state = ParserState::DEFAULT;  // Initial state is DEFAULT.

  // Function to handle print statements.
  void handlePrintStatement();

  // Function to check if the current token matches the expected type.
  void expectToken(Lexer::TokenType expectedType, int position,
                   const std::string &errorMessage) {
    if (tokens.at(position).type != expectedType)
      throw std::runtime_error(errorMessage);
  }
};

// Function to parse the list of tokens into AST nodes.
std::vector<std::unique_ptr<ASTNode>> Parser::parse() {
  if (tokens.empty())
    throw std::runtime_error("Syntax error: no tokens to parse");

  // Iterate through the tokens and process them based on the current state.
  while (tokenIndex < tokens.size()) {
    const Lexer::Token &token = tokens.at(tokenIndex);

    switch (state) {
      case ParserState::DEFAULT: {
        // Check if the current token matches any of the defined parser states.
        auto it = stateMap.find(token.type);
        if (it != stateMap.end())
          state = it->second;  // Change state based on token type.
        else
          throw std::runtime_error("Syntax error: unexpected token '" +
                                   token.value + "' at position " +
                                   std::to_string(tokenIndex));
        break;
      }

      case ParserState::PRINT:
        // Handle the print statement.
        handlePrintStatement();
        break;
    }
  }

  // Return the list of AST nodes created during the parsing process.
  return std::move(nodes);
}

// Function to handle a print statement.
void Parser::handlePrintStatement() {
  if (tokens.size() < tokenIndex + 5)
    throw std::runtime_error("Syntax error: incomplete print statement");

  // Expect a left parenthesis after the "print" keyword.
  expectToken(Lexer::TokenType::LPAR, tokenIndex + 1,
              "Syntax error: expected '(' after 'print' keyword");

  // If the next token is not a string, insert an unknown token.
  if (tokens.at(tokenIndex + 2).type != Lexer::TokenType::STRING)
    tokens.insert(tokens.begin() + tokenIndex + 2,
                  {Lexer::TokenType::UNKNOWN, ""});

  // Expect a right parenthesis after the string literal.
  expectToken(Lexer::TokenType::RPAR, tokenIndex + 3,
              "Syntax error: expected ')' after string literal");

  // Expect an END token (newline or semicolon) after the print statement.
  expectToken(Lexer::TokenType::END, tokenIndex + 4,
              "Syntax error: expected newline or semicolon after print");

  // Create an AST node for the print statement using the tokens.
  nodes.push_back(ASTNodeFactory::createNode(
      {tokens.at(tokenIndex), tokens.at(tokenIndex + 2)}));

  // Move the token index forward by 5 to process the next statement.
  tokenIndex += 5;
  state = ParserState::DEFAULT;  // Reset the state to DEFAULT.
}

#endif
