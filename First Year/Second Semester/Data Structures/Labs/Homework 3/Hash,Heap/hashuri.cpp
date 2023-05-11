#include <iostream>
#include <fstream>

std::ifstream f("hashuri.in");
std::ofstream g("hashuri.out");

struct Node {
    int value;
    Node *next;

    Node() {
        this->value = 0;
        this->next = NULL;
    }

    Node(int value) {
        this->value = value;
        this->next = NULL;
    }

    Node &operator=(const Node& obj) {
        if(this != &obj) {
            this->value = obj.value;
            this->next = obj.next;
        }
        return *this;
    }
};

class Hash {
private:
    Node* v;
    const int mod = 666013;

public:
    Hash();
    void insert(int);
    void remove(int);
    bool search(int);
};

Hash::Hash() {
    v = new Node[666013];
    for(int i=0;i<666013;i++) v[i].value = 0, v[i].next = NULL;
}

void Hash::insert(int value) {
    int hash_value = value % mod;
    if(v[hash_value].value == 0) v[hash_value].value = value;
    else {
        bool found = false;
        Node *temp = new Node(value);
        Node *it = &v[hash_value];
        while (it->next != NULL) {
            if (it->value == value) {found = true; break;}
            it = it->next;
        }
        if(found == false && it->value != value) it->next = temp;
    }
}

void Hash::remove(int value) {
    int hash_value = value % mod;
    if(v[hash_value].value == 0) return;
    if(v[hash_value].value == value && v[hash_value].next != NULL) {
        Node* temp = v[hash_value].next;
        v[hash_value] = *temp;
    }
    else if(v[hash_value].value == value && v[hash_value].next == NULL)  {
        v[hash_value].value = 0;
    }
    else {
        Node *it = &v[hash_value];
        while(it->next != NULL && it->next->value != value) it = it->next;
        if(it->next != NULL && it->next->value == value) {
            if(it->next->next == NULL) it->next = NULL;
            else it->next = it->next->next;
        }
    }
}

bool Hash::search(int value) {
    int hash_value = value % mod;
    if(v[hash_value].value == 0) return 0;
    if(v[hash_value].value == value) return 1;
    Node *it = &v[hash_value];
    while(it->next != NULL && it->next->value != value) it = it->next;
    if(it->next != NULL && it->next->value == value) return 1;
    return 0;
}

int main() {
    Hash h;
    int n,option,number;
    f>>n;

    for(int i=0;i<n;i++) {
        f>>option>>number;
        switch (option)
        {
        case 1:
            h.insert(number);
            break;
        
        case 2:
            h.remove(number);
            break;

        case 3:
            g<<h.search(number)<<"\n";
            break;

        default:
            break;
        }
    }
    return  0;
}