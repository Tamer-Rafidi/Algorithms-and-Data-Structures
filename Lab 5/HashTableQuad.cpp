#include "HashTableQuad.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// time complexity = n
// space complexity = 1
bool HashTableQuad::Is_Prime(int n) {
    // If statement that returns false is n is 1 or 0 since they are not prime numbers
    if ((n == 1) || (n == 0)) { return false; }
    // For loop to check if n is a prime number. count starts at 2 since 0 and 1 are not prime numbers
    for (int count = 2; count < n; count++) {
        // If statement to check if n modulo count == 0, not a prime number if so
        if (n % count == 0) { return false; }
    }
    return true;
}

// time complexity = n^2
// space complexity = 1
HashTableQuad::HashTableQuad(int maxNum, double load) {

    // initializing variable and calculating load factor by maxNum / load
    size_table = maxNum / load;
    double double_tablesize = maxNum / load;
    // If statmeent to check if load factor has a decimal, increments size_table by 1 if so
    if (double_tablesize > size_table) { size_table++; }
    // While loop that increments size_table by 1 until it is not a prime number
    while (!Is_Prime(size_table)) { size_table++; }
    // Initializing a vector temp that holds the size of the table
    vector<int> temperory(size_table);
    // Assigns value of temporary to hashTable and sets key values
    hashTable = temperory;
    key_max = size_table * load;
    keys_num = 0;
    max_loadfactor = load;
}

// time complexity = n^2
// space complexity = 1
void HashTableQuad::insert(int n){

    // Initialize count variable
    int count = 1;
    //If statement that proceeds if n is not in the hash table
    if (!isIn(n)){
        // Initialize variable i and resolves collision using linear probing
        int i = n % size_table;
        // If statement that checks if location i in hashTable is null, sets ending to n and increments keys_num
        if (hashTable[i] == NULL) {
            hashTable[i] = n;
            keys_num++;
        }
        else {
            // While loop that iterates until NULL is met
            while (hashTable[i] != NULL) {
                // Sets i to quadratic probing
                i = (n % size_table + (count * count)) % size_table;
                // If statement that checks if the count is == to size_table, ends function if true
                if (count == size_table) { return; }
                // Increment count by 1 every iteration count != size_table 
                count++;
            }
            // Sets ending to n and incrememnts keys_num by 1
            hashTable[i] = n;
            keys_num++;
        }
        // If statement to check if key_max is less than keys_num, calls reshas function if so 
        if (key_max < keys_num) { rehash(); }
    }
}

// time complexity = n
// space complexity = 1
void HashTableQuad::rehash(){

    // Setting size_table to double its size
    size_table = size_table * 2;
    // Setting key_max to the product of size_table and max_loadfactor
    key_max = size_table * max_loadfactor;
    // Initialize hashTable_copy vector and sets it to hashTable
    std::vector<int> hashTable_copy = hashTable;
    // While loop that iterates until size_table is a prime number. Increments size_table by 1 every loop
    while (!Is_Prime(size_table)) { size_table++; }
    keys_num = 0;
    // Clears table the resizes it depending on size_table 
    hashTable.resize(0);
    hashTable.resize(size_table);
    // For loop that iterates through the size of original hashTable
    for (int count = 0; count < hashTable_copy.size(); count++) {
        // If statement that checks if location is NULL, calls insert function if so 
        if (hashTable_copy[count] != NULL) { insert(hashTable_copy[count]); }
    }
}

// time complexity = n
// space complexity = 1
bool HashTableQuad::isIn(int n){

    // Initialize i and counter variable 
    int count = 1;
    int i = n % size_table;
    //While loop that iterates until NULL is reached
    while (hashTable[i] != NULL) {
        // If statement that returns true if n == to the value in index i
        if (hashTable[i] == n) { return true; }
        // Else, i will undergo quadratic probing 
        else {
            // i is set using quadratic probing
            i = (n % size_table + (count * count)) % size_table;
            // If statement that returns false if count == size_table
            if (count == size_table) { return false; }
            // Increment i by 1 
            count++;
        }
    }
    return false;
}

