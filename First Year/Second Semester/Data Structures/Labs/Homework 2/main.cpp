#include <iostream>
#include <cstring>
#include <vector>

struct Node {
//    value of the node
//    nrDuplicates stores the frequency of a number
    int value,nrDuplicates;
//    for every level we will have a pointer to another node
    std::vector<Node*> next;

    Node(int value,int level);
};

Node::Node(int value, int level) {
    this->value = value;
//    to make every next node NULL
    next.resize(level+1,NULL);
}

class SkipList {
private:
    Node* begin;
    int maxLevel,n,level;

public:
    int randomLevel() const;
};

int SkipList::randomLevel() const {
//    temp will be the level we're at
    int temp = 1;
    while (random()<0.5 && temp<this->maxLevel)
        temp += 1;
    return temp;
}

int main() {

    return 0;
}
