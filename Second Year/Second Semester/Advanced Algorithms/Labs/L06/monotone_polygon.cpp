#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
public:
    int x, y;

    Point() = default;
    Point(int x, int y) : x(x), y(y) { }
};

bool isMonotoneX(vector<Point> &points) {
    int minXIndex = 0;
    int maxXIndex = 0;

    for (int i=0; i<points.size(); i++) {
        if (points[i].x > points[maxXIndex].x)
            maxXIndex = i;
        if (points[i].x < points[minXIndex].x)
            minXIndex = i;
    }

    vector<Point> leftSplit;
    vector<Point> rightSplit;

    for (int i=minXIndex; i!=maxXIndex; i = (i+1) % points.size())
        leftSplit.push_back(points[i]);


    for (int i=maxXIndex; i!=minXIndex; i = (i+1) % points.size())
        rightSplit.push_back(points[i]);

    for (int i=1; i<leftSplit.size(); i++)
        if (leftSplit[i].x < leftSplit[i-1].x)
            return false;

    for (int i=1; i<rightSplit.size(); i++)
        if (rightSplit[i].x > rightSplit[i-1].x)
            return false;

    return true;
}

bool isMonotoneY(vector<Point> &points) {
    int minYIndex = 0;
    int maxYIndex = 0;

    for (int i=0; i<points.size(); i++) {
        if (points[i].y > points[maxYIndex].y)
            maxYIndex = i;
        if (points[i].y < points[minYIndex].y)
            minYIndex = i;
    }

    vector<Point> leftSplit;
    vector<Point> rightSplit;

    for (int i=minYIndex; i != maxYIndex; i = (i + 1) % points.size())
        leftSplit.push_back(points[i]);


    for (int i=maxYIndex; i != minYIndex; i = (i + 1) % points.size())
        rightSplit.push_back(points[i]);

    for (int i=1; i<leftSplit.size(); i++)
        if (leftSplit[i].y < leftSplit[i-1].y)
            return false;

    for (int i=1; i<rightSplit.size(); i++)
        if (rightSplit[i].y > rightSplit[i-1].y)
            return false;

    return true;
}

int main() {
    int n;
    vector<Point> points;

    cin >> n;
    for (int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    if (isMonotoneX(points))
        cout << "YES\n";
    else cout << "NO\n";

    if (isMonotoneY(points))
        cout << "YES\n";
    else cout << "NO\n";

    return 0;
}