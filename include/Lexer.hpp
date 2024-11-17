#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Lexer {
 public:
  // Enum class to define the different token types.
  enum class TokenType { PRINT, LPAR, STRING, RPAR, END, UNKNOWN };

  // Structure to represent a Token consisting of its type and value.
  struct Token {
    TokenType type;
    std::string value;
  };

  // Constructor to initialize the lexer with source code.
  // Normalizes newlines in the provided source code.
  Lexer(const std::string &sourceCode) : sourceCode(sourceCode) {
    normalizeNewlines(this->sourceCode);
  }

  // Tokenize function that returns a vector of tokens extracted from the source
  // code.
  std::vector<Token> tokenize();

 private:
  std::string sourceCode;  // The source code to be tokenized.

  // Maps keywords to their corresponding token type.
  std::unordered_map<std::string, TokenType> keyWords = {
      {"print", TokenType::PRINT}};

  // Maps special characters to their corresponding token type.
  std::unordered_map<char, TokenType> specialCharacters = {
      {'(', TokenType::LPAR}, {')', TokenType::RPAR}, {';', TokenType::END}};

  // Enum class to define the lexer states (DEFAULT for normal state and STRING
  // for string literals).
  enum class LexerState { DEFAULT, STRING };
  LexerState state = LexerState::DEFAULT;

  // Helper functions to handle specific cases.
  void handleSpecialCharacter(std::vector<Token> &tokens, char currentChar,
                              std::string &currentToken, int &i);

  void addKeywordToken(std::vector<Token> &tokens, std::string &currentToken,
                       int position);

  // Normalizes newlines by replacing all carriage return and newline
  // combinations with just a newline.
  void normalizeNewlines(std::string &sourceCode);
};

// Function to tokenize the source code into a series of tokens.
std::vector<Lexer::Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  std::string currentToken;

  // Iterate through each character in the source code.
  for (int i = 0; i < sourceCode.length(); i++) {
    char currentChar = sourceCode.at(i);

    switch (state) {
      case LexerState::DEFAULT:
        // Ignore whitespace characters.
        if (currentChar == ' ' || currentChar == '\t') continue;

        // Handle alphabetic characters (likely keywords or identifiers).
        if (isalpha(currentChar))
          currentToken += currentChar;
        else
          handleSpecialCharacter(tokens, currentChar, currentToken, i);
        break;

      case LexerState::STRING:
        // Handle string literals enclosed in quotes.
        std::string str;
        while (i < sourceCode.length() && sourceCode.at(i) != '"')
          str += sourceCode.at(i++);
        if (i == sourceCode.length())
          throw std::runtime_error(
              "Syntax error: unclosed string literal at position " +
              std::to_string(i) +
              ". Did you forget to close it with a '\"'? Current input: "
              "'" +
              sourceCode.substr(std::max(0, i - 5), 10) + "'");

        // Add the string literal token.
        tokens.push_back({TokenType::STRING, str});
        state = LexerState::DEFAULT;  // Reset state to DEFAULT after processing
                                      // the string.
        break;
    }
  }

  // Add any remaining keyword token if applicable.
  addKeywordToken(tokens, currentToken, sourceCode.length());

  // Ensure there is an END token at the end of the token list.
  if (!tokens.empty() && tokens.back().type != TokenType::END)
    tokens.push_back({TokenType::END, ""});

  return tokens;
}

// Function to handle special characters and add corresponding tokens.
void Lexer::handleSpecialCharacter(std::vector<Token> &tokens, char currentChar,
                                   std::string &currentToken, int &i) {
  addKeywordToken(
      tokens, currentToken,
      i);  // Add any keyword token before processing the special character.
  currentToken.clear();  // Clear the current token.

  // Check if the character is a special character (like parentheses or
  // semicolon).
  auto it = specialCharacters.find(currentChar);
  if (it != specialCharacters.end())
    tokens.push_back({it->second, std::string(1, currentChar)});
  else if (currentChar == '\n') {
    // If it's a newline, add an END token.
    if (!tokens.empty() && tokens.back().type != TokenType::END)
      tokens.push_back({TokenType::END, "\\n"});
  } else if (currentChar == '"')
    // If it's a quote, switch to the STRING state to handle string literals.
    state = LexerState::STRING;
  else
    throw std::runtime_error("Syntax error: unexpected character '" +
                             std::string(1, currentChar) + "' at position " +
                             std::to_string(i) + " in input: '" +
                             sourceCode.substr(std::max(0, i - 5), 10) + "'");
}

// Function to add a keyword token if the currentToken is a recognized keyword.
void Lexer::addKeywordToken(std::vector<Token> &tokens,
                            std::string &currentToken, int position) {
  if (!currentToken.empty()) {
    auto it = keyWords.find(currentToken);
    if (it != keyWords.end())
      tokens.push_back({it->second, currentToken});
    else
      throw std::runtime_error(
          "Syntax error: unexpected token '" + currentToken + "' at position " +
          std::to_string(position) + " in input: '" +
          sourceCode.substr(std::max(0, position - 5), 10) + "'");
  }
}

// Function to normalize line endings by replacing \r\n and \r with \n.
void Lexer::normalizeNewlines(std::string &sourceCode) {
  int pos = 0;
  while ((pos = sourceCode.find("\r\n", pos)) != std::string::npos) {
    sourceCode.replace(pos, 2, "\n");
  }

  pos = 0;
  while ((pos = sourceCode.find("\r", pos)) != std::string::npos) {
    sourceCode.replace(pos, 1, "\n");
  }
}

#endif
