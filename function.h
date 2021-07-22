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
	bool isNumber(const string& str);			
	bool isAlphabet(const string& str);			
	string intToString(int num);		
	string floatToString(float num);	
	bool isAccepted(char key);			//Phat
	int convert(char key);				//Phat
	string filter(string sen);			//Phat
	void inputFile(TrieNode*& root, ifstream& file);							//Khanh
	void insertSentence(TrieNode*& root, string sen, int& pos, bool isTitle);	//Khanh
	void insertWord(TrieNode*& root, string word, int& pos, bool isTitle);		//Khanh
};

#endif // !_SEARCH_ENGINE_H_
