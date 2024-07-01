#include <iostream>
#include "console.h"
#include "Question2.h"

using namespace std;

void huntTreasure(int& pocket, int& storage1, int& storage2, int& storage3);

int question2() {
    int yourPocket = 0;
    int goldStorage1 = 850;
    int goldStorage2 = 970;
    int goldStorage3 = 620;

    huntTreasure(yourPocket, goldStorage1, goldStorage2, goldStorage3);

    cout << "Your treasure: " << yourPocket << endl << endl;
    cout << "Gold Storage 1: " << goldStorage1 << endl
         << "Gold Storage 2: " << goldStorage2 << endl
         <<"Gold Storage 3: " << goldStorage3 << endl;

    return 0;
}

void huntTreasure(int& pocket, int& storage1, int& storage2, int& storage3){
    pocket += storage1;
    storage1 = 0;

    pocket += storage2;
    storage2 = 0;

    pocket += storage3;
    storage3 = 0;
}
