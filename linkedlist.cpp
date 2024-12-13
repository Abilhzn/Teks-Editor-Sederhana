#include "linkedlist.h"
#include <iostream>

using namespace std;

Address createElement(Infotype data) {
    Address p = new ElmList;
    p->info = data;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void insertFirst(List &L, Address P) {
    if (L.first == nullptr) {
        L.first = P;
        L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}

void insertLast(List &L, Address P) {
    if (L.first == nullptr) {
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

void insertAfter(List &L, Address P, Address &Cursor){
    if (Cursor == L.last) {
        insertLast(L, P);
        Cursor = P;
    } else {
        P->next = Cursor->next;
        P->prev = Cursor;
        ((Cursor->next)->prev) = P;
        Cursor->next = P;
        Cursor = P;
    }
}

void deleteFirst(List &L, Address &P) {
    if (L.first != nullptr) {
        P = L.first;
        if (L.first == L.last) {
            L.first = nullptr;
            L.last = nullptr;
        } else {
            L.first = L.first->next;
            L.first->prev = nullptr;
        }
        P->next = nullptr;
    }
}

void deleteLast(List &L, Address &P) {
    if (L.last != nullptr) {
        P = L.last;
        if (L.first == L.last) {
            L.first = nullptr;
            L.last = nullptr;
        } else {
            L.last = L.last->prev;
            L.last->next = nullptr;
        }
        P->prev = nullptr;
    }
}

void deleteAfter(List &L, Address &P, Address &Cursor){
    if (Cursor == L.last || Cursor->next == L.last) {
        deleteLast(L, P);
    } else {
        P = Cursor->next;
        Cursor->next = P->next;
        P->next->prev = Cursor;
        P->next = nullptr;
        P->prev = nullptr;
    }
}

Address search(List L, Infotype data){
    Address P;
    P = L.first;
    while (P->next != nullptr && P->info != data) {
        P = P->next;
    }
    return P;
}

void shiftLeft(List L, Address &Cursor) {
    if (Cursor != nullptr) {
        Cursor = Cursor->prev;
    }
}

void shiftRight(List L, Address &Cursor) {
    if (Cursor != nullptr) {
        Cursor = Cursor->next;
    }
}

void displayList(List L) {
    Address P = L.first;
    cout << "Current Text  : ";
    while (P != nullptr) {
        cout << P->info;
        P = P->next;
    }
    cout << endl;
}

void displayCursor(List L, Address cursor) {
    Address P = L.first;
        cout << "Current Cursor: ";
    while (P != nullptr) {
        if (P == cursor) {
            cout << "^";
        } else {
            cout << " ";
        }
        P = P->next;
    }
    cout << endl;
}
