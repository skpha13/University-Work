#include <iostream>

using namespace std;

int main() {
    int n, a, b, c;
    double minX = -1e7, maxX = 1e7, minY = -1e7, maxY = 1e7;
    cin >> n;

    for (int i=0; i<n; i++) {
        cin >> a >> b >> c;

        if (a == 0) {
            double newY = (-1.0 * c) / b;

            if (b > 0 && newY < maxY)
                maxY = newY;
            else if (b < 0 && newY > minY)
                minY = newY;
        } else if (b == 0) {
            double newX = (-1.0 * c) / a;

            if (a > 0 && newX < maxX)
                maxX = newX;
            else if (a < 0 && newX > minX)
                minX = newX;
        }
    }

    if (minX > maxX || minY > maxY) {
        cout << "VOID\n";
        return 0;
    }

    if (minX != -1e7 && maxX != 1e7 && minY != -1e7 && maxY != 1e7) {
        cout << "BOUNDED\n";
        return 0;
    }

    cout << "UNBOUNDED\n";
    return 0;
}