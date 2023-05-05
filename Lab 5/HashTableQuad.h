#ifndef HASHTABLEQUAD_H_
#define HASHTABLEQUAD_H_
#include <vector>

class HashTableQuad
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
	// required constructor
	HashTableQuad(int maxNum, double load);

	// required methods
	// Bool variable to track if n is a prime number or not
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

	// used for testing
	std::vector<int> getTable() {
		return hashTable;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLEQUAD_H_ */