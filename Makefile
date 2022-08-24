EXEC = compiler
G++ = g++-12 -std=c++17
BUILD = $(G++) -c
LINK = $(G++) -o

executable: main token
	$(LINK) $(EXEC) main.o token.o
main:
	$(BUILD) main.cpp
token:
	$(BUILD) token.cpp

clean:
	rm *.o
