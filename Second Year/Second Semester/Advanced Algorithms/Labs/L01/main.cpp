#include <iostream>

using namespace std;

int add(int x, int y) {
    return x + y;
}

int main() {
    int n;
    cin >> n;
    int a, b;
    for (int i=0; i<n; i++) {
        cin >> a >> b;
        cout << add(a, b) << endl;
    }
    return 0;
}
