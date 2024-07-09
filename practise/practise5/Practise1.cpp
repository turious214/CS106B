#include <iostream>
#include "SimpleTest.h"
#include "strlib.h"
#include "stack.h"

using namespace std;

bool ifdigit(string s) {
    for(char c: s) {
        if(! isdigit(c)){
            return false;
        }
    }

    return true;
}

Vector<string> extraToken(string s){
    Vector<string> result;
    result = stringSplit(s, " ");

    return result;
}

int calculation(Vector<string> vs){
    Stack<string> sk;
    int result;

    for(string s: vs){
        if(ifdigit(s)) {
            sk.push(s);
        } else {
            int rightHandOperand = stringToInteger(sk.pop());
            int leftHandOperand = stringToInteger(sk.pop());
            int calResult;

            switch(stringToChar(s)){
                case '+':
                    calResult = leftHandOperand + rightHandOperand;
                    break;
                case '-':
                    calResult = leftHandOperand - rightHandOperand;
                    break;
                case '*':
                    calResult = leftHandOperand * rightHandOperand;
                    break;
                case '/':
                    calResult = leftHandOperand / rightHandOperand;
                    break;
            }

            sk.push(integerToString(calResult));
        }
    }

    result = stringToInteger(sk.pop());
    return result;
}

bool processPostfix(string expr, int& result){
    Vector<string> exprToken = extraToken(expr);
    result = calculation(exprToken);

    return true;
}

PROVIDED_TEST("valid postfix expressions"){
    int result = 0;

    EXPECT_EQUAL(processPostfix("5 10 +", result), true);
    EXPECT_EQUAL(result, 15);

    EXPECT_EQUAL(processPostfix("3 8 *", result), true);
    EXPECT_EQUAL(result, 24);

    EXPECT_EQUAL(processPostfix("5 10 12 + -", result), true);
    EXPECT_EQUAL(result, -17);

    EXPECT_EQUAL(processPostfix("10 12 + 5 -", result), true);
    EXPECT_EQUAL(result, 17);

    EXPECT_EQUAL(processPostfix("5 2 * 3 + 4 -", result), true);
    EXPECT_EQUAL(result, 9);

    EXPECT_EQUAL(processPostfix("2 3 + 4 5 + *", result), true);
    EXPECT_EQUAL(result, 45);

    EXPECT_EQUAL(processPostfix("2 3 4 * + 5 +", result), true);
    EXPECT_EQUAL(result, 19);

    EXPECT_EQUAL(processPostfix("2 3 + 4 +", result), true);
    EXPECT_EQUAL(result, 9);

    EXPECT_EQUAL(processPostfix("2 3 4 + +", result), true);
    EXPECT_EQUAL(result, 9);

    EXPECT_EQUAL(processPostfix("2 3 1 * + 9 -", result), true);
    EXPECT_EQUAL(result, -4);

    EXPECT_EQUAL(processPostfix("10", result), true);
    EXPECT_EQUAL(result, 10);
}
