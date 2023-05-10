#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

ifstream f("deque.in");
ofstream g("deque.out");

class Deque {
private:
    int size,left,right;
    int *v;

public:
    Deque(int size);
    bool empty();
    bool full();
    void push_back(int val);
    void push_front(int val);
    int back();
    int front();
    void pop_back();
    void pop_front();
    ~Deque();
};

Deque::Deque(int size) {
    this->size = size;
    v = new int[size];
    for(int i=0;i<size;i++) v[i] = 0;
    left = -1;
    right = 0;
}

bool Deque::empty() {
    if(left == -1) return true;
    return false;
}

bool Deque::full() {
    if(left == 0 && right == size-1 || left == right + 1) return true;
    return false;
}

void Deque::push_front(int val) {
    if(this->full()) return;
    if(left == -1) left = 0, right = 0;
    else if(left == 0) left = size-1;
        else left--;
    v[left] = val;
}

void Deque::push_back(int val) {
    if (this->full()) return;
    if (left == -1) left = 0, right = 0;
    else if (right == size - 1) right = 0;
        else right++;
    v[right] = val;
}

int Deque::front() {
    if(left >= 0 && !this->empty()) return v[left];
    return 0;
}

int Deque::back() {
    if(right >= 0 && !this->empty()) return v[right];
    return 0;
}

void Deque::pop_back() {
    if(this->empty()) return;
    if(left == right) left = -1, right = -1;
    else if(right == 0) right = size-1;
        else right--;
}

void Deque::pop_front() {
    if(this->empty()) return;
    if(left == right) left = -1,right = -1;
    else if(left == size-1) left = 0;
        else left++;
}

Deque::~Deque() {
    delete v;
}


int main()
{
    int n,k;
    long long int s=0;
    f>>n>>k;
    Deque d(n+1);
    vector<int> v(n+1,0);

    for(int i=0;i<n;i++) f>>v[i];

    for(int i=0;i<n;i++) {
        while(!d.empty() && v[i] <= v[d.back()]) d.pop_back();
        d.push_back(i);

        if (d.front() == i - k) d.pop_front();

        if(i>=k-1) s += v[d.front()];
    }

    g<<s;
    return 0;
}