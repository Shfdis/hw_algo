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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <iterations> [wide|narrow]" << endl;
        return 1;
    }
    
    int iterations = atoi(argv[1]);
    string mode = argc > 2 ? argv[2] : "wide";
    
    Circle A(1.0, 1.0, 1.0);
    Circle B(1.5, 2.0, sqrt(5.0) / 2.0);
    Circle C(2.0, 1.5, sqrt(5.0) / 2.0);
    
    double fx, fy, sx, sy;
    
    if (mode == "wide") {
        fx = 0.0;
        fy = 0.0;
        sx = 1.0 + sqrt(5.0) / 2.0;
        sy = 1.0 + sqrt(5.0) / 2.0;
    } else {
        fx = 0.8;
        fy = 0.8;
        sx = 2.1;
        sy = 2.1;
    }
    
    Generator Xgen(fx, sx), Ygen(fy, sy);
    int in = 0;
    
    for (int it = 0; it < iterations; ++it) {
        double x = Xgen();
        double y = Ygen();
        if (A.in(x, y) && B.in(x, y) && C.in(x, y)) {
            in++;
        }
    }
    
    double area = (sx - fx) * (sy - fy) * 1.0 * in / iterations;
    cout << setprecision(15) << fixed << area << endl;
    
    return 0;
}

