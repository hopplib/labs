#include <iostream>
#include <iomanip>

int main() {
    using std::cin;
    using std::cout;
    using std::endl;

    // =========================
    // ЗАДАНИЕ 1 (вариант 4)
    // ((a+b)^3 - a^3) / (3ab^2 + b^3 + 3a^2b), a=1000, b=0.0001
    // Сравнение результатов для float и double
    // =========================

    // ----- float -----
    float af = 1000.0f;
    float bf = 0.0001f;

    // Числитель: (a+b)^3 - a^3
    float f_sum = af + bf;
    float f_sum3 = f_sum * f_sum * f_sum;
    float f_a3 = af * af * af;
    float f_num = f_sum3 - f_a3;

    // Знаменатель: 3ab^2 + b^3 + 3a^2b
    float f_b2 = bf * bf;
    float f_b3 = f_b2 * bf;
    float f_a2 = af * af;

    float f_den1 = 3.0f * af * f_b2;      // 3ab^2
    float f_den2 = f_b3;                  // b^3
    float f_den3 = 3.0f * f_a2 * bf;      // 3a^2b
    float f_den = f_den1 + f_den2 + f_den3;

    float f_res = f_num / f_den;

    // ----- double -----
    double ad = 1000.0;
    double bd = 0.0001;

    // Числитель: (a+b)^3 - a^3
    double d_sum = ad + bd;
    double d_sum3 = d_sum * d_sum * d_sum;
    double d_a3 = ad * ad * ad;
    double d_num = d_sum3 - d_a3;

    // Знаменатель: 3ab^2 + b^3 + 3a^2b
    double d_b2 = bd * bd;
    double d_b3 = d_b2 * bd;
    double d_a2 = ad * ad;

    double d_den1 = 3.0 * ad * d_b2;      // 3ab^2
    double d_den2 = d_b3;                 // b^3
    double d_den3 = 3.0 * d_a2 * bd;      // 3a^2b
    double d_den = d_den1 + d_den2 + d_den3;

    double d_res = d_num / d_den;

    cout << std::fixed << std::setprecision(15);
    cout << "Task 1:\n";
    cout << "float  result = " << f_res << endl;
    cout << "double result = " << d_res << endl;

    return 0;
}
