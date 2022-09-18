// ast.cpp

#include "ast.hpp"

Node* AST::createInnerNode(int symbol, std::vector<Node*> nodes) {
  std::vector<int> body;
  for (auto n : nodes) body.push_back(n->symbol);
  int prodNum = G->productionNumber(symbol, body);

  if (symbol == G->serialize("STMT")) {
    if (prodNum == 0) { // STMT => { STMTS }
      nodes[1]->scope = newScope();
      return nodes[1];
    } else if (prodNum == 1) { // STMT => IF ( EXPR ) STMT
      int L1 = newLabel();
      Node* cond = nodes[2];
      Node* stmt = nodes[4];
      cond->jump = L1;
      stmt->end = L1;
      std::vector<Node*> children;
      for (Node* n : nodes) {
        if (n == cond || stmt) children.push_back(n);
        else delete n;
      }
      return new Parent(symbol, children);

    } else if (prodNum == 2) { // STMT => IF ( EXPR ) STMT ELSE STMT
      int L1 = newLabel();
      int L2 = newLabel();
      Node* cond = nodes[2];
      Node* firstStmt = nodes[4];
      Node* secondStmt = nodes[6];
      cond->jump = L1;
      firstStmt->next = L2;
      firstStmt->end = L1;
      secondStmt->end = L2;
      std::vector<Node*> children;
      for (Node* n : nodes) {
        if (n == cond || n == firstStmt || n == secondStmt) children.push_back(n);
        else delete n;
      }
      return new Parent(symbol, children);

    } else if (prodNum == 3) { // STMT => WHILE ( EXPR ) STMT
      int L1 = newLabel();
      int L2 = newLabel();
      Node* cond = nodes[2];
      Node* stmt = nodes[4];
      cond->jump = L2;
      stmt->next = L1;
      stmt->end = L2;
      std::vector<Node*> children;
      for (Node* n : nodes) {
        if (n == cond || n == stmt) children.push_back(n);
        else delete n;
      }
      return new Parent(symbol, children);

    } else if (prodNum == 4) {
      std::vector<Node*> children;
      delete nodes[0];
      children.push_back(nodes[1]);
      children.push_back(nodes[2]);
      delete nodes[3];
      return new Parent(symbol, children);

    } else if (prodNum == 5) {
      std::vector<Node*> children;
      children.push_back(nodes[0]);
      delete nodes[1];
      children.push_back(nodes[2]);
      delete nodes[3];
      return new Parent(symbol, children);

    } else if (prodNum == 6) {
      nodes[1]->print = true;
      return nodes[1];

    }
  } else if (symbol == G->serialize("EXPR")) {
    if (prodNum == 0) { // ( EXPR )
      return nodes[1];
    } else if (nodes.size() == 3) { // EXPR + EXPR (etc..)
      std::vector<Node*> children;
      children.push_back(nodes[0]);
      children.push_back(nodes[2]);
      Node* newNode = new Parent(symbol, children);
      newNode->op = nodes[1]->symbol;
      return newNode;

    } else { // ID or NUM
      return nodes[0];
    }     
  }
}

Node* AST::createLeafNode(int symbol, Token *token) {
  return new Node(0);
}

int AST::newLabel() {
  return labelCounter++;
}

int AST::newTemp() {
  return tempCounter++;
}

int AST::newScope() {
  return tempCounter++;
}
