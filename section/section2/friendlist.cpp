/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "map.h"
#include "vector.h"
#include "filelib.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"

using namespace std;

Map<string, Vector<string>> friendList(string filename){
    Map<string, Vector<string>> result;
    ifstream in(filename);

    if (! in.is_open()) {
        return result;
    }

    Vector<string> lines = readLines(in);

    for (string s : lines) {
        Vector<string> splitedLines = stringSplit(s, " ");
        string first = splitedLines[0];
        string last = splitedLines[1];

        result[first].add(last);
        result[last].add(first);
    }

    return result;
}


///* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("provided test case from handout"){
    Map<string, Vector<string>> soln;
    soln["Abby"] = {"Barney", "Clyde"};
    soln["Barney"] = {"Abby"};
    soln["Clyde"] = {"Abby"};
    EXPECT_EQUAL(soln, friendList("res/buddies.txt"));
}
