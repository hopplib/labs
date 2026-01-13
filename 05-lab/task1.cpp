#include <iostream>
#include <iomanip>
using namespace std;

// Максимальные размеры массива
const int MAXR = 100;
const int MAXC = 100;

/*
Функция вывода матрицы на экран
a  — двумерный массив
r  — количество строк
c  — количество столбцов
*/
void printMatrix(const int a[MAXR][MAXC], int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }
}

/*
Функция удаления одной строки из матрицы
a   — двумерный массив
r   — количество строк
c   — количество столбцов
idx — индекс строки для удаления (нумерация с 0)
*/
void deleteRow(int a[MAXR][MAXC], int r, int c, int idx) {
    // Сдвигаем все строки ниже удаляемой на одну позицию вверх
    for (int i = idx; i < r - 1; i++) {
        for (int j = 0; j < c; j++) {
            a[i][j] = a[i + 1][j];
        }
    }

    // Последнюю строку заполняем нулями
    for (int j = 0; j < c; j++) {
        a[r - 1][j] = 0;
    }
}

/*
Функция удаления диапазона строк с номерами от A до B
A и B задаются в человеческой нумерации (с 1)
*/
void deleteRowsRange(int a[MAXR][MAXC], int r, int c, int A, int B) {
    // Если A больше B — меняем их местами
    if (A > B) {
        swap(A, B);
    }

    // Количество строк для удаления
    int count = B - A + 1;

    // Перевод номера строки в индекс массива
    int startIndex = A - 1;

    // Удаляем строки по одной
    for (int i = 0; i < count; i++) {
        deleteRow(a, r, c, startIndex);
    }
}

int main() {
    int r, c;
    int a[MAXR][MAXC] = {0}; // инициализация массива нулями

    // Ввод количества строк
    do {
        cout << "Введите количество строк R (1.." << MAXR << "): ";
        cin >> r;
    } while (r < 1 || r > MAXR);

    // Ввод количества столбцов
    do {
        cout << "Введите количество столбцов C (1.." << MAXC << "): ";
        cin >> c;
    } while (c < 1 || c > MAXC);

    // Ввод элементов матрицы
    cout << "\nВведите элементы матрицы:\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << "a[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> a[i][j];
        }
    }

    int A, B;

    // Ввод номеров строк для удаления
    do {
        cout << "\nВведите A и B (номера строк для удаления, 1.." << r << "): ";
        cin >> A >> B;
    } while (A < 1 || B < 1 || A > r || B > r);

    // Удаление строк
    deleteRowsRange(a, r, c, A, B);

    // Вывод результата
    cout << "\nМатрица после удаления строк:\n";
    printMatrix(a, r, c);

    return 0;
}

