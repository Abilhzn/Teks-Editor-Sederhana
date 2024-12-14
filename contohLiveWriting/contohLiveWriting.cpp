#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stack>

using namespace std;

int main(){
    char data;
    string kalimat;

    do {
        system("cls");
        cout << "Tekan 'Esc' untuk keluar dari program\n";
        cout << "Anda memasukan : " << int(data) << endl;
        cout << kalimat;
        data = getch();
        if (int(data) == 8){
            kalimat.pop_back();
        } else if (int(data) == 13) {
            kalimat += "\n";
        } else {
            kalimat += data;
        }
    } while (int(data) != 27);
    
}