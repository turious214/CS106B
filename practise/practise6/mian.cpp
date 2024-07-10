#include <iostream>
#include "SimpleTest.h"
#include "Practise2.h"
#include "Practise4.h"
#include "map.h"

using namespace std;

int main(){
    Map<string, Vector<string>> map;

    map["Julie"].add("Zelenski");
    map["Julie"].add("Stanford");
    map["Chris"].add("Gregg");
    map["Chris"].add("Piech");
    map["Nick"].add("Troccoli");
    map["Nick"].add("Parlante");

    practise2(map);

    Map<string, int> wordToFrequencyMap;
    getFrequencies("res/poem.txt", wordToFrequencyMap);

    return 0;
}