// time complexity = n
// space complexity = 1
void HashTableQuad::printKeys(){

    // For loop that iterates from i to size_table
    for (int i = 0; i < size_table; i++) {
        // If statement that checks if value != NULL, prints key if true
        if (hashTable[i] != NULL) { printf(hashTable[i] + ", "); }
    }
}

// time complexity = n
// space complexity = 1
void HashTableQuad::printKeysAndIndexes(){

    // For loop that iterates from i to size_table
    for (int i = 0; i < size_table; i++) {
        // If statement that checks if value != NULL, prints key and index if true
        if (hashTable[i] != NULL) { printf(i + ", " + hashTable[i]); }
    }
}

// time complexity = n
// space complexity = 1
int HashTableQuad::getNumKeys() {

    // Initialize variables
    int key_counter = 0;
    //For loop that iterates from i to size_table
    for (int i = 0; i < size_table; i++) {
        // If statememnt that checks if value != NULL, increments key counter if true 
        if (hashTable[i] != NULL) { key_counter++; }
    }
    // Returns key_counter
    return key_counter;
}

// time complexity = 1
// space complexity = 1
int HashTableQuad::getTableSize() {

    return size_table;
}

// time complexity = n
// space complexity = 1
double HashTableQuad::getMaxLoadFactor() {

    return max_loadfactor;
}

// time complexity = n^2
// space complexity = 1
int HashTableQuad::insert_count(int n) {

    // Initializing variables
    int num_probe = 0;
    int counter = 1;
    // If statement that checks if n is not a prime number
    if (!isIn(n)) {
        // Initialize i 
        int i = n % size_table;
        // If statement that checks if value == NULL
        if (hashTable[i] == NULL) {
            // Sets n to that location, increments keys_num and num_probe
            hashTable[i] = n;
            keys_num++;
            num_probe++;
        }

        // Else, it will perform quadratic probing and insert
        else {
            //While loop that iterates until NULL is met
            while (hashTable[i] != NULL) {
                // i is set using quadratic probing, then increments num_probe 
                i = (n % size_table + (counter * counter)) % size_table;
                num_probe++;
                //If statement that checks if counter == size_table, returns 0 if so 
                if (counter == size_table) { return 0; }
                counter++;
            }
            hashTable[i] = n;
            keys_num++;
            num_probe++;
        }
        // If statement that checks if max key is less than num of keys, rehashes if so
        if (key_max < keys_num) { rehash(); }
    }
    return num_probe;
}
std::vector<double> HashTableQuad::simProbeSuccess(){
    // storing the load factor in a vector for 9 diff values
    vector<double> result(9);
    // initializing variables
    int count = 0;
    int max_size = 100000;
    int random_val_list[100000];
    double val_size = 100000;
    double sum = 0;
    double probe_avg = 0;
    // For loop that iterates from 0 to 1000000
    for (int i = 0; i < max_size; i++) {
        // Initialize int variable and boolean variable
        int random_number;
        bool isIn = true;
        // While loop to iterate if isIn is true
        while (isIn) {
            //Sets isIn to false and generates random number which is stored in random_number
            isIn = false;
            random_number = rand() * rand();
            // For loop that iterates through all variables to make sure no duplicates are in the list
            for (int j = 0; j < i; j++) {
                if (random_number == random_val_list[j]) {
                    isIn = true;
                    break;
                }
            }
        }
        random_val_list[i] = random_number;
    }
    // For loop that iterates through different load factors
    for (double loadfactor = 0.1; loadfactor < 0.99; loadfactor += 0.1) {
        // sum variable is cleared after every iteration
        sum = 0;
        // For loop that tests loadfactor 100 times
        for (int i = 0; i < 100; i++) { HashTableQuad hashtable = HashTableQuad(max_size, loadfactor);
            // For loop to find the numbers of proves
            for (int j = 0; j < val_size; j++) { sum += (hashtable.insert_count(random_val_list[j])) / (val_size); }
        }
        // Calculation to find the average probing value
        probe_avg = sum / 100;
        result[count] = probe_avg;
        count++;
    }
    return result;
}
