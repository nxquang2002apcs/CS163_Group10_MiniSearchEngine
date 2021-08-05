#ifndef _SEARCH_ENGINE_H_
#define _SEARCH_ENGINE_H_

#include <iostream>
#include <string>
#include<sstream>
#include<vector>
#include<fstream>

using namespace std;

struct TrieNode {
	TrieNode* children[42];  //0-9: number; 10-35: alphabet; 36: space; 37: dot(.); 38:(#); 39:(%); 40:($); 41:(-)
	bool isTitle;			 //To decide this word is in title or not
	bool isEndOfWord;		
	vector<int> pos;
};
struct File {
	string name;
	vector<int> pos;
	int score;
};

class searchEngine {
public:
	void Initialize(TrieNode**& root, int n);	//Quang
	TrieNode* createNode();				//Quang
	bool isNumber(char key);			//Quan
	bool isAlphabet(char key);			//Quan
	string intToString(int num);		//Quan
	string floatToString(float num);	//Quan
	bool isAccepted(char& key);			//Phat
	int convert(char key);				//Phat
	string filter(string sen);			//Phat
	void inputFile(TrieNode*& root, ifstream& file, string path);				//Khanh
	void insertSentence(TrieNode*& root, string sen, int& pos, bool isTitle);	//Khanh
	void insertWord(TrieNode*& root, string word, int& pos, bool isTitle);		//Khanh
	TrieNode* searchWord(TrieNode* root, string word, bool isTitle);			//Quang
	bool searchTrie(TrieNode* root, TrieNode* stopwordRoot, vector<int>& pos, int& rankScore, string query);	//Quang
	void merge(vector<int>& vec1, vector<int> vec2);	//Quang
	void releaseTrie(TrieNode*& root);					//Quang
	void match(vector<int>& vec1, vector<int>& vec2, int asterisk);	//Quang
	pair<int,int> findAsterisk(string query);
	void findRange(string query, double& low, double& high);	//Phat
	void searchNumber_DFS(TrieNode* root, double low, double high, double num, int power, vector<int>& pos);
	void Synonyms(string word, vector<string>& syno);
	int countWord(string sen); 
	void display(File file);
};

#endif // !_SEARCH_ENGINE_H_
