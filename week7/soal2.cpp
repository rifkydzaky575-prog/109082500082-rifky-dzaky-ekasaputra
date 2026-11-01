#include <iostream>
#include <string>
using namespace std;

struct node {
    string data;
    node* next;
};
class stack {
    node* top = nullptr;
public:
void push(string s) {
    top = new node{s, top};
}
void pop(){
    if (top == nullptr) {
        cout << "riwayat kosong!\n.";
        return;
    }
    node* temp = top;
    cout << "dibatalkan: " << temp->data << endl;
    top = top->next;
    delete temp;
}
void tampil(){
if (top == nullptr) {
    cout << "riwayat kosong!\n";
    return;
}
for (node* p = top; p !=nullptr; p = p->next)
cout << p->data << endl;
}
~stack() {
    while (top != nullptr) {
        node* p = top;
        top = top->next;
        delete p;
    }
}
};
int main(){
    stack s;
    string data;

    for (int i = 1; i <= 5; i++){
        cout << "perubahan ke-" << i << ": ";
        getline(cin >> ws, data);
        s.push(data);
    }
    cout << "\nriwayat awal:\n";
    s.tampil();
    cout << "\nmembatalkan perubahan:\n";
    s.pop();
    s.pop();
    cout << "\nriwayat akhir:\n";
    s.tampil();
    cout << "\nuji stack kosong:\n";
    stack kosong;
    kosong.pop();

    return 0;
}