#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

ifstream f("deque.in");
ofstream g("deque.out");

struct Node {
    int val;
    Node* next;
    Node* prev;

    Node() {
        this->val = -1;
        this->next = NULL;
        this->prev = NULL;
    }

    Node(int val) {
        this->val = val;
        this->next = NULL;
        this->prev = NULL;
    }

//    ~Node() {
//        cout<<"delete node: "<<this->val;
//        if(next != NULL) {
//            cout<<" yes";
//            next->prev = prev;
//            delete next;
//            next = NULL;
//        }
//        cout<<"\n";
//    }
};

class Deque {
private:
    int size;
    Node* up;
    Node* down;

public:
    Deque();
    bool empty();
    void push_back(int val);
    void push_front(int val);
    int back();
    int front();
    void pop_back();
    void pop_front();
    ~Deque();
};

Deque::Deque() {
    this->size = 0;
    this->up = new Node(-10000001);
    this->down = new Node(-10000002);
}

bool Deque::empty() {
    if(up->next == NULL && up->prev == NULL && down->next == NULL && down->prev || this->size == 0)
        return true;
    return false;
}

void Deque::push_front(int val) {
    Node* temp = new Node(val);
    if(size == 0) {
        temp->prev = up;
        up->next = temp;
        temp->next = down;
        down->prev = temp;
    }
    else {
//        cout<<"*"<<up->next->val<<"\n";
        temp->prev = up;
        temp->next = up->next;
        up->next->prev = temp;
        up->next = temp;
    }
    size++;
}

void Deque::push_back(int val) {
    Node* temp;
    temp = new Node(val);
    if(size == 0) {
        temp->next = down;
        temp->prev = up;
        down->prev = temp;
        up->next = temp;
    }
    else {
        temp->prev = down->prev;
        down->prev = temp;
        temp->next = down;
        temp->prev->next = temp;
    }
    size++;
}

int Deque::back() {
    Node* it = down;
    it = it->prev;
    return it->val;
}

int Deque::front() {
    Node* it = up;
    it = it->next;
    return it->val;
}

void Deque::pop_back() {
    if(size==0) return;
    Node* temp = down->prev->prev;
    temp->next = down;
    delete down->prev;
    down->prev = temp;
    size--;
}

void Deque::pop_front() {
    if(size==0) return;
    Node* temp = up->next->next;
    temp->prev = up;
    delete up->next;
    up->next = temp;
    size--;
}

Deque::~Deque() {
    Node* it = up->next;
    while(it != down) {
        Node* urm = it->next;
        delete it;
        it = urm;
    }
    delete up;
    delete down;
    size = 0;
}

int main()
{

    Deque d;
//    d.push_front(1);
//    cout<<"front: "<<d.front()<<endl;
//    d.push_front(2);
//    d.push_front(3);
//    cout<<"back: "<<d.back()<<endl;
//    d.push_back(10);
//    cout<<"back: "<<d.back()<<endl;
//    d.pop_back();
//    d.pop_front();

     int n,k;
     long long int s=0;
     f>>n>>k;
     vector<int> v(n);
//     deque<int> d;

     for(int i=0;i<n;i++) f>>v[i];

     for(int i=0;i<n;i++) {
         while(!d.empty() && v[i] <= v[d.back()]) d.pop_back();
         d.push_back(i);

         if(d.front() == i-k) d.pop_front();

         if(i>=k-1) s += v[d.front()];
     }

     g<<s;
     return 0;
}