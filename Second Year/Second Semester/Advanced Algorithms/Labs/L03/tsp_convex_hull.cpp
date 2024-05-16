#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cfloat>

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

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        return hash1;
    }
};

double getDistance(const pair<int,int> &pointA, const pair<int,int> &pointB) {
    return sqrt(pow(pointA.first - pointB.first, 2) + pow(pointA.second - pointB.second, 2));
}


struct Candidate {
    pair<int, int> i;
    pair<int, int> j;
    pair<int, int> r;
    int insertIndex;

    double getDistance() {
        return (::getDistance(i, r) + ::getDistance(r, j)) /
               ::getDistance(i, j);
    }
};

int main() {
    // read input and sort vector
    int n, x, y;
    vector<pair<int, int>> points;
    cin >> n;

    for (int i=0; i<n; i++) {
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    sort(points.begin(), points.end());

    vector<pair<int, int>> convexHull = ConvexHull::getConvexHull(points);
    unordered_set<pair<int, int>, hash_pair> subTour;

    // see what points are in the sub tour and which not
    for (auto point: convexHull)
        subTour.insert(point);

    int countOfRemainingPoints = points.size() - convexHull.size();
    vector<Candidate> candidates;

    // do this while we have not inserted all points in the sub tour
    while (countOfRemainingPoints) {
        for (auto point: points) {
            // for a point which is not in sub tour find all candidates
            if (subTour.find(point) == subTour.end()) {
                int minIndex = 0;
                double minDistance = DBL_MAX;
                for (int i=0; i < convexHull.size() - 1; i++) {
                    double distance =
                            getDistance(convexHull[i], point) +
                            getDistance(point, convexHull[i + 1]) -
                            getDistance(convexHull[i], convexHull[i + 1]);
                    if (distance < minDistance) {
                        minDistance = distance;
                        minIndex = i;
                    }
                }

                // Checking for last two points in subtour:
                // This results in the line of last point in convex hull with first point in convex hull
                double distance =
                        getDistance(convexHull[convexHull.size()-1], point) +
                        getDistance(point, convexHull[0]) -
                        getDistance(convexHull[convexHull.size()-1], convexHull[0]);

                if (distance < minDistance) {
                    minIndex = convexHull.size() - 1;
                }

                candidates.emplace_back(Candidate {
                    .i = convexHull[minIndex],
                    .j = convexHull[(minIndex + 1) % convexHull.size()],
                    .r = point,
                    .insertIndex = minIndex
                });
            }
        }

        // insert the best candidate
        Candidate minCandidate = candidates[0];
        for (int i=1; i<candidates.size(); i++) {
            if (candidates[i].getDistance() < minCandidate.getDistance())
                minCandidate = candidates[i];
        }

        convexHull.insert(convexHull.begin() + minCandidate.insertIndex + 1, minCandidate.r);
        candidates.clear();
        subTour.insert(minCandidate.r);
        countOfRemainingPoints--;
    }

    // Find point with minimum x value
    int minXValueIndex = 0;
    for (int i=1; i<convexHull.size(); i++) {
        if (convexHull[i].first < convexHull[minXValueIndex].first)
            minXValueIndex = i;
    }

    // print result
    for (int i=minXValueIndex; i<convexHull.size(); i++)
        printf("%d %d\n", convexHull[i].first, convexHull[i].second);

    for (int i=0; i<=minXValueIndex; i++)
        printf("%d %d\n", convexHull[i].first, convexHull[i].second);

    return 0;
}