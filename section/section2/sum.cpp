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
#include "grid.h"
#include "filelib.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
using namespace std;

/*
 * Sum Numbers (Code Write)
 * ----------------------------------
 * Write a program to read through a given file and sum
 * all of the numbers in the file. You can assume that numbers
 * will be composed entirely of numerical digits, optionally
 * preceded by a single negative sign.
 */

int sum(Vector<int> numberVector){
    int sumResult = 0;
    for(int num: numberVector){
        sumResult += num;
    }

    return sumResult;
}

Vector<int> extractNumber(Vector<string>& splitedline) {
    Vector<int> result;

    for (string elem: splitedline){
        string currentNum;

        for (int i = 0; i < elem.length(); i++) {
            bool addState = false;
            string currentString = to_string(elem.at(i));
            if(isdigit(elem.at(i))){
                currentNum.append(currentString);
                addState = true;
            } else if(currentString.compare("-") == 0){
                if (currentNum.length() == 0){
                    currentNum.append(currentString);
                }else {
                    if(currentNum.compare("-") != 0 || currentNum.length() > 1){
                        result.add(stringToInteger(currentNum));
                    }
                    currentNum = "-";
                }

                addState = true;
            }

            if(! addState or i == elem.length() - 1){
                if(currentNum.length() == 1 && currentNum.compare("-") == 0) {
                    currentNum = "";
                }else if(currentNum.length() > 0){
                    result.add(stringToInteger(currentNum));
                    currentNum = "";
                }else{
                    currentNum = "";
                }
            }
        }
    }

    return result;
}

bool checkFileReadable(ifstream& file){
    bool result = file.is_open();

    return result;
}

Vector<string> getWholeVectorText(ifstream& file) {
    Vector<string> wholeVectorText{readLines(file)};

    return wholeVectorText;
}

Vector<int> getNumberVector(Vector<string>& wholeVectorText){
    Vector<int> numberVector;
    for (int i = 0; i < wholeVectorText.size(); i++){
        string lineText = wholeVectorText.get(i);
        Vector<string> splitedline = stringSplit(lineText, " ");
        numberVector += extractNumber(splitedline);
    }

    return numberVector;
}

int sumNumbers(string filename){
    int sumResult;
    ifstream file(filename);

    bool readAble = checkFileReadable(file);
    if (! readAble) {
        return 0;
    }else {
        Vector<string> wholeVectorText = getWholeVectorText(file);
        Vector<int> numberVector = getNumberVector(wholeVectorText);
        sumResult = sum(numberVector);
    }

    return sumResult;
}


/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("given file in handout"){
    EXPECT_EQUAL(sumNumbers("res/numbers.txt"), 148);
}

PROVIDED_TEST("Nonexistent file should sum to zero") {
    EXPECT_EQUAL(sumNumbers("nonexistent_filename"), 0);
}

