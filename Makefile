EXEC = compiler
G++ = g++-12 -std=c++17 -Wall
BUILD = $(G++) -c
LINK = $(G++) -o

executable: main token lexer grammar util
	$(LINK) $(EXEC) main.o token.o lexer.o grammar.o util.o

tests: token lexer token_test lexer_test grammar util
	$(LINK) lex_test lexer_test.o token.o lexer.o grammar.o util.o
	$(LINK) token_test token_test.o token.o lexer.o grammar.o util.o
	
lexer_test:
	$(BUILD) ./tests/lexer_test.cpp

token_test:
	$(BUILD) ./tests/token_test.cpp

main:
	$(BUILD) main.cpp

grammar:
	$(BUILD) grammar.cpp

token:
	$(BUILD) token.cpp

lexer:
	$(BUILD) lexer.cpp

util:
	$(BUILD) util.cpp

clean:
	rm *.o

spotless:
	rm *.o $(EXEC) lex_test token_test
