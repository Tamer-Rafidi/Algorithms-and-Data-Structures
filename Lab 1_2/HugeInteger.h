#ifndef HUGEINTEGERH
#define HUGEINTEGERH
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
using namespace std;

class HugeInteger
{
private:
	std::vector<int>HugeInt;
	bool IsPos;
	
public:
	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);
	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
};

#endif /* HUGEINTEGER_H_ */
