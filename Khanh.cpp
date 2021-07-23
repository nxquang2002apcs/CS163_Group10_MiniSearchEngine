#include "function.h"

void searchEngine::inputFile(TrieNode*& root, ifstream& file)
{
	file.open("input.txt");
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
	int flag = 0;
	while (!file.eof())						// Insert vào các câu tiếp theo
	{
		getline(file, sen1, '.');
		while (isNumber(sen1[sen1.length() - 1]))
		{
			if (!file.eof())
				getline(file, sen2, '.');
			if (isNumber(sen2[0]))
				sen1 = sen1 + "." + sen2;
			else {
				flag = 1;
				break;
			}
		}
		insertSentence(root, sen1, pos, isTitle);
		if (flag == 1)
		{
			insertSentence(root, sen2, pos, isTitle);
			flag = 0;
		}
	}
	file.close();
}

void searchEngine::insertWord(TrieNode* root, string word, int& pos, bool isTitle)
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
	cur->isTitle = isTitle;
	cur->pos.push_back(pos);
	++pos;
}

void searchEngine::insertSentence(TrieNode* root, string sen, int& pos, bool isTitle)
{
	string sen1 = filter(sen);

	stringstream spliter;
	spliter << sen1;
	string word;
	while (!spliter.eof())
	{
		spliter >> word;
		insertWord(root, word, pos, isTitle);
	}
}
