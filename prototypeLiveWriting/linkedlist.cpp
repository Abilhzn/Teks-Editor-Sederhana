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
    if (P->info != '\0'){
        if (P == L.last) {
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

// void search(List L, string data, Address &P, Address &Q){
//     bool thereIs = false;
//     int i = 0;
//     int kalimatnya = 0;
//     while (Q->next != nullptr && thereIs == false) {
//         if (data[i] == Q->info){
//             if (data[data.length()-1] == Q->info && data.length() == kalimatnya){
//                 thereIs = true;
//             } else {
//                 Q = Q->next;
//                 i++;
//                 kalimatnya++;
//             }
//         } else {
//             Q = Q->next;
//             P = Q;
//             i = 0;
//             kalimatnya = 0;
//         }
//     }
// }

// void replace(List &L, List &tempList, Address &P, Address &Q){
//     if (P->prev != nullptr && Q->next != nullptr){
//         Address temp1, temp2;
//         temp1 = tempList.first;
//         temp2 = tempList.last;
//         (P->prev)->next = temp1;
//         (Q->next)->prev = temp2;
//         P->prev = nullptr;
//         Q->next = nullptr;
//         tempList.first = P;
//         tempList.last = Q;
//         while (tempList.first != nullptr) {
//             deleteLast(tempList , P);
//         }
//     }
// }

// void findAndReplace(List &L, string data, Address &P, Address &Q){
//     P = L.first;
//     Q = P;
//     search(L, data, P, Q);
//     string kalimat;
//     cin >> kalimat;
//     List L2;
//     createList(L2);
//     for (int i = 0; i < kalimat.length(); i++){
//         Address tempPtr = createElement(kalimat[i]);
//         insertLast(L2, tempPtr);
//     }
//     replace(L, L2, P, Q);
// }

void search(List L, string data, Address &P, Address &Q) {
    bool thereIs = false;
    int i = 0;

    P = L.first; 
    Q = P;       

    while (Q != nullptr && !thereIs) { 
        if (data[i] == Q->info) {
            i++;
            if (i == data.length()) { 
                thereIs = true;
            } else {
                Q = Q->next; 
            }
        } else {
            P = P->next; 
            Q = P;       
            i = 0;       
        }
    }

    if (!thereIs) {
        P = nullptr;
        Q = nullptr;
    }
}

void replace(List &L, List &tempList, Address &P, Address &Q) {
    Address temp1 = tempList.first;
    Address temp2 = tempList.last;

    if (P == L.first->next) {
        L.first = temp1;
    } else {
        P->prev->next = temp1;
    }
    if (Q == L.last) {
        L.last = temp2;
    } else {
        Q->next->prev = temp2;
    }

    temp1->prev = P->prev;
    temp2->next = Q->next;

    while (P != Q) {
        Address temp = P;
        P = P->next;
        delete temp;
    }
    delete Q;
}

void findAndReplace(List &L, string data, Address &P, Address &Q) {
    P = L.first;
    Q = P;
    search(L, data, P, Q);
    if (P == nullptr || Q == nullptr) {
        cout << "Takdeu laa kata macam tu" << endl;
        return;
    }

    cout << "Masukan kalimat pengganti : ";
    string replacement;
    cin >> replacement;
    List tempList;
    createList(tempList);
    for (int i = 0; i < replacement.length(); i++) {
        Address tempPtr = createElement(replacement[i]);
        insertLast(tempList, tempPtr);
    }
    replace(L, tempList, P, Q);
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

void shiftUp(List L, Address &Cursor, Address &befCursor){
    int currentColumn = 0; // Posisi kolom pada baris saat ini
    Address P = L.first;

    // Hitung posisi kolom dan baris saat ini
    while (P != nullptr && P != Cursor) {
        if (P->info == '\n' || P->info == '\0') {
            currentColumn = 0; // Reset kolom jika menemukan akhir baris
        } else {
            currentColumn++; // Hitung kolom
        }
        P = P->next;
    }
    if (P == nullptr) return; // Jika Cursor tidak ditemukan di list, keluar

    // Cari awal baris saat ini
    Address startOfCurrentLine = Cursor;
    while (startOfCurrentLine->prev != nullptr && startOfCurrentLine->prev->info != '\n' && startOfCurrentLine->prev->info != '\0') {
        startOfCurrentLine = startOfCurrentLine->prev;
    }

    // Jika sudah di baris pertama, tidak bisa pindah ke atas
    if (startOfCurrentLine->prev == nullptr) return;

    // Cari awal baris sebelumnya
    Address startOfPrevLine = startOfCurrentLine->prev;
    while (startOfPrevLine->prev != nullptr && startOfPrevLine->prev->info != '\n' && startOfPrevLine->prev->info != '\0') {
        startOfPrevLine = startOfPrevLine->prev;
    }

    // Cari elemen di kolom yang sesuai pada baris sebelumnya
    Address target = startOfPrevLine;
    int column = 0;
    while (target != nullptr && target->info != '\n' && target->info != '\0') {
        if (column == currentColumn) break; // Jika kolom ditemukan, berhenti
        column++;
        target = target->next;
    }

    // Jika tidak ada kolom yang sesuai, arahkan ke elemen terakhir di baris sebelumnya
    if (target == nullptr || target->info == '\n' || target->info == '\0') {
        target = startOfPrevLine;
        while (target->next != nullptr && target->next->info != '\n' && target->next->info != '\0') {
            target = target->next;
        }
    }

    // Update Cursor dan befCursor
    Cursor = target;
    befCursor = (Cursor != nullptr) ? Cursor->prev : nullptr;
}

void shiftDown(List L, Address &Cursor, Address &befCursor){
    if (Cursor == nullptr) return; // Jika Cursor kosong, tidak perlu melakukan apapun

    int currentColumn = 0; // Posisi kolom pada baris saat ini
    Address P = L.first;

    // Hitung posisi kolom saat ini
    while (P != nullptr && P != Cursor) {
        if (P->info == '\n' || P->info == '\0') {
            currentColumn = 0; // Reset kolom jika menemukan akhir baris
        } else {
            currentColumn++; // Hitung kolom
        }
        P = P->next;
    }

    if (P == nullptr) return; // Jika Cursor tidak ditemukan di list, keluar

    // Cari akhir baris saat ini
    Address endOfCurrentLine = Cursor;
    while (endOfCurrentLine != nullptr && endOfCurrentLine->info != '\n' && endOfCurrentLine->info != '\0') {
        endOfCurrentLine = endOfCurrentLine->next;
    }

    // Jika tidak ada baris berikutnya, keluar
    if (endOfCurrentLine == nullptr || endOfCurrentLine->next == nullptr) return;

    // Cari awal baris berikutnya
    Address startOfNextLine = endOfCurrentLine->next;

    // Cari elemen di kolom yang sesuai pada baris berikutnya
    Address target = startOfNextLine;
    int column = 0;
    while (target != nullptr && target->info != '\n' && target->info != '\0') {
        if (column == currentColumn) break; // Jika kolom ditemukan, berhenti
        column++;
        target = target->next;
    }

    // Jika tidak ada kolom yang sesuai, arahkan ke elemen terakhir di baris berikutnya
    if (target == nullptr || target->info == '\n' || target->info == '\0') {
        target = startOfNextLine;
        while (target->next != nullptr && target->next->info != '\n' && target->next->info != '\0') {
            target = target->next;
        }
    }

    // Update Cursor dan befCursor
    Cursor = target;
    befCursor = (Cursor != nullptr) ? Cursor->prev : nullptr;
}

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