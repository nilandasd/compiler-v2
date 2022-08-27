EXEC = compiler
G++ = g++-12 -std=c++17 -Wall
BUILD = $(G++) -c
LINK = $(G++) -o

executable: main token lexer grammar util
	$(LINK) $(EXEC) main.o token.o lexer.o grammar.o util.o

test: tests
	./lex_test
	./token_test
	./grammar_test
	./util_test

tests: token lexer token_test lexer_test grammar_test grammar util util_test
	$(LINK) lex_test lexer_test.o token.o lexer.o grammar.o util.o
	$(LINK) token_test token_test.o token.o lexer.o grammar.o util.o
	$(LINK) grammar_test grammar_test.o token.o lexer.o grammar.o util.o
	$(LINK) util_test util_test.o util.o

util_test:
	$(BUILD) ./tests/util_test.cpp

grammar_test:
	$(BUILD) ./tests/grammar_test.cpp

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
	rm *.o $(EXEC) *_test
