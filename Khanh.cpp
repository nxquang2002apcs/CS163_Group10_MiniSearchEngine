#include "function.h"

void searchEngine::inputFile(TrieNode*& root, ifstream& file, string path)
{
	file.open(path);
	if (!file.is_open())
	{
		cout << "Can not open file" << endl;
		return;
	}

	root = createNode();

	int pos = 1;
	bool isTitle = true;

	string sen;
	getline(file, sen);
	insertSentence(root, sen, pos, isTitle); // Lấy vào dòng đầu tiên là tiêu đề
	isTitle = false;

	string sen1, sen2;
	while (!file.eof())						// Insert vào các câu tiếp theo
	{
		getline(file, sen1, '.');
		while (isNumber(sen1[sen1.length() - 1]))
		{
			if (!file.eof())
			{
				getline(file, sen2, '.');
				if (isNumber(sen2[0]))
					sen1 = sen1 + "." + sen2;
				else {
					insertSentence(root, sen1, pos, isTitle);
					sen1 = sen2;
				}
			}
		}
		insertSentence(root, sen1, pos, isTitle);
	}
	file.close();
}

void searchEngine::insertWord(TrieNode*& root, string word, int& pos, bool isTitle)
{
	int len = word.length();
	int index;

	TrieNode* cur = root;

	for (int i = 0; i < len; ++i)
	{
		index = convert(word[i]);
		if (index == -1)
			continue;
		if (cur->children[index] == nullptr)
			cur->children[index] = createNode();
		cur = cur->children[index];
	}

	cur->isEndOfWord = true;
	if (cur->isTitle == false)
		cur->isTitle = isTitle;
	cur->pos.push_back(pos);
	++pos;
}

void searchEngine::insertSentence(TrieNode*& root, string sen, int& pos, bool isTitle)
{
	string sen1 = filter(sen);

	stringstream spliter;
	spliter << sen1;
	string word;
	while (spliter >> word)
	{
		insertWord(root, word, pos, isTitle);
	}
}

void searchEngine::insertListOfFile(TrieNode**& list, ifstream& in)
{
	list = new TrieNode * [100];
	for (int i = 0; i < 100; ++i)
		list[i] = nullptr;
	
	string path = "Data";						// Ví dụ các văn bản đặt trong folder Data, có tên là text1, text2,...

	for (int i = 0; i < 100; ++i)
	{
		path += "\\text" + intToString(i + 1) + ".txt";
		inputFile(list[i], in, path);
	}
}

void tieude(int& choice)
{
	choice = 3;

	while (choice != 1 && choice != 2)
	{
		system("cls");
		TextColor(10);
		gotoXY(5, 5);
		cout << "  SSSSSSS EEEEEEE     AAA     RRRRRRR  CCCCCCC HH    HH     EEEEEEE NNN   NN  GGGGGGG II NNN   NN EEEEEEE";
		gotoXY(5, 6);
		cout << "SSSSSSSS  EE         AA AA    RR  RR  CCCCCCCC HH    HH     EE      NNNN  NN GG       II NNNN  NN EE";
		gotoXY(5, 7);
		cout << "   SSS    EEEEEEE   AAAAAAA   RRRRR   CC       HHHHHHHH     EEEEEEE NN NN NN GG  GGGG II NN NN NN EEEEEEE";
		gotoXY(5, 8);
		cout << "  SSSSSSS EE       AA     AA  RR  RR  CCCCCCCC HH    HH     EE      NN  NNNN GG    GG II NN  NNNN EE";
		gotoXY(5, 9);
		cout << "SSSSSSSS  EEEEEEE AA       AA RR   RR  CCCCCCC HH    HH     EEEEEEE NN   NNN  GGGGGGG II NN   NNN EEEEEEE";

		gotoXY(35, 12);
		cout << char(201);
		for (int i = 0; i < 40; ++i)
			cout << char(205);
		cout << char(187);



		gotoXY(35, 13); cout << char(186);
		gotoXY(76, 13); cout << char(186);

		gotoXY(35, 14);
		cout << char(186) << "         1. Search";
		gotoXY(76, 14); cout << char(186);

		gotoXY(35, 15); cout << char(186);
		gotoXY(76, 15); cout << char(186);

		gotoXY(35, 16);
		cout << char(186) << "         2. View History";
		gotoXY(76, 16); cout << char(186);

		gotoXY(35, 17); cout << char(186);
		gotoXY(76, 17); cout << char(186);

		gotoXY(35, 18);
		cout << char(200);
		for (int i = 0; i < 40; ++i)
			cout << char(205);
		cout << char(188);

		gotoXY(30, 20);
		cout << "Enter your choice (1 or 2): ";
		cin >> choice;

	}
}

void search(int& choice)				// Khi lựa chọn là search thì gọi hàm này để cho chọn tiếp là search hay based on history suggestion
{
	choice = 3;

	while (choice != 1 && choice != 2)
	{
		system("cls");
		gotoXY(35, 0);
		cout << char(201);
		for (int i = 0; i < 40; ++i)
			cout << char(205);
		cout << char(187);

		gotoXY(35, 1); cout << char(186);
		gotoXY(76, 1); cout << char(186);

		gotoXY(35, 2);
		cout << char(186) << " 1. Search";
		gotoXY(76, 2); cout << char(186);

		gotoXY(35, 3); cout << char(186);
		gotoXY(76, 3); cout << char(186);

		gotoXY(35, 4);
		cout << char(186) << " 2. Search based on history suggestion";
		gotoXY(76, 4); cout << char(186);

		gotoXY(35, 5); cout << char(186);
		gotoXY(76, 5); cout << char(186);

		gotoXY(35, 6);
		cout << char(200);
		for (int i = 0; i < 40; ++i)
			cout << char(205);
		cout << char(188);

		gotoXY(30, 8);
		cout << "Enter your choice (1 or 2): ";
		cin >> choice;
	}
}

void readInQuery(string& query)
{
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
	cout << "Enter query: ";
	cin.ignore();
	gotoXY(30, 3);  getline(cin, query);
}
