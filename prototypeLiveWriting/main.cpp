#include "header.h"
#include "linkedlist.cpp"
#include "stack.cpp"
#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int main() {
    // varibel
    const int MAXLINES = 1024;
    int line = 0;
    Infotype data;
    // List L[MAXLINES];
    // L[line].first = nullptr;
    // L[line].last = nullptr;
    // L[line].up = nullptr;
    // L[line].down = nullptr;
    List L;
    createList(L);
    Address befCursor = L.first;
    Address cursor = L.first;
    Stack undoStack;
    Stack redoStack;
    createStack(undoStack);
    createStack(redoStack);

    // main program
    do {
        system("cls"); // reset tampilan terminal
        cout << "Tekan 'Esc' untuk keluar dari program\n";
        // cout << "Posisi Cursor Antara : " << befCursor->info << " " << cursor->info << "\n\n" << endl;
        // cout << int(befCursor->info) << " cursor " << int(cursor->info) << endl;
        cout << int(data) << endl;
        cout << "====================================================\n" << endl;
        
        displayList(L, cursor);
        data = getch();

        if (data == 8){ // backspace
            deleteAfter(L, cursor, befCursor);
            push(undoStack, cursor, befCursor, "delete");
            cursor = befCursor;
            befCursor = befCursor->prev;
        } else if (data == 13){ // enter atau newline
            data = '\n';
            cursor = createElement(data);
            insertAfter(L, cursor, befCursor);
            push(undoStack, cursor, befCursor, "insert");
            befCursor = cursor;
        } else if (data == -32) {
            data = getch();
            if (data == 75){ // 75 == left arrow
                shiftLeft(L, cursor);
                befCursor = cursor->prev;
            } else if (data == 77){ // 77 == right arrow
                shiftRight(L, cursor);
                befCursor = cursor;
            } else if (data == 72){ // 72 == up arrow

            } else if (data == 80){ // 80 == down arrow

            }
        } else if (data == 26){ // 26 == undo (ctrl+z)
            // do undo
        } else if (data == 25){ // 25 == redo (ctrl+y)
            // do redo
        } else{
            cursor = createElement(data);
            insertAfter(L, cursor, befCursor);
            push(undoStack, cursor, befCursor, "insert");
            befCursor = cursor;
        }
    } while (data != 27);
}