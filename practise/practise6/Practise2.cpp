#include <iostream>
#include "console.h"
#include "map.h"
#include "vector.h"

using namespace std;

void practise2(Map<string, Vector<string>>& map) {
    for (string firstName: map) {
        for (string lastName: map.get(firstName)) {
            cout << firstName << " " << lastName << endl;
        }
    }
}
