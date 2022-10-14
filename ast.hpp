// ast.hpp

#pragma once

#include "grammar.hpp"
#include "ir.hpp"

struct symbolEntry {
  std::string id;
  int idNum;
  int type;
};

class Scope {
  public:
    Scope(Scope* p): parent(p) {};
    Scope* parent;
    std::vector<Scope*> children;
    std::vector<symbolEntry*> symbols;
    bool contains(std::string s);
    int getIdNum(std::string s);
    symbolEntry getId(int idnum);
};

class Node {
  public:
    Node(int s, int pn): symbol(s), prodNum(pn) {};
    int symbol = 0;
    int prodNum = 0;
    int start = 0;
    int end = 0;
    int jump = 0;
    int next = 0;
    int op = 0;
    int temp = 0;
    int type = 0;
    Scope* scope = 0;
    bool newScope = false;
    bool print = false;
    virtual value val() = 0;
    virtual ~Node() {};
};

class Parent: public Node {
  public:
    Parent(int symbol, int prodNum, std::vector<Node*> nodes):
      Node(symbol, prodNum), children(nodes) {};
    virtual value val();
    std::vector<Node*> children;
};

class Leaf: public Node {
  public:
    Leaf(int symbol, Token *t): Node(symbol, -1), token(t) {};
    virtual value val();
    Token *token;
};

class AST {
  public:
    AST(Grammar* g): G(g) {};
    Grammar* G;
    Node* root;
    Scope* symbolTree = new Scope(NULL);
    Node* createInnerNode(int symbol, std::vector<Node*> nodes, int productionNumber);
    Node* createLeafNode(int symbol, Token *token);
    void printAST();
    void traverse(Node* node, Scope* scope);
    void preProcessNode(Node* node, Scope* scope);
    void processNode(Node* node);
    int newLabel();
    int newTemp();
    int newId();
    Scope* newScope(Scope *scope);
    void printCode();

  private:
    std::vector<Tac*> code;
    void printNode(Node* node, int indentLevel);
    int labelCounter = 0;
    int tempCounter = 0;
    int idCounter = 0;
};
