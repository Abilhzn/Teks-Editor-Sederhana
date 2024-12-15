#include <iostream>
#include "header.h"

using namespace std;

void createStack(Stack &S) {
    S.top = 0;
}

bool isEmpty(Stack S) {
    return S.top == 0;
}

bool isFull(Stack S) {
    return S.top == MAXSIZE;
}

void push(Stack &S, Address P, Address prev, string perintah) {
    if (!isFull(S)) {
        S.info[S.top].komand = perintah;
        S.info[S.top].element = P; // Simpan alamat elemen saat ini
        S.info[S.top].beforeElement = prev;  // Simpan alamat elemen sebelumnya
        S.top++;
    } else {
        cout << "Stack is full!" << std::endl;
    }
}

void pop(Stack &S, Address &P, Address &prev, string &perintah) {
    if (!isEmpty(S)) {
        S.top--;
        perintah = S.info[S.top].komand;
        P = S.info[S.top].element; // Ambil alamat elemen saat ini
        prev = S.info[S.top].beforeElement;  // Ambil alamat elemen sebelumnya
    } else {
        cout << "Stack is empty!" << std::endl;
    }
}

void emptyStack(Stack &S, Address &P, Address &prev, string &perintah){
    while (!isEmpty(S)){
        pop(S, P, prev, perintah);
    }
}