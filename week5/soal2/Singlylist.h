#ifndef SINGLYLIST_H
#define SINGLYLIST_H

#include <iostream>
using namespace std;

#define Nil NULL

typedef int infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
};

struct List {
    address First;
};

// soal 1
void createList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(List L);
void insertFirst(List &L, address P);

// soal 2
void deleteFirst(List &L);
void deleteLast(List &L);
void deleteAfter(List &L, address Prev);
int nbList(List L);
void deleteList(List &L);

#endif