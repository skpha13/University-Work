#include <iostream>
#include <vector>

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
        int addElements = Q.first * R.second + P.second * R.first + P.first * Q.second;
        int substractElements = Q.first * P.second + Q.second * R.first + P.first * R.second;
        int det = addElements - substractElements;

        if (det < 0)
            return 1;

        if (det > 0)
            return -1;

        return 0;
    }
};

/**
 * @brief The ConvexHull class computes the convex hull of a set of points.
 */
class ConvexHull {
public:
    /**
     * @brief Computes the convex hull of a set of points.
     *
     * This function takes a vector of points as input and computes the convex hull
     * using the Graham's scan algorithm.
     *
     * @param points A reference to a vector of points represented as pairs of integers.
     * @return A vector containing the points that form the convex hull.
     */
    static vector<pair<int, int>> getConvexHull(vector<pair<int, int>> &points) {
        vector<pair<int, int>> stk;

        if (points.size() < 3)
            return points;

        points.emplace_back(points[0]);

        vector<pair<int, int>>::iterator point;
        for (point = points.begin(); point != points.end(); point++) {
            if (stk.size() < 2) {
                stk.emplace_back(*point);
                continue;
            }

            while (
                    stk.size() >= 2 &&
                    Orientation::orientationTest(
                        stk[stk.size() - 2],
                        stk[stk.size() - 1],
                        *point
                    ) >= 0
                )
            {
                stk.pop_back();
            }

            stk.emplace_back(*point);
        }

        stk.pop_back();
        if (!stk.empty() &&
            Orientation::orientationTest(stk[stk.size()-1], stk[0], stk[1]) >= 0)
            stk.erase(stk.begin());

        return stk;
    }

    // No default constructor as this is a Utility Class
    ConvexHull() = delete;
};

int main() {
    int n, x, y;
    vector<pair<int, int>> points;
    cin >> n;

    for (int i=0; i<n; i++) {
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    vector<pair<int, int>> result = ConvexHull::getConvexHull(points);
    printf("%zu\n", result.size());
    for (auto point: result)
        printf("%d %d\n", point.first, point.second);

    return 0;
}