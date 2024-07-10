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
#include "stack.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
using namespace std;

int checkBalance(string code) {
    Stack<char> sc;
    int i;

    for (i = 0; i < code.length(); i++) {
        char c = code[i];

        if (c == '(' || c == '{') {
            sc.push(c);
        } else if (c == ')' || c == '}') {
            if (sc.isEmpty()) {
                return i;
            } else if (sc.peek() == '(' && c != ')') {
                return i;
            } else if (sc.peek() == '{' && c != '}') {
                 return i;
            } else {
                sc.pop();
            }
        }
    }

    if (! sc.isEmpty()) {
        return i;
    } else {
        return -1;
    }
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("test cases from handout"){
    EXPECT_EQUAL(checkBalance("if (a(4) > 9) { foo(a(2)); }"), -1);
    EXPECT_EQUAL(checkBalance("for (i=0;i<a;(3};i++) { foo{); )"), 15);
    EXPECT_EQUAL(checkBalance("while (true) foo(); }{ ()"), 20);
    EXPECT_EQUAL(checkBalance("if (x) {"), 8);
}
