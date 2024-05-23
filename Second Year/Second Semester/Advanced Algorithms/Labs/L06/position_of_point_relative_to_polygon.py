class Point:
    def __init__(self, _x, _y):
        self.x = _x
        self.y = _y

    def __str__(self):
        return f"({self.x}, {self.y})"

    def __repr__(self):
        return f"({self.x}, {self.y})"

class Solution:
    def __init__(self, _polygon):
        self.polygon = _polygon

    def point_on_segment(self, P: Point, Q: Point, R: Point):
        return (
            min(P.x, Q.x) <= R.x <= max(P.x, Q.x) and
            min(P.y, Q.y) <= R.y <= max(P.y, Q.y) and
            self.orientation(P, Q, R) == 0
        )

    def orientation(self, P: Point, Q: Point, R: Point):
        det = (Q.x * R.y - R.x * Q.y) - \
              (P.x * R.y - R.x * P.y) + \
              (P.x * Q.y - Q.x * P.y)

        if det < 0:
            return 1

        if det > 0:
            return -1

        return 0

    def point_in_polygon(self, point: Point):
        count = 0

        for i in range(len(self.polygon)):
            current = polygon[i]
            next = polygon[(i+1) % len(polygon)]

            if self.point_on_segment(current, next, point):
                return "BOUNDARY"

            if point.x <= max(current.x, next.x) and min(current.y, next.y) < point.y <= max(current.y, next.y):
                if current.y != next.y:
                    x = (point.y - current.y) * (next.x - current.x) / (next.y - current.y) + current.x

                if current.x == next.x or point.x <= x:
                    count += 1

        if count % 2:
            return "INSIDE"

        return "OUTSIDE"

n = int(input().strip())
polygon = []

for _ in range(n):
    x, y = [int(it) for it in input().strip().split()]
    polygon.append(Point(x, y))

s = Solution(polygon)
m = int(input().strip())
for _ in range(m):
    x, y = [int(it) for it in input().strip().split()]
    print(s.point_in_polygon(Point(x, y)))
