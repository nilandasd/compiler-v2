// ast.cpp

#include "ast.hpp"

Node* AST::createInnerNode(int symbol, std::vector<Node*> nodes, int prodNum) {
  if (symbol == G->serialize("STMT")) {
    if (prodNum == 0) { // STMT => { STMTS }
      delete nodes[0];
      delete nodes[2];
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
      cond->start = L1;
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
      delete nodes[0];
      nodes[1]->print = true;
      return nodes[1];
    }

  } else if (symbol == G->serialize("EXPR")) {
    if (prodNum == 0) { // ( EXPR )
      delete nodes[0];
      delete nodes[2];
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
  } else if (symbol == G->serialize("STMTS")) { // STMTS => STMTS STMT
    if (prodNum == 0) {
      static_cast<Parent*>(nodes[0])->children.push_back(nodes[1]);
      return nodes[0];
    } else {
      return nodes[0];
    }
  } else if (symbol == G->serialize("TYPE")) {
    return nodes[0];
  } else if (symbol == G->serialize("START")) {
    return nodes[0];
  }
}

void AST::printAST() {
  std::cout << "printing AST" << std::endl;
  printNode(root, 0);
}

void AST::printNode(Node* node, int indentLevel) {
  for (int i = 0; i < indentLevel; i++) {
    std::cout << "\t";
  }
  std::cout << G->symbolToString(node->symbol) << std::endl;
  Parent* p = dynamic_cast<Parent*>(node);
  if (p != nullptr) {
    for(Node* n : p->children) {
      printNode(n, indentLevel + 1);
    }
  }
}

Node* AST::createLeafNode(int symbol, Token *token) {
  return new Leaf(symbol, token);
}

void AST::traverse(Node* node) {
  Parent* p = dynamic_cast<Parent*>(node);
  if (p != nullptr) {
    for (auto n: p->children) {
      traverse(n);
    }
  }
  processNode(node);
}

void AST::processNode(Node* node) {
  if (node->start != 0) {
    ir.label(node->start);
  }
  if (node->scope != 0 && node->scope != currentScope) {
    if()
  }

  if (node->jump != 0) {
    if (node->symbol == G.serialize("EXPR")) {
      node->temp = newTemp();
    } else if (node->symbol == G.serialize("STMT")) {
      if (node->prodId == 4) {
        // TODO: assign the id to the symbol table
        //  Symbol Table
        //  nested scopes
        //  identifiers -> type
      } else if (node->prodId == 5) {
        // get the identifier from the symbol table 
        // if the identifier does not exist
        // check the type of the opk
      }
    }
    std::cout << "IF (EXPR) GOTO " << node->jump << std::endl;
  }

  if (node->next != 0) {
    ir.jump(node->label);
  }
  if(node->end != 0) {
    ir.label(node->label);
  }
}

std::string Parent::value() {

}

std::string Leaf::value() {

}

int AST::newLabel() {
  return ++labelCounter;
}

int AST::newTemp() {
  return ++tempCounter;
}

int AST::newScope() {
  return ++tempCounter;
}
