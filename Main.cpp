#include "Function.h"

int main() {
	searchEngine engine;
	File file;
	ifstream in;
	TrieNode* root;
	string path = "../Data/001.txt";
	engine.inputFile(root, in, path);
	file.name = "../Data/001.txt";
	file.score = 0;

	string query;
	cout << "QUERY: ";
	getline(cin, query);
	cout << "Result: ";
	if (engine.searchTrie(root, nullptr, file.pos, file.score, query))
		cout << "True" << endl;
	else cout << "False" << endl;
	cout << "Score: " << file.score << endl;
	cout << "Position: ";
	for (int i = 0; i < file.pos.size(); ++i)
		cout << file.pos[i] << " ";
	cout << endl;
	cout << "===============================================================================" << endl;
	cout << "001.txt" << endl;
	engine.display(file);

	engine.releaseTrie(root);
	return 0;
}