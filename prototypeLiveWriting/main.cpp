#include "header.h"
#include "linkedlist.cpp"
#include "stack.cpp"
#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int main() {
    // varibel
    Infotype data;
    List L;
    Stack undoStack, redoStack;
    Address cursor, befCursor;

    // creating stack for undo n redo
    createStack(undoStack);
    createStack(redoStack);

    // creating line
    createList(L);
    cursor = createElement('\0');
    befCursor = L.last;
    insertAfter(L, cursor, befCursor);
    befCursor = cursor;

    // main program
    do {
        system("cls"); // reset tampilan terminal
        cout << "Tekan 'Esc' untuk keluar dari program\n";
        if (cursor->next == nullptr){
            cout << "Posisi Cursor Antara : '" << cursor->info << "' '" << " " << "'" << endl;
        } else {
            cout << "Posisi Cursor Antara : '" << cursor->info << "' '" << (cursor->next)->info << "'"  << endl;
        }
        cout << "anda menekan : " << int(data) << endl;
        cout << "====================================================\n" << endl;
        
        displayList(L, cursor);
        data = getch();

        if (data == 8){ // backspace
            if (cursor != nullptr && cursor->info != '\0'){ // pengecekan klo ini bukan di huruf paling awal
                // reset stack di redo
                string komando; Address temp1, temp2;
                emptyStack(redoStack, temp1, temp2, komando);
                // delete karakter
                deleteAfter(L, cursor, befCursor);
                push(undoStack, cursor, befCursor, "delete");
                if (cursor == nullptr) {
                    befCursor = nullptr; // Jika list kosong, befCursor juga harus nullptr
                } else {
                    cursor = befCursor;
                    befCursor = (cursor != nullptr) ? cursor->prev : nullptr; // bentuk ternary operator ygy
                }
            }
        } else if (data == 13){ // enter atau newline
            // reset stack di redo
            string komando; Address temp1, temp2;
            emptyStack(redoStack, temp1, temp2, komando);
            // insert karakter
            befCursor = cursor;
            data = '\n';
            cursor = createElement(data);
            insertAfter(L, cursor, befCursor);
            push(undoStack, cursor, befCursor, "insert");
        } else if (data == -32) { // move cursor
            data = getch();
            if (data == 75){ // 75 == left arrow
                shiftLeft(L, cursor, befCursor);
            } else if (data == 77){ // 77 == right arrow
                shiftRight(L, cursor, befCursor);
            } else if (data == 72){ // 72 == up arrow
                shiftUp(L, cursor, befCursor);
            } else if (data == 80){ // 80 == down arrow
                shiftDown(L, cursor, befCursor);
            }
        // } else if (data == 18) { // find and replace

        } else if (data == 26){ // 26 == undo (ctrl+z)
            // do undo
            if (!isEmpty(undoStack)) {    
                string komando;
                // Ambil operasi terakhir dari undoStack
                pop(undoStack, cursor, befCursor, komando);
                if ( komando == "insert") {
                    deleteAfter(L, cursor, befCursor);
                    // Simpan operasi ke redoStack untuk memungkinkan redo
                    push(redoStack, cursor, befCursor, komando);
                    if (cursor == nullptr) {
                        befCursor = nullptr; // Jika list kosong, befCursor juga harus nullptr
                    } else {
                        cursor = befCursor;
                        befCursor = (cursor != nullptr) ? cursor->prev : nullptr; // bentuk ternary operator ygy
                    }
                } else if (komando == "delete") {
                    insertAfter(L, cursor, befCursor);
                    // Simpan operasi ke redoStack untuk memungkinkan redo
                    push(redoStack, cursor, befCursor, komando);
                    // befCursor = cursor;
                }
            } else {
                cout << "Nothing to undo!\n";
            }
        } else if (data == 25){ // 25 == redo (ctrl+y)
            // do redo
            if (!isEmpty(redoStack)) {
                string komando;
                // Ambil operasi terakhir dari undoStack
                pop(redoStack, cursor, befCursor, komando);
                if ( komando == "insert") {
                    insertAfter(L, cursor, befCursor);
                    // Simpan operasi ke redoStack untuk memungkinkan redo
                    push(undoStack, cursor, befCursor, komando);
                    // befCursor = cursor;
                } else if (komando == "delete") {
                    deleteAfter(L, cursor, befCursor);
                    // Simpan operasi ke redoStack untuk memungkinkan redo
                    push(undoStack, cursor, befCursor, komando);
                    if (cursor == nullptr) {
                        befCursor = nullptr; // Jika list kosong, befCursor juga harus nullptr
                    } else {
                        cursor = befCursor;
                        befCursor = (cursor != nullptr) ? cursor->prev : nullptr; // bentuk ternary operator ygy
                    }
                }
            } else {
                cout << "Nothing to redo!\n";
            }
        } else {
            // reset stack di redo
            string komando; Address temp1, temp2;
            emptyStack(redoStack, temp1, temp2, komando);
            // insert karakter
            befCursor = cursor;
            cursor = createElement(data);
            insertAfter(L, cursor, befCursor);
            push(undoStack, cursor, befCursor, "insert");
        }
    } while (data != 27);

    // tampilan akhir
    system("cls"); // reset tampilan terminal
    cout << "Tekan 'Esc' untuk keluar dari program\n";
    if (cursor->next == nullptr){
        cout << "Posisi Cursor Antara : '" << cursor->info << "' '" << " " << "'" << endl;
    } else {
        cout << "Posisi Cursor Antara : '" << cursor->info << "' '" << (cursor->next)->info << "'"  << endl;
    }
    cout << "====================================================\n" << endl;
    cursor = nullptr;
    displayList(L, cursor);
}