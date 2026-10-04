
#include <iostream>
using namespace std;

// Menukar 3 variabel menggunakan pointer
void tukarPointer(int *a, int *b, int *c) {
    int temp = *a;
    *a = *b;
    *b = *c;
    *c = temp;
}

// Menukar 3 variabel menggunakan reference
void tukarReference(int &a, int &b, int &c) {
    int temp = a;
    a = b;
    b = c;
    c = temp;
}

int main() {
    int a, b, c;

    cout << "=== MENUKAR 3 VARIABEL ===" << endl;
    cout << "Masukkan nilai a: ";
    cin >> a;
    cout << "Masukkan nilai b: ";
    cin >> b;
    cout << "Masukkan nilai c: ";
    cin >> c;

    cout << "\nNilai sebelum ditukar:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    // Menggunakan pointer
    int x = a, y = b, z = c;
    tukarPointer(&x, &y, &z);

    cout << "\nHasil menggunakan Pointer:" << endl;
    cout << "a = " << x << endl;
    cout << "b = " << y << endl;
    cout << "c = " << z << endl;

    // Menggunakan reference
    tukarReference(a, b, c);

    cout << "\nHasil menggunakan Reference:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;

    return 0;
}