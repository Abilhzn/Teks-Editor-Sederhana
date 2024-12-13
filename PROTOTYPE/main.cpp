#include "header.h"
#include "source.cpp"
#include "undo.cpp"
#include <iostream>

using namespace std;

int main() {
    List textEditor;
    textEditor.first = nullptr;
    textEditor.last = nullptr;

    Stack undoStack = createStack();
    Stack redoStack = createStack();

    int choice;
    do {
        cout << "\nText Editor Menu:\n";
        cout << "1. Insert Character\n";
        cout << "2. Insert Character in certain positon\n";
        cout << "3. Delete Character\n";
        cout << "4. Delete Character in certain positon\n";
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
                adr P = createElmList(ch);

                push(undoStack, textEditor);
                insertLast(textEditor, P);
                printDepan_Belakang(textEditor);
                break;
            }
            case 2: {
                char ch, karakter;
                cout << "Enter character to insert: ";
                cin >> ch;

                cout << "Enter position after char: ";
                cin >> karakter;
                adr cari = search(textEditor, karakter);
                pushAfterChar(textEditor, karakter, ch);

                insertAfterCursor(textEditor, createElmList(ch), cari);
                printDepan_Belakang(textEditor);
                break;
            }
            case 3: {
                push(undoStack, textEditor);
                adr P;
                deleteLast(textEditor, P);
                printDepan_Belakang(textEditor);
                break;
            }
            case 4: {
                char ch;
                cout << "Enter char after char to delete: ";
                cin >> ch;

                adr P;
                push(undoStack, textEditor);
                adr cursor = search(textEditor, ch);
                deleteAfterCursor(textEditor, P, cursor);
                printDepan_Belakang(textEditor);
                break;
            }
            case 5: {
                printDepan_Belakang(textEditor);
                break;
            }
            case 6: {
                if (!isEmpty(undoStack)) {
                    push(redoStack, textEditor);
                    pop(undoStack, textEditor);
                    cout << "Undo successful.\n";
                } else {
                    cout << "Nothing to Undo!" << endl;
                }
                printDepan_Belakang(textEditor);
                break;
            }
            case 7: {
                if (!isEmpty(redoStack)) {
                    push(undoStack, textEditor);
                    pop(redoStack, textEditor);
                    cout << "Redo successful.\n";
                } else {
                    cout << "Nothing to Redo!" << endl;
                }
                printDepan_Belakang(textEditor);
                break;
            }
        }
    } while (choice != 8);

    return 0;
}
