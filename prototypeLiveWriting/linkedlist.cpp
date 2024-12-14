#include "header.h"
#include <iostream>

using namespace std;

void createList(List &L){
    L.first = nullptr;
    L.last = nullptr;
}

Address createElement(Infotype data) {
    Address p = new ElmList;
    p->info = data;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

// insert functions section
// void insertFirst(List &L, Address P) {
//     if (L.first == nullptr) {
//         L.first = P;
//         L.last = P;
//     } else {
//         P->next = L.first;
//         L.first->prev = P;
//         L.first = P;
//     }
// }
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
void insertAfter(List &L, Address P, Address &befCursor){
    if (befCursor == L.last) {
        insertLast(L, P);
        befCursor = P;
    } else {
        P->next = befCursor->next;
        P->prev = befCursor;
        (befCursor->next)->prev = P;
        befCursor->next = P;
        befCursor = P;
    }
}

// delete functions section
// void deleteFirst(List &L, Address &P) {
//     if (L.first != nullptr) {
//         P = L.first;
//         if (L.first == L.last) {
//             L.first = nullptr;
//             L.last = nullptr;
//         } else {
//             L.first = L.first->next;
//             L.first->prev = nullptr;
//         }
//         P->next = nullptr;
//     }
// }
void deleteLast(List &L, Address &P) {
    if (L.first == L.last) {
        P = nullptr;
        return;
    }
    P = L.last;
    L.last = L.last->prev;
    L.last->next = nullptr;
    P->prev = nullptr;
}
void deleteAfter(List &L, Address &P, Address &befCursor){
    if (befCursor != nullptr && befCursor->info != '\0'){
        if (befCursor == L.last) {
            deleteLast(L, P);
            befCursor = L.last;
        } else {
            P = befCursor->next;
            befCursor->next = P->next;
            if (P->next != nullptr){
                P->next->prev = befCursor;
            }
            P->next = nullptr;
            P->prev = nullptr;
        }
    }
}

void search(List L, string data, Address &P, Address &Q){
    P = L.first;
    Q = P;
    bool thereIs = false;
    int i = 0;
    while (Q->next != nullptr && thereIs == false) {
        if (data[i] == Q->info){
            if (data[data.length()-1] == Q->info){
                thereIs = true;
            } else {
                Q = Q->next;
                i++;
            }
        } else {
            Q = Q->next;
            P = Q;
            i = 0;
        }
    }
}

void replace(List &L, List &tempList, Address &P, Address &Q){
    if (P->prev != nullptr && Q->next != nullptr){
        Address temp1, temp2;
        temp1 = tempList.first;
        temp2 = tempList.last;
        (P->prev)->next = temp1;
        (Q->next)->prev = temp2;
        P->prev = nullptr;
        Q->next = nullptr;
        tempList.first = P;
        tempList.last = Q;
        while (tempList.first != nullptr) {
            deleteLast(tempList , P);
        }
    }
}

void findAndReplace(List &L, string data, Address &P, Address &Q){
    search(L, data, P, Q);

    List L2;
    createList(L2);
    for (int i = 0; i < data.length(); i++){
        Address tempPtr = createElement(data[i]);
        insertLast(L2, tempPtr);
    }

    replace(L, L2, P, Q);
}

void shiftLeft(List L, Address &Cursor, Address &befCursor) {
    if (Cursor->prev != nullptr) {
        Cursor = Cursor->prev;
        befCursor = Cursor->prev;
    }
}

void shiftRight(List L, Address &Cursor, Address &befCursor) {
    if (Cursor->next != nullptr) {
        Cursor = Cursor->next;
        befCursor = Cursor->prev;
    }
}

void shiftUp(List L, Address &Cursor, Address &befCursor);

void shiftDown(List L, Address &Cursor, Address &befCursor);

void displayList(List L, Address Cursor) {
    Address P = L.first;
    if (P != nullptr){
        // if (Cursor->next == L.first) cout << P->info << '|';
        // if (Cursor->prev == L.last) cout << P->info << '|';
        while (P != nullptr) {
            cout << P->info;
            if (Cursor == P){
                cout << '|';
            }
            P = P->next;
        }
    }
    cout << endl;
}