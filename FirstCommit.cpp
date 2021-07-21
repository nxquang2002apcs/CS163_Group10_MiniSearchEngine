#include "function.h"

int main() {
	cout << "CS163 - APCS - Group 10" << std::endl;

	string str;
	cin >> str;

	isAlphabet(str)? cout << "The character is an alphabet\n" : cout << "The character is not an alphabet\n";

	isNumber(str) ? cout << "The character is a number\n" : cout << "The character is not a number\n";

	int i;
	float t;
	cin >> i;
	cin >> t;
	intToString(i);
	floatToString(t);

	return 0;
}
