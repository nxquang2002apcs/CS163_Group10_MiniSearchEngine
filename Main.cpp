#include "Function.h"

int main() {
	searchEngine engine;
	
	ifstream file;
	TrieNode* root;
	string path = "../Data/001.txt";
	engine.inputFile(root, file, path);

	string query;
	cout << "QUERY: ";
	getline(cin, query);
	cout << "Result: ";
	vector<int>pos;
	int score = 0;
	if (engine.searchTrie(root, nullptr, pos, score, query))
		cout << "True" << endl;
	else cout << "False" << endl;
	cout << score << endl;

	engine.releaseTrie(root);
	return 0;
}