#ifndef VISITOR_HPP
#define VISITOR_HPP

// Abstract base class for all visitors that will operate on AST nodes.
class Visitor {
 public:
  // Virtual method to visit a StringNode. Derived visitors must implement this
  // method.
  virtual void visit(class StringNode *node) = 0;

  // Virtual method to visit a PrintNode. Derived visitors must implement this
  // method.
  virtual void visit(class PrintNode *node) = 0;
};

#endif
