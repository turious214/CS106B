#include <iostream>
#include "console.h"
#include "vector.h"
#include "question2.h"

using namespace std;

void printVector(Vector<int>& v);
string addSide(int num, int line, int i);

void question2() {
    Vector<int> v {43, 19, 12, 95, 83, 13};

    printVector(v);

    cout << endl << "Q2 finished" << endl << endl;
}

void printVector(Vector<int>& v){
    string line1;
    string line2;
    string line4;
    int num;
    string strNum;
    for (int i = 0; i < v.size(); i++){
        num = v.get(i);
        strNum = to_string(num);

        line1 += "+-" + addSide(strNum.length(), 1, i) + "-+";
        line2 += "| " + strNum + " |";
        line4 += addSide(strNum.length(), 4, i);
    }

    cout << line1 << endl << line2 << endl << line1 << endl << line4 << endl;
}

string addSide(int num, int line, int i){
    int digit = 0;
    string side;

    switch (line) {
        case 1:
            while (digit < num) {
                side += "-";
                digit++;
            }
            break;
        case 4:
            while (digit <= num * 2 + 1) {
                if (digit == num/2 + 1) {
                    side += to_string(i);
                } else {
                    side += " ";
                }

                digit++;
            }
            break;
    }

    return side;
}
