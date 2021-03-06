#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main () {
	double low, high;
	int start, end;
	cout << "Query: ";
	string query;
	getline(cin, query); 
	size_t found = query.find("..");
	size_t check = query.find("..$");
	// high 
	if (check != string::npos)
		found += 3;
	else 
		found += 2;
	end = found;
	while(query[end] != 32 && query[end]){
		end++;
	}
	string num1 = query.substr(found, end - found);
	stringstream ss1, ss2;
	ss1 << num1;
	ss1 >> high;
	// low
	if (check != string::npos)
		found -= 3;
	else
		found -= 2;
	start = found - 1;
	while(query[start] != '$' && query[start] != 32 && start)
		start--;
	if(query[start] == '$' || query[start] == 32)
		start += 1;
	
	string num2 = query.substr(start, found - start);
	ss2 << num2;
	ss2 >> low;
	cout << "low: "<< low <<endl;
	cout << "high: " << high;

}
