#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

using namespace std;

typedef char Infotype;
typedef struct ElmList *Address;

struct ElmList {
    Infotype info;
    Address next;
    Address prev;
};

struct List {
    Address first;
    Address last;
};

Address createElement(Infotype data);
void insertFirst(List &L, Address P);
void insertLast(List &L, Address P);
void insertAfter(List &L, Address P, Address &Cursor);
void deleteFirst(List &L, Address &P);
void deleteLast(List &L, Address &P);
void deleteAfter(List &L, Address &P, Address &Cursor);
Address search(List L, Infotype data);
void shiftLeft(List L, Address &Cursor);
void shiftRight(List L, Address &Cursor);
void displayList(List L);
void displayCursor(List L, Address cursor);

#endif // LINKEDLIST_H_INCLUDED