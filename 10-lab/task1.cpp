#include <iostream>
#include <cstdlib>  // rand, srand
#include <ctime>    // time
#include <iomanip>
using namespace std;

// Печать массива
void printArray(const int* a, int n, const string& title) {
    cout << title << " (n=" << n << "): ";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << a[i];
    }
    cout << "\n";
}

/*
Удаление элемента по номеру pos (1..n).
Возвращает новый массив, а новый размер записывает в newN.
Старый массив НЕ удаляет — это делает main().
*/
int* deleteByNumber(const int* a, int n, int pos, int& newN) {
    // pos переводим в индекс (0..n-1)
    int idx = pos - 1;

    newN = n - 1;
    int* b = new int[newN];

    // Копируем всё, кроме удаляемого элемента
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i == idx) continue;      // пропускаем удаляемый
        b[j++] = a[i];
    }

    return b;
}

/*
Вставка K элементов, начиная с номера pos (1..n+1).
Пример: pos=1 — вставка в начало, pos=n+1 — вставка в конец.
Вставляемые значения берём из массива add[0..k-1].
Возвращает новый массив, новый размер в newN.
*/
int* insertKFromNumber(const int* a, int n, int pos, const int* add, int k, int& newN) {
    int idx = pos - 1; // куда вставлять (0..n)
    newN = n + k;

    int* b = new int[newN];

    // 1) Копируем часть до позиции вставки
    for (int i = 0; i < idx; i++) {
        b[i] = a[i];
    }

    // 2) Вставляем K новых элементов
    for (int i = 0; i < k; i++) {
        b[idx + i] = add[i];
    }

    // 3) Копируем оставшуюся часть исходного массива
    for (int i = idx; i < n; i++) {
        b[k + i] = a[i];
    }

    return b;
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    cout << "Введите размер массива n (n >= 1): ";
    while (!(cin >> n) || n < 1) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка. Введите целое n >= 1: ";
    }

    // 1) Создаём динамический массив
    int* a = new int[n];

    // 2) Заполняем (случайные числа)
    srand((unsigned)time(nullptr));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100; // 0..99
    }

    printArray(a, n, "Исходный массив");

    // 3) Удаление элемента с заданным номером
    int delPos;
    cout << "\nВведите номер элемента для удаления (1.." << n << "): ";
    while (!(cin >> delPos) || delPos < 1 || delPos > n) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка. Введите номер (1.." << n << "): ";
    }

    int nAfterDel = 0;
    int* afterDel = deleteByNumber(a, n, delPos, nAfterDel);

    // Старый массив больше не нужен
    delete[] a;
    a = nullptr;

    printArray(afterDel, nAfterDel, "После удаления");

    // 4) Вставка K элементов начиная с заданного номера
    int k;
    cout << "\nВведите K (сколько элементов добавить, K >= 1): ";
    while (!(cin >> k) || k < 1) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка. Введите целое K >= 1: ";
    }

    // Позиция вставки может быть от 1 до nAfterDel+1
    int insPos;
    cout << "Введите номер, начиная с которого добавить элементы (1.." << (nAfterDel + 1) << "): ";
    while (!(cin >> insPos) || insPos < 1 || insPos > nAfterDel + 1) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка. Введите номер (1.." << (nAfterDel + 1) << "): ";
    }

    // Массив добавляемых элементов (можно тоже случайно, а можно вводом)
    int* add = new int[k];
    cout << "\nВведите " << k << " добавляемых элементов:\n";
    for (int i = 0; i < k; i++) {
        cout << "add[" << (i + 1) << "] = ";
        while (!(cin >> add[i])) {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Ошибка. Введите целое число: ";
        }
    }

    int nFinal = 0;
    int* finalArr = insertKFromNumber(afterDel, nAfterDel, insPos, add, k, nFinal);

    // Освобождаем временные массивы
    delete[] afterDel;
    delete[] add;

    printArray(finalArr, nFinal, "После добавления K элементов");

    // Освобождаем итоговый массив
    delete[] finalArr;

    return 0;
}

