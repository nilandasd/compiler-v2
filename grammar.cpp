// grammar.cpp

#include "grammar.hpp"


int Grammar::tokenSymbol(Token* t) {
  return serialize(t->toString());
}

/*the first symbol of the grammar (i.e symbol with value 1)
  is implicitly defined as the start symbol)*/
void Grammar::augmentStart() {
  symbols["AUGMENTED_START"] = -1;
  Nonterminal* nt = new Nonterminal(AUGMENTED_START);
  std::vector<int> production { 1 };
  nt->productions.push_back(production); 
  nonterminals.push_back(nt);
}


/*This function would have to be changed durastically
  if the grammar were altered to accept empty productions*/
std::vector<int> Grammar::first(int i) {
  std::set<int> s; 

  if (!nonterminalExists(i)) {
    s.insert(i);
    std::vector v( s.begin(), s.end() );
    return v;
  }
  Nonterminal *nt = getNonterminal(i);
 
  for (auto production : nt->productions) {
    int k = production[0];

    if (nt->head == k) continue;

    if(!nonterminalExists(i)) {
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

  nonterminals.push_back(nt);
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

std::vector<Item*> Grammar::productionItems(int i) {
  std::vector<Item*> result;
  if (!nonterminalExists(i)) return result;

  for (auto production : getNonterminal(i)->productions) {
    std::vector<int> body = { CURSOR };
    body.insert(body.end(), production.begin(), production.end());
    Item *newItem = new Item(i, body, DNE);
    result.push_back(newItem);
  }

  return result;
}

std::string Grammar::symbolToString(int x) {
  if (x == AUGMENTED_START) return "AUGMENTED_START";
  if (x == DNE) return "DNE";
  if (x == ACCEPT) return "ACCEPT";

  for (auto i : symbols) {
    if (i.second == x) return i.first;
  }

  return "SYMBOL NOT FOUND";
}

bool Grammar::productionPrecedes(Item* a, Item* b) {
  if (b->head != a->head) {
    for (auto nt : nonterminals) {
      if (nt->head == a->head) break;
      if (nt->head == b->head) return false;
    }
  } else { // this doesnt work really work
    std::vector<int> aa = a->production();
    std::vector<int> bb = b->production();
    for (auto production : getNonterminal(a->head)->productions) {
      if (aa == production) break;
      if (bb == production) return false;
    }
  }

  return true;
}

int Grammar::productionNumber(Item* item) {
  int i = 0;
  std::vector<int> body = item->production();
  for (auto nt : nonterminals) {
    for (auto production : nt->productions) {
      if ( nt->head == item->head && production == body) return i;
      i++;
    }
  }

 throw std::runtime_error("production not found"); 
}

bool Grammar::nonterminalExists(int i) {
  for(auto nt : nonterminals) {
    if (i == nt->head) return true;
  }
  return false;
}

Nonterminal* Grammar::getNonterminal(int i) {
  for(auto nt : nonterminals) {
    if (i == nt->head) return nt;
  }
  return NULL;
}

std::pair<int, std::vector<int>> Grammar::getProduction(int pid) {
  std::pair<int, std::vector<int>> result;
  int i = 0;
  for (auto nt : nonterminals) {
    for (auto production : nt->productions) {
      if ( i == pid) return {nt->head, production};
      i++;
    }
  }
  throw std::runtime_error("production not found"); 
}