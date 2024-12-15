
#include <iostream>
#include "header.h"

using namespace std;

void createList(List &L){
    L.first = nullptr;
    L.last = nullptr;
}

adr createElmList(infotype data){
    adr ptr;
    ptr = new elmList;
    ptr->info = data;
    ptr->next = nullptr;
    ptr->prev = nullptr;
    return ptr;
}

void insertFirst(List &L, adr ptr){
    if (L.first == nullptr) {
        L.first = ptr;
        L.last = ptr;
    } else {
        ptr->next = L.first;
        L.first->prev = ptr;
        L.first = ptr;
    }
}

void insertLast(List &L, adr ptr){
    if (L.first == nullptr) {
        L.first = ptr;
        L.last = ptr;
    } else {
        ptr->prev = L.last;
        L.last->next = ptr;
        L.last = ptr;
    }
}

void insertAfterCursor(List &L, adr ptr, adr &cursor){
    if (cursor->next == L.last) {
        insertLast(L, ptr);
        cursor = ptr;
    } else {
        ptr->next = cursor->next;
        ptr->prev = cursor;
        ((cursor->next)->prev) = ptr;
        cursor->next = ptr;
        cursor = ptr;
    }
}

void deleteFirst(List &L, adr &ptr){
    if (L.first != nullptr) {
        ptr = L.first;
        if (L.first->next == nullptr) {  // Jika hanya ada satu elemen
            L.first = nullptr;
            L.last = nullptr;
        } else {  // Jika ada lebih dari satu elemen
            L.first = L.first->next;
            L.first->prev = nullptr;
        }
        // Hanya memutus elemen dari List tanpa menghapusnya
        ptr->next = nullptr;
        ptr->prev = nullptr;
    }
}

void deleteLast(List &L, adr &ptr){
    if (L.first != nullptr) {
        ptr = L.last;
        if (L.first == L.last) {  // Jika hanya ada satu elemen
            L.first = nullptr;
            L.last = nullptr;
        } else {  // Jika ada lebih dari satu elemen
            L.last = L.last->prev;
            L.last->next = nullptr;
        }
        // Hanya memutus elemen dari List tanpa menghapusnya
        ptr->next = nullptr;
        ptr->prev = nullptr;
    }
}

void  deleteAfterCursor(List &L, adr ptr, adr &cursor){
    if (cursor->next == L.last) {
        deleteLast(L, ptr);
    } else {
        ptr = cursor->next;
        cursor->next = ptr->next;
        ptr->next->prev = cursor;
        ptr->next = nullptr;
        ptr->prev = nullptr;
    }
}

adr search(List L, infotype data){
    adr ptr;
    ptr = L.first;
    while (ptr->next != nullptr && ptr->info != data) {
        ptr = ptr->next;
    }
    return ptr;
}

void printDepan_Belakang(List L){
    adr ptr = L.first;
    while (ptr != nullptr) {
        cout << ptr->info;
        // if (ptr->next != nullptr) cout << " <-> ";
        ptr = ptr->next;
    }
    cout << endl;
}

void printBelakang_Depan(List L){
    adr ptr = L.last;
    while (ptr != nullptr) {
        cout << ptr->info;
        // if (ptr->prev != nullptr) cout << " <-> ";
        ptr = ptr->prev;
    }
    cout << endl;
}

