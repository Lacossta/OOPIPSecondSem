#include <iostream>
#include "lab1.h"
//#include "lab2.h"
//#include "lab3.h"
#include "lab4.h"
#include "lab5.h"
//#include "lab6.h"
//#include "lab7.h"
//#include "lab8.h"
using namespace std;

int static CheckToInt(){
    int number;
    while (true) {
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You didn't enter a number! Retry " << endl;
        }
        else {
            break;
        }
    }
    return number;
}

int main() {
    int task;
    while(true){

        cout << endl;
        cout << "Enter a number of Lab work: ";
        task = CheckToInt();

        switch(task){
            case 1:
                lab1();
                break;
//            case 2:
//                lab2();
//                break;
//            case 3:
//                lab3();
//                break;
            case 4:
                lab4();
                break;
            case 5:
                lab5();
                break;
//            case 6:
//                lab6();
//                break;
//            case 7:
//                lab7();
//                break;
//            case 8:
//                lab8();
//                break;
            case -13:
                exit(0);
            default:
                cout << "There are not task with number " << task << endl;
                break;
        }
    }

    return 0;
}


