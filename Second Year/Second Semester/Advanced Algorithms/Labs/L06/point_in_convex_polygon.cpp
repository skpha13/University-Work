#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

enum Answer {
    INSIDE = -1,
    OUTSIDE = 1,
    BOUNDARY = 0
};

string getAnswerString(Answer answer) {
    switch (answer) {
        case INSIDE: return "INSIDE";
        case OUTSIDE: return "OUTSIDE";
        case BOUNDARY: return "BOUNDARY";
        default: return "UNKNOWN";
    }
}

bool compare(pair<int,int> A, pair<int, int> B) {
    return A.first < B.first || (A.first == B.first && A.second < B.second);
}

long long crossProduct(pair<int, int> A, pair<int, int> B) {
    return A.first * B.second - A.second * B.first;
}

long long crossProduct(pair<int, int> A, pair<int, int> B, pair<int, int> C) {
    pair<int, int> newA, newB;

    newA.first = B.first - A.first;
    newA.second = B.second - A.second;

    newB.first = C.first - A.first;
    newB.second = C.second - A.second;

    return crossProduct(newA, newB);
}

Answer isInTriangle(pair<int, int> A, pair<int, int> B, pair<int, int> C, pair<int, int> point) {
    long long s1 = abs(crossProduct(A, B, C));
    long long s2 = abs(crossProduct(point, A, B)) + abs(crossProduct(point, B, C)) + abs(crossProduct(point, C, A));

    if (s1 == s2) {
        if (Orientation::orientationTest(A, B, point) == 0)
            return BOUNDARY;

        return INSIDE;
    }

    return OUTSIDE;
}

Answer isInsideConvexPolygon(vector<pair<int, int>> &polygon, pair<int, int> point) {
    int orientationWithPoint = Orientation::orientationTest(polygon[1], point, polygon[0]);
    int orientationWithLastSegment = Orientation::orientationTest(polygon[1], polygon[polygon.size()-1], polygon[0]);

    if (orientationWithPoint != 0 && orientationWithPoint != orientationWithLastSegment)
        return OUTSIDE;

    orientationWithPoint = Orientation::orientationTest(polygon[polygon.size()-1], point, polygon[0]);
    int orientationWithFirstSegment = Orientation::orientationTest(polygon[polygon.size()-1], polygon[1], polygon[0]);

    if (orientationWithPoint != 0 && orientationWithPoint != orientationWithFirstSegment)
        return OUTSIDE;

    orientationWithPoint = Orientation::orientationTest(polygon[1], point, polygon[0]);
    if (orientationWithPoint == 0 && (polygon[1].first * polygon[1].first + polygon[1].second * polygon[1].second) < (point.first * point.first + point.second * point.second)) {
        return OUTSIDE;
    }

    int left = 1, right = polygon.size()-1, mid;
    while (left < right - 1) {
        mid = left + (right - left) / 2;

        if (Orientation::orientationTest(polygon[mid], point, polygon[0]) <= 0)
            left = mid;
        else
            right = mid;
    }

    // check to see coliniarity on edge cases
    if (left == 1 && isInTriangle(polygon[left], polygon[left+1], polygon[0], point) == INSIDE &&
        (Orientation::orientationTest(polygon[0], polygon[left], point) == 0 ||
         Orientation::orientationTest(polygon[left], polygon[left+1], point) == 0))
    {
        return BOUNDARY;
    }

    // check to see coliniarity on edge cases
    if (left == polygon.size()-2 && isInTriangle(polygon[left], polygon[left+1], polygon[0], point) == INSIDE &&
        (Orientation::orientationTest(polygon[0], polygon[left+1], point) == 0 ||
         Orientation::orientationTest(polygon[left], polygon[left+1], point) == 0))
    {
        return BOUNDARY;
    }

    return isInTriangle(polygon[left], polygon[left+1], polygon[0], point);
}

int main() {
    int n, m;
    vector<pair<int, int>> polygon;
    cin >> n;

    int x, y;
    cin >> x >> y;
    polygon.emplace_back(x, y);
    int smallestXIndex = 0;

    for (int i=1; i<n; i++) {
        cin >> x >> y;
        polygon.emplace_back(x, y);

        if (compare(polygon[i], polygon[smallestXIndex]))
            smallestXIndex = i;
    }
    rotate(polygon.begin(), polygon.end() + smallestXIndex, polygon.end());

    cin >> m;
    for (int i=0; i<m; i++) {
        pair<int, int> R;
        cin >> R.first >> R.second;

        cout << getAnswerString(isInsideConvexPolygon(polygon, R)) << endl;
    }

    return 0;
}
