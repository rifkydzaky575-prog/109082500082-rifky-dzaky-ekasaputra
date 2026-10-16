#include <iostream>
using namespace std;

void tampilkanArray2D(int arr[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void tukarArray2D(int arr1[3][3], int arr2[3][3], int baris, int kolom) {
    int temp = arr1[baris][kolom];
    arr1[baris][kolom] = arr2[baris][kolom];
    arr2[baris][kolom] = temp;
}

void tukarPointer(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main() {
    int arrA[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int arrB[3][3] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    cout << "Array A sebelum ditukar:" << endl;
    tampilkanArray2D(arrA);
    cout << "\nArray B sebelum ditukar:" << endl;
    tampilkanArray2D(arrB);

    int baris, kolom;
    cout << "\nMasukkan posisi baris yang ditukar (0-2): ";
    cin >> baris;
    cout << "Masukkan posisi kolom yang ditukar (0-2): ";
    cin >> kolom;

    tukarArray2D(arrA, arrB, baris, kolom);

    cout << "\nArray A setelah ditukar:" << endl;
    tampilkanArray2D(arrA);
    cout << "\nArray B setelah ditukar:" << endl;
    tampilkanArray2D(arrB);

    int x = 10, y = 20;
    int *px = &x;
    int *py = &y;

    cout << "\nSebelum ditukar (pointer): x=" << x << " y=" << y << endl;
    tukarPointer(px, py);
    cout << "Setelah ditukar (pointer): x=" << x << " y=" << y << endl;

    return 0;
}