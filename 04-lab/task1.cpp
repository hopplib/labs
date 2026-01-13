#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

int main() {
    const int N = 15;
    const int MIN = -10;
    const int MAX = 10;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    vector<int> M;

    // 1) Формирование массива
    for (int i = 0; i < N; ++i) {
        M.push_back(MIN + std::rand() % (MAX - MIN + 1));
    }

    // 2) Печать исходного массива
    cout << "Исходный массив:\n";
    for (int x : M) cout << x << " ";
    cout << endl;

    // 3) Удаление элементов с индексами, кратными 3
    for (int i = M.size() - 1; i >= 0; --i) {
        if (i % 3 == 0) {
            M.erase(M.begin() + i);
        }
    }

    // 4) Добавление после каждого отрицательного элемента
    for (int i = 0; i < M.size(); ++i) {
        if (M[i] < 0 && i > 0) {
            int newElem = std::abs(M[i - 1] + 1);
            M.insert(M.begin() + i + 1, newElem);
            ++i; // пропускаем добавленный элемент
        }
    }

    // 5) Печать результирующего массива
    cout << "\nРезультирующий массив:\n";
    for (int x : M) cout << x << " ";
    cout << endl;

    return 0;
}

