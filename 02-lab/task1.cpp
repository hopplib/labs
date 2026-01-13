#include <iostream>

int main() {
    using std::cout;
    using std::endl;

    int sum = 0;

    for (int i = 21; i < 100; ++i) {
        if (i % 3 == 0) {
            sum += i;
        }
    }

    cout << "Sum of positive integers greater than 20, "
            "less than 100 and divisible by 3: "
         << sum << endl;

    return 0;
}

