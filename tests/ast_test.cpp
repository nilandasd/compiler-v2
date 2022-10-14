//ast_test.cpp

#include "../ast.hpp"
#include "../grammar.hpp"
#include <fstream>
#include <cassert>

void test_constructors() {
  std::stringstream ss;
  Grammar G(&ss);
  G.read();

  IdToken t("test");
  AST ast(&G);
  Parent Parent(G.serialize("EXPR"), 0, std::vector<Node*> {});
  Leaf leaf(G.serialize("EXPR"), &t);
}

void test_createNode() {
  std::ifstream file( "./grammar.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();

  AST ast(&G);
  std::vector<Node*> children;
  Node* l1 = new Leaf(G.serialize("{"), 0);
  Node* l2 = new Leaf(G.serialize("}"), 0);
  Node* stmts = new Parent(G.serialize("STMTS"), 0, std::vector<Node*> {});
  children.push_back(l1);
  children.push_back(stmts);
  children.push_back(l2);
  Node* node = ast.createInnerNode(G.serialize("STMT"), children, 0);
  assert(node == stmts);
}

void test_createNode2() {
  std::ifstream file( "./grammar.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();

  AST ast(&G);
  std::vector<Node*> children;
  Node* l1 = new Leaf(G.serialize("WHILE"), 0);
  Node* l2 = new Leaf(G.serialize("("), 0);
  Node* expr = new Parent(G.serialize("EXPR"), 0, std::vector<Node*> {});
  Node* l3 = new Leaf(G.serialize(")"), 0);
  Node* stmt = new Parent(G.serialize("STMT"), 0, std::vector<Node*> {});
  children.push_back(l1);
  children.push_back(l2);
  children.push_back(expr);
  children.push_back(l3);
  children.push_back(stmt);
  Node* node = ast.createInnerNode(G.serialize("STMT"), children, 3);
  assert(node->symbol == G.serialize("STMT"));
  assert(((Parent *)node)->children.size() == 2);
  assert(expr->jump == 2);
  assert(stmt->next == 1);
  assert(stmt->end == 2);
}

int main() {
  test_constructors();
  test_createNode();
  test_createNode2();
}

