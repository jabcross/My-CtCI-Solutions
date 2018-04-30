#include <assert.h>
#include <math.h>
#include <iostream>

#define EPS 1e-6

struct Scalar {
    double value;

    Scalar() {
        value = 0;
    }
    Scalar(int a) {
        value = (double) a;
    }
    Scalar(double a) {
        value = a;
    }

    template <typename T>
    Scalar operator=(T rhs) {
        value = (double) rhs;
        return (*this);
    }

    Scalar operator-() {
        return Scalar(-value);
    }
    Scalar operator+(Scalar rhs) {
        return Scalar(value + rhs.value);
    }
    Scalar operator-(Scalar rhs) {
        return Scalar(value - rhs.value);
    }
    Scalar operator*(Scalar rhs) {
        return Scalar(value * rhs.value);
    }
    Scalar operator/(Scalar rhs) {
        return Scalar(value / rhs.value);
    }

    bool operator==(const Scalar& rhs) const {
        return fabs(value - rhs.value) < EPS;
    }
    bool operator!=(Scalar rhs) {
        return !(*this == rhs);
    }
    bool operator<(Scalar rhs) {
        return (value - rhs.value) < EPS;
    }
    bool operator>(const Scalar& rhs) const {
        return (rhs.value - value) < EPS;
    }


    friend std::ostream& operator<<(std::ostream& lhs, Scalar rhs) {
        return lhs << rhs.value;
    }
};

struct Point {
    Scalar x;
    Scalar y;
    Point() {
        x = 0;
        y = 0;
    }
    Point(Scalar _x, Scalar _y) {
        x = _x;
        y = _y;
    }

    Point operator+(Point rhs) {
        return Point(x + rhs.x, y + rhs.y);
    }
    bool operator==(const Point& rhs) {
        return x == rhs.x and y == rhs.y;
    }
    bool operator!=(Point rhs) {
        return x != rhs.x or y != rhs.y;
    }

    Point operator*(Scalar rhs) {
        return Point(x * rhs, y * rhs);
    }

    Point operator/(Scalar rhs) {
        assert(rhs != 0);
        return Point(x / rhs, y / rhs);
    }
};

struct Line {
    Scalar a;
    Scalar b;
    Scalar c;
    Line() {
        a = 0;
        b = 1;
        c = 0;
    }
    // a * x + b * y + c == 0
    Line(Point p, Point q) {
        assert(p != q);
        if (p.x == q.x) {
            a = 1;
            b = 0;
            c = -p.x;
        } else {
            a = -(q.y - p.y) / (q.x - p.x);
            b = 1;
            c = -a * p.x - p.y;
        }
    }

    bool operator==(const Line& rhs) const {
        return a == rhs.a and b == rhs.b and c == rhs.c;
    }

    bool operator<(const Line& rhs) const {
        return a > rhs.a;
    }

    bool contains(Point p) {
        return (p.x * a + p.y * b + c == 0);
    }

    friend std::ostream& operator<<(std::ostream& lhs, Line rhs) {
        return lhs << "Line(" << rhs.a << "x + " << rhs.b << "y + " << rhs.c
                   << " == 0)";
    }
};

struct Rect {
    Point topleft;
    Point bottomright;
    Rect(Point a, Point b) {
        topleft     = a;
        bottomright = b;
    }
};

namespace std {

    template <>
    struct hash<Line> {
        std::size_t operator()(const Line& l) const {
            return *(size_t*) &(l.a.value) ^ *(size_t*) &(l.b.value) ^
                   *(size_t*) &(l.c.value);
        }
    };
}