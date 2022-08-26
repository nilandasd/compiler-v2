// grammar.cpp

#include "grammar.hpp"
#include "util.hpp"
#include "token.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>


int Grammar::tokenSymbol(Token* t) {
  return serialize(t->toString());
}

void Grammar::read() {
  char l[256];

  while (ss->getline(l, 256)) {
    std::string line(l);

    if (emptyline(line)) continue;

    if (onlyalpha(line))
      throw std::runtime_error("BAD GRAMMAR FILE: nonterminal can only be letters");

    readNonterminal(line);
  }
}

void Grammar::readNonterminal(std::string head) {
  Nonterminal* nt = new Nonterminal( serialize(head));

  readProductions(nt);

  nonterminals[nt->head] = nt;
}

void Grammar::readProductions(Nonterminal* nt) {
  char l[256];

  while (ss->getline(l, 256)) {
    std::string line(l);

    if (emptyline(line)) break;

    validateProduction(line);
    
    std::vector<int> production = parseProduction(line);
    nt->productions.push_back(production);
  }

  if (nt->productions.size() == 0) 
    throw std::runtime_error("BAD GRAMMAR FILE: Nonterminal must have at least one production");  
}

std::vector<int> Grammar::parseProduction(std::string line) {
  std::vector<int> prod;
  std::vector<std::string> words = getwords(line.substr(2, line.size() - 1));

  for (std::string w: words)
    prod.push_back(serialize(w));

  return prod;
}

void Grammar::validateProduction(std::string line) {
  if ( line.length() < 2 || line[0] != '\t' || line[1] != '|' )
    throw std::runtime_error("BAD GRAMMAR FILE: invalid production"); 
}

int Grammar::serialize(std::string s) {
  if (symbols.find(s) != symbols.end()) return symbols[s];

  symbolCounter++;
  symbols[s] = symbolCounter;
  return symbolCounter;
}
