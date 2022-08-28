EXEC = compiler
G++ = g++-12 -std=c++17 -Wall
BUILD = $(G++) -c
LINK = $(G++) -o

TEST_DIR=./tests/

SRCS=token.cpp lexer.cpp grammar.cpp util.cpp item.cpp
OBJS=$(subst .cpp,.o, $(SRCS))

TESTS=$(subst .cpp,_test.cpp, $(SRCS))
TEST_EXECS=$(subst .cpp,, $(TESTS))

all: $(EXEC)

$(EXEC): $(OBJS) main.o
	$(LINK) $(EXEC) main.o $(OBJS)

test: spotless $(OBJS) $(TEST_EXECS)

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
