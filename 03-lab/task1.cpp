#include <iostream>
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

// Точное значение функции: y = x*atan(x) - ln(sqrt(1+x^2))
double exact_y(double x) {
    return x * std::atan(x) - std::log(std::sqrt(1.0 + x * x));
}

// Вычисление i-го члена ряда a_i по явной формуле:
// a_i = (-1)^(i+1) * x^(2i) / (2i(2i-1))
double term_formula(double x, int i) {
    double sign = (i % 2 == 1) ? 1.0 : -1.0; // i=1 -> +, i=2 -> -, ...
    double p = std::pow(x, 2.0 * i);         // x^(2i)
    double den = (2.0 * i) * (2.0 * i - 1.0);
    return sign * p / den;
}

int main() {
    // ===== ДАНО ПО ВАРИАНТУ =====
    const double a = 0.1;
    const double b = 0.8;
    const int k = 10;
    const double eps = 0.0001;

    int n;
    cout << "Enter n (for part a): ";
    cin >> n;

    const double h = (b - a) / k;

    cout << std::fixed << std::setprecision(10);
    cout << "\nВычисление функции\n";

    // ===== ВНЕШНИЙ ЦИКЛ ПО x =====
    for (int j = 0; j <= k; ++j) {
        double x = a + j * h;

        // ----- точное значение -----
        double y = exact_y(x);

        // ===== ВНУТРЕННИЙ ЦИКЛ №1: сумма для заданного n =====
        double SN = 0.0;
        if (n > 0) {
            for (int i = 1; i <= n; ++i) {
                double ai = term_formula(x, i);
                SN += ai;
            }
        }

        // ===== ВНУТРЕННИЙ ЦИКЛ №2: сумма для заданной точности eps =====
        double SE = 0.0;
        int i = 1;
        while (true) {
            double ai = term_formula(x, i);
            SE += ai;

            // критерий остановки по модулю очередного члена
            if (std::fabs(ai) < eps) break;

            ++i;

            // защита от зацикливания (на всякий случай)
            if (i > 100000) break;
        }

        // ===== ВЫВОД В ФОРМАТЕ МЕТОДИЧКИ =====
        cout << "X=" << x
             << " SN=" << SN
             << " SE=" << SE
             << " Y=" << y
             << endl;
    }

    return 0;
}

