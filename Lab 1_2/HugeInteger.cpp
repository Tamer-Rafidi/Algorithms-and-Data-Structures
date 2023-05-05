#include "HugeInteger.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

HugeInteger::HugeInteger(const std::string& val) {
	//Initializing variable
	int i = 0;
	//If statement to check if the value given is a negative. Sets i=1 so while loop starts at second character if so
	//Sets IsPos to false if the number is a negative
	if (val[i] == '-') {
		IsPos = false;
		i = 1;
	}
	else { IsPos = true; }
	//While loop that iterates through each character until the NULL character has been reached 
	while (val[i] != '\0') {

		//Convertes character to an integer to validate its value 
		int IntChar = val[i] - '0';

		//If statement to check that the current character is a valid value between 0 and 9. Throws exception if it isnt
		if (IntChar < 0 || IntChar > 9) { throw std::invalid_argument("Invalid HugeInteger"); }
		else { HugeInt.push_back(IntChar); }

		//Increment i by 1
		i++;
	}
	//If statement to check if the string is empty. Throws exception if so 
	if (val.length() == 0) { throw std::invalid_argument("Invalid HugeInteger"); }
}

HugeInteger::HugeInteger(int n) {
	//Using srand() and time() API methods to generate a random number. Use time(0) to give a different value every time the code runs
	srand(time(0));

	//If statement to check if n is less than 1. Throws an exception if so
	if (n < 1) { throw std::invalid_argument("Invalid Input Number"); }

	IsPos = rand() % 2;

	//Use rand() API method to pick a random number in the range 1 to 9 due to algorithm
	HugeInt.push_back(((rand() % 9) + 1));

	//For loop to add n-1 integers to the HugeInteger 
	for (int i = 0; i < n - 1; i++) {
		int RandNum = rand() % 10;
		HugeInt.push_back(RandNum);
	}
}

