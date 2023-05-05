#include "HashTableLin.h"
#include <stddef.h>
#include <iostream>
using namespace std;

// time complexity = n
// space complexity = 1
bool HashTableLin::Is_Prime(int n) {
    // If statement to check if n == 1 or 0 since they are not prime numbers
    if ((n == 1) || (n == 0)) { return false; }
    // For loop that iterates from counter to n to check if a number is prime or not
    for (int count = 2; count < n; count++) {
        // Checks to see if the number is not a prime number by seeing if the mod == 0
        if (n % count == 0) { return false; }
    }
    return true;
}

// time complexity = n^2
// space complexity = 1
HashTableLin::HashTableLin(int maxNum, double load){

    // Calculation to find the load factor
    size_table = maxNum / load;
    double dsize_table = maxNum / load;
    if (dsize_table > size_table) { size_table++; }
    // this will make sure the vector size is prime.
    // While loop to check that the vector size is a prime number. Keeps incremeneting value until its a prime number
    while (!Is_Prime(size_table)) { size_table++; }
    vector<int> temp(size_table);
    hashTable = temp;
    keys_num = 0;
    max_loadfactor = load;
    key_max = size_table * load;
}

// time complexity = n^2
// space complexity = 1
void HashTableLin::insert(int n){

    // If statement to check if value n is not in the hashtable, increments keys_num
    if (!isIn(n)) { keys_num++;
        // If max keys is less than the number of keys present, rehash will be called
        if (key_max < keys_num) { rehash(); }
        int index_value = n % size_table;
        // If statement to check if value at position index_value is NULL. If so, then it will set n to that value
        if (hashTable[index_value] == NULL) { hashTable[index_value] = n; }
        // If the value at index_value is not NULL, then it will enter a while loop to continuosly increment index_value until it is
        else {
            while (hashTable[index_value] != NULL) { index_value = (index_value + 1) % size_table; }
            // Sets n to value at index_value
            hashTable[index_value] = n;
        }
    }
}
// time complexity = n
// space complexity = 1
void HashTableLin::rehash(){

    // Takes the value of size_table and doubles it
    size_table = size_table * 2;
    // Calculates the new value of key_ma with the new value of size_table
    key_max = max_loadfactor * size_table;
    // Creates a copy of its table and sets it to copy_table
    std::vector<int> copy_table = hashTable;
    // While look that iterates until size_table is a prime number. If it is not a prime number, it will be incremented by 1
    while (!Is_Prime(size_table)){ size_table++; }
    //Sets keys_num to 0
    keys_num = 0;
    // Clears table the resizes it depending on size_table  
    hashTable.resize(0);
    hashTable.resize(size_table);
    // For loop that iterates through the size of copy_table
    for (int count = 0; count < copy_table.size(); count++) {
        // If statement to check if value at count is not NULL. Inserts value to table
        if (copy_table[count] != NULL) { insert(copy_table[count]); }
    }
}

// time complexity = n
// space complexity = 1
bool HashTableLin::isIn(int n){

    //Initialize variables
    int count = n % size_table;
    // While loop that iterates until a NULL value has been reached
    while (hashTable[count] != NULL){
        // If statement to check if n is the same number as index. If so, return true
        if (hashTable[count] == n) { return true; }
        // Else, increase count by 1 each iteration and calculate a new count value.
        else{
            count = (count + 1) % size_table;
            // If statement to check if the new index value matches the old index value. If so, returns false
            if (count == n % size_table){ return false; }
        }
    }
    //Return false
    return false;
}

// time complexity = n
// space complexity = 1
void HashTableLin::printKeys(){

    //For loop to iterate through size of table
    for (int index = 0; index < size_table; index++){
        // If statement to check if the value at index is not equal to null. If true, print the key
        if (hashTable[index] != NULL) { printf(hashTable[index] + ", "); }
    }
}

// time complexity = n
// space complexity = 1
void HashTableLin::printKeysAndIndexes(){

    // For loop that iterates through the size of the table
    for (int index_pos = 0; index_pos < size_table; index_pos++) {
        // If statement to check if the value at index_pos does not equal to NULL. If true, prints key and index position
        if (hashTable[index_pos] != NULL) { printf(index_pos + ", " + hashTable[index_pos]); }
    }
}

// time complexity = n
// space complexity = 1
int HashTableLin::getNumKeys() {

    // Initialize variables
    int count_key = 0;
    // For loop that iterates through the size of the table
    for (int index_pos = 0; index_pos < size_table; index_pos++){
        // If statement to check if the value at index posistion is not equal to NULL. If tue, increments key count
        if (hashTable[index_pos] != NULL){ count_key++; }
    }
    // Return key count
    return count_key;
}

// time complexity = n
// space complexity = 1
int HashTableLin::getTableSize() {

    return size_table;
}

// time complexity = 1
// space complexity = 1
double HashTableLin::getMaxLoadFactor() {

    return max_loadfactor;
}

// time complexity = 1
// space complexity = 1
int HashTableLin::insert_count(int n) {

    // Initialize probe_num
    int probe_num = 0;
    // If statement to check if n is not a prime number
    if (!isIn(n)) {
        // Increment keys_num each iteration
        keys_num++;
        // If statement to check if the max keys is less than the number of keys present. If so, call rehash function
        if (key_max < keys_num) { rehash(); }
        // Initialze index_pos variable and calculates it
        int index_pos = n % size_table;
        // If statement to check if the value at index_pos is equal to NULL. If so, set it to n and increment probe_num
        if (hashTable[index_pos] == NULL) {
            hashTable[index_pos] = n;
            probe_num++;
        }
        // If it is not equal to NULL, undergo while look that increments the index_pos to find which position contains a NULL valyue
        else {
            while (hashTable[index_pos] != NULL) {
                index_pos = (index_pos + 1) % size_table;
                probe_num++;
            }
            // Set n to that position and increment probe_num
            hashTable[index_pos] = n;
            probe_num++;
        }
    }
    // Returns probe_num
    return probe_num;
}


std::vector<double> HashTableLin::simProbeSuccess() {
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
        for (int i = 0; i < 100; i++) { 
            HashTableLin hashtable = HashTableLin(max_size, loadfactor);
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


std::vector<double> HashTableLin::simProbeUnsuccess(){

    vector<double> result(9);
    return result;
}