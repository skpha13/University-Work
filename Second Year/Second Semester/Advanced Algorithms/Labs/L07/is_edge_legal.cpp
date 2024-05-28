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

Answer isInsideCircle(pair<long long, long long> A, pair<long long, long long> B, pair<long long, long long> C, pair<long long, long long> D) {
    long long det = 0;
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
    pair<int, int> X, Y, Z, D;
    cin >> X.first >> X.second >> Y.first >> Y.second >> Z.first >> Z.second;
    cin >> D.first >> D.second;

    cout << "AC: " << getAnswerString(isInsideCircle(X, Y, Z, D)) << endl;
    cout << "BD: " << getAnswerString(isInsideCircle(Y, Z, D, X)) << endl;

    // TODO: duplicate points
    // TODO: collinear points -> A, B, C

    return 0;
}
