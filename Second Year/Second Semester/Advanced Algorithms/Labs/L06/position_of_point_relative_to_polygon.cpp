#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

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

    static bool liesOnSegment(pair<int, int> P, pair<int, int> Q, pair<int, int> R) {
        return min(P.first, Q.first) <= R.first && R.first <= max(P.first, Q.first) &&
               min(P.second, Q.second) <= R.second && R.second <= max(P.second, Q.second) &&
               orientationTest(P, Q, R) == 0;
    }
};

Answer isInsidePolygon(vector<pair<int, int>> &polygon, pair<int, int> point) {
    long long count = 0;

    for (int i=0; i<polygon.size()-1; i++) {
        if (Orientation::liesOnSegment(polygon[i], polygon[i+1], point))
            return BOUNDARY;

        if (
            point.first <= max(polygon[i].first, polygon[i+1].first) &&
            point.second > min(polygon[i].second, polygon[i+1].second) &&
            point.second <= max(polygon[i].second, polygon[i+1].second)
        )
        {
            int x = INT_MAX;

            if (polygon[i].second != polygon[i+1].second)
                x = (point.second - polygon[i].second) * (polygon[i+1].first - polygon[i].first) /
                    (polygon[i+1].second - polygon[i].second) + polygon[i].first;

            if ((polygon[i].first == polygon[i+1].first ) || point.first <= x)
                count += 1;
        }
    }

    if (count % 2)
        return INSIDE;

    return OUTSIDE;
}

int main() {
    int n, m;
    vector<pair<int, int>> polygon;
    cin >> n;

    int x, y;
    for (int i=0; i<n; i++) {
        cin >> x >> y;
        polygon.emplace_back(x, y);
    }
    polygon.push_back(polygon[0]);

    cin >> m;
    for (int i=0; i<m; i++) {
        pair<int, int> R;
        cin >> R.first >> R.second;

        cout << getAnswerString(isInsidePolygon(polygon, R)) << endl;
    }

    return 0;
}