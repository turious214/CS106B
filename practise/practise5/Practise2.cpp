#include <iostream>
#include "SimpleTest.h"
#include "strlib.h"
#include "stack.h"

using namespace std;

bool ifdigit2(string s);

bool ifValidExpression(Vector<string> vs) {
    int digitNum = 0;
    int symbolNum = 0;

    if (vs.size() == 0) {
        return false;
    } else if (vs.size() == 1) {
        if (! ifdigit2(vs.get(0))) {
            return false;
        }
    } else {
        if (! ifdigit2(vs.get(0)) || ! ifdigit2(vs.get(1))){
            return false;
        }
    }

    for (string s: vs) {
        if (ifdigit2(s)) {
            digitNum++;
        } else if (s.length() > 1) {
                return false;
        } else {
            char c = stringToChar(s);

            if (c == '+' || c == '-' || c == '*' || c == '/') {
                symbolNum++;
            } else{
                if (c == ' ') {
                    continue;
                } else {
                    return false;
                }
            }
        }
    }

    if (digitNum - symbolNum != 1 || digitNum == 0) {
        return false;
    } else {
        return true;
    }
}

bool ifdigit2(string s) {
    for(char c: s) {
        if(! isdigit(c)){
            return false;
        }
    }

    return true;
}

Vector<string> extraToken2(string s) {
    Vector<string> result;
    result = stringSplit(s, " ");

    return result;
}

bool calculation2(Vector<string> vs, int& result) {
    Stack<string> sk;

    for(string s: vs){
        if(ifdigit2(s)) {
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
                if (rightHandOperand == 0) {
                    return false;
                }

                calResult = leftHandOperand / rightHandOperand;
                break;
            }

            sk.push(integerToString(calResult));
        }
    }

    result = stringToInteger(sk.pop());
    return true;
}

bool processPostfix2(string expr, int& result){
    Vector<string> exprToken = extraToken2(expr);

    if (! ifValidExpression(exprToken)) {
        return false;
    }

    if (! calculation2(exprToken, result)){
        return false;
    } else {
        return true;
    }
}

PROVIDED_TEST("valid postfix expressions"){
    int result = 0;

    EXPECT_EQUAL(processPostfix2("5 10 +", result), true);
    EXPECT_EQUAL(result, 15);

    EXPECT_EQUAL(processPostfix2("3 8 *", result), true);
    EXPECT_EQUAL(result, 24);

    EXPECT_EQUAL(processPostfix2("5 10 12 + -", result), true);
    EXPECT_EQUAL(result, -17);

    EXPECT_EQUAL(processPostfix2("10 12 + 5 -", result), true);
    EXPECT_EQUAL(result, 17);

    EXPECT_EQUAL(processPostfix2("5 2 * 3 + 4 -", result), true);
    EXPECT_EQUAL(result, 9);

    EXPECT_EQUAL(processPostfix2("2 3 + 4 5 + *", result), true);
    EXPECT_EQUAL(result, 45);

    EXPECT_EQUAL(processPostfix2("2 3 4 * + 5 +", result), true);
    EXPECT_EQUAL(result, 19);

    EXPECT_EQUAL(processPostfix2("2 3 + 4 +", result), true);
    EXPECT_EQUAL(result, 9);

    EXPECT_EQUAL(processPostfix2("2 3 4 + +", result), true);
    EXPECT_EQUAL(result, 9);

    EXPECT_EQUAL(processPostfix2("2 3 1 * + 9 -", result), true);
    EXPECT_EQUAL(result, -4);

    EXPECT_EQUAL(processPostfix2("10", result), true);
    EXPECT_EQUAL(result, 10);
}

PROVIDED_TEST("invalid postfix expressions"){
    int result = 0;

    EXPECT_EQUAL(processPostfix2("5 10 + +", --result), false);
    EXPECT_EQUAL(result, -1);

    EXPECT_EQUAL(processPostfix2("3 8 * 0 / 5 +", --result), false);
    EXPECT_EQUAL(result, -2);

    EXPECT_EQUAL(processPostfix2("", --result), false);
    EXPECT_EQUAL(result, -3);

    EXPECT_EQUAL(processPostfix2("10 12 + 13", --result), false);
    EXPECT_EQUAL(result, -4);

    EXPECT_EQUAL(processPostfix2("10 12 13 +", --result), false);
    EXPECT_EQUAL(result, -5);

    EXPECT_EQUAL(processPostfix2("10 + 20", --result), false);
    EXPECT_EQUAL(result, -6);

    EXPECT_EQUAL(processPostfix2("- 10 8", --result), false);
    EXPECT_EQUAL(result, -7);

    EXPECT_EQUAL(processPostfix2("- 10", --result), false);
    EXPECT_EQUAL(result, -8);

    EXPECT_EQUAL(processPostfix2("-", --result), false);
    EXPECT_EQUAL(result, -9);

    EXPECT_EQUAL(processPostfix2("10 15 + sandwhich", --result), false);
    EXPECT_EQUAL(result, -10);
}
