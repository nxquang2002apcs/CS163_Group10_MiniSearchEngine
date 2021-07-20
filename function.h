#ifndef _SEARCH_ENGINE_H_
#define _SEARCH_ENGINE_H_

#include <iostream>
#include <string>
#include<sstream>
#include<vector>

using namespace std;

struct TrieNode {
	TrieNode* children[41];  //0-9: number; 10-35: alphabet
	bool isTitle;			 //To decide this word is in title or not
	bool isEndOfWord;		
	vector<int> pos;
};

class searchEngine {
public:
	bool isNumber(char key);			//Quan
	bool isAlphabet(char key);			//Quan
	string intToString(int num);		//Quan
	string floatToString(float num);	//Quan
	bool isAccepted(char key);			//Phat
	int convert(char key);				//Phat
	string filter(string sen);			//Phat
	void inputFile(TrieNode*& root, ifstream& file);							//Khanh
	void insertSentence(TrieNode*& root, string sen, int& pos, bool isTitle);	//Khanh
	void insertWord(TrieNode*& root, string word, int& pos, bool isTitle);		//Khanh
};

bool searchEngine::isAccepted(char key) {
	// lowercase and numbers
	if ((97 <= key && key <= 122) || (48 <= key && key <= 57)) 
		return true;	
	// uppercase -> lowercase
	if (65 <= key && key <= 90) {
		key += 32;
		return true;
	}
	// enter (\n), single quote (') -> space
	if (key == '\n' || key == 39 ) {
		key = 32;
		return true;
	}
	// special characters
	if ((35 <= key && key <=37) || key == 45 || key == 32)
		return true;
	return false;
}

int searchEngine::convert(char key) {
	if (key >= 48 && key <= 57){
		key -= 48;
		return key;
	}
	else if (97 <= key && key <= 122){
		key -= 87;
		return key;
	}
	else if (65 <= key && key <= 90) {
		key -= 55;
		return key;
	}
	switch (key) {
	case 32:
		key += 4;
		break;
	case 46:
		key -= 9;
		break;
	case 35:
		key += 3;
		break;	
	case 37:
		key += 2;
		break;
	case 36:
		key += 4;
		break;
	case 45:
		key -= 4;
		break;
	}
}

string searchEngine::filter(string sen) {
	string res;
	for (int i = 0; i <= sen.length(); i++) {
		if(isAccepted(sen[i]))
			res.push_back(sen[i]);
		if(sen[i] == 46) {
			if (48 <= sen[i-1] && sen[i-1] <= 57 && 48 <= sen[i+1] && sen[i+1] <= 57)
				res.push_back(sen[i]);
			else 
				return res;
		}
	}
	return res;
}

#endif // !_SEARCH_ENGINE_H_
