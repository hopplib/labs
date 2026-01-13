#include <iostream>
#include <cstdio>    // fgets
#include <cctype>    // isdigit
using namespace std;

const int MAXN = 256; // 255 символов + '\0'

/*
Функция печатает слово, если в нем ровно одна цифра
*/
void printIfOneDigit(const char* wordStart, int len) {
    int digitCount = 0;

    for (int i = 0; i < len; i++) {
        if (isdigit((unsigned char)wordStart[i])) {
            digitCount++;
        }
    }

    if (digitCount == 1) {
        for (int i = 0; i < len; i++) {
            cout << wordStart[i];
        }
        cout << endl;
    }
}

int main() {
    char s[MAXN];

    cout << "Введите текст (в конце должна быть точка):\n";

    // Ввод строки (безопасный аналог gets)
    fgets(s, MAXN, stdin);

    cout << "\nСлова, содержащие ровно одну цифру:\n";

    int i = 0;

    while (s[i] != '\0') {
        // Пропуск пробелов
        while (s[i] == ' ') i++;

        // Конец строки или точка
        if (s[i] == '\0' || s[i] == '.') break;

        // Начало слова
        int start = i;

        // Движемся до конца слова
        while (s[i] != '\0' && s[i] != ' ' && s[i] != '.') {
            i++;
        }

        int len = i - start;

        // Проверяем слово
        printIfOneDigit(&s[start], len);

        // Если точка — конец текста
        if (s[i] == '.') break;
    }

    return 0;
}

