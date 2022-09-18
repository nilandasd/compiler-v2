// ast.hpp

#pragma once

#include "grammar.hpp"

class Node {
  public:
    Node(int s): symbol(s) {};
    int symbol;
    int end;
    int jump;
    int next;
    int op;
    int scope;
    bool print = false;
};

class Parent: public Node {
  public:
    Parent(int symbol, std::vector<Node*> nodes):
      Node(symbol), children(nodes) {};

    std::vector<Node*> children;
};

class Leaf: public Node {
  public:
    Leaf(int symbol, Token *t): Node(symbol), token(t) {};
    Token *token;
};

class AST {
  public:
    AST(Grammar* g): G(g) {};
    Grammar* G;
    Node* root;
    Node* createInnerNode(int symbol, std::vector<Node*> nodes);
    Node* createLeafNode(int symbol, Token *token);
    int newLabel();
    int newTemp();
    int newScope();

  private:
    int labelCounter = 0;
    int tempCounter = 0;
    int scopeCounter = 0;
};

