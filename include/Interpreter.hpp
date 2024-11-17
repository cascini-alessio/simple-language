#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ASTNode.hpp"
#include "Visitor.hpp"

// Visitor for semantic analysis.
// It checks if the semantics of the AST are correct, e.g., checking if PRINT
// has a string argument.
class SemanticAnalysisVisitor : public Visitor {
 public:
  // Visit a StringNode. Currently, no specific semantic checks are needed for
  // StringNode.
  void visit(StringNode *node) override {}

  // Visit a PrintNode. It checks if the PrintNode has a valid string argument.
  void visit(PrintNode *node) override {
    if (node->getStringNode() == nullptr)
      throw std::runtime_error(
          "Semantic error: PRINT requires a string argument.");
  }
};

// Visitor for optimization.
// It performs optimizations on the AST, like removing unnecessary nodes or
// detecting empty operations.
class OptimizationVisitor : public Visitor {
 public:
  // Visit a StringNode. No optimizations are performed on StringNode in this
  // example.
  void visit(StringNode *node) override {}

  // Visit a PrintNode. It checks if the string is empty and throws an error if
  // it is.
  void visit(PrintNode *node) override {
    if (node->getStringNode()->getValue().empty())
      throw std::runtime_error(
          "Optimization error: PRINT statement with empty string.");
  }
};

// Visitor for executing the AST.
// This is where the logic for executing or interpreting the AST nodes is
// defined.
class ExecuteVisitor : public Visitor {
 public:
  // Visit a StringNode. Currently, no specific execution is done for
  // StringNode.
  void visit(StringNode *node) override {}

  // Visit a PrintNode. This executes the PRINT statement by printing the string
  // value.
  void visit(PrintNode *node) override {
    StringNode *stringNode = node->getStringNode();
    std::cout << stringNode->getValue() << std::endl;
  }
};

#endif
