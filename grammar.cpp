// grammar.cpp

#include "grammar.hpp"
#include "util.cpp"
#include "token.hpp"
#include <vector>

int Grammar::tokenSymbol(Token* t) {
  return serialize(t.toString());
}

Grammar::read() {
  std::string line;

  while (std::getline(ss, line)) {
    if (emptyline(line)) continue;

    if (onlyalpha(line))
      throw std::exception("BAD GRAMMAR FILE: nonterminal can only be letters");

    readNonterminal(line);
  }
}

void Grammar::readNonterminal(std::string head) {
  Nonterminal* nt = new Nonterminal( serialize(head));

  readProductions(nt);
}

void Grammar::readProductions(Nonterminal* nt) {
  std::string line;

  while (std::getline(ss, line)) {
    if (emptyline(line)) break;

    validateProduction(line);
    
    vector<int> production = parseProduction(line);
    nt.body.push_back(production);
  }

  if (nt.body.size() == 0) throw std::exception("BAD GRAMMAR FILE: Nonterminal must have at least one production");
}

vector<int> Grammar::parseProduction(std::string line) {
  vector<int> prod;
  vector<string> words = words(line);

  for (string w: words)
    prod.push_back(serialize(w));

  return prod;
}

void Grammar::validateProduction(std::string line) {
  if ( line.length() < 2 || line[0] != '\t' || line[1] != '|' )
    throw std::exception("BAD GRAMMAR FILE: invalid production");
}

int Grammar::serialize(string s) {
  if (symbols.find(s) != symbols.end()) return symbols[s];

  symbolCounter++;
  symbols[s] = symbolCounter;
  return symbolCounter;
}
