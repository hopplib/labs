#include <iostream>

int main() {
    using std::cin;
    using std::cout;
    using std::endl;

    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;

    int m1 = m, n1 = n;
    cout << "1) n++ * m = " << (n1++ * m1)
         << "   n=" << n1 << " m=" << m1 << endl;

    int m2 = m, n2 = n;
    cout << "2) n++ < m = " << (n2++ < m2)
         << "   n=" << n2 << " m=" << m2 << endl;

    int m3 = m;
    cout << "3) m-- > m = " << (m3-- > m3)
         << "   m=" << m3 << endl;

    return 0;
}

