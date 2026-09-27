#include <iostream>
using namespace std;
 
int main() {
    float a, b;
 
    cout << "Masukkan bilangan pertama : ";
    cin >> a;
    cout << "Masukkan bilangan kedua   : ";
    cin >> b;
 
    cout << "\nHasil operasi:" << endl;
    cout << "Penjumlahan : " << (a + b) << endl;
    cout << "Pengurangan : " << (a - b) << endl;
    cout << "Perkalian   : " << (a * b) << endl;
    cout << "Pembagian   : " << (a / b) << endl;
 
    return 0;
}