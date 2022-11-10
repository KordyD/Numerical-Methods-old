#include <iostream>
#include <cmath>

double f(double x) {
    return 3 * x - cos(x) - 1;
}

double diff_f(double x) {
    return 3 + sin(x);
}

int main() {
    // 3x - cos(x) - 1 = 0
    // eps = 0.0001
    // x0 = 0.6
    double eps = 0.0001;
    double x0 = 0.6;
    double x1 = x0 - f(x0)/ diff_f(x0);
    double temp;
    double t = std::abs(x1 - x0);

    while (std::abs(x1 - x0) >= eps )
    {
        temp = x0;
        x0 = x1;
        x1 = temp - f(temp)/ diff_f(temp);
    }
    std::cout << x1;
    return 0;
}