HugeInteger HugeInteger::add(const HugeInteger& h) {

	//Initializing two HugeInteger input vectors as num1 and num2
	std::vector<int>num_1 = HugeInt;
	std::vector<int>num_2 = h.HugeInt;

	//Initializing 2 result variables 
	std::string AddResult = "";
	std::string EndResult = "";

	//Initialzing length of the 2 input vectors. Length -1 is done to remove the undefinied character 
	int len1 = HugeInt.size() - 1;
	int len2 = h.HugeInt.size() - 1;

	//Initialize a carry variable
	int carry = 0;

	//If statement to check all combinations for signs of two integers and allows for seamingless algebra
	//If statement if both inputs are negative. Completes normal addition with positive integers and adds "-" at the end
	if (this->IsPos == false && h.IsPos == false) { EndResult += '-'; }
	else if (this->IsPos == false && h.IsPos == true) {
		//Initliazes the variable to ans_1
		HugeInteger ans_1 = *this;
		//Setting IsPos to true which allows two positive numbers to be subtracted
		ans_1.IsPos = true;
		//Result object that holds the subtraction of two positive numbers
		HugeInteger FirstNegative = ans_1.subtract(h);
		//If statement that checks if this HugeInteger (in its positive form) is bigger than h. Output the subtraction with a negative sign if so
		if (ans_1.compareTo(h) == 1) { FirstNegative.IsPos = false; }
		else if (ans_1.compareTo(h) == -1 || ans_1.compareTo(h) == 0) { FirstNegative.IsPos = true; }
		return FirstNegative;
	}
	else if (this->IsPos == true && h.IsPos == false) {
		//Assigning h's HugeInteger object to ans_2
		HugeInteger ans_2 = h;
		//Setting IsPos equal to true to perform subtraction with two positive numbers
		ans_2.IsPos = true;
		//Initliazes SecondNegative and assigns it to the subtraction of the following function call
		HugeInteger SecondNegative = this->subtract(ans_2);
		return SecondNegative;
	}

	//While loop to iterate until we run out of digits for either of the vectors
	while (len1 >= 0 || len2 >= 0) {
		//Initialize val as integers
		int val1 = 0;
		int val2 = 0;

		//If statement to check if num_1 still has digits.Coverts character to an integerand stores in val1 if so
		if (len1 >= 0) {
			val1 = num_1[len1];
			len1--;
		}

		//If statement to check if num_2 still has digits.Coverts character to an integerand stores in val1 if so
		if (len2 >= 0) {
			val2 = num_2[len2];
			len2--;
		}

		//Adds the vals and carry each iteration. Stores the first digit as the result and second digit in carry if need be
		int sum = val1 + val2 + carry;
		int result = sum % 10;
		carry = sum / 10;

		//Adds the result to the AddResult string
		AddResult += std::to_string(result);
	}

	//Checks if there is a carry after the last iteration from the loop
	//If yes, it adds the digit to the end of the AdditionResult string
	if (carry > 0) { AddResult += std::to_string(carry); }

	//Checks if there is a carry after the last iteration from the loop. Adds the carry to the end of the AddResult string if so
	for (int i = AddResult.length() - 1; i >= 0; i--) {
		//For loop to reverse the digits of AddResult since it was appended in the reverse order
		EndResult += AddResult[i];
	}

	return HugeInteger(EndResult);
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	//Initializing two HugeInteger vectors as num_1 and num_2
	std::vector<int>num_1 = HugeInt;
	std::vector<int>num_2 = h.HugeInt;

	//Initializing 2 result variables 
	std::string SubResult = "";
	std::string EndResult = "";

	//Initialzing length of the 2 input vectors. Length - 1 is done to remove the undefinied character
	int len1 = HugeInt.size() - 1;
	int len2 = h.HugeInt.size() - 1;

	//If statement to check condition where both numbers are equal in sign and magnitude. Returns subtraction = 0
	if ((num_1 == num_2) && (this->IsPos == h.IsPos)) { return HugeInteger("0"); }


	//Series of If statements to detect all possible combinations of signs 
	if (this->IsPos == false && h.IsPos == false) {
		//If statement to check if HugeInt is bigger than h
		if (this->compareTo(h) == 1) {
			std::vector<int>temp_1 = num_1;
			int temp_2 = len1;
			num_1 = num_2;
			len1 = len2;
			num_2 = temp_1;
			len2 = temp_2;
		}
		else if (this->compareTo(h) == -1) {
			EndResult += '-';
		}
	}
	else if (this->IsPos == false && h.IsPos == true) {
		//Sets the negative HugeInteger to positive
		IsPos = true;
		//Initializing FirstNegative and assigns it to the addition of two positive numbers
		HugeInteger FirstNegative = this->add(h);
		FirstNegative.IsPos = false;
		return FirstNegative;
	}
	else if (this->IsPos == true && h.IsPos == false) {
		//Assigning h's HugeInteger object to h2
		HugeInteger ans_2 = h;
		//Allow addition with two positive numbers by setting ans_2 to true
		ans_2.IsPos = true;
		//Perform the addition of two positive numbers and assigning it to SecondNegative
		HugeInteger SecondNegative = this->add(ans_2);
		SecondNegative.IsPos = true;
		return SecondNegative;
	}
	else if (this->IsPos == true && h.IsPos == true) {
		//If statement that checks if this HugeInteger is smaller than h. Swaps integers and adds a "-" to the final answer
		if (this->compareTo(h) == -1) {
			std::vector<int>temp_1 = num_1;
			int temp_2 = len1;
			num_1 = num_2;
			len1 = len2;
			num_2 = temp_1;
			len2 = temp_2;
			EndResult += '-';
		}
	}

	//While loop to iterate until all digits for either vector are looked at
	while (len1 >= 0 || len2 >= 0) {
		//Initializing answer and val
		int answer = 0;
		int val1 = 0;
		int val2 = 0;

		//If statement to check if num_1 still has digits. Assigns current digit to val1 and decrements len1 if so
		if (len1 >= 0) {
			val1 = num_1[len1];
			len1--;
		}

		//If statement to check if num_2 still has digits. Assignts current digt to val2 and decrements len2 if so
		if (len2 >= 0) {
			val2 = num_2[len2];
			len2--;
		}

		//If statement to check if val2 is greater than val1. Borrows a 1 from first number above zero and subtracts if so
		if (val2 > val1) {
			answer = (val1 + 10) - val2;
			int size = len1;
			//While loop that decrements until we reach the first index to the left of a zero, and would only borrow that
			while (num_1[size] == 0) {
				size--;
			}
			num_1[size]--;
			//While loop that turns all zeros into 9s and we borrowed a 1 
			while (num_1[size + 1] == 0) {
				num_1[size + 1] = 9;
				size++;
			}
		}
		else {
			//If no special cases exist, normal subtraction occurs and is stored in answer
			answer = val1 - val2;
		}

		//Adds the answer to the SubResult string
		SubResult += std::to_string(answer);
	}

	//For loop to reverse the digits of AddResult since it was appended in the reverse order
	for (int i = SubResult.length() - 1; i >= 0; i--) { EndResult += SubResult[i]; }

	//If statetements to remove leading 0s
	if (EndResult[0] == '-') {
		EndResult.erase(0, 1);
		EndResult.erase(0, EndResult.find_first_not_of('0'));
		EndResult.insert(0, 1, '-');
	}
	else if (EndResult[0] == '0') {
		EndResult.erase(0, EndResult.find_first_not_of('0'));
	}

	return HugeInteger(EndResult);
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {

	//Initializing two vectors to num_1 and num_2
	std::vector<int>num_1 = HugeInt;
	std::vector<int>num_2 = h.HugeInt;

	//Initializing 2 length integers for the vectors
	int len1 = HugeInt.size();
	int len2 = h.HugeInt.size();

	//Initializing a result vector
	std::vector<int>MultResult(len1 + len2, 0);

	//Initializing index to find positions in result vector
	int num1_index = 0;
	int num2_index = 0;

	//Initializing an EndResult string
	std::string EndResult = "";

	//If statement to check if any vector is empty, returns 0 if so
	if (len1 == 0 || len2 == 0 || num_1[0] == 0 || num_2[0] == 0) { return HugeInteger("0"); }

	//For loop that iterates from the end of num_1 to start
	for (int i = len1 - 1; i >= 0; i--) {
		//Initializing carry variable
		int carry = 0;
		//Initializing val1 variable which holds current num_1 value
		int val1 = num_1[i];
		num2_index = 0;

		//For loop to iterates through end of len2 to start
		for (int j = len2 - 1; j >= 0; j--) {
			//Initialize val2 to hold current num_2 value
			int val2 = num_2[j];
			//Sum is equal to val1 * val2 + MultResult at the current position + carry
			int sum = val1 * val2 + MultResult[num1_index + num2_index] + carry;

			//Stores the remainder in the vector while carry is stored in the carry variable
			MultResult[num1_index + num2_index] = sum % 10
			carry = sum / 10;

			//Increment num2_index
			num2_index++;
		}

		//If statement to check if carry is greater than 0. Adds the carry to te result in the next iteration
		if (carry > 0) {
			MultResult[num1_index + num2_index] += carry;
		}

		//Increment num1_index
		num1_index++;
	}

	//If statement to check the signs of both inputs. Adds a "-" to the result if so
	if ((this->IsPos == true && h.IsPos == false) || (this->IsPos == false && h.IsPos == true)) { EndResult += '-'; }

	//For loop to reverse the digits of AddResult since it was appended in the reverse order
	for (int i = MultResult.size() - 1; i >= 0; i--) { EndResult += std::to_string(MultResult[i]); }

	//If statetements to remove leading 0s
	if (EndResult[0] == '-') {
		EndResult.erase(0, 1);
		EndResult.erase(0, EndResult.find_first_not_of('0'));
		EndResult.insert(0, 1, '-');
	}
	else if (EndResult[0] == '0') {
		EndResult.erase(0, EndResult.find_first_not_of('0'));
	}

	return HugeInteger(EndResult);
}

int HugeInteger::compareTo(const HugeInteger& h) {
	//Initializing two vectors to num_1 and num_2
	std::vector<int>num_1 = HugeInt;
	std::vector<int>num_2 = h.HugeInt;

	//Initializing 2 length integers for the vectors
	int len1 = HugeInt.size();
	int len2 = h.HugeInt.size();

	//Initalize a variable to trigger if both numbers are equal
	int trigger = 0;

	//If statement to check if HugeInteger is positive while the other is negative. Return 1 if so. Return -1 if opposite is true.
	if (this->IsPos == true && h.IsPos == false) { return 1; }
	else if (this->IsPos == false && h.IsPos == true) { return -1; }

	//If statement to check if both HugetIntegers are negative. Swaps them if so
	if (this->IsPos == false && h.IsPos == false) {
		std::vector<int>temp_1 = num_1;
		int temp_2 = len1;
		num_1 = num_2;
		len1 = len2;
		num_2 = temp_1;
		len2 = temp_2;
	}

	//If statement to check the size of both HugeIntegers. Returns -1 if h.HugeInteger is greater
	if (len2 > len1) { return -1; }
	
	//If statements to check the size of both HugeIntegers. Returns 1 if HugeInteger is greater and both values are positive
	else if (len1 > len2) { return 1; }

	//If statement that checks if both lengths are the same
	else if (len1 == len2) {
		//For loop to iterate through all digits in the vector. Returns 1 if num_2's current digit is greater than num_1's digit. Returns -1 if opposite occurs
		for (int i = 0; i < len1; i++) {
			if ((num_1[i]) > (num_2[i])) {
				trigger = 1;
				return 1;
			}
			else if ((num_2[i]) > (num_1[i])) {
				trigger = 1;
				return -1;
			}
		}
		
		//If the numbers are the same, returns 0 
		if (trigger == 0) { return 0; }
	}
	return 0;
}

std::string HugeInteger::toString() {
	//Initializing EndResult as a string
	std::string EndResult = "";

	//If IsPos is false, add "-" to final result
	if (!IsPos) {
		EndResult += '-';
	}

	//For loop to iterate through the digits of HugeInteger and add it to the string
	for (auto i = HugeInt.begin(); i != HugeInt.end(); i++) {
		EndResult += std::to_string(*i);
	}

	return EndResult;
}

