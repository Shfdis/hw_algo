#include <bits/stdc++.h>
using namespace std;
mt19937_64 rnd(179);
class Circle {
    double x, y, r;
    public:
        Circle(double x, double y, double r) {
            this->x = x;
            this->y = y;
            this->r = r;
        }
        bool in(double x, double y) const {
            return hypot(x - this->x, y - this->y) <= r;
        }
};
class Generator {
    double mn, mx;
    public: 
        Generator(double mn, double mx) {
            this->mn = mn;
            this->mx = mx;
        }
        double operator()() {
            return mn + (mx - mn) * (rnd() * 1.0 / mt19937_64::max());
        }
};
int main() {
    double fx = 1e9, fy = 1e9, sx = -1e9, sy = -1e9;
    const int iterations = 1000000;
    double X, Y, R;
    cin >> X >> Y >> R;
    fx = min(fx, X - R);
    fy = min(fy, Y - R);
    sx = max(sx, X + R);
    sy = max(sy, Y + R);
    Circle A(X, Y, R);
    cin >> X >> Y >> R;
    fx = min(fx, X - R);
    fy = min(fy, Y - R);
    sx = max(sx, X + R);
    sy = max(sy, Y + R);
    Circle B(X, Y, R);
    cin >> X >> Y >> R;
    fx = min(fx, X - R);
    fy = min(fy, Y - R);
    sx = max(sx, X + R);
    sy = max(sy, Y + R);
    Circle C(X, Y, R);
    Generator Xgen(fx, sx),
              Ygen(fy, sy);
    int in = 0;
    for (int it = 0; it < iterations; ++it) {
        double x = Xgen();
        double y = Ygen();
        if (A.in(x, y) && B.in(x, y) && C.in(x, y)) {
            in++;
        }
    }
    cout << setprecision(10) << fixed << (sx - fx) * (sy - fy) * 1.0 * in / iterations;
}