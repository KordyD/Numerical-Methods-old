#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

//std::ofstream fout("output.txt");

void gaussMethod(std::vector<std::vector<double>> a, std::vector<double> b) {
    std::cout << "Gauss Method\n";
    std::cout << std::setprecision(6);

    int size = int(a.size());
    std::vector<double> res(size);
    double ratio;

    //прямой ход метода Гаусса
    for (int i = 0; i < size - 1; i++) {
        if (a[i][i] == 0) {
            return;
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


    std::cout << "    [";
    for (int i = 0; i < size; i++) {
        std::cout << " " << std::setw(7) << res[i];
    }
    std::cout << " ]\n";
}

void seidelMethod(std::vector<std::vector<double>> a, std::vector<double> b, int iterNo) {
    std::cout << "Zeidel Method\n";
    std::cout << std::setprecision(6);

    size_t size = a.size();
    std::vector<double> x(size), res(size);
    std::fill(x.begin(), x.end(), 0);

    for (int iter = 0; iter < iterNo; iter++) {
        std::cout << std::setw(2) << iter + 1 << ": [";
        for (int i = 0; i < size; i++) {
            res[i] = b[i] / a[i][i];
            for (int j = 0; j < size; j++) {
                if (j == i)
                    continue;
                res[i] = res[i] - ((a[i][j] / a[i][i]) * x[j]);
                x[i] = res[i];
            }
            std::cout << " " << std::setw(7) << res[i];
        }
        std::cout << " ]\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    {
        std::cout << "#1\n";
        std::vector<std::vector<double>> a0 = {{9, 1, 1}, {1, 11, 1}, {1, 1, 13}};
        std::vector<double> b0 = {11, 13, 15};
        gaussMethod(a0, b0);
        seidelMethod(a0, b0, 4);
    }
    double eps = 10e-6;
    {
        std::cout << "\n#2\n";
        std::vector<std::vector<double>> a1 =
                {{1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps}};
        std::vector<double> b1 = {-1, -1, -1, -1, 1};
        gaussMethod(a1, b1);
        seidelMethod(a1, b1, 20);
    }
    {
        std::cout << "\n#3\n";
        std::vector<std::vector<double>> a2 =
                {{1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps}};
        std::vector<double> b2 = {-1, -1, -1, -1, -1, 1};
        gaussMethod(a2, b2);
        seidelMethod(a2, b2, 25);
    }
    {
        std::cout << "\n#4\n";
        std::vector<std::vector<double>> a3 =
                {{1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps, -1 - 7 * eps},
                 {    7 * eps,      7 * eps,      7 * eps,      7 * eps,      7 * eps,      7 * eps,  1 + 7 * eps}};
        std::vector<double> b3 = {-1, -1, -1, -1, -1, -1, 1};
        gaussMethod(a3, b3);
        seidelMethod(a3, b3, 30);
    }
    return 0;
}