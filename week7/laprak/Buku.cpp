
#include "Buku.h"

void CreateList(List &L) {
    L.First = NULL;
    L.Last = NULL;
}

address alokasi(infotype x) {
    address P = new ElmList;
    P->info = x;
    P->next = NULL;
    P->prev = NULL;
    return P;
}

void dealokasi(address &P) {
    delete P;
    P = NULL;
}

void insertLast(List &L, address P) {
    if (L.First == NULL) {
        L.First = P;
        L.Last = P;
    } else {
        P->prev = L.Last;
        L.Last->next = P;
        L.Last = P;
    }
}

void printInfo(List L) {
    address P = L.Last;

    while (P != NULL) {
        cout << "Kode Buku : " << P->info.kodeBuku << endl;
        cout << "Judul : " << P->info.judul << endl;
        cout << "Tahun Terbit : " << P->info.thnTerbit << endl;
        cout << endl;

        P = P->prev;
    }
}

address findElm(List L, infotype x) {
    address P = L.First;

    while (P != NULL) {
        if (P->info.kodeBuku == x.kodeBuku) {
            return P;
        }
        P = P->next;
    }

    return NULL;
}

void deleteFirst(List &L, address &P) {
    P = L.First;

    if (P != NULL) {
        L.First = P->next;

        if (L.First != NULL)
            L.First->prev = NULL;
        else
            L.Last = NULL;

        P->next = NULL;
    }
}

void deleteLast(List &L, address &P) {
    P = L.Last;

    if (P != NULL) {
        L.Last = P->prev;

        if (L.Last != NULL)
            L.Last->next = NULL;
        else
            L.First = NULL;

        P->prev = NULL;
    }
}

void deleteAfter(address Prec, address &P) {
    if (Prec != NULL && Prec->next != NULL) {
        P = Prec->next;
        Prec->next = P->next;

        if (P->next != NULL)
            P->next->prev = Prec;

        P->next = NULL;
        P->prev = NULL;
    } else {
        P = NULL;
    }
}
