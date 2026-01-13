#include <iostream>
using namespace std;

/*
Структура для представления комплексного числа
re — действительная часть
im — мнимая часть
*/
struct Complex {
    double re;
    double im;
};

/*
Перегруженная функция вычитания целых чисел
*/
int subtract(int a, int b) {
    return a - b;
}

/*
Перегруженная функция вычитания комплексных чисел
(a.re + a.im*i) - (b.re + b.im*i)
*/
Complex subtract(Complex a, Complex b) {
    Complex result;
    result.re = a.re - b.re;
    result.im = a.im - b.im;
    return result;
}

int main() {
    // ===== Работа с целыми числами =====
    int x, y;
    cout << "Введите два целых числа:\n";
    cin >> x >> y;

    int intResult = subtract(x, y);
    cout << "Результат вычитания целых чисел: "
         << intResult << endl;

    // ===== Работа с комплексными числами =====
    Complex c1, c2;

    cout << "\nВведите первое комплексное число:\n";
    cout << "Действительная часть: ";
    cin >> c1.re;
    cout << "Мнимая часть: ";
    cin >> c1.im;

    cout << "\nВведите второе комплексное число:\n";
    cout << "Действительная часть: ";
    cin >> c2.re;
    cout << "Мнимая часть: ";
    cin >> c2.im;

    Complex complexResult = subtract(c1, c2);

    cout << "\nРезультат вычитания комплексных чисел: ";
    cout << complexResult.re;
    if (complexResult.im >= 0)
        cout << " + " << complexResult.im << "i\n";
    else
        cout << " - " << -complexResult.im << "i\n";

    return 0;
}

