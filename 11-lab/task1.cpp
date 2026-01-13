#include <iostream>
#include <fstream>
using namespace std;

/*
Узел однонаправленного списка.
key — ключевое поле (int)
next — указатель на следующий узел
*/
struct Node {
    int key;
    Node* next;
};

/* ===================== 1) Печать списка ===================== */
void printList(const Node* head) {
    if (head == nullptr) {
        cout << "Список пустой\n";
        return;
    }

    cout << "Список: ";
    const Node* p = head;
    while (p != nullptr) {
        cout << p->key << " ";
        p = p->next;
    }
    cout << "\n";
}

/* ===================== 2) Уничтожение списка ===================== */
void destroyList(Node*& head) {
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

/* ===================== Вспомогательное: длина списка ===================== */
int listSize(const Node* head) {
    int n = 0;
    while (head) {
        n++;
        head = head->next;
    }
    return n;
}

/* ===================== 3) Создание списка =====================
Создаёт список из n элементов (ввод с клавиатуры).
*/
Node* createList(int n) {
    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; i++) {
        int x;
        cout << "Введите ключ элемента #" << (i + 1) << ": ";
        while (!(cin >> x)) {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Ошибка. Введите целое число: ";
        }

        Node* node = new Node{ x, nullptr };

        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

/* ===================== 4) Удаление элемента по номеру =====================
Удаляет элемент с номером pos (1..n).
Возвращает true, если удаление выполнено.
*/
bool deleteByNumber(Node*& head, int pos) {
    if (head == nullptr) return false;

    // удаление первого элемента
    if (pos == 1) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }

    // ищем элемент перед удаляемым
    Node* prev = head;
    int i = 1;
    while (prev != nullptr && i < pos - 1) {
        prev = prev->next;
        i++;
    }

    // если позиции нет
    if (prev == nullptr || prev->next == nullptr) return false;

    Node* victim = prev->next;
    prev->next = victim->next;
    delete victim;
    return true;
}

/* ===================== 5) Вставка K элементов начиная с номера =====================
Вставляет K новых элементов, начиная с позиции pos (1..n+1).
pos=1  -> вставка в начало
pos=n+1-> вставка в конец
Значения ключей вводятся с клавиатуры.
*/
bool insertKFromNumber(Node*& head, int pos, int K) {
    if (K <= 0) return false;

    // Вставка в начало
    if (pos == 1) {
        // Чтобы сохранить порядок ввода, удобнее собирать "цепочку" и потом прицепить
        Node* firstNew = nullptr;
        Node* lastNew = nullptr;

        for (int i = 0; i < K; i++) {
            int x;
            cout << "Введите ключ добавляемого элемента #" << (i + 1) << ": ";
            while (!(cin >> x)) {
                cin.clear();
                cin.ignore(100000, '\n');
                cout << "Ошибка. Введите целое число: ";
            }

            Node* node = new Node{ x, nullptr };
            if (firstNew == nullptr) firstNew = lastNew = node;
            else { lastNew->next = node; lastNew = node; }
        }

        lastNew->next = head;
        head = firstNew;
        return true;
    }

    // Ищем узел перед позицией вставки
    Node* prev = head;
    int i = 1;
    while (prev != nullptr && i < pos - 1) {
        prev = prev->next;
        i++;
    }

    if (prev == nullptr) return false; // позиция вне списка

    Node* after = prev->next; // то, что было на позиции pos (может быть nullptr, если вставка в конец)

    Node* firstNew = nullptr;
    Node* lastNew = nullptr;

    for (int j = 0; j < K; j++) {
        int x;
        cout << "Введите ключ добавляемого элемента #" << (j + 1) << ": ";
        while (!(cin >> x)) {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Ошибка. Введите целое число: ";
        }

        Node* node = new Node{ x, nullptr };
        if (firstNew == nullptr) firstNew = lastNew = node;
        else { lastNew->next = node; lastNew = node; }
    }

    // Вставляем цепочку
    prev->next = firstNew;
    lastNew->next = after;

    return true;
}

/* ===================== 6) Запись списка в файл =====================
Формат: в первой строке количество элементов n,
потом n целых чисел (по одному в строке).
*/
bool saveToFile(const string& filename, const Node* head) {
    ofstream out(filename);
    if (!out) {
        cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }

    int n = listSize(head);
    out << n << "\n";

    const Node* p = head;
    while (p != nullptr) {
        out << p->key << "\n";
        p = p->next;
    }

    if (!out) {
        cerr << "Ошибка ввода/вывода при записи в файл.\n";
        return false;
    }
    return true;
}

/* ===================== 7) Восстановление списка из файла ===================== */
Node* loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return nullptr;
    }

    int n;
    if (!(in >> n) || n < 0) {
        cerr << "Ошибка: неверный формат файла.\n";
        return nullptr;
    }

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; i++) {
        int x;
        if (!(in >> x)) {
            cerr << "Ошибка: неверный формат файла (не хватает данных).\n";
            destroyList(head);
            return nullptr;
        }

        Node* node = new Node{ x, nullptr };
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
    }

    return head;
}

/* ===================== main: демонстрация по шагам из задания ===================== */
int main() {
    const string filename = "list.txt";

    // 1) Создать список
    int n;
    cout << "Введите количество элементов списка n: ";
    while (!(cin >> n) || n < 0) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка. Введите целое n >= 0: ";
    }

    Node* head = nullptr;
    if (n > 0) head = createList(n);

    // 2) Печать списка
    cout << "\nПосле создания:\n";
    printList(head);

    // 3) Удалить элемент с заданным номером
    if (head != nullptr) {
        int posDel;
        int sz = listSize(head);
        cout << "\nВведите номер элемента для удаления (1.." << sz << "): ";
        while (!(cin >> posDel) || posDel < 1 || posDel > sz) {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Ошибка. Введите номер (1.." << sz << "): ";
        }

        deleteByNumber(head, posDel);
        cout << "\nПосле удаления:\n";
        printList(head);
    } else {
        cout << "\nУдаление пропущено: список пустой.\n";
    }

    // 4) Добавить K элементов, начиная с заданного номера
    int K;
    cout << "\nВведите K (сколько элементов добавить): ";
    while (!(cin >> K) || K < 1) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка. Введите K >= 1: ";
    }

    int posIns;
    int sz2 = listSize(head);
    cout << "Введите номер, начиная с которого вставить (1.." << (sz2 + 1) << "): ";
    while (!(cin >> posIns) || posIns < 1 || posIns > sz2 + 1) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Ошибка. Введите номер (1.." << (sz2 + 1) << "): ";
    }

    insertKFromNumber(head, posIns, K);
    cout << "\nПосле добавления:\n";
    printList(head);

    // 5) Запись списка в файл
    if (!saveToFile(filename, head)) {
        destroyList(head);
        return 1;
    }
    cout << "\nСписок записан в файл: " << filename << "\n";

    // 6) Уничтожение списка
    destroyList(head);

    // 7) Печать (должно быть "Список пустой")
    cout << "\nПосле уничтожения:\n";
    printList(head);

    // 8) Восстановление списка из файла
    head = loadFromFile(filename);

    // 9) Печать восстановленного списка
    cout << "\nПосле восстановления из файла:\n";
    printList(head);

    // 10) Уничтожить список
    destroyList(head);

    return 0;
}

