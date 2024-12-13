#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "linkedlist.h"
#include <string>

using namespace std;

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

void createStack(Stack &S);
// void push(Stack &S, List data);
// void pop(Stack &S, List &data);
void push(Stack &S, Address P, Address prev, string perintah);
void pop(Stack &S, Address &P, Address &prev, string &perintah);
bool isEmpty(Stack S);
bool isFull(Stack S);
void displayStack(Stack S);

#endif // STACK_H_INCLUDED