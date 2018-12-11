#include "Hash.h"

/**
 * Creates a hash table
 */
Hash::Hash(unsigned int size) {

    this->size = size;
    hashTable = new int[size];

    for (int i = 0; i < size; ++i)
        hashTable[i] = EMPTY;

    xInTComparisons = 0;
    xNotInTComparisons = 0;
}

/**
 *
 * @param key
 * @return
 */
int Hash::getValue(int key) {
    return hashTable[key];
}

/**
 * Checks and returns whether the key is in the hash table or not.
 * Time complexity: O(1)
 *
 * @param key The key to look for
 * @param collisionMethod
 * @param comparisonMethod
 * @return Whether the key is in the hash table or not
 */
bool Hash::search(int key, CollisionMethod collisionMethod, ComparisonMethod comparisonMethod) {

    auto hashedKey = divisionHashFunction(key);

    if(DEBUG) cout << "Searching " << key << " in h[" << hashedKey << "]... ";

    // If the position is empty
    if(hashTable[hashedKey] == EMPTY) {
        if(DEBUG) cout << "EMPTY > ";
        return false;
    }

    // If the key has been found in the expected spot
    if(hashTable[hashedKey] == key) {
        if(DEBUG) cout << "FOUND > ";
        return true;
    }

    // If the key is not in the expected spot, we have to look for the key in
    // other spots
    if(DEBUG) cout << "COLLISION > Searching with ";
    switch (collisionMethod) {
        case linear:
            return linearProbingSearch(key, hashedKey, comparisonMethod);
        case quadratic:
            return quadraticProbingSearch(key, hashedKey, comparisonMethod);
        default:
            throw runtime_error("search: Collision method not defined");
    }
}

/**
 * Inserts the key into the hash table.
 * Time complexity: O(1)
 *
 * @param key The key to insert
 */
void Hash::insert(int key, CollisionMethod collisionMethod) {

    auto hashedKey = divisionHashFunction(key);

    if(DEBUG) cout << "Inserting " << key << " in h[";

    // If the position is empty, insert
    if(hashTable[hashedKey] == EMPTY) {
        if(DEBUG) cout << hashedKey << "] " << endl;
        hashTable[hashedKey] = key;
    }

    // If the position is not empty, look for a place to insert
    else {
        switch (collisionMethod) {
            case linear:
                linearProbingInsertion(key, hashedKey);
                break;
            case quadratic:
                quadraticProbingInsertion(key, hashedKey);
                break;
            default:
                throw runtime_error("insert: Collision method not defined");
        }
    }
}

/**
 * Division hash function
 * Time complexity: O(1)
 *
 * @param key The key to hash
 * @return
 */
unsigned int Hash::divisionHashFunction(int key) {
    return key % size;
}

/**
 * Using the linear probing algorithm for collision, returns whether the key is
 * in the hash table or not.
 * Time complexity: O(n)
 *
 * @param key The key (value) to look for
 * @param hashedKey The hashed key (index)
 * @param size The size of the hash table
 * @return Whether the key is in the hashed table or not
 */
bool Hash::linearProbingSearch(int key, unsigned int hashedKey, ComparisonMethod comparisonMethod) {

    if(DEBUG) cout << "linear probing h[";

    auto tempSize = size;
    unsigned int iterations = 0;

    // Visits the entire hash table and loops until reach the start position
    // again. E.g.:
    // size = 7
    // start = 2
    // output = 3,4,5,6,0,1
    for (int i = hashedKey; i < tempSize && iterations < 2; ++i) {

        if(comparisonMethod == xInT) xInTComparisons++;
        else if(comparisonMethod == xNotInT) xNotInTComparisons++;

        if(DEBUG) cout << i << ",";

        if(hashTable[i] == key) {
            if(DEBUG) cout << "]... FOUND > ";
            return true;
        }
        else if(hashTable[i] == EMPTY) {
            if(DEBUG) cout << "]... NOT FOUND > ";
            return false;
        }

        if(i == tempSize-1) {
            tempSize = hashedKey;
            i = -1; //i should be 0, but the i++ of the end of the loop adds 1
            iterations++;
        }
    }

    if(DEBUG) cout << "]... NOT FOUND > ";
    return false;
}

/**
 * Using the linear probing algorithm for collision, inserts the key in the hash
 * table.
 * Time complexity: O(n)
 *
 * @param key The key (value) to insert
 * @param hashedKey The hashed key (index)
 */
void Hash::linearProbingInsertion(int key, unsigned int hashedKey) {

    auto tempSize = size;
    unsigned int iterations = 0;

    for (int i = hashedKey; i < tempSize && iterations < 2; ++i) {

        if(hashTable[i] == EMPTY) {
            if(DEBUG) cout << i << "] " << endl;
            hashTable[i] = key;
            break;
        }

        if(i == tempSize-1) {
            tempSize = hashedKey;
            i = -1;
            iterations++;
        }
    }
}

/**
 * Using the quadratic probing algorithm for collision, returns whether the key
 * is in the hash table or not.
 * Time complexity: O(n)
 *
 * @param key The key (value) to look for
 * @param hashedKey The hashed key (index)
 * @param size The size of the hash table
 * @return Whether the key is in the hashed table or not
 */
bool Hash::quadraticProbingSearch(int key, unsigned int hashedKey, ComparisonMethod comparisonMethod) {

    if(DEBUG) cout << "quadratic probing h[";

    int rehashedKey;

    for (unsigned int i = 1; i < size; ++i) {

        if(comparisonMethod == xInT) xInTComparisons++;
        else if(comparisonMethod == xNotInT) xNotInTComparisons++;

        rehashedKey = quadraticHash(i, hashedKey);

        if(DEBUG) cout << rehashedKey << ",";

        if(hashTable[rehashedKey] == key) {
            if(DEBUG) cout << "]... FOUND > ";
            return true;
        }
        else if(hashTable[rehashedKey] == EMPTY) {
            if(DEBUG) cout << "]... NOT FOUND > ";
            return false;
        }
    }

    if(DEBUG) cout << "]... NOT FOUND > ";
    return false;
}

/**
 * Using the quadratic probing algorithm for collision, inserts the key in the
 * hash table.
 * Time complexity: O(n)
 *
 * @param key The key (value) to insert
 * @param hashedKey The hashed key (index)
 */
void Hash::quadraticProbingInsertion(int key, unsigned int hashedKey) {

    int rehashedKey;

    for (unsigned int i = 1; i < size; ++i) {

        rehashedKey = quadraticHash(i, hashedKey);

        if(hashTable[rehashedKey] == EMPTY) {
            if(DEBUG) cout << rehashedKey << "] " << endl;
            hashTable[rehashedKey] = key;
            break;
        }
    }
}

/**
 * Calculates and returns the hashed key using the quadratic formula.
 *
 * @param i The loop index
 * @param hashedKey The hashed key
 * @return The hashed key using the quadratic formula
 */
int Hash::quadraticHash(unsigned int i, unsigned int hashedKey) {

    // e = ((-1^(i-1))*(i+1)/2)^2
    int e = (int)pow(pow(-1, i-1)*((i+1)/2), 2);

    // p(i) = (h(k) +/- e) % size
    int he = (i%2)? hashedKey + e: hashedKey - e;

    return (int)mod(he, size);
}