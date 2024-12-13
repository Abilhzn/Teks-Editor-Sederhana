#include "linkedlist.h"
#include "linkedlist.cpp"
#include "stack.h"
#include "stack.cpp"
#include <iostream>
#include <stdlib.h>

using namespace std;

void clearScreen() {
    system("cls");
}

int main() {
    List L;
    L.first = nullptr;
    L.last = nullptr;

    Stack undoStack;
    Stack redoStack;

    createStack(undoStack);
    createStack(redoStack);

    int choice;
    do {
        clearScreen();
        displayList(L);

        cout << "\nText Editor Menu:\n";
        cout << "1. Insert Character\n";
        cout << "2. Insert After Cursor\n";
        cout << "3. Delete Character\n";
        cout << "4. Delete After Cursor\n";
        cout << "5. Display Text\n";
        cout << "6. Undo\n";
        cout << "7. Redo\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                char ch;
                cout << "Enter character to insert: ";
                cin >> ch;
                Address P = createElement(ch);

                insertLast(L, P); // Lakukan perubahan pada List

                // Simpan ke undoStack sebelum perubahan
                push(undoStack, P, P->prev, "insert");
                break;
            }
            case 2: {
                clearScreen();
                displayList(L);              

                char cursor;
                cout << "Enter position after char: ";
                cin >> cursor;
                Address cariCursor = search(L, cursor);  // Sesuaikan cursor dengan kebutuhan aplikasi
                
                if (cariCursor == nullptr) {
                    cout << "Upss..";
                } else {
                    int pilih;
                    do {
                        clearScreen();
                        displayList(L);
                        displayCursor(L, cariCursor);
                        cout << endl;
                        cout << "is that the right position?" << endl;
                        cout << "1. No, shift the cursor to the left pwease uwu\n";
                        cout << "2. No, shift the cursor to the right pwease uwu\n";
                        cout << "3. Absolutely yes\n";
                        cout << "4. Nuh uh, I'm about cancel this thing\n";
                        cout << "Enter choice: ";
                        cin >> pilih;

                        switch (pilih){
                            case 1: {
                                shiftLeft(L, cariCursor);
                                break;
                            }
                            case 2: {
                                shiftRight(L, cariCursor);
                                break;
                            }
                            case 3: {
                                char ch;
                                cout << "Enter character to insert: ";
                                cin >> ch;
                                Address P = createElement(ch);

                                insertAfter(L, P, cariCursor);  // Insert after cursor
                                displayList(L);

                                // Simpan ke undoStack sebelum perubahan
                                push(undoStack, P, P->prev, "insert after");
                                break;
                            }
                            case 4: {
                                break;
                            }
                        } 
                    } while (pilih != 3 && pilih != 4);
                    break;
                }
            }
            case 3: {
                if (L.first != nullptr) {
                    Address P;   

                    // Simpan ke undoStack sebelum penghapusan
                    push(undoStack, L.last, L.last->prev, "delete");

                    // Menghapus elemen terakhir
                    deleteLast(L, P);
                    displayList(L);  // Menampilkan list setelah penghapusan
                } else {
                    cout << "List is empty!" << endl;  // Menangani jika list kosong
                }
                break;
            }
            case 4: {
                clearScreen();
                displayList(L);
                char cursor;
                cout << "Enter position after char to delete: ";
                cin >> cursor;
                Address cariCursor = search(L, cursor);  // Menemukan posisi cursor
                
                if (cariCursor == nullptr) {
                    cout << "Upss..";
                } else {
                    int pilih;
                    do {
                        clearScreen();
                        displayList(L);
                        displayCursor(L, cariCursor);
                        cout << "Is that the right position to delete after?" << endl;
                        cout << "1. No, shift the cursor to the left pwease uwu\n";
                        cout << "2. No, shift the cursor to the right pwease uwu\n";
                        cout << "3. Absolutely yes, delete after this position\n";
                        cout << "4. Nuh uh, I'm about to cancel this thing\n";
                        cout << "Enter choice: ";
                        cin >> pilih;

                        switch (pilih){
                            case 1: {
                                shiftLeft(L, cariCursor);
                                break;
                            }
                            case 2: {
                                shiftRight(L, cariCursor);
                                break;
                            }
                            case 3: {
                                Address P;
                                
                                // Simpan ke undoStack sebelum penghapusan
                                push(undoStack, cariCursor->next, cariCursor, "delete after");

                                // Hapus elemen setelah posisi cursor
                                deleteAfter(L, P, cariCursor);
                                displayList(L);  // Menampilkan list setelah penghapusan
                                break;
                            }
                            case 4: {
                                break;
                            }
                        }
                    } while (pilih != 3 && pilih != 4);  // Ulangi jika belum memilih "Yes" atau "Cancel"
                    break;
                }
            }
            case 5: {
                displayList(L);
                break;
            }
            case 6: {
                if (!isEmpty(undoStack)) {
                    // Address P, prev;
                    // string komando;

                    // // Ambil operasi terakhir dari undoStack
                    // pop(undoStack, P, prev);
                    // // Simpan operasi ke redoStack untuk memungkinkan redo
                    // push(redoStack, P, prev, komando);

                    // // Lakukan undo berdasarkan kondisi elemen
                    // if (P == nullptr && prev == nullptr) {
                    //     // Undo penambahan elemen pertama
                    //     deleteFirst(L, P);  
                    // } else if (P == nullptr) {
                    //     // Undo penambahan elemen terakhir
                    //     deleteLast(L, P);
                    // } else if (prev == nullptr) {
                    //     // Undo penghapusan elemen pertama
                    //     insertFirst(L, P);
                    // } else {
                    //     // Undo penghapusan elemen setelah elemen tertentu
                    //     insertAfter(L, P, prev);
                    // }
                    // // Tampilkan daftar setelah undo
                    // displayList(L);


                    Address P, prev;
                    string komando;

                    // Ambil operasi terakhir dari undoStack
                    pop(undoStack, P, prev, komando);
                    // Simpan operasi ke redoStack untuk memungkinkan redo
                    push(redoStack, P, prev, komando);

                    if ( komando == "insert") {
                        deleteLast(L, P);
                    } else if (komando == "insert after") {
                        deleteAfter(L, P, prev);
                    } else if (komando == "delete") {
                        insertLast(L, P);
                    } else {
                        insertAfter(L, P, prev);
                    }
                    displayList(L);
                } else {
                    cout << "Nothing to undo!\n";
                }
                break;
            }
            case 7: {
                if (!isEmpty(redoStack)) {
                    // Address P, prev;

                    // // Ambil operasi terakhir dari redoStack
                    // pop(redoStack, P, prev);

                    // // Simpan state ke undoStack untuk memungkinkan undo kembali
                    // push(undoStack, P, prev);

                    // // Lakukan redo berdasarkan kondisi elemen
                    // if (P == nullptr && prev == nullptr) {
                    //     // Redo penghapusan elemen pertama
                    //     insertFirst(L, P);
                    // } else if (P != nullptr) {
                    //     // Redo penghapusan elemen terakhir
                    //     insertLast(L, P);
                    // } else if (prev == nullptr) {
                    //     // Redo penambahan elemen pertama
                    //     deleteFirst(L, P);
                    // } else {
                    //     // Redo penambahan elemen setelah elemen tertentu
                    //     deleteAfter(L, P, prev);
                    // }
                    
                    // // Tampilkan daftar setelah redo
                    // displayList(L);


                    Address P, prev;
                    string komando;

                    // Ambil operasi terakhir dari undoStack
                    pop(redoStack, P, prev, komando);
                    // Simpan operasi ke redoStack untuk memungkinkan redo
                    push(undoStack, P, prev, komando);

                    if ( komando == "insert") {
                        insertLast(L, P);
                    } else if (komando == "insert after") {
                        insertAfter(L, P, prev);
                    } else if (komando == "delete") {
                        deleteLast(L, P);
                    } else {
                        deleteAfter(L, P, prev);
                    }
                    displayList(L);
                } else {
                    cout << "Nothing to redo!\n";
                }
                break;
            }
        }
    } while (choice != 8);

    return 0;
}