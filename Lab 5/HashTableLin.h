#ifndef HASHTABLELIN_H_
#define HASHTABLELIN_H_

#include <vector>

class HashTableLin
{
private:
	std::vector<int> hashTable;
	// Variable to store the size of the table
	int size_table;
	// Variables to store keys in the table
	int keys_num;
	int key_max;
	// Variable to store the maximum load factor allowed
	double max_loadfactor;

public:
	// Required constructor
	HashTableLin(int maxNum, double load);

	// Required methods used
	// Boolean variable that will track if n is a prime number or not
	bool Is_Prime(int n);
	int insert_count(int n);
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();
	static std::vector<double> simProbeUnsuccess(); 

	// used for testing
	std::vector<int> getTable() {
		return hashTable;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLELIN_H_ */