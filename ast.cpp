// ast.cpp

#include "ast.hpp"

Node* AST::createInnerNode(int symbol, std::vector<Node*> nodes, int prodNum) {
  if (symbol == G->serialize("STMT")) {
    if (prodNum == 0) { // STMT => { STMTS }
      delete nodes[0];
      delete nodes[2];
      nodes[1]->newScope = true;
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
      return new Parent(symbol, prodNum, children);

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
      return new Parent(symbol, prodNum, children);

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
      return new Parent(symbol, prodNum, children);

    } else if (prodNum == 4) {
      std::vector<Node*> children;
      delete nodes[0];
      children.push_back(nodes[1]);
      children.push_back(nodes[2]);
      delete nodes[3];
      return new Parent(symbol, prodNum, children);

    } else if (prodNum == 5) {
      std::vector<Node*> children;
      children.push_back(nodes[0]);
      delete nodes[1];
      children.push_back(nodes[2]);
      delete nodes[3];
      return new Parent(symbol, prodNum, children);

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
      Node* newNode = new Parent(symbol, prodNum, children);
      newNode->op = operators[G->symbolToString(nodes[1]->symbol)];
      newNode->temp = newTemp();
      return newNode;

    } else { // ID or NUM
      return nodes[0];
    } 
  } else if (symbol == G->serialize("STMTS")) { // STMTS => STMTS STMT
    if (prodNum == 0) {
      if (nodes[0]->symbol == G->serialize("STMTS")) {
        static_cast<Parent*>(nodes[0])->children.push_back(nodes[1]);
        return nodes[0];
      } else {
        return new Parent(symbol, prodNum, nodes);
      }
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

void AST::traverse(Node* node, Scope* scope) {
  Parent* p = dynamic_cast<Parent*>(node);
  preProcessNode(node, scope);

  if (p != nullptr) {
    for (auto n: p->children) {
      traverse(n, node->scope);
    }
  }

  processNode(node);
}

void AST::preProcessNode(Node* node, Scope* scope) {
  if (node->start != 0) {
     code.push_back(Tac::label(node->start));
  }
  if (node->newScope) {
    node->scope = newScope(scope);
  } else {
    node->scope = scope;
  }
}

void AST::processNode(Node* node) {
  if (node->symbol == G->serialize("NUM")) {
    node->type = INT_TYPE;
  } else if (node->symbol == G->serialize("EXPR")) {
    // an expression will allways have 3 children
    // and an operator
    // a value is of type <TYPE, NUM>
    // type = ID, temp, num
    // num = id id or temp number or the actual value
    Parent* parent = static_cast<Parent*>(node);
    Node* c1 = parent->children[0];
    Node* c2 = parent->children[1];
    value v1 = c1->val();
    value v2 = c2->val();

    if (c1->type != c2->type) {
      throw std::runtime_error("type error");
    }

    node->type = c1->type;

    code.push_back(
      Tac::expr(
        node->temp,
        node->op,
        v1,
        v2));

    if (node->jump) {
      code.push_back(Tac::conj(node->jump, node->temp));
    }
  } else if (node->symbol == G->serialize("STMT")) {
    if (node->prodNum == 4) { // ID TYPE
      Parent* p = static_cast<Parent*>(node);
      Leaf* var = static_cast<Leaf*>(p->children[0]);
      Leaf* type = static_cast<Leaf*>(p->children[1]);
      IdToken* idtoken = static_cast<IdToken*>(var->token);
      std::string id = idtoken->attr;
      if (node->scope->contains(id)) {
        throw std::runtime_error("id already declared in this scope");
      }
      symbolEntry* se = new symbolEntry;
      se->id = id;
      se->idNum = newId();
      se->type = INT_TYPE;
      node->scope->symbols.push_back(se);

    } else if (node->prodNum == 5) { // ID EXPR
      Parent* p = static_cast<Parent*>(node);
      Leaf* var = static_cast<Leaf*>(p->children[0]);
      Leaf* expr = static_cast<Leaf*>(p->children[1]);
      IdToken* idtoken = static_cast<IdToken*>(var->token);
      std::string id = idtoken->attr;
      if (!node->scope->contains(id)) {
        throw std::runtime_error("id not declared in this scope");
      }

      code.push_back(Tac::asg(node->scope->getIdNum(id), expr->temp));

    } else if (node->prodNum == 6) { // PRINT EXPR
      //code.push_back(Tac::print(expr.temp))
    }
  }

  if (node->next != 0) {
    code.push_back(Tac::jump(node->next));
  }

  if(node->end != 0) {
     code.push_back(Tac::label(node->end));
  }
}

value Parent::val() {
  return {TEMP_VAL, temp};
}

value Leaf::val() {
  if (symbol == ID) {
    IdToken* idtoken = static_cast<IdToken*>(token);
    std::string id = idtoken->attr;
    int n = scope->getIdNum(id);
    symbolEntry se = scope->getId(n);
    int idNum = se.idNum;
    type = se.type;
    if (idNum == -1) {
      throw std::runtime_error("id not declared in this scope");
    }
    
    return { ID_VAL, idNum };
  } else if (symbol == NUM) {

    NumToken* numtoken = static_cast<NumToken*>(token);
    return { INT_VAL, numtoken->attr };
  }
}

int AST::newLabel() {
  return ++labelCounter;
}

int AST::newTemp() {
  return ++tempCounter;
}

int AST::newId() {
  return ++idCounter;
}

Scope* AST::newScope(Scope* scope) {
  Scope* newScope =  new Scope(scope);
  scope->children.push_back(newScope);
  return newScope;
}

bool Scope::contains(std::string s) {
  for (auto id: symbols) {
    if (s == id->id) return true;
  }

  if (parent == NULL) {
    return false;
  } else {
    return parent->contains(s);
  }
}

int Scope::getIdNum(std::string s) {
  for (auto id: symbols) {
    if (s == id->id) {
      return id->idNum;
    }
  }

  if (parent == NULL) {
    return -1;
  } else {
    return parent->getIdNum(s);
  }
}

symbolEntry Scope::getId(int idnum) {
  for (auto id: symbols) {
    if (idnum == id->idNum) return *id;
  }
  if (parent == NULL) {
    throw std::runtime_error("unable to find id");
  } else {
    return parent->getId(idnum);
  }
}

void AST::printCode() {
  for (auto c : code) {
    c->print();
  }
}
