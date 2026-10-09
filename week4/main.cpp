#include<iostream>
#include "mahasiswa.h"

using namespace std;

int main() {
    Mahasiswa mhs;
    inputMhs(mhs);
    cout << "rata-rata = " << rata2(mhs);
    return 0;
}
