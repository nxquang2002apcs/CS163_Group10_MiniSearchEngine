#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void historySuggestion(string query, vector<string>& his) {
	ifstream fin;
	string sen;
	int order = 1; // so thu tu
	
	fin.open("history.txt");
	if (!fin.is_open()) 
		cout << "Can't create file" << endl;
	else {
		getline(fin, sen);
		while(!fin.eof()) {
			size_t found = sen.find(query); 
			if (found != string::npos) {
				cout << order <<". "<< sen << endl;
				order++;
			}	
			getline(fin, sen);
		}
	}
	fin.close();
}

int main ()
{
	vector<string> his;
	string query;
	cout << "Pls input the query: ";
	getline(cin, query);
	historySuggestion(query, his);
}

