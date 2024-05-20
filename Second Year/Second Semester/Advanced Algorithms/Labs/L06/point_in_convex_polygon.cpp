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

class Point {
public:
    pair<int, int> point;
    static pair<int, int> anchor;

    Point() = default;
    Point(pair<int, int> point) { this->point = point; }

    Point operator+(const Point &p) const;
    Point operator-(const Point &p) const;
    long long crossProduct(const Point &p) const;
    long long crossProduct(const Point &p1, const Point &p2) const ;
    long long dotProduct(const Point &p) const;
    long long dotProduct(const Point &p1, const Point &p2) const;
    long long sqrtDistance() const { return this->dotProduct(*this); }
};

pair<int,int> Point::anchor;

Point Point::operator+(const Point &p) const {
    return {make_pair(this->point.first + p.point.first,
                      this->point.second + p.point.second)};
}

Point Point::operator-(const Point &p) const {
    return {make_pair(this->point.first - p.point.first,
                      this->point.second - p.point.second)};
}

long long Point::crossProduct(const Point &p) const {
    return this->point.first * p.point.second - this->point.second * p.point.first;
}

long long Point::crossProduct(const Point &p1, const Point &p2) const {
    return (p1 - *this).crossProduct(p2 - *this);
}

long long Point::dotProduct(const Point &p) const {
    return this->point.first * p.point.first + this->point.second * p.point.second;
}

bool compare(const Point &A, const Point &B) {
    return A.point.first < B.point.first || (A.point.first == B.point.first && A.point.second < B.point.second);
}

int sign(long long value) {
    if (value == 0)
        return 0;

    return value > 0 ? 1 : -1;
}

Answer isInTriangle(Point A, Point B, Point point) {
    Point C = Point(make_pair(0, 0));
    long long s1 = abs(A.crossProduct(B, C));
    long long s2 = abs(point.crossProduct(A, B)) +
                   abs(point.crossProduct(B, C)) +
                   abs(point.crossProduct(C, A));

    if (s1 == s2) {
        // check to see if point is situated on polygon
        if (Orientation::orientationTest(A.point, B.point, point.point) == 0)
            return BOUNDARY;

        return INSIDE;
    }

    return OUTSIDE;
}

Answer isInsideConvexPolygon(vector<Point> &polygon, Point point) {
    // normalize point
    point.point.first = point.point.first - Point::anchor.first;
    point.point.second = point.point.second - Point::anchor.second;

    // check for edge cases
    if (polygon[0].crossProduct(point) != 0 &&
        sign(polygon[0].crossProduct(point)) != sign(polygon[0].crossProduct(*(polygon.end()-1))))
        return OUTSIDE;

    if ((*(polygon.end()-1)).crossProduct(point) != 0 &&
        sign((*(polygon.end()-1)).crossProduct(point)) != sign((*(polygon.end()-1)).crossProduct(polygon[0])))
        return OUTSIDE;

    if (polygon[0].crossProduct(point) == 0 && polygon[0].sqrtDistance() < point.sqrtDistance())
        return OUTSIDE;

    // binary search
    int left = 0, right = polygon.size()-1, mid;
    while (left < right - 1) {
        mid = left + (right - left) / 2;

        // see orientation of generated line from anchor point
        if (Orientation::orientationTest(polygon[mid].point, point.point, make_pair(0, 0)) <= 0)
            left = mid;
        else
            right = mid;
    }

    // check to see coliniarity on edge cases
    if (left == 0 && isInTriangle(polygon[left], polygon[left+1], point) != OUTSIDE &&
        (Orientation::orientationTest(make_pair(0, 0), polygon[left].point, point.point) == 0 ||
         Orientation::orientationTest(polygon[left].point, polygon[left+1].point, point.point) == 0))
    {
        return BOUNDARY;
    }

    // check to see coliniarity on edge cases
    if (left == polygon.size()-2 && isInTriangle(polygon[left], polygon[left+1], point) != OUTSIDE &&
        (Orientation::orientationTest(make_pair(0, 0), polygon[left+1].point, point.point) == 0 ||
         Orientation::orientationTest(polygon[left].point, polygon[left+1].point, point.point) == 0))
    {
        return BOUNDARY;
    }

    return isInTriangle(polygon[left], polygon[left+1], point);
}

int main() {
    int n, m;
    vector<Point> polygon;
    cin >> n;

    int x, y;
    cin >> x >> y;
    polygon.emplace_back(make_pair(x, y));
    int smallestXIndex = 0;

    for (int i=1; i<n; i++) {
        cin >> x >> y;
        polygon.emplace_back(make_pair(x, y));

        if (compare(polygon[i], polygon[smallestXIndex]))
            smallestXIndex = i;
    }
    rotate(polygon.begin(), polygon.end() + smallestXIndex, polygon.end());

    vector<Point> points(polygon.size()-1);
    for (int i=0; i<points.size(); i++)
        points[i] = polygon[i+1] - polygon[0];
    Point::anchor = polygon[0].point;

    cin >> m;
    for (int i=0; i<m; i++) {
        Point R;
        cin >> R.point.first >> R.point.second;

        cout << getAnswerString(isInsideConvexPolygon(points, R)) << endl;
    }

    return 0;
}
