#include "BSTSet.h"
#include "SNode.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//running time: theta(1)
//space complexity: O(1)
BSTSet::BSTSet(){

	// Initializing empty tree
	root = NULL;
}

//running time: theta(n^2)
//space complexity: O(n)
BSTSet::BSTSet(const std::vector<int>& input){

	//bool variable that determines the direction that the node traveled
	bool lastDirection = false;

	// If statement to check the input size
	if (input.size() > 0){

		root = new TNode(input[0], NULL, NULL);
		// Set pointers
		TNode* current = root;
		TNode* previous = root;
		// For loop to insert all inputs into the tree
		for (int i = 1; (unsigned)i < input.size(); i++){

			// While loop to insert remaining inputs
			while (current != NULL && current->element != input[i]){

				// Compares values of current node and input, moves to left if current is greater
				if (current->element > input[i]){

					previous = current;
					current = current->left;
					lastDirection = false;
				}
				// Else move to the right
				else if (current->element < input[i]){

					previous = current;
					current = current->right;
					lastDirection = true;
				}
			}

			// If statement that checks the boolean and inserts node to the right of previous node
			if (current == NULL && lastDirection){ previous->right = new TNode(input[i], NULL, NULL); }
			// If statement that checks the boolean and inserts node to the left of previous node
			if (current == NULL && !lastDirection){ previous->left = new TNode(input[i], NULL, NULL); }
			// Sets current and previous to default to undergo insertion from the root
			current = root;
			previous = root;
		}
	}
}

//running time: theta(n^2)
//space complexity: O(1)
BSTSet::~BSTSet(){

	sort();
	//For loop to free memory
	for (int i = find_max(root); i >= find_min(root); i--) { remove(i);  }
}

//worst case run time: big theta(n), n is the number of tree nodes, average run time: big theta(logn)
//space complexity: O(1)
bool BSTSet::isIn(int v){

	// checks for empty tree
	if (root == NULL) {
		return false;
	}
	//Initialize root node
	TNode* current = root;
	// While loop to iterate through the elements of the tree based on consecutive if statements
	while (current != NULL) {
		// If statement to move left if true
		if (v < current->element) { current = current->left; }
		//Else if statement to move right if true
		else if (v > current->element) { current = current->right; }
		// Returns true if v == current -> element
		else { return true; }
	}
	//Returns false if not found
	return false;
}

// running time: theta(n^2)
//space complexity: O(1)
void BSTSet::add(int v){

	// If statement to check if the tree is empty, sets v to the root if so
	if (root == NULL) { root = new TNode(v, NULL, NULL); }

	// If statement to prevent duplicates
	if (isIn(v) == false) {
		// Initialize variables
		bool previous_direction = false;
		TNode* current = root;
		TNode* previous = root;
		// While loop to iterate through the tree
		while (current != NULL) {
			// If statement to move left of tree if true
			if (current->element > v) {
				previous = current;
				current = current->left;
				previous_direction = false;
			}
			// Else if statement to move right of tree if true
			else if (current->element < v) {
				previous = current;
				current = current->right;
				previous_direction = true;
			}
		}
		// If statement that adds element to the right of previous node
		if (current == NULL && previous_direction) { previous->right = new TNode(v, NULL, NULL); }
		// If statement that adds element to the right of previous node
		if (current == NULL && !previous_direction) { previous->left = new TNode(v, NULL, NULL); }
		// Resets current and previous variables
		current = root;
		previous = root;
	}
}

//running time: theta(n)
//space complexity: O(1)
int BSTSet::find_min(TNode* t) {

	// If statement to check if the tree is empty
	if (t == NULL) { return NULL; }
	//While loop to iterate through the left branch of the tree to find minimum
	while (t->left != NULL) { t = t->left; }
	//Returns the leftmost element (minimum)
	return (t->element);
}

//running time: theta(n)
//space complexity: O(1)
int BSTSet::find_max(TNode* t) {

	// If statement to check if the tree is empty
	if (t == NULL) { return NULL; }
	//While loop to iterate through the right branch of the tree to find maximum
	while (t->right != NULL) { t = t->right; }
	// Returns the rightmost element (maximum)
	return (t->element);
}

//running time: theta(n)
//space complexity: O(1)
void BSTSet::sort() {

	// Initializes new_root variable that will replace the node
	TNode* new_root = new TNode(find_min(root), NULL, NULL);
	TNode* current = new_root;
	// For loop to iterate through all possible values within the tree
	for (int i = find_min(root) + 1; i <= find_max(root); i++) {
		// if i is in tree then it will add it
		// If statement to check is i is in the tree, will add it to vector
		if (isIn(i)) {
			current->right = new TNode(i, NULL, NULL);
			current = current->right;
		}
	}
	// Replace root with new_root
	root = new_root;
}

