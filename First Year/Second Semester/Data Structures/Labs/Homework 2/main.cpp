#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>

std::ifstream f("../abce.in");
std::ofstream g("../abce.out");

struct Node {
//    value of the node
//    nrDuplicates stores the frequency of a number
    int value;
//    for every level we will have a pointer to another node
    std::vector<Node*> next;

    Node(int value,int level);
};

Node::Node(int value, int level) {
    this->value = value;
//    to make every next node NULL
    this->next.resize(level+1,NULL);
}

class SkipList {
private:
    Node* begin;
    int maxLevel,n;

public:
    // constructors & destructors
    SkipList();
    SkipList(int maxLevel);

    // operators
    friend std::istream& operator>>(std::istream& in, SkipList& obj);
    friend std::ostream& operator<<(std::ostream& out,const SkipList& obj);

    // methods
    int randomLevel() const;
    Node* newNode(int value,int level);
    void insert(int value);
    void remove(int value);
    bool search(int value);
    int biggestNumber(int value);
    int smallestNumber(int value);
    void printBetween(int x,int y);
};

SkipList::SkipList() {
    // a random number
    this->maxLevel = 5;
    this->begin = new Node(-1,this->maxLevel);
}

SkipList::SkipList(int maxLevel) {
    this->maxLevel = maxLevel;
    this->begin = new Node(-1,this->maxLevel);
}

Node* SkipList::newNode(int value, int level) {
    Node* temp = new Node(value,level);
    return temp;
}

int SkipList::randomLevel() const {
//    temp will be the level we're at
    int temp = 1;
    while (std::rand()/(double)RAND_MAX<0.5 && temp<this->maxLevel)
        temp += 1;
    return temp;
}

void SkipList::insert(int value) {
    Node* iterator = begin;
    std::vector<Node*> updateNext(this->maxLevel+1,NULL);

//    we start from highest level and until we find a node with value lesser than insert value
    for(int i=this->maxLevel;i>=0;i--) {
        while(iterator->next[i] != NULL && iterator->next[i]->value < value)
            iterator = iterator->next[i];
        updateNext[i] = iterator;
    }

    iterator = iterator->next[0];

    int newLevel = this->randomLevel();
    Node* temp = this->newNode(value,newLevel);

    for(int i=newLevel;i>=0;i--) {
        temp->next[i] = updateNext[i]->next[i];
        updateNext[i]->next[i] = temp;
    }
}

void SkipList::remove(int value) {
    Node* iterator = begin;
    std::vector<Node*> updateNext(this->maxLevel+1,NULL);

    for(int i=this->maxLevel;i>=0;i--) {
        while(iterator->next[i] != NULL && iterator->next[i]->value < value)
            iterator = iterator->next[i];
        updateNext[i] = iterator;
    }

//    additional check because there can be only elements smaller than the one we want to delete,
//    reaching the end
    if(iterator->next[0] != NULL && iterator->next[0]->value == value) {
        iterator = iterator->next[0];
        for(int i=iterator->next.size()-1;i>=0;i--)
            updateNext[i]->next[i] = iterator->next[i];
        delete iterator;
    }
}

bool SkipList::search(int value) {
    Node* iterator = begin;

    for(int i=this->maxLevel;i>=0;i--) {
        while(iterator->next[i] != NULL && iterator->next[i]->value < value)
            iterator = iterator->next[i];
    }
    iterator = iterator->next[0];
    if(iterator != NULL && iterator->value == value) return true;
    return false;
}

int SkipList::biggestNumber(int value) {
    Node* iterator = begin;

    for(int i=this->maxLevel;i>=0;i--) {
        while(iterator->next[i] != NULL && iterator->next[i]->value <= value)
            iterator = iterator->next[i];
    }

    return iterator->value;
}

int SkipList::smallestNumber(int value) {
    Node* iterator = begin;

    for(int i=this->maxLevel;i>=0;i--) {
        while(iterator->next[i] != NULL && iterator->next[i]->value < value)
            iterator = iterator->next[i];
    }

    iterator = iterator->next[0];
    return iterator->value;
}

void SkipList::printBetween(int x, int y) {
    Node* iterator = begin;

    for(int i=this->maxLevel;i>=0;i--) {
        while(iterator->next[i] != NULL && iterator->next[i]->value < x)
            iterator = iterator->next[i];
    }

    while (iterator->next[0] != NULL && iterator->next[0]->value <= y) {
        iterator = iterator->next[0];
        g<<iterator->value<<" ";
    }
}

std::istream& operator>>(std::istream& in, SkipList& obj) {
    std::cout<<"Number of elements: \n";
    in>>obj.n;
    std::cout<<"Elements: \n";
    int temp;
    obj.maxLevel = log2(obj.n);
    if(obj.begin != NULL)
        delete obj.begin;
    obj.begin = new Node(-1,obj.maxLevel);
    for(int i=0;i<obj.n;i++)
    {
        in>>temp;
        obj.insert(temp);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out,const SkipList& obj) {
    Node* it = obj.begin;
    it = it->next[0];

    while(it != NULL)
    {
        out<<it->value<<" ";
        it = it->next[0];
    }
    out<<"\n";

    return out;
}

int main() {
    // log2(100 000) = 16,6
    SkipList s(16);

    int n,query;
    f>>n;
    for(int i=0;i<n;i++)
    {
        f>>query;
        switch (query) {
            case 1: {
                int temp;
                f>>temp;
                s.insert(temp);
                break;
            }
            case 2: {
                int temp;
                f>>temp;
                s.remove(temp);
                break;
            }
            case 3: {
                int temp;
                f>>temp;
                g<<s.search(temp)<<std::endl;
                break;
            }
            case 4: {
                int temp;
                f>>temp;
                g<<s.biggestNumber(temp)<<std::endl;
                break;
            }
            case 5: {
                int temp;
                f>>temp;
                g<<s.smallestNumber(temp)<<std::endl;
                break;
            }
            case 6: {
                int x,y;
                f>>x>>y;
                s.printBetween(x,y);
                g<<std::endl;
                break;
            }
        }
    }
    return 0;
}

// TODO see time improvements
// TODO 1,2,3 operations faster, maybe use array instead of vector
// TODO op 6 can be made faster