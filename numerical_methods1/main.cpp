#include <iostream>
#include <cmath>

double factorial(int num) {
    double res = 1;
    for (int i = 1; i <= num; ++i) {
        res *= i;
    }
    return res;
}

int main() {
    /*
     * z(x) = sqrt(cos(2,6 * x + 0,1)) / exp(1 + x)
     * 0,1 <= x <= 0,2
     * шаг = 0,01
     * e = 1e-6
     * f(u, v) = sqrt(u) / v; u = cos(2,6 * x + 0,1); v = exp(1 + x)
     * 0,81 <= u <= 0,94
     * 3 <= v <= 3,33
     * |∂f/∂u| <= 0,185; |∂f/∂v| <= 0,107
     * ε1 = 1e-6 / 0,185 * 3; ε2 = 1e-6 / 0,107 * 3; ε3 = 1e-6 / 3
     */
    double x = 0.1;
    double f;
    double f_apr;
    double v;
    double u;
    while (x <= 0.2) {
        u = 0;
        v = 0;
        f_apr = sqrt(cos(2.6 * x + 0.1)) / exp(1 + x);
        int n = 1;
        while (pow((2.6 * x + 0.1), (2 * n)) / (factorial(2 * n)) > 1e-6 / (0.185 * 3)) {
            n++;
        }
        int p = 1;
        while (pow((1 + x), (p)) / (factorial(p)) > 1e-6 / (0.107 * 3)) {
            p++;
        }
        for (int i = 0; i <= n; ++i) {
            u += pow(-1, i) * pow(2.6 * x + 0.1, 2 * i) / factorial(2 * i);
        }

        for (int i = 0; i <= p; ++i) {
            v += pow(1 + x, i) / factorial(i);
        }
        double w = 1;
        double wnew = 0.5 * (w + u / w);
        while (std::abs(wnew - w) / v > 1e-6 / 3) {
            w = wnew;
            wnew = 0.5 * (w + u / w);
        }
        f = wnew / v;

        std::cout << x << " | " << f << " | " << f_apr << " | " << f - f_apr << std::endl;
        x += 0.01;
        x = std::ceil(x * 100.0) / 100.0;
    }
}
