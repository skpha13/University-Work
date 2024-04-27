#include <iostream>
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
        vector<pair<int, int>> bottom_convex_hull;
        vector<pair<int, int>> top_convex_hull;

        if (points.size() < 3)
            return points;

        bottom_convex_hull.emplace_back(points[0]);
        bottom_convex_hull.emplace_back(points[1]);

        vector<pair<int, int>>::iterator point;
        for (point = points.begin() + 2; point != points.end(); point++) {
            bottom_convex_hull.emplace_back(*point);

            while (
                    bottom_convex_hull.size() > 2 &&
                    Orientation::orientationTest(
                            bottom_convex_hull[bottom_convex_hull.size() - 3],
                            bottom_convex_hull[bottom_convex_hull.size() - 2],
                            bottom_convex_hull[bottom_convex_hull.size() - 1]
                    ) >= 0
                    )
            {
                bottom_convex_hull.erase(bottom_convex_hull.end() - 2);
            }
        }

        top_convex_hull.emplace_back(points[0]);
        top_convex_hull.emplace_back(points[1]);

        for (point = points.begin() + 2; point != points.end(); point++) {
            top_convex_hull.emplace_back(*point);

            while (
                    top_convex_hull.size() > 2 &&
                    Orientation::orientationTest(
                            top_convex_hull[top_convex_hull.size() - 3],
                            top_convex_hull[top_convex_hull.size() - 2],
                            top_convex_hull[top_convex_hull.size() - 1]
                    ) <= 0
                    )
            {
                top_convex_hull.erase(top_convex_hull.end() - 2);
            }
        }

        reverse(top_convex_hull.begin(), top_convex_hull.end());
        bottom_convex_hull.insert(
                bottom_convex_hull.end() ,
                top_convex_hull.begin() + 1,
                top_convex_hull.end() - 1);
        return bottom_convex_hull;
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

    sort(points.begin(), points.end());

    vector<pair<int, int>> result = ConvexHull::getConvexHull(points);
    printf("%zu\n", result.size());
    for (auto point: result)
        printf("%d %d\n", point.first, point.second);

    return 0;
}