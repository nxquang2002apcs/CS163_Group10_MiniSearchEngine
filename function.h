#ifndef _SEARCH_ENGINE_H_
#define _SEARCH_ENGINE_H_

#include <iostream>
#include <string>
#include<sstream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<set>
#include<time.h>

using namespace std;

struct TrieNode {
	TrieNode* children[43];  //0-9: number; 10-35: alphabet; 36: space; 37: dot(.); 38:(#); 39:(%); 40:($); 41:(-); 
							 //42 for special word: ã , & ,... no accepted character but stand alone as a word   
	bool isTitle;		
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
	void Initialize(TrieNode* root[100], TrieNode* stopWord, string path);	//Quang
	void Initialize(vector<TrieNode*>& root, vector<string>& listName, TrieNode* stopWord, string path);
	TrieNode* createNode();				//Quang
	bool isNumber(char key);			//Quan
	bool isAlphabet(char key);			//Quan
	string intToString(int num);		//Quan
	string floatToString(float num);	//Quan
	void insertStopWord(TrieNode*& stopword, string word);					//Quan
	void readFileStopWord(TrieNode*& stopword, ifstream& fin, string path);	//Quan
	bool isAccepted(char& key);			//Phat
	int convert(char key);				//Phat
	string filter(string sen);			//Phat
	void inputFile(TrieNode*& root, ifstream& file, string path);				//Khanh
	void insertSentence(TrieNode*& root, string sen, int& pos, bool isTitle);	//Khanh
	void insertWord(TrieNode*& root, string word, int& pos, bool isTitle);		//Khanh
	bool checkOperator(string sen);		//Phat
	TrieNode* searchWord(TrieNode* root, string word, bool isTitle);			//Quang
	bool searchTrie(TrieNode* root, TrieNode* stopwordRoot, vector<int>& pos, int& rankScore, string query);	//Quang
	void merge(vector<int>& vec1, vector<int> vec2);	//Quang
	void releaseTrie(TrieNode*& root);					//Quang
	void match(vector<int>& vec1, vector<int>& vec2, int asterisk);	//Quang
	pair<int,int> findAsterisk(string query);
	void findRange(string query, double& low, double& high);	//Phat
	void searchNumber_DFS(TrieNode* root, double low, double high, double num, int power, vector<int>& pos);	//Quang
	void Synonyms(string word, vector<string>& syno);			//Quang
	void historySuggestion(string query, vector<string>& his);	//Phat
	void historySuggestionInterface(string& query);				//Quang
	void viewHistory(string path);								//Quang
	void updateHistory(string query, string path);			
	int countWord(string sen);	
	void display(File file, string path);						//Quang
	void printDocument(File file,string path);					//Quang

	void Interface();						//Khanh
	void titleInterface(int& choice);		//Khanh
	void readInQuery(string& query);		//Khanh
	void searchInterface(int& choice);		//Khanh
	//void searchProcess(string query, TrieNode* root[100], TrieNode* stopword);//Quang
	void searchProcess(string query, vector<TrieNode*> root, vector<string> listName, TrieNode* stopword);
	string getFileName(int i);				//Quang
};

#endif // !_SEARCH_ENGINE_H_


