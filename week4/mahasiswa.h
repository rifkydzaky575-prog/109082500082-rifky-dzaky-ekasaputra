#ifndef MAHASISWA_H_INCLUEDED
#define MAHASISWA_H_INCLUEDED

struct Mahasiswa {
    char nim[10];
    int nilai1, nilai2;
};

void inputMhs(Mahasiswa &m) ;
float rata2 (Mahasiswa m) ;
#endif // MAHASISWA_H_INCLUEDED