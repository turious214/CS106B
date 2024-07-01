#include <iostream>
#include "console.h"
#include "SimpleTest.h"
#include "Question1.h"

using namespace std;

void mySwap(int& a, int& b);

PROVIDED_TEST("basic test of swap() function with two integers")
{
    int a = 53;
    int b = 42;

    mySwap(a, b);

    EXPECT_EQUAL(a, 42);
    EXPECT_EQUAL(b, 53);
}

void mySwap(int& a, int& b){
    int c = a;
    a = b;
    b = c;
}

int question1(){
    runSimpleTests(ALL_TESTS);
    return 0;
}
