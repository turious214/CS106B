#include "console.h"
#include <iostream>
#include "SimpleTest.h"
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to root n-1, testing for a
 * zero remainder from the division.
 */
long smarterSum(long n) {
    long total = 0;

    if(n <= 0 || n == 1){
        return total;
    }

    for (long divisor = 1; divisor <= sqrt(n); divisor++) {
        if (n % divisor == 0) {
            total += divisor;
            if (divisor != 1 && divisor != n / divisor) {
                total += n / divisor;
            }
        }
    }

    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function use Mersenne primes and Euclid. calculate Mersenne primes
 * and use it to calculate perfect number.
 */
long findNthPerfectEuclid(long n) {
    long power = 1;
    long perfectNum;
    int index = 0;

    while(index != n){
        long mersenne = pow(2, power) - 1;
        bool ifMersenneP = (1 == smarterSum(mersenne)) && (mersenne != 1);

        if(ifMersenneP){
            perfectNum = pow(2, power - 1) * mersenne;
            index++;
        }
        power++;
    }

    return perfectNum;
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

STUDENT_TEST("Confirm negitive number are non-perfect"){
    EXPECT(!isPerfect(-1));
    EXPECT(!isPerfect(-6));
}

STUDENT_TEST("Check smarterSum in small number"){
    EXPECT_EQUAL(smarterSum(1), divisorSum(1));
    EXPECT_EQUAL(smarterSum(4), divisorSum(4));
    EXPECT_EQUAL(smarterSum(36), divisorSum(36));
}

STUDENT_TEST("Check smarterSum in big number"){
    EXPECT_EQUAL(smarterSum(2500), divisorSum(2500));
    EXPECT_EQUAL(smarterSum(3600), divisorSum(3600));
}

STUDENT_TEST("Compare operation time of smartSum and divisorSum"){
    TIME_OPERATION(100000, findPerfects(31250));
    TIME_OPERATION(100000, findPerfects(62500));
    TIME_OPERATION(100000, findPerfects(125000));
    TIME_OPERATION(100000, findPerfects(250000));
    TIME_OPERATION(100000, findPerfectsSmarter(31250));
    TIME_OPERATION(100000, findPerfectsSmarter(62500));
    TIME_OPERATION(100000, findPerfectsSmarter(125000));
    TIME_OPERATION(100000, findPerfectsSmarter(250000));
}

STUDENT_TEST("Check findNthPerfectEuclid"){
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
}
