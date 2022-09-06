//  main.cpp

#include "lexer.hpp"
#include "parser.hpp"
#include <fstream>

int main() {

    std::ifstream file1( "./grammar.txt");
    std::stringstream ss1;
    ss1 << file1.rdbuf();
    file1.close();
    Grammar G(&ss1);  
    G.read();
    G.augmentStart();
  
    LALR lalr(G);
    lalr.init();
    lalr.print();

    std::ifstream file2( "./tests/programs/p2.nil");
    std::stringstream ss2;
    ss2 << file2.rdbuf();
    file2.close();
    Lexer lexer(&ss2);
    lexer.analyze();

    std::vector<int> symbols;
    while(true) {
      Token* token = lexer.getToken();
      if (token == NULL) break;
      token->toString();
      symbols.push_back(G.tokenSymbol(token));
    }

    lalr.parse(symbols);
}
