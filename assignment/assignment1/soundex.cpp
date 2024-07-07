#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function takes one argument `s` and returns a boolean
 * (true/false) value indicating whether or not the string `s`
 * contains only alphabetic characters. A string is considered
 * to contain only alphabetic characters if every character in
 * the string is a letter (either uppercase or lowercase).
 */
// bool isStringInAlphabets(const string& s) {
//     for (char ch : s) {
//         if (!isalpha(ch)) {
//             return false;
//         }
//     }

//     return true;
// }

/* This function takes one argument `s` and returns a new string
 * where each character in `s` is replaced by its corresponding
 * digit based on the specified encoding table.
 */
string removeNonLetters(string s) {
    string result = "";

    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string encoding(string s) {
    Grid<char> encodingTable();
    encodingTable.set(0, 0, 'A'); encodingTable.set(0, 1, 'E'); encodingTable.set(0, 2, 'I');
    encodingTable.set(0, 3, 'O'); encodingTable.set(0, 4, 'U'); encodingTable.set(0, 5, 'H');
    encodingTable.set(0, 6, 'W'); encodingTable.set(0, 7, 'Y');

    encodingTable.set(1, 0, 'B'); encodingTable.set(1, 1, 'F'); encodingTable.set(1, 2, 'P');
    encodingTable.set(1, 3, 'V');

    encodingTable.set(2, 0, 'C'); encodingTable.set(2, 1, 'G'); encodingTable.set(2, 2, 'J');
    encodingTable.set(2, 3, 'K'); encodingTable.set(2, 4, 'Q'); encodingTable.set(2, 5, 'S');
    encodingTable.set(2, 6, 'X'); encodingTable.set(2, 7, 'Z');

    encodingTable.set(3, 0, 'D'); encodingTable.set(3, 1, 'T');

    encodingTable.set(4, 0, 'L');

    encodingTable.set(5, 0, 'M'); encodingTable.set(5, 1, 'N');

    encodingTable.set(6, 0, 'R');


}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string soundex(string s) {
    string pureLetter = removeNonLetters(s);
    string encoded = encoding(pureLetter);

    return "";
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    ifstream in(filepath);
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        databaseNames = readLines(in);
        // readEntire(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    string input;
    while(input != "") {
        input = getLine("Enter a surname (RETURN to quit): ");
        Vector<string> result = soundex(input);

        // if(isStringInAlphabets(input)){
        //     Vector<string> result = soundex(input);
        // } else {
        //     cout << "Invalid Input" << endl;
        // }
    }
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

STUDENT_TEST("Test edge cases of function removeNonLetters"){
    string s = "";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "");
    s = " ";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "");
    s = "123123";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "");
    s = "q$!#$b";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "qb");
    s = "$@%$a!@#$";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "a");
}

