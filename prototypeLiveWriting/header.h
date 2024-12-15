#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <string>

using namespace std;

// data structure for linked-List
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

// data structure for Stack
const int MAXSIZE = 2024;
struct InfoStack {
    Address element;
    Address beforeElement;
    string komand;
};
struct Stack {
    InfoStack info[MAXSIZE];
    int top;
};

// function for Linked-List
void createList(List &L);
Address createElement(Infotype data);
//  inserting
void insertLast(List &L, Address P);
void insertAfter(List &L, Address P, Address &Cursor);
//  deleting
void deleteLast(List &L, Address &P);
void deleteAfter(List &L, Address &P, Address &Cursor);
//  find and replace
void search(List L, string data, Address &P, Address &Q);
void replace(List &L, List &tempList, Address &P, Address &Q);
void findAndReplace(List &L, string data, Address &P, Address &Q);
//  movecursor
void shiftLeft(List L, Address &Cursor, Address &befCursor);
void shiftRight(List L, Address &Cursor, Address &befCursor);
void shiftUp(List L, Address &Cursor, Address &befCursor);
void shiftDown(List L, Address &Cursor, Address &befCursor);
// display
void displayList(List L, Address Cursor);
void displayCursor(List L, Address cursor);

// function for Stack
void createStack(Stack &S);
bool isEmpty(Stack S);
bool isFull(Stack S);
// undo and redo
void push(Stack &S, Address P, Address prev, string perintah);
void pop(Stack &S, Address &P, Address &prev, string &perintah);
void emptyStack(Stack &S, Address &P, Address &prev, string &perintah);


#endif // HEADER_H_INCLUDED