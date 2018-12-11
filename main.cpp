#include <iostream>
#include <iomanip>
#include "Hash.h"

using namespace std;

int getKey();
int generateRandomNumber(int, int);

/**
 * Assignment 5: Hashing
 * Sergio Berlinches (100291288)
 * 08/04/18
 *
 * The goal of this assignment is to compare linear probing against quadratic
 * probing. In class we said that quadratic probing was better. We will see if
 * this is true by doing an experiment.
 *
 * Create a function getKey() that returns a random number x to simulate random
 * keys, where x is in the range 0 ≤ x and at least x < 2^20. In this assignment
 * (and you could implement it), we use 0 ≤ x < 2^30
 *
 * For the hash table T we will use an array of size n = 1999 integers. Use -1
 * to indicate that slot T[i] is empty. For the hash function h(x) use h(x) = x
 * mod 1999 which you can code as:
 * int h(int x) { return( x % 1999 ); } //1999 is a closest prime number to 2000
 *
 * Now write two functions:
 * search(x, T) to test if a given key 0 ≤ x < 2^30 is in the hash table T
 * insert(x, T) to insert a given key x into the hash table T
 * You will need two versions of each function, one that uses linear probing and
 * the other which uses quadratic probing, so four functions in total. (You can
 * pass the probing function as an argument or pass an argument to distinguish
 * linear probing from quadratic probing. If you do, document your code properly
 * and do not complicate your code unnecessarily)
 *
 * @return
 */
int main() {

    /*
     * Now perform the following experiment. Using getKey(), generate 1000
     * distinct keys and insert them into the hash table T. If the keys are
     * repeats, keep producing and inserting new keys until T has 1000 distinct
     * values and the hash table is half full. You can do this by first
     * searching T for the key and if it is not already there, insert it.
     *
     * First do this using linear probing, then do this using quadratic probing.
     * So you will need two hash tables, TL and TQ for linear probing and for
     * quadratic probing.
     */
    /*unsigned int tableSize = 1999; //1999
    unsigned int numberOfkeys = 1000; //1000
    auto TL = new Hash(tableSize);
    auto TQ = new Hash(tableSize);

    for (int i = 0; i < numberOfkeys; ++i) {
        int TLKey;
        do TLKey = getKey();
        while (TL->search(TLKey, linear, none));
        TL->insert(TLKey, linear);
    }

    for (int i = 0; i < numberOfkeys; ++i) {
        int TQKey;
        do TQKey = getKey();
        while (TQ->search(TQKey, quadratic, none));
        TQ->insert(TQKey, quadratic);
    }*/

    /*
     * Now, suppose we have a key x such that 0 ≤ x < 2^30 . We want to
     * determine the average number of comparisons to search for x in the hash
     * table T for the two cases:
     *
     * (i) when x is in T
     * (ii) when x is not in T
     *
     * And we want to do this for linear probing and quadratic probing. So there
     * will be four averages.
     *
     * To do this for case (i), you could go through each key in T, and search
     * in T for each key counting the number of comparisons made by the search
     * function, then taking the average.
     *
     * I leave it to you to figure out how to do this for case (ii).
     *
     * That is one experiment. If you repeat this 100 times, each time with 1000
     * different random keys, so that the load factor is α=0.5 each time, and if
     * you take the average over the 100 experiments, you should be close to the
     * theoretical values obtained from the formulae below.
     *
     * For linear probing, with a load factor α, the approximate average number
     * of comparisons that a search requires for a successful search is:
     * (1/2)*(1+(1/(1-α)))
     *
     * For linear probing, with a load factor α, the approximate average number
     * of comparisons that a search requires for an unsuccessful search is:
     * (1/2)*(1+(1/((1-α)^2)))
     *
     * For quadratic probing, with a load factor α, the approximate average
     * number of comparisons that a search requires for a successful search is:
     * 1-ln(1-α)-(α/2)
     *
     * For quadratic probing, with a load factor α, the approximate average
     * number of comparisons that a search requires for an unsuccessful search
     * is:
     * (1/1-α)-α-ln(1-α)
     */
    unsigned int numberOfTests = 100; // 100
    unsigned int tableSize = 1999; //1999
    unsigned int numberOfkeys = 1000; //1000
    unsigned int linearXInTComparisons = 0;
    unsigned int linearXNotInTComparisons = 0;
    unsigned int quadraticXInTComparisons = 0;
    unsigned int quadraticXNotInTComparisons = 0;
    float lf = 0.5; // load factor
    float linearProbingSuccessful = ((float)1/2)*(1+(1/(1-lf)));
    float linearProbingUnsuccessful = ((float)1/2)*(1+(1/(pow((1-lf),2))));
    float quadraticProbingSuccessful = 1-log(1-lf)-(lf/2);
    float quadraticProbingUnsuccessful = (1/1-lf)-lf-log(1-lf);

    for (int i = 0; i < numberOfTests; ++i) {

        auto TL = new Hash(tableSize);
        auto TQ = new Hash(tableSize);
        int keyInTL, keyNotInTL, keyInTQ, keyNotInTQ;

        for (int j = 0; j < numberOfkeys; ++j) {
            int TLKey;
            do TLKey = getKey();
            while (TL->search(TLKey, linear, none));
            TL->insert(TLKey, linear);
        }

        for (int j = 0; j < numberOfkeys; ++j) {
            int TQKey;
            do TQKey = getKey();
            while (TQ->search(TQKey, quadratic, none));
            TQ->insert(TQKey, quadratic);
        }

        // Gets a key that exists in the linear hash table.
        do keyInTL = TL->getValue(generateRandomNumber(0, tableSize - 1));
        while (keyInTL == EMPTY);

        // Generates a keys that doesn't exists in the linear hash
        do keyNotInTL = getKey();
        while (TL->search(keyNotInTL, linear, none));

        // Gets a key that exists in the quadratic hash table.
        do keyInTQ = TQ->getValue(generateRandomNumber(0, tableSize - 1));
        while (keyInTQ == EMPTY);

        // Generates a keys that doesn't exists in the quadratic hash table.
        do keyNotInTQ = getKey();
        while (TQ->search(keyNotInTQ, quadratic, none));

        // Linear probing: x is in T
        TL->search(keyInTL, linear, xInT);
        // Linear probing: x is not in T
        TL->search(keyNotInTL, linear, xNotInT);
        // Quadratic probing: x is in T
        TQ->search(keyInTQ, quadratic, xInT);
        // Quadratic probing: x is not in T
        TQ->search(keyNotInTQ, quadratic, xNotInT);


        linearXInTComparisons += TL->xInTComparisons;
        linearXNotInTComparisons += TL->xNotInTComparisons;
        quadraticXInTComparisons += TQ->xInTComparisons;
        quadraticXNotInTComparisons += TQ->xNotInTComparisons;
    }

    cout << "Average comparisons Linear probing:" << endl;
    cout << "When x is in T: "
         << (float)linearXInTComparisons/numberOfTests
         << " (Expected "
         << linearProbingSuccessful
         << ")" << endl;
    cout << "When x is not in T: "
         << (float)linearXNotInTComparisons/numberOfTests
         << " (Expected "
         << linearProbingUnsuccessful
         << ")" << endl;

    cout << endl;

    cout << "Average comparisons Quadratic probing:" << endl;
    cout << "When x is in T: "
         << (float)quadraticXInTComparisons/numberOfTests
         << " (Expected "
         << quadraticProbingSuccessful
         << ")" << endl;
    cout << "When x is not in T: "
         << (float)quadraticXNotInTComparisons/numberOfTests
         << " (Expected "
         << quadraticProbingUnsuccessful
         << ")" << endl;

    return 0;
}



/**
 * Generates and returns a random number between 0 and 2^30 (1073741824).
 * @return A random number between 0 and 2^30
 */
int getKey() {
    return generateRandomNumber(0, 1073741824);
}

/**
 * Generates and returns a random number in the interval of min and max.
 * Complexity: O(1)
 *
 * @param min The minimum number in the interval
 * @param max The maximum number in the interval
 * @return A random number in the interval of min and max
 */
int generateRandomNumber(int min, int max) {

    if(min > max)
        throw runtime_error("generateRandomNumber: The minimum number must be lower than the maximum number.");

    //Workaround for the seeding
    static bool firstTime = true;
    if (firstTime) {
        srand(time(NULL));
        firstTime = false;
    }

    return min + rand() % ((max + 1) - min);
}