//running time: theta(n)
//space complexity: O(1)
bool BSTSet::remove(int v){

	//If statement to check if tree is empty or value is not in tree
	if (root == NULL || isIn(v) == false) { return false; }
	sort();

	//overwrites root
	// If statement to check if the root == v, moves the root to the right if so
	if (root->element == v) {
		root = root->right;
		return true;
	}
	//Initialize variables
	TNode* current = root;
	TNode* previous = root;

	// While loop to iterate through the right side to find v
	while (current->element != v) {
		previous = current;
		current = current->right;
	}
	// If statement if the node that is being removed is a lead
	if (current->right == NULL) {
		previous->right = NULL;
		free(current);
	}

	// Else statement when the node that is being removed only has one child
	else { previous->right = current->right; }
	return true;
}

//running time: theta(n^4)
//space complexity: O(1)
void BSTSet::Union(const BSTSet& s){
	
	// Creates a duplicate of s
	BSTSet s_copy = s;

	// For loop to iterate through all values of s
	for (int i = find_min(s.root); i <= find_max(s.root); i++) {
		// If statement to check if its in s, add it to s_copy if so
		if (s_copy.isIn(i)) { add(i); }
	}
}

//running time: theta(n)
//space complexity: O(1)
void BSTSet::intersection(const BSTSet& s){
	
	// Calls sort function
	sort();
	// Create a duplicate of s
	BSTSet s_copy = s;
	TNode* current = root;
	// While loop to iterate through tree
	while (current != NULL) {
		//If statement to remove items that are not in both trees
		if (!isIn(current->element) || !s_copy.isIn(current->element)) { remove(current->element); }
		current = current->right;
	}
}

//running time: theta(n^2)
//space complexity: O(1)
void BSTSet::difference(const BSTSet& s){

	// Create a copy of s
	BSTSet s_copy = s;

	// For loop that iterates from the minimum to maxmimum of s
	for (int i = find_min(s.root); i <= find_max(s.root); i++) {
		// If statement to remove what is common
		if (s_copy.isIn(i)) { remove(i); }
	}
}

//running time: theta(n)
//space complexity: O(n)
int BSTSet::size(){

	// If statement to check if the tree is empty
	if (root == NULL) { return 0; }
	// Call sort function to set tree in a vector
	sort();
	// Initialize variables
	TNode* current = root;
	int i = 0;
	// While loop that iterates through the tree, counts elements
	while (current != NULL) {
		i++;
		current = current->right;
	}
	//returns size of tree
	return i;
}

//running time: theta(n)
//space complexity: O(n)
int BSTSet::height(){

	// If statement to check if tree is empty
	if (root == NULL) { return -1; }

	// Initialize variables
	int height = 0;

	// For loop that iterates from minimum to maxmimum 
	for (int i = find_min(root); i <= find_max(root); i++) {
		// If statement to check the depth of every node it iterates through. Sets height to node with highest depth
		if (height < depth(i)) { height = depth(i); }
	}
	return height;
}

//running time: theta(n)
//space complexity: O(n)
int BSTSet::depth(int i) {

	// Initializing variables
	TNode* current = root;
	int counter = 0;

	// While loop that iterates through the tree
	while (current != NULL) {
		// If statement that moves the node to the left if true
		if (i < current->element) { current = current->left; }
		// If statement that moves the node to the right if true
		else if (i > current->element) { current = current->right; }
		// Returns depth of tree 
		else { return counter; }
		counter++;
	}
	// Returns 0 if tree is empty
	return 0; 
}

//running time: theta(1)
//space complexity: O(1)
MyStack::MyStack() {
	// Intializes empty tree
	root = NULL; 
}

//running time: theta(1)
//space complexity: O(1)
bool MyStack::isempty() { 
	//Returns true is tree is empty
	return(root == NULL);
}

//running time: theta(1)
//space complexity: O(1)
void MyStack::push(TNode* v) {
	// Creates new node
	root = new SNode(v, root);
}

//running time: theta(1)
//space comeplexity: O(1)
TNode* MyStack::pop() {

	//Throws error if stack is empty
	if (isempty()) { throw std::underflow_error("Stack underflow"); }
	// Else statement that pops value in stack 
	else {
		SNode* temproot = root; //tmp to hold root
		TNode* current = root->element;
		root = root->next;
		delete temproot;
		return current;
	}
}

//running time: theta(n)
//space comeplexity: O(n)
void BSTSet::printNonRec() {

	// Initializing variables
	TNode* pop;
	MyStack stack = MyStack();
	TNode* current = root;

	// While loop that iterates through the stack 
	while (current != NULL || !stack.isempty()) { 
		if (current != NULL) {
			stack.push(current);
			current = current->left;
		}
		if (current == NULL) {
			current = stack.pop();
			cout << current->element << ",";
			current = current->right;
		}
	}
}

// Do not modify following provided methods
void BSTSet::printBSTSet()
{
	if (root == NULL)
		std::cout << "";
	else
	{
		printBSTSet(root);
	}
}

void BSTSet::printBSTSet(TNode* t)
{
	if (t != NULL)
	{
		printBSTSet(t->left);
		std::cout << t->element << ",";
		printBSTSet(t->right);
	}
}
