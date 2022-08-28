// grammar.cpp

#include "grammar.hpp"
#include "util.hpp"
#include "token.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <set>


int Grammar::tokenSymbol(Token* t) {
  return serialize(t->toString());
}

/*the first symbol of the grammar (i.e symbol with value 1)
  is implicitly defined as the start symbol)*/
void Grammar::augmentStart() {
  Nonterminal* nt = new Nonterminal( serialize("AUGMENTED_START"));
  std::vector<int> production { 1 };
  nt->productions.push_back(production); 
  nonterminals[nt->head] = nt;
}


/*This function would have to be changed durastically
  if the grammar were altered to accept empty productions*/
std::vector<int> Grammar::first(int i) {
  std::set<int> s; 

  if (nonterminals.find(i) == nonterminals.end()) {
    s.insert(i);
    std::vector v( s.begin(), s.end() );
    return v;
  }
  Nonterminal *nt = nonterminals[i];
 
  for ( auto &production : nt->productions ) {
    int k = production[0];

    if ( nt->head == k ) continue;

    if(nonterminals.find(k) == nonterminals.end()) {
      s.insert(k);
    } else {
      for (auto j : Grammar::first(k)) {
        s.insert(j);
      }
    }
  }

  std::vector v( s.begin(), s.end() );
  return v;
}

void Grammar::read() {
  char l[256];

  while (ss->getline(l, 256)) {
    std::string line(l);

    if (empty(line)) continue;

    if (!alpha(line))
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

    if (empty(line)) break;

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
