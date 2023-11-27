#include <iostream>
#include <vector>
#include <functional>

using namespace std;

typedef vector<double> Vector;


Vector f(const Vector& x) {
    Vector result(2);
    result[0] = x[0] * x[0] - 2 * x[0] * x[1] + 1;
    result[1] = x[0] * x[0] + x[1] * x[1] - 2;
    return result;
}

Vector f_N(const Vector& x) {
    int n = x.size();
    Vector result(n);
    double squaredNorm = 0.0;
    for (int i = 0; i < n; ++i) {
        squaredNorm += x[i] * x[i];
    }
    for (int i = 0; i < n; ++i) {
        result[i] = squaredNorm - n;
        result[i] -= x[i] * x[i] - x[i] * x[i] * x[i];
    }
    return result;
}

Vector relaxation(const function<Vector(const Vector&)>& system, Vector x, double omega, double epsilon) {
    int iterations = 0;
    int maxIterations = 100009;
    while (iterations < maxIterations) {
        iterations++;
        Vector x1 = x;
        for (int i = 0; i < x.size(); ++i) {
            x1[i] = x[i] - omega * system(x)[i];
        }
        if (sqrt(x1[0] * x1[0] + x1[1] * x1[1]) < epsilon) {
            return x1;
        }
        x = x1;
    }
    cout << iterations;
    return x;
}

int main() {
    double epsilon = 0.0001;
    double omega = 0.01;

    Vector x2D = { -1, -1 };
    Vector resultRelaxation2D = relaxation(f, x2D, omega, epsilon);
    cout << "Relaxation method (2D): \n";
    for (double val : resultRelaxation2D) {
        cout << val << " ";
    }
    cout << endl;

    int n = 10;
    Vector xN(n, 0.9);
    Vector resultRelaxationN = relaxation(f_N, xN, omega, epsilon);
    cout << "Relaxation method (n-dimensional): \n";
    for (double val : resultRelaxationN) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}