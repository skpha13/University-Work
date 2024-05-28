#include <iostream>

using namespace std;

enum Answer {
    INSIDE = -1,
    OUTSIDE = 1,
    BOUNDARY = 0
};

string getAnswerString(Answer answer) {
    switch (answer) {
        case INSIDE: return "ILLEGAL";
        case OUTSIDE: return "LEGAL";
        case BOUNDARY: return "ILLEGAL";
        default: return "UNKNOWN";
    }
}

long long distance(pair<long long, long long> p1, pair<long long, long long> p2) {
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}

long long dotProduct(pair<long, long> p1, pair<long, long> p2, pair<long, long> p3) {
    return (p2.first - p1.first) * (p3.first - p2.first) + (p2.second - p1.second) * (p3.second - p2.second);
}

bool isSquare(pair<long long, long long> A, pair<long long, long long> B, pair<long long, long long> C, pair<long long, long long> D) {
    return (distance(A, B) == distance(B, C) &&
            distance(C, D) == distance(D, A) &&
            distance(A, B) == distance(C, D));
}

bool isRectangle(pair<long long, long long> A, pair<long long, long long> B, pair<long long, long long> C, pair<long long, long long> D) {
    return (distance(A, B) == distance(C, D) &&
            distance(B, C) == distance(D, A) &&
            dotProduct(A, B, C) == 0);
}

Answer isInsideCircle(pair<long long, long long> A, pair<long long, long long> B, pair<long long, long long> C, pair<long long, long long> D) {
    if (isSquare(A, B, C, D) || isRectangle(A, B, C, D))
        return OUTSIDE;

    long long det;
    long long ACoordinatesSquared = A.first * A.first + A.second * A.second;
    long long BCoordinatesSquared = B.first * B.first + B.second * B.second;
    long long CCoordinatesSquared = C.first * C.first + C.second * C.second;
    long long DCoordinatesSquared = D.first * D.first + D.second * D.second;

    long long firstDet = A.first * (
            (B.second * CCoordinatesSquared + C.second * DCoordinatesSquared + BCoordinatesSquared * D.second) -
            (D.second * CCoordinatesSquared + B.second * DCoordinatesSquared + BCoordinatesSquared * C.second)
    );

    long long secondDet = A.second * (
            (B.first * CCoordinatesSquared + C.first * DCoordinatesSquared + D.first * BCoordinatesSquared) -
            (D.first * CCoordinatesSquared + B.first * DCoordinatesSquared + C.first * BCoordinatesSquared)
    );

    long long thirdDet = ACoordinatesSquared * (
            (B.first * C.second + C.first * D.second + D.first * B.second) -
            (D.first * C.second + B.first * D.second + C.first * B.second)
    );

    long long fourthDet = 1 * (
            (B.first * C.second * DCoordinatesSquared + C.first * D.second * BCoordinatesSquared + B.second * CCoordinatesSquared * D.first) -
            (D.first * C.second * BCoordinatesSquared + D.second * CCoordinatesSquared * B.first + C.first * B.second * DCoordinatesSquared)
    );

    det = firstDet - secondDet + thirdDet - fourthDet;

    if (det < 0)
        return OUTSIDE;

    if (det > 0)
        return INSIDE;

    return BOUNDARY;
}

int main() {
    pair<long long, long long> X, Y, Z, D;
    cin >> X.first >> X.second >> Y.first >> Y.second >> Z.first >> Z.second;
    cin >> D.first >> D.second;

    cout << "AC: " << getAnswerString(isInsideCircle(X, Y, Z, D)) << endl;
    cout << "BD: " << getAnswerString(isInsideCircle(Y, Z, D, X)) << endl;

    return 0;
}

/*

 SQUARE:
-1000000 -1000000
1000000 -1000000
1000000 1000000
-1000000 1000000

 RECTANGLE:
0 0
2 0
2 1
0 1

 TRAPEZOID:
0 0
4 0
3 2
1 2

*/