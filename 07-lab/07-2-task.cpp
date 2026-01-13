#include <iostream>
#include <cstdarg>   // для работы с переменным числом параметров
using namespace std;

/*
Функция sum
count — количество передаваемых чисел
...   — переменное число параметров типа int

Формула:
S = a1*a2 + a3*a4 + a5*a6 + ...
*/
int sum(int count, ...) {
    int result = 0;

    // Инициализация списка параметров
    va_list args;
    va_start(args, count);

    // Читаем параметры попарно
    for (int i = 0; i < count / 2; i++) {
        int a = va_arg(args, int);
        int b = va_arg(args, int);
        result += a * b;
    }

    // Завершение работы со списком параметров
    va_end(args);

    return result;
}

int main() {
    // Вызов функции sum с 8 параметрами
    int s1 = sum(8, 1, 2, 3, 4, 5, 6, 7, 8);
    cout << "S (8 параметров) = " << s1 << endl;

    // Вызов функции sum с 10 параметрами
    int s2 = sum(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    cout << "S (10 параметров) = " << s2 << endl;

    // Вызов функции sum с 12 параметрами
    int s3 = sum(12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    cout << "S (12 параметров) = " << s3 << endl;

    return 0;
}

