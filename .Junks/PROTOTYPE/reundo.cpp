#include <iostream>
#include "header.h"

using namespace std;

Stack createStack() {
    Stack S;
    S.top = 0;
    return S;
}

bool isEmpty(Stack S) {
    return S.top == 0;
}

bool isFull(Stack S) {
    return S.top == MAXSIZE;
}

void push(Stack &S, List data) {
    if (!isFull(S)) {
        S.info[S.top] = data;
        S.top++;
    }
}

void pop(Stack &S, List &data) {
    if (!isEmpty(S)) {
        S.top--;
        data = S.info[S.top];
    }
}

void pushAfterChar(Stack &S, List &data, char target, char data){
    if (!isFull(S)) {
        // Mencari posisi data target di list terakhir stack
    if (S.top > 0) {
        adr cursor = search(data, target);
        if (cursor != nullptr) {
            adr newElement = createElmList(newData);
            insertAfterCursor(data, newElement, cursor);
        } else {
            cout << "Target character '" << target << "' tidak ditemukan di List." << endl;
        }
    }
    push(S, data);
    }
}
