#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>   // strncpy
using namespace std;

const int NAME_LEN  = 40;
const int ADDR_LEN  = 80;
const int PHONE_LEN = 20;

// Структура "Человек" (подходит для прямой записи/чтения блоком)
struct Person {
    char surname[NAME_LEN];
    char name[NAME_LEN];
    char patronymic[NAME_LEN];
    char address[ADDR_LEN];
    char phone[PHONE_LEN];
    int  age;
};

// Безопасная запись строки в char-массив (обрезает и гарантирует '\0')
void setField(char* dest, int destSize, const string& src) {
    std::strncpy(dest, src.c_str(), destSize - 1);
    dest[destSize - 1] = '\0';
}

// Ввод одной записи с клавиатуры
Person inputPerson() {
    Person p{};
    string s;

    cout << "Фамилия: ";
    getline(cin, s);
    setField(p.surname, NAME_LEN, s);

    cout << "Имя: ";
    getline(cin, s);
    setField(p.name, NAME_LEN, s);

    cout << "Отчество: ";
    getline(cin, s);
    setField(p.patronymic, NAME_LEN, s);

    cout << "Домашний адрес: ";
    getline(cin, s);
    setField(p.address, ADDR_LEN, s);

    cout << "Номер телефона: ";
    getline(cin, s);
    setField(p.phone, PHONE_LEN, s);

    cout << "Возраст: ";
    while (!(cin >> p.age)) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка ввода. Введите возраст (целое число): ";
    }
    cin.ignore(100000, '\n'); // убрать '\n' после возраста

    return p;
}

// Печать одной записи (красиво)
void printPerson(const Person& p, int index) {
    cout << index << ") "
         << p.surname << " " << p.name << " " << p.patronymic
         << ", возраст: " << p.age << "\n"
         << "   Адрес: " << p.address << "\n"
         << "   Телефон: " << p.phone << "\n";
}

// Формирование двоичного файла (перезапись файла)
bool createFile(const string& filename, int n) {
    ofstream fout(filename, ios::binary | ios::trunc);
    if (!fout) {
        cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }

    cout << "\n=== Ввод " << n << " записей ===\n";
    for (int i = 0; i < n; i++) {
        cout << "\nЗапись #" << (i + 1) << "\n";
        Person p = inputPerson();
        fout.write(reinterpret_cast<const char*>(&p), sizeof(Person));
        if (!fout) {
            cerr << "Ошибка ввода/вывода при записи в файл.\n";
            return false;
        }
    }

    return true;
}

// Печать содержимого двоичного файла
bool printFile(const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return false;
    }

    cout << "\n=== Содержимое файла ===\n";

    Person p{};
    int idx = 1;
    bool any = false;

    while (fin.read(reinterpret_cast<char*>(&p), sizeof(Person))) {
        printPerson(p, idx++);
        any = true;
    }

    if (!fin.eof()) {
        cerr << "Ошибка ввода/вывода при чтении файла.\n";
        return false;
    }

    if (!any) {
        cout << "(Файл пуст)\n";
    }

    return true;
}

// Поиск: существует ли элемент с данным телефоном
bool existsPhone(const string& filename, const string& phone) {
    ifstream fin(filename, ios::binary);
    if (!fin) return false;

    Person p{};
    while (fin.read(reinterpret_cast<char*>(&p), sizeof(Person))) {
        if (phone == p.phone) return true;
    }
    return false;
}

