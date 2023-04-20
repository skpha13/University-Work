#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

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
    this->next.resize(level+1,NULL);
}

class SkipList {
private:
    Node* begin;
    int maxLevel,n,level;

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

void SkipList::insert(int value) {
    Node* iterator = begin;
    std::vector<Node*> updateNext(this->maxLevel+1,NULL);

//    we start from highest level and until we find a node with value lesser than insert value
    for(int i=this->maxLevel;i>=0;i--) {
        while(iterator->next[i] != NULL && iterator->next[i]->value < value)
            iterator = iterator->next[i];
        updateNext[i] = iterator;
    }

    if(iterator->value == value) {
        iterator->nrDuplicates += 1;
        return;
    }
    else
    {
        iterator = iterator->next[0];

        int newLevel = this->randomLevel();
        Node* temp = this->newNode(value,newLevel);

        for(int i=newLevel;i>=0;i--) {
            temp->next[i] = updateNext[i]->next[i];
            updateNext[i]->next[i] = temp;
        }
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

Node* SkipList::newNode(int value, int level) {
    Node* temp = new Node(value,level);
    return temp;
}

int SkipList::randomLevel() const {
//    temp will be the level we're at
    int temp = 1;
    while (random()<0.5 && temp<this->maxLevel)
        temp += 1;
    return temp;
}

int main() {
    SkipList s(5);
    std::cin>>s;
    std::cout<<s;
    return 0;
}
