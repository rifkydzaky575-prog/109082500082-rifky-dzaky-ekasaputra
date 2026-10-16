#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float uts, uas, tugas;
    float nilaiAkhir;
};

float hitungNilaiAkhir(float uts, float uas, float tugas) {
    return 0.3 * uts + 0.4 * uas + 0.3 * tugas;
}

int main() {
    Mahasiswa data[10];
    int jumlah;

    cout << "Masukkan jumlah mahasiswa (max 10): ";
    cin >> jumlah;

    for (int i = 0; i < jumlah; i++) {
        cout << "\nData mahasiswa ke-" << i + 1 << endl;
        cout << "Nama  : ";
        cin >> data[i].nama;
        cout << "NIM   : ";
        cin >> data[i].nim;
        cout << "UTS   : ";
        cin >> data[i].uts;
        cout << "UAS   : ";
        cin >> data[i].uas;
        cout << "Tugas : ";
        cin >> data[i].tugas;

        data[i].nilaiAkhir = hitungNilaiAkhir(data[i].uts, data[i].uas, data[i].tugas);
    }

    cout << "\n--- Rekap Nilai Akhir ---" << endl;
    for (int i = 0; i < jumlah; i++) {
        cout << data[i].nama << " (" << data[i].nim << ") : " << data[i].nilaiAkhir << endl;
    }

    return 0;
}