// Удалить все элементы с заданным возрастом (через временный файл)
bool deleteByAge(const string& filename, int ageToDelete) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return false;
    }

    const string tmpName = filename + ".tmp";
    ofstream fout(tmpName, ios::binary | ios::trunc);
    if (!fout) {
        cerr << "Ошибка: не удалось создать временный файл.\n";
        return false;
    }

    Person p{};
    int deleted = 0;

    while (fin.read(reinterpret_cast<char*>(&p), sizeof(Person))) {
        if (p.age == ageToDelete) {
            deleted++;
            continue; // пропускаем (удаляем)
        }
        fout.write(reinterpret_cast<const char*>(&p), sizeof(Person));
        if (!fout) {
            cerr << "Ошибка ввода/вывода при записи во временный файл.\n";
            return false;
        }
    }

    if (!fin.eof()) {
        cerr << "Ошибка ввода/вывода при чтении исходного файла.\n";
        return false;
    }

    fin.close();
    fout.close();

    // Заменяем исходный файл временным
    if (std::remove(filename.c_str()) != 0) {
        cerr << "Ошибка: не удалось удалить исходный файл при замене.\n";
        return false;
    }
    if (std::rename(tmpName.c_str(), filename.c_str()) != 0) {
        cerr << "Ошибка: не удалось переименовать временный файл.\n";
        return false;
    }

    cout << "Удалено записей с возрастом " << ageToDelete << ": " << deleted << "\n";
    return true;
}

// Добавить элемент ПОСЛЕ элемента с заданным номером телефона
bool addAfterPhone(const string& filename, const string& phoneKey, const Person& toAdd) {
    // Сначала проверим, есть ли вообще такая запись (поиск через функцию)
    if (!existsPhone(filename, phoneKey)) {
        cerr << "Ошибка: запись с телефоном \"" << phoneKey << "\" не найдена. Добавление не выполнено.\n";
        return false;
    }

    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return false;
    }

    const string tmpName = filename + ".tmp";
    ofstream fout(tmpName, ios::binary | ios::trunc);
    if (!fout) {
        cerr << "Ошибка: не удалось создать временный файл.\n";
        return false;
    }

    Person p{};
    bool inserted = false;

    while (fin.read(reinterpret_cast<char*>(&p), sizeof(Person))) {
        // пишем текущую запись
        fout.write(reinterpret_cast<const char*>(&p), sizeof(Person));
        if (!fout) {
            cerr << "Ошибка ввода/вывода при записи во временный файл.\n";
            return false;
        }

        // если телефон совпал — сразу после него добавляем новую запись
        if (!inserted && phoneKey == p.phone) {
            fout.write(reinterpret_cast<const char*>(&toAdd), sizeof(Person));
            if (!fout) {
                cerr << "Ошибка ввода/вывода при добавлении записи.\n";
                return false;
            }
            inserted = true;
        }
    }

    if (!fin.eof()) {
        cerr << "Ошибка ввода/вывода при чтении исходного файла.\n";
        return false;
    }

    fin.close();
    fout.close();

    if (std::remove(filename.c_str()) != 0) {
        cerr << "Ошибка: не удалось удалить исходный файл при замене.\n";
        return false;
    }
    if (std::rename(tmpName.c_str(), filename.c_str()) != 0) {
        cerr << "Ошибка: не удалось переименовать временный файл.\n";
        return false;
    }

    cout << "Добавление выполнено: запись вставлена после телефона \"" << phoneKey << "\".\n";
    return true;
}

int main() {
    ios::sync_with_stdio(false);

    const string filename = "people.dat";

    int n;
    cout << "Сколько записей сформировать в файле? ";
    while (!(cin >> n) || n < 0) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка ввода. Введите целое число >= 0: ";
    }
    cin.ignore(100000, '\n'); // очистка '\n'

    if (!createFile(filename, n)) return 1;
    if (!printFile(filename)) return 1;

    // --- Удаление по возрасту ---
    int ageDel;
    cout << "\nВведите возраст, который нужно удалить: ";
    while (!(cin >> ageDel)) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка ввода. Введите возраст (целое число): ";
    }
    cin.ignore(100000, '\n');

    if (!deleteByAge(filename, ageDel)) return 1;
    if (!printFile(filename)) return 1;

    // --- Добавление после телефона ---
    string phoneKey;
    cout << "\nВведите номер телефона, после которого добавить элемент: ";
    getline(cin, phoneKey);

    cout << "\nВведите данные добавляемого человека:\n";
    Person newPerson = inputPerson();

    if (!addAfterPhone(filename, phoneKey, newPerson)) {
        // не завершаем аварийно — просто покажем текущее состояние
        cout << "\nТекущее содержимое файла (без изменений):\n";
        printFile(filename);
        return 0;
    }

    // Печать после добавления
    printFile(filename);

    return 0;
}

