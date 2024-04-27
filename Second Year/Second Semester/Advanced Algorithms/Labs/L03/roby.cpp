#include <iostream>

using namespace std;

/**
 * @brief Determine the orientation of a point relative to a line segment.
 *
 * Given two points defining a line segment (P and Q) and a test point (R),
 * this function determines whether the test point lies to the left, right,
 * or on the line segment formed by P and Q.
 *
 * @param P The first point defining the line segment.
 * @param Q The second point defining the line segment.
 * @param R The point to test for orientation.
 *
 * @return -1 if R lies to the left of the line segment (PQ),
 *          0 if R lies on the line segment (PQ),
 *          1 if R lies to the right of the line segment (PQ).
 */
class Orientation {
public:
    static int orientationTest(pair<int, int> P, pair<int, int> Q, pair<int, int> R) {
        long long det = (1LL * Q.first * R.second - 1LL * R.first * Q.second) -
                        (1LL * P.first * R.second - 1LL * R.first * P.second) +
                        (1LL * P.first * Q.second - 1LL * Q.first * P.second);

        if (det < 0)
            return 1;

        if (det > 0)
            return -1;

        return 0;
    }
};

int main() {
    int n, countLeft = 0, countRight = 0, countTouch = 0;
    pair<int, int> P, Q, R, initial;

    cin >> n >> P.first >> P.second >> Q.first >> Q.second;
    initial.first = P.first;
    initial.second = P.second;

    for (int i=2; i<=n; i++) {
        if (i == n)
            R = initial;
        else
            cin >> R.first >> R.second;

        switch (Orientation::orientationTest(P, Q, R)) {
            case -1: {
                countLeft ++;
                break;
            }
            case 0: {
                countTouch ++;
                break;
            }
            case 1: {
                countRight ++;
                break;
            }
        }

        P = Q;
        Q = R;
    }

    printf("%d %d %d\n", countLeft, countRight, countTouch);
    return 0;
}

/*

7
1 1 5 3 2 3
1 1 5 3 4 1
1 1 5 3 3 2
5 5 5 10 5 5
-3 -1 -1 -2 -3 -2
-1 -2 -3 -1 -3 -2
0 0 0 0 0 0

*/