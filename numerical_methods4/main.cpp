#include <iostream>
#include <cmath>
#include <vector>

double f1(double x, double y) {
    return cos(x) + y - 1.5;
}


double f2(double x, double y) {
    return 2 * x - sin(y - 0.5) - 1;
}

double diff_f1x(double x, double y) {
    return -sin(x);
}

double diff_f1y(double x, double y) {
    return 1;
}

double diff_f2x(double x, double y) {
    return 2;
}

double diff_f2y(double x, double y) {
    return -cos(y - 0.5);
}

std::vector<double> gaussMethod(std::vector<std::vector<double>> a, std::vector<double> b) {

    int size = int(a.size());
    std::vector<double> res(size);
    double ratio;

    //прямой ход метода Гаусса
    for (int i = 0; i < size - 1; i++) {
        if (a[i][i] == 0) {
            return std::vector<double>{};
        }
        for (int j = i + 1; j < size; j++) {
            ratio = a[j][i] / a[i][i];

            for (int k = 0; k < size; k++) {
                a[j][k] -= ratio * a[i][k];
            }
            b[j] -= ratio * b[i];
        }
    }

    //обратный ход метода Гаусса
    res[size - 1] = b[size - 1] / a[size - 1][size - 1];
    for (int i = size - 1; i >= 0; i--) {
        res[i] = b[i];
        for (int j = i + 1; j < size; j++) {
            res[i] -= a[i][j] * res[j];
        }
        res[i] /= a[i][i];
    }

    return res;
}


int main() {
    //cos(x) + y = 1.5
    // 2x - sin(y - 0.5) = 1
    double x0 = 0.6;
    double y0 = 0.7;
    double eps = 0.0001;
    std::vector<std::vector<double>> a0 = {{diff_f1x(x0, y0), diff_f1y(x0, y0)},
                                           {diff_f2x(x0, y0), diff_f2y(x0, y0)}};
    std::vector<double> b0 = {-f1(x0, y0), -f2(x0, y0)};
    double x1 = x0 + gaussMethod(a0, b0)[0];
    double y1 = y0 + gaussMethod(a0, b0)[1];
    double temp1;
    double temp2;
    while (std::abs(x1 - x0) >= eps) {
        temp1 = x1;
        temp2 = y1;
        a0 = {{diff_f1x(x0, y0), diff_f1y(x0, y0)},
              {diff_f2x(x0, y0), diff_f2y(x0, y0)}};
        b0 = {-f1(x0, y0), -f2(x0, y0)};
        x1 = temp1 + gaussMethod(a0, b0)[0];
        y1 = temp2 + gaussMethod(a0, b0)[1];
        x0 = temp1;
        y0 = temp2;
    }
    std::cout << x1 << " " << y1;
    return 0;
}
