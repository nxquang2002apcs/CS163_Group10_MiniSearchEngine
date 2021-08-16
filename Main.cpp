#include "Function.h"
#include "ConsoleManagement.h"

int main() {	
	searchEngine engine;
	
	File file;
	ifstream in;
	//TrieNode* root[100];
	vector<TrieNode*> root;
	vector<string> listName;
	TrieNode* stopWord = engine.createNode();
	string path = "../Search Engine-Data/";
	clock_t start, stop;
	start = clock();
	engine.Initialize(root,  listName, stopWord, path);
	stop = clock();
	cout << "Time for indexing 100 files: " << stop - start << endl;;
	
	
	int choice = 1;
	string query;
	int choice2;
	while (choice != 3) {
		engine.titleInterface(choice);
		system("cls");
		if (choice == 1)
		{
			engine.readInQuery(query);
			engine.searchInterface(choice2);

			while (choice2 != 1 && choice2 != 2 && choice2 != 3)
			{
				system("cls");
				gotoXY(15, 2);
				cout << char(218);
				for (int i = 0; i < 86; ++i)
					cout << char(196);
				cout << char(191);

				gotoXY(15, 3); cout << char(179);
				gotoXY(102, 3); cout << char(179);

				gotoXY(15, 4);
				cout << char(192);
				for (int i = 0; i < 86; ++i)
					cout << char(196);
				cout << char(217);

				gotoXY(17, 3);
				cout << "QUERY: " << query;

				engine.searchInterface(choice2);
			}
			if (choice2 == 1) {
				system("cls");
				gotoXY(15, 2);
				cout << char(218);
				for (int i = 0; i < 86; ++i)
					cout << char(196);
				cout << char(191);

				gotoXY(15, 3); cout << char(179);
				gotoXY(102, 3); cout << char(179);

				gotoXY(15, 4);
				cout << char(192);
				for (int i = 0; i < 86; ++i)
					cout << char(196);
				cout << char(217);

				gotoXY(17, 3);
				cout << "QUERY: " << query;
				cout << endl << endl;
				engine.searchProcess(query, root, listName, stopWord);
				system("pause");
			} 
			else if (choice2 == 2) {
				system("cls");
				gotoXY(15, 2);
				cout << char(218);
				for (int i = 0; i < 86; ++i)
					cout << char(196);
				cout << char(191);

				gotoXY(15, 3); cout << char(179);
				gotoXY(102, 3); cout << char(179);

				gotoXY(15, 4);
				cout << char(192);
				for (int i = 0; i < 86; ++i)
					cout << char(196);
				cout << char(217);

				gotoXY(17, 3);
				cout << "QUERY: " << query;

				engine.historySuggestionInterface(query);
				system("cls");
				gotoXY(15, 2);
				cout << char(218);
				for (int i = 0; i < 86; ++i)
					cout << char(196);
				cout << char(191);

				gotoXY(15, 3); cout << char(179);
				gotoXY(102, 3); cout << char(179);

				gotoXY(15, 4);
				cout << char(192);
				for (int i = 0; i < 86; ++i)
					cout << char(196);
				cout << char(217);

				gotoXY(17, 3);
				cout << "QUERY: " << query << endl << endl;

				engine.searchProcess(query, root, listName, stopWord);
				system("pause");
			}
			if (choice2 == 3) continue;
		}
		if (choice == 2) {
			string path = "history.txt";
			engine.viewHistory(path);
		}
	}

	for (int i = 0; i < root.size(); ++i)
		engine.releaseTrie(root[i]);

	return 0;
}