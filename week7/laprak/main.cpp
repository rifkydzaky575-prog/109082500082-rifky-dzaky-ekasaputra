
#include "Buku.h"

int main() {
    List L;
    infotype x;
    address P, cari, hapus;

    CreateList(L);

    // INSERT DATA
    for (int i = 1; i <= 4; i++) {
        cout << "Masukkan kode buku: ";
        cin >> x.kodeBuku;

        cout << "Masukkan judul buku: ";
        cin.ignore();
        getline(cin, x.judul);

        cout << "Masukkan tahun terbit: ";
        cin >> x.thnTerbit;

        if (findElm(L, x) != NULL) {
            cout << "Kode buku sudah terdaftar" << endl;
        } else {
            P = alokasi(x);
            insertLast(L, P);
        }

        cout << endl;
    }

    cout << "DATA LIST 1" << endl;
    printInfo(L);

    // SEARCHING
    cout << "Masukkan Kode Buku yang dicari: ";
    cin >> x.kodeBuku;

    cari = findElm(L, x);

    if (cari != NULL) {
        cout << "Kode Buku : " << cari->info.kodeBuku << endl;
        cout << "Judul : " << cari->info.judul << endl;
        cout << "Tahun Terbit : " << cari->info.thnTerbit << endl;
    } else {
        cout << "Data buku tidak ditemukan" << endl;
    }

    cout << endl;

    // DELETE DATA
    cout << "Masukkan Kode Buku yang akan dihapus: ";
    cin >> x.kodeBuku;

    cari = findElm(L, x);

    if (cari != NULL) {
        if (cari == L.First) {
            deleteFirst(L, hapus);
        } else if (cari == L.Last) {
            deleteLast(L, hapus);
        } else {
            deleteAfter(cari->prev, hapus);
        }

        dealokasi(hapus);
        cout << "Data dengan kode buku "
             << x.kodeBuku << " berhasil dihapus." << endl;
    } else {
        cout << "Data buku tidak ditemukan." << endl;
    }

    cout << endl;
    cout << "DATA LIST 1" << endl;
    printInfo(L);

    return 0;
}
