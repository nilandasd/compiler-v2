// item.hpp

#pragma once

#include <vector>
#include <stdexcept>

#define ACCEPT_STATE 0
#define DNE -1
#define CURSOR -2
#define ACCEPT -3
#define AUGMENTED_START -4
#define SHIFT -5
#define REDUCE -6

class Item {
  public:
    Item(int h, std::vector<int> b, int la): head(h), body(b), lookahead(la) {};

    int head;
    std::vector<int> body;
    int lookahead;

    int expects();
    Item* shiftCursor();
    std::vector<int> postfix();
    bool in(std::vector<Item*> items);
    std::vector<int> production();

    bool operator==(const Item& i);
    bool operator!=(const Item& i);
};
