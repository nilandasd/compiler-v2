EXEC = compiler
G++ = g++-12 -std=c++17 -Wall
BUILD = $(G++) -c
LINK = $(G++) -o

executable: main token lexer
	$(LINK) $(EXEC) main.o token.o lexer.o

tests: token lexer token_test lexer_test
	$(LINK) lex_test lexer_test.o token.o lexer.o
	$(LINK) token_test token_test.o token.o lexer.o

lexer_test:
	$(BUILD) ./tests/lexer_test.cpp

token_test:
	$(BUILD) ./tests/token_test.cpp

main:
	$(BUILD) main.cpp

token:
	$(BUILD) token.cpp

lexer:
	$(BUILD) lexer.cpp

clean:
	rm *.o
