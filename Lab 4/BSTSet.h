#ifndef BSTSET_H_
#define BSTSET_H_

#include "TNode.h"
#include <vector>
#include "MyStack.h"
#include <stddef.h>

class BSTSet
{
private:
	// must contain only one private field
	TNode* root = NULL;

public:
	// required constructors/destructor
	BSTSet();
	BSTSet(const std::vector<int>& input);
	~BSTSet();

	int find_min(TNode* t);
	int find_max(TNode* t);
	// required methods
	bool isIn(int v);
	void add(int v);
	bool remove(int v);
	void Union(const BSTSet& s);
	void intersection(const BSTSet& s);
	void difference(const BSTSet& s);
	int size();
	int height();
	int depth(int i);
	void printNonRec(); 
	void printBSTSet();
	void sort();

	// Used for testing
	TNode* getRoot()
	{
		return root;
	}

private:
	// provided helper methods
	void printBSTSet(TNode* t);
};

#endif /* BSTSET_H_ */
