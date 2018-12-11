#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <vector>
#include <cmath>
#include "utils.h"

using namespace std;

const bool DEBUG = false;
const int EMPTY = -1;
enum CollisionMethod {linear, quadratic};
enum ComparisonMethod {none, xInT, xNotInT};

/**
 * Hash class
 */
class Hash {
public:
    Hash(unsigned int);
    int getValue(int);
    bool search(int, CollisionMethod, ComparisonMethod);
    void insert(int, CollisionMethod);
    unsigned int xInTComparisons;
    unsigned int xNotInTComparisons;
private:
    int* hashTable;
    unsigned int size;
    unsigned int divisionHashFunction(int);
    bool linearProbingSearch(int, unsigned int, ComparisonMethod);
    void linearProbingInsertion(int, unsigned int);
    bool quadraticProbingSearch(int, unsigned int, ComparisonMethod);
    void quadraticProbingInsertion(int, unsigned int);
    int quadraticHash(unsigned int, unsigned int);
};

#endif
