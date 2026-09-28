#include <iostream>
using namespace std;

int main() {
    int angka;
    
    cout << "Masukkan angka (0-100): ";
    cin >> angka;

    string satuan[] = {
        "nol", "satu", "dua", "tiga", "empat",
        "lima", "enam", "tujuh", "delapan", "sembilan",
        "sepuluh", "sebelas"
    };

    if (angka < 0 || angka > 100) {
        cout << "Angka harus dari 0 sampai 100" << endl;
    }
    else if (angka <= 11) {
        cout << satuan[angka] << endl;
    }
    else if (angka < 20) {
        cout << satuan[angka - 10] << " belas" << endl;
    }
    else if (angka < 100) {
        int puluhan = angka / 10;
        int satuanAngka = angka % 10;

        cout << satuan[puluhan] << " puluh";

        if (satuanAngka != 0) {
            cout << " " << satuan[satuanAngka];
        }

        cout << endl;
    }
    else {
        cout << "seratus" << endl;
    }

    return 0;
}