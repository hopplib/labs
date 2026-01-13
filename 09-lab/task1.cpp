#include <iostream>
#include <fstream>
#include <string>
#include <cctype>   // isspace
using namespace std;

/*
Создаёт файл F1 и записывает в него минимум 10 строк.
(Для лабораторной — проще всего сделать заполнение автоматически.)
*/
bool createF1(const string& f1) {
    ofstream out(f1);
    if (!out) {
        cerr << "Ошибка: не удалось открыть файл " << f1 << " для записи.\n";
        return false;
    }

    // 10 строк (можешь заменить своими)
    out << "Строка 1: Пример текста для файла F1\n";
    out << "Строка 2: Здесь может быть любая информация\n";
    out << "Строка 3: Важно чтобы строк было не меньше 10\n";
    out << "Строка 4: Эта строка должна попасть в F2\n";
    out << "Строка 5: И эта тоже\n";
    out << "Строка 6: Продолжаем запись\n";
    out << "Строка 7: Текстовые файлы удобны\n";
    out << "Строка 8: Работа со строками\n";
    out << "Строка 9: Последняя строка почти\n";
    out << "Строка 10: Последнее_слово\n";

    if (!out) {
        cerr << "Ошибка ввода/вывода при записи в " << f1 << ".\n";
        return false;
    }

    return true;
}

/*
Копирует из F1 в F2 строки, начиная с 4-й (включительно).
*/
bool copyFrom4thLine(const string& f1, const string& f2) {
    ifstream in(f1);
    if (!in) {
        cerr << "Ошибка: не удалось открыть файл " << f1 << " для чтения.\n";
        return false;
    }

    ofstream out(f2);
    if (!out) {
        cerr << "Ошибка: не удалось открыть файл " << f2 << " для записи.\n";
        return false;
    }

    string line;
    int lineNo = 0;

    while (getline(in, line)) {
        lineNo++;
        if (lineNo >= 4) {
            out << line << '\n';
            if (!out) {
                cerr << "Ошибка ввода/вывода при записи в " << f2 << ".\n";
                return false;
            }
        }
    }

    if (!in.eof()) {
        cerr << "Ошибка ввода/вывода при чтении " << f1 << ".\n";
        return false;
    }

    // Если строк меньше 4 — F2 будет пустой, но это уже по ситуации
    return true;
}

/*
Возвращает длину последнего слова в файле.
Слово — последовательность непробельных символов.
*/
int lastWordLengthInFile(const string& f2) {
    ifstream in(f2);
    if (!in) {
        cerr << "Ошибка: не удалось открыть файл " << f2 << " для чтения.\n";
        return -1;
    }

    string lastWord;   // будем запоминать последнее найденное слово
    string line;

    while (getline(in, line)) {
        int i = 0;
        while (i < (int)line.size()) {
            // пропускаем пробелы/табуляции
            while (i < (int)line.size() && isspace((unsigned char)line[i])) i++;

            // читаем слово
            int start = i;
            while (i < (int)line.size() && !isspace((unsigned char)line[i])) i++;

            if (start < i) {
                lastWord = line.substr(start, i - start);
            }
        }
    }

    if (!in.eof()) {
        cerr << "Ошибка ввода/вывода при чтении " << f2 << ".\n";
        return -1;
    }

    // Если F2 пустой или слов нет
    if (lastWord.empty()) return 0;

    return (int)lastWord.size();
}

int main() {
    const string F1 = "F1.txt";
    const string F2 = "F2.txt";

    // 1) Создать F1 (не менее 10 строк)
    if (!createF1(F1)) return 1;

    // 2.1) Скопировать из F1 в F2 строки, начиная с 4-й
    if (!copyFrom4thLine(F1, F2)) return 1;

    // 2.2) Подсчитать количество символов в последнем слове F2
    int len = lastWordLengthInFile(F2);
    if (len < 0) return 1;

    cout << "Готово.\n";
    cout << "Строки из " << F1 << " (начиная с 4) скопированы в " << F2 << ".\n";
    cout << "Количество символов в последнем слове " << F2 << ": " << len << "\n";

    return 0;
}

