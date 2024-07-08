#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

unordered_map<char, char> ENCODINGTABLE = {
    {'A', '0'}, {'E', '0'}, {'I', '0'}, {'O', '0'}, {'U', '0'}, {'H', '0'}, {'W', '0'}, {'Y', '0'},
    {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
    {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'}, {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
    {'D', '3'}, {'T', '3'},
    {'L', '4'},
    {'M', '5'}, {'N', '5'},
    {'R', '6'}
};

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

/* This function takes one argument `s` and returns a new string
 * where each character in `s` is replaced by its corresponding
 * digit based on the specified encoding table.
 */
string encoding(string s) {
    string result = charToString(toUpperCase(s).at(0));

    for(char c: toUpperCase(s)) {
        result += ENCODINGTABLE[c];
    }

    return result;
}

/* This function takes one argument `s` and returns a new string
 * where consecutive duplicate characters are merged into a single
 * character.
 */
string combine(string s) {
    for(int i = 0; i < s.length();) {
        if(s[i] == s[i + 1]){
            s.erase(i + 1, 1);
        } else {
            i++;
        }
    }

    string result = s;
    return result;
}

/* This function takes one argument `s` and returns a new string
 * where the second character in the string is removed.
 */
string replaceInitials(string s){
    string result = s.erase(1, 1);

    return result;
}

/* This function takes one argument `s` and returns a new string
 * where all '0' characters are removed.
 */
string cleanZero(string s){
    string result;

    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '0') {
            continue;
        } else {
            result += s[i];
        }
    }

    return result;
}

/* This function takes one argument `s` and returns a new string
 * where the string is either truncated to 4 characters if it is longer
 * than 4 characters, or padded with '0' characters if it is shorter than
 * 4 characters.
 */
string fillOrCut(string s){
    string result = s;

    if(result.length() > 4){
        result = result.substr(0, 4);
    } else if(s.length() < 4) {
        result.append(4 - s.length(), '0');
    } else {
        return result;
    }

    return result;
}

/* This function takes one argument `s` and returns the Soundex code
 * for that string. It applies a series of transformations including
 * removing non-letter characters, encoding letters, combining
 * duplicate encodings, replacing initials, cleaning zeros, and
 * filling or cutting the result to ensure it is 4 characters long.
 */
string soundex(string s) {
    string pureLetter = removeNonLetters(s);
    string encoded;

    if(pureLetter == "") {
        return "";
    } else {
        encoded = encoding(pureLetter);
    }

    string combinedEncoded = combine(encoded);
    string initialsEncoded = replaceInitials(combinedEncoded);
    string cleanedEncoded = cleanZero(initialsEncoded);
    string soundexCode = fillOrCut(cleanedEncoded);

    return soundexCode;
}


/* This function takes one argument `filepath` and performs a Soundex
 * search on the names found in the file at `filepath`. It prompts the user
 * to enter surnames and prints out the Soundex code and matching names
 * from the database. The function continues until the user enters an empty
 * string.
 */
void soundexSearch(string filepath) {
    ifstream in(filepath);
    Vector<string> databaseNames;

    if (in.is_open()) {
        databaseNames = readLines(in);
        // readEntire(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    string input = "None";
    string soundexCode;
    while(input != "") {
        input = getLine("\nEnter a surname (RETURN to quit): ");

        if(input == ""){
            continue;
        } else {
            soundexCode = soundex(input);
        }

        Vector<string> matchingName;
        for(string s: databaseNames){
            if(soundexCode == soundex(s)){
                matchingName.add(s);
            }
        }

        matchingName.sort();

        cout << "Soundex code is "
             << soundexCode << endl;

        cout << "Matches from database: "
             << matchingName << endl;
    }

    cout << "All done!" << endl;
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
    s = "Avril Lavigne";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "AvrilLavigne");
}

STUDENT_TEST("Test function of encoding"){
    string s = "kevin";
    string result = encoding(s);
    EXPECT_EQUAL(result, "K20105");
    s = "Stella";
    result = encoding(s);
    EXPECT_EQUAL(result, "S230440");
    s = "AvrilLavigne";
    result = encoding(s);
    EXPECT_EQUAL(result, "A016044010250");
    s = "hanrahan";
    result = encoding(s);
    EXPECT_EQUAL(result, "H00560005");
}

STUDENT_TEST("Test function of combine"){
    string s = "K20105";
    string result = combine(s);
    EXPECT_EQUAL(result, "K20105");
    s = "S230440";
    result = combine(s);
    EXPECT_EQUAL(result, "S23040");
    s = "A016044010250";
    result = combine(s);
    EXPECT_EQUAL(result, "A01604010250");
    s = "H00560005";
    result = combine(s);
    EXPECT_EQUAL(result, "H05605");
}

STUDENT_TEST("Test function of replaceInitials"){
    string s = "K20105";
    string result = replaceInitials(s);
    EXPECT_EQUAL(result, "K0105");
    s = "S23040";
    result = replaceInitials(s);
    EXPECT_EQUAL(result, "S3040");
    s = "A01604010250";
    result = replaceInitials(s);
    EXPECT_EQUAL(result, "A1604010250");
    s = "H05605";
    result = replaceInitials(s);
    EXPECT_EQUAL(result, "H5605");
}

STUDENT_TEST("Test function of cleanZero"){
    string s = "K0105";
    string result = cleanZero(s);
    EXPECT_EQUAL(result, "K15");
    s = "S3040";
    result = cleanZero(s);
    EXPECT_EQUAL(result, "S34");
    s = "A1604010250";
    result = cleanZero(s);
    EXPECT_EQUAL(result, "A164125");
    s = "H5605";
    result = cleanZero(s);
    EXPECT_EQUAL(result, "H565");
}

STUDENT_TEST("Test function of fillOrCut"){
    string s = "K15";
    string result = fillOrCut(s);
    EXPECT_EQUAL(result, "K150");
    s = "S34";
    result = fillOrCut(s);
    EXPECT_EQUAL(result, "S340");
    s = "A164125";
    result = fillOrCut(s);
    EXPECT_EQUAL(result, "A164");
    s = "H565";
    result = fillOrCut(s);
    EXPECT_EQUAL(result, "H565");
}
