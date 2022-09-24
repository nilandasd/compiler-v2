// ast.hpp

#pragma once

#include "grammar.hpp"

class Node {
  public:
    Node(int s): symbol(s) {};
    int symbol = 0;
    int prodNum = 0;
    int start = 0;
    int end = 0;
    int jump = 0;
    int next = 0;
    int op = 0;
    int scope = 0;
    bool print = false;
    virtual std::string value();
};

class Parent: public Node {
  public:
    Parent(int symbol, std::vector<Node*> nodes):
      Node(symbol), children(nodes) {};
    virtual std::string value();
    std::vector<Node*> children;
};

class Leaf: public Node {
  public:
    Leaf(int symbol, Token *t): Node(symbol), token(t) {};
    virtual std::string value();
    Token *token;
};

class AST {
  public:
    AST(Grammar* g): G(g) {};
    Grammar* G;
    Node* root;
    Node* createInnerNode(int symbol, std::vector<Node*> nodes, int productionNumber);
    Node* createLeafNode(int symbol, Token *token);
    void printAST();
    void traverse(Node * node);
    void processNode(Node* node);
    int newLabel();
    int newTemp();
    int newScope();

  private:
    void printNode(Node* node, int indentLevel);
    int labelCounter = 0;
    int tempCounter = 0;
    int scopeCounter = 0;
};

