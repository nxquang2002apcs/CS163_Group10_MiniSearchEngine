#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
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
		stringstream spliter;
		while(!fin.eof()) {
			spliter << query;
			string word;
			int flag = 1;
			while (spliter >> word) {
				size_t found = sen.find(word); 
				if (found == string::npos) {
					flag = -1;
					break;
				}
			}
			if (flag == 1) {
				cout  << sen << endl;
			}
			getline(fin, sen);
			spliter.str("");
			spliter.clear();
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

