#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <memory>
#include <string>
#include <vector>

#include "Lexer.hpp"
#include "Visitor.hpp"

// Base class for all AST nodes.
class ASTNode {
 public:
  // Enum representing different types of AST nodes (e.g., String and Print).
  enum class NodeType { STRING, PRINT };
  NodeType type;  // Type of the AST node.

  // Accept method for the visitor pattern (will be implemented in derived
  // classes).
  virtual void accept(class Visitor &visitor) = 0;
  virtual ~ASTNode() = default;  // Virtual destructor to ensure proper cleanup.
};

// AST node for string literals.
class StringNode : public ASTNode {
 public:
  // Constructor that initializes a StringNode with a value.
  StringNode(const std::string &value) : value(value) {
    this->type = NodeType::STRING;
  }

  // Getter for the string value stored in this node.
  const std::string &getValue() const { return value; }

  // Accepts a visitor for this node type.
  void accept(Visitor &visitor) override { visitor.visit(this); }

 private:
  std::string value;  // The string value stored in the node.
};

// AST node for print statements.
class PrintNode : public ASTNode {
 public:
  // Constructor that initializes a PrintNode with a StringNode.
  PrintNode(std::unique_ptr<StringNode> stringNode)
      : stringNode(std::move(stringNode)) {
    this->type = NodeType::PRINT;
  }

  // Getter for the string node associated with this print statement.
  StringNode *getStringNode() const { return stringNode.get(); }

  // Accepts a visitor for this node type.
  void accept(Visitor &visitor) override { visitor.visit(this); }

 private:
  std::unique_ptr<StringNode>
      stringNode;  // The string node associated with the print statement.
};

// Factory class to create AST nodes based on tokens.
class ASTNodeFactory {
 public:
  // Static method to create an AST node based on the provided tokens.
  static std::unique_ptr<ASTNode> createNode(
      const std::vector<Lexer::Token> &tokens) {
    const Lexer::Token &token = tokens.at(0);

    switch (token.type) {
      case Lexer::TokenType::PRINT:
        // Create a PrintNode and associate it with a StringNode (if available).
        return std::make_unique<PrintNode>(
            tokens.at(1).type == Lexer::TokenType::UNKNOWN
                ? nullptr
                : std::move(createStringNode(tokens.at(1))));

      default:
        throw std::runtime_error("Syntax error: unrecognized instruction");
    }
  }

 private:
  // Helper method to create a StringNode based on a token.
  static std::unique_ptr<StringNode> createStringNode(
      const Lexer::Token &token) {
    return std::make_unique<StringNode>(token.value);
  }
};

#endif
