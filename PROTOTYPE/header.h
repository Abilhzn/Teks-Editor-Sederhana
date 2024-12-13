#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

using namespace std;

typedef char infotype;
typedef struct elmList *adr;

struct elmList {
    infotype info;
    adr prev, next;
};

struct List {
    adr first, last;
};

// fungsi untuk List 'perkata'
void createList(List &L);
adr createElmList(infotype x);
void insertFirst(List &L, adr ptr);
void insertLast(List &L, adr ptr);
void insertAfterCursor(List &L, adr ptr, adr &cursor);
void deleteFirst(List &L, adr &ptr);
void deleteLast(List &L, adr &ptr);
void deleteAfterCursor(List &L, adr &cursor);
adr search(List L, infotype data);
void printDepan_Belakang(List L);
void printBelakang_Depan(List L);

// fungsi untuk Multi Linked-List 'perkalimat'

// fungsi untuk undo/redo
const int MAXSIZE = 100;
struct Stack {
    List info[MAXSIZE];
    int top;
};
Stack createStack();
void push(Stack &S, List data);
void pushAfterChar(Stack &S, List &data, char target, char data);
void pop(Stack &S, List &data);
bool isEmpty(Stack S);
bool isFull(Stack S);
void undo(Stack &S, Stack &redoStack, List &currentList);
void redo(Stack &S, Stack &redoStack, List &currentList);


#endif // HEADER_H_INCLUDED
