EXEC = compiler
G++ = g++-12 -std=c++17 -Wall
BUILD = $(G++) -c
LINK = $(G++) -o

executable: main token lexer grammar util item
	$(LINK) $(EXEC) main.o token.o lexer.o grammar.o util.o item.o

test: tests
	./lex_test
	./token_test
	./grammar_test
	./util_test
	./item_test

tests: token_test token lexer_test lexer grammar_test grammar util_test util item_test item
	$(LINK) lex_test lexer_test.o token.o lexer.o grammar.o util.o
	$(LINK) token_test token_test.o token.o lexer.o grammar.o util.o
	$(LINK) grammar_test grammar_test.o token.o lexer.o grammar.o util.o
	$(LINK) util_test util_test.o util.o
	$(LINK) item_test item_test.o item.o

item_test:
	$(BUILD) ./tests/item_test.cpp

util_test:
	$(BUILD) ./tests/util_test.cpp

grammar_test:
	$(BUILD) ./tests/grammar_test.cpp

lexer_test:
	$(BUILD) ./tests/lexer_test.cpp

token_test:
	$(BUILD) ./tests/token_test.cpp

item:
	$(BUILD) item.cpp

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
	rm *.o $(EXEC) *_test
