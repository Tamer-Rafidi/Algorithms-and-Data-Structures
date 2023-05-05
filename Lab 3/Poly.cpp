#include "Poly.h"
#include <cmath>
#include <iostream>

using namespace std;

Poly::Poly(){

	head = new PolyNode(-1, 0, NULL);
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff){
	//Initializing polynomial
	head = new PolyNode(NULL, NULL, NULL);
	PolyNode* curr = head;
	//For loop to create a linked list for every term
	for (int i = 0; i < size(deg); i++) {
		curr->next = new PolyNode(deg[i], coeff[i], NULL);
		curr = curr->next;
	}
}

Poly::~Poly(){
	//While loop to delete terms in linked list
	while (head->next) { 
		auto tmp = head->next;
		head->next = tmp->next;
		delete tmp;
	}
}

/*
* time complexity:n
* Space: n+1
*/
void Poly::addMono(int i, double c) {
	//Check to see if monomial exists, adds it if so
	if (c != 0.0) {
		//Initializing variables
		int set = 0;
		PolyNode* curr = head;
		//While loop to iterate through each term of the polynomial
		while (curr->next != NULL) {
			//If statement to check if the next polynomial has a higher degree than monomial, curr points to the next term if so
			if (curr->next->deg > i) { curr = curr->next; }
			//If statement to check if the next polynomial has the same degree as the monomial, curr points to the next term if so
			else if (curr->next->deg == i) {
				//adds coefficients together
				if (curr->next->coeff + c != 0) { curr->next->coeff = curr->next->coeff + c; }
				//Else the node will be deleted as it has a coefficient of 0
				else { curr->next = curr->next->next; }
				//Set is true which breaks the loop 
				set = 1;
				break;
			}
			//If statement to check if the next polynomial has a lower degree than monomial, create a new node to hold the monomial if so
			else if (curr->next->deg < i) {
				PolyNode* temp = new PolyNode(i, c, NULL);
				temp->next = curr->next;
				curr->next = temp;
				set = 1;
				break;
			}
		}
		//If set was never changed to true, then a new node is created for the monomial
		if (set == 0) { curr->next = new PolyNode(i, c, NULL); }
	}
}

/*
* time:n
* space:2n
*/
void Poly::addPoly(const Poly& p){
	//Initialize variables
	PolyNode* curr = head;
	PolyNode* pNew = p.head;
	//While loop that iterates through the terms of both polynomial
	while (curr->next != NULL && pNew->next != NULL) {
		//If statement to check if the degree on current polynomial is greater than new polynomial, points to next if so
		if (curr->next->deg > pNew->next->deg) { curr = curr->next; }
		//If statemente to check if the degree on both polynomials are equal, adds the coefficients if so 
		else if (curr->next->deg == pNew->next->deg) {
			if (curr->next->coeff + pNew->next->coeff != 0) {
				curr->next->coeff = curr->next->coeff + pNew->next->coeff;
				curr = curr->next;
				pNew = pNew->next;
			}
			//If the sum of coefficients = 0, then the term can be removed
			else {
				PolyNode* temp = new PolyNode(curr->next->deg, curr->next->coeff, curr->next->next);
				curr->next = temp->next;
				delete temp;
				pNew = pNew->next;
			}
		}
		//If statement to check if the degree on current polynomial is less than new polynomial, new node is created if so
		else if (curr->next->deg < pNew->next->deg) {
			PolyNode* temp = new PolyNode(pNew->next->deg, pNew->next->coeff, NULL);
			temp->next = curr->next;
			curr->next = temp;
			pNew = pNew->next;
		}
	}
	//While loop to check that all terms of the new polynomial was assessed and added to curr polynomial
	while (pNew->next != NULL) {
		PolyNode* temp2 = new PolyNode(pNew->next->deg, pNew->next->coeff, NULL);
		curr->next = temp2;
		pNew = pNew->next;
		curr = curr->next;
	}
}

/*
* Time: n
* Space: n
*/
void Poly::multiplyMono(int i, double c){
	//If statement to check if c == 0, product polynomial set to 0 if so
	if (c == 0.0) { head->next = NULL; }
	//Else statement to multiply monomial
	else {
		//Initialize variable
		PolyNode* curr = head;
		//While loop to perform multiplication operation
		while (curr->next != NULL) {
			//Degree is added by the degree of monomial
			curr->next->deg = curr->next->deg + i;
			//Coefficient is multiplied by the coefficient of the monomial
			curr->next->coeff = curr->next->coeff * c;
			curr = curr->next;
		}
	}
}

/*
* Time: n^3
* Space:2n
*/
void Poly::multiplyPoly(const Poly& p){
	//Initialize variables
	PolyNode* curr = head;
	PolyNode* pNew = p.head;
	Poly pResult = Poly();
	//While loop to iterate through every node in the polynomial
	while (curr->next != NULL) {
		//Nested while loop to iterate through every node of pNew 
		while (pNew->next != NULL) {
			//If statement to check if sum of degrees is not 0, calls addMono to add the terms together if so
			if (curr->next->deg + pNew->next->deg != 0) {
				pResult.addMono(curr->next->deg + pNew->next->deg, curr->next->coeff * pNew->next->coeff);
			}
			//points to next term in pNew
			pNew = pNew->next;
		}
		//Adjusts pointers to next terms
		pNew = p.head;
		curr = curr->next;
	}
	pResult.duplicate(*this);
}

/*
* Time: n
* Space:2n
*/
void Poly::duplicate(Poly& outputPoly){
	//initialize vairables and dummy node
	PolyNode* curr = head;
	outputPoly.head = new PolyNode(-1, 0, NULL);
	PolyNode* copyCurr = outputPoly.head;
	//While loop to iterate through all nodes
	while (curr->next != NULL) {
		//If statement to check if next node is NULL, creates a new node if so
		if (copyCurr->next == NULL) { copyCurr->next = new PolyNode(-1, 0, NULL); }
		//adjusts pointers as it adds nodes to the copy
		copyCurr->next->deg = curr->next->deg;
		copyCurr->next->coeff = curr->next->coeff;
		curr = curr->next;
		copyCurr = copyCurr->next;
	}
}


int Poly::getDegree(){
	//If statement to check degree, returns -1 if polynomial is empty
	if (head->next == NULL) { return -1; }
	//Else it returns the degree of first term
	else { return head->next->deg; }
}

int Poly::getTermsNo(){
	//Initialize counter variable
	int counter = 0;
	PolyNode* curr = head;
	//Return 0 if polynomial is empty
	if (curr->next == NULL) { return 0; }
	else {
		//While loop to iterate through all nodes of the polynomial
		while (curr->next != NULL) {
			curr = curr->next;
			//If statement to check if degree is -1, returns 0 if so 
			if (curr->deg == -1) { return 0; }
			//Increment counter variable after each term 
			counter++;
		}
		return counter;
	}
}

double Poly::evaluate(double x){
	//Initialize variables
	double total = 0;
	PolyNode* curr = head;
	//While loop it iterate through all nodes, and evaluates each term
	while (curr->next != NULL) {
		total += curr->next->coeff * pow(x, curr->next->deg);
		//Points to next term after each iteration
		curr = curr->next;
	}
	return total;
}

std::string Poly::toString(){
	//Initializing variables
	std::string str_rep = "";
	PolyNode* curr = head;
	//While loop that appends the coefficients into the string
	while (curr->next) { str_rep += std::to_string(curr->next->coeff) + " "; }
	//Appends the degree into the string representation
	str_rep += ":degree: " + std::to_string(getDegree());
	return str_rep;
}