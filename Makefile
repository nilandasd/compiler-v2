EXEC = compiler
G++ = g++ -std=c++17 -Wall
BUILD = $(G++) -c
LINK = $(G++) -o

SRCS=parser.cpp token.cpp lexer.cpp grammar.cpp util.cpp item.cpp state.cpp
OBJS=$(subst .cpp,.o, $(SRCS))
TESTS=$(subst .cpp,_test, $(SRCS))

all: $(EXEC)

$(EXEC): $(OBJS) main.o
	$(LINK) $(EXEC) main.o $(OBJS)

test: spotless $(OBJS) $(TESTS)

%_test: %_test.o
	$(LINK) $@ $< $(OBJS)
	./$@
	
%_test.o: ./tests/%_test.cpp
	$(BUILD) $<

%.o : %.cpp
	$(BUILD) $<

clean:
	rm *.o

spotless:
	rm *.o $(EXEC) *_test || true
