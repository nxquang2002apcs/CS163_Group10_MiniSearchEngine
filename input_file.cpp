#include "function.h"

int searchEngine::findIndex(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'z') return int(c) - 87;
	if (c == ' ') return 36;
	if (c >= '#' && c <= '%') return int(c) + 2;
	return int(c) - 5;
}

TrieNode* searchEngine::createNode()
{
	TrieNode* p = new TrieNode;
	p->isTitle = p->isEndOfWord = false;

	for (int i = 0; i < 41; ++i)
		p->children[i] = nullptr;

	return p;
}

void searchEngine::inputFile(TrieNode*& root, ifstream& file)
{
	file.open("text.txt");
	if (!file.is_open())
	{
		cout << "Can not open file" << endl;
		return;
	}

	if (root == nullptr)
		root = createNode();
	int pos = 1;
	bool isTitle = true;
	
	string sen;
	getline(file, sen);
	insertSentence(root, sen, pos, isTitle); // Lấy vào dòng đầu tiên là tiêu đề
	isTitle = false;

	string sen1, sen2;
	int flag;
	while (!file.eof())						// Insert vào các câu tiếp theo
	{
		getline(file, sen1, '.');
		while (isNumber(sen1[sen1.length() - 1]))
		{
			if (!file.eof())
			{
				getline(file, sen2, '.');
				flag = 1;
			}
			if (isNumber(sen2[0]))
				sen1 = sen1 + "." + sen2;
			else
				break;

		}
	
		insertSentence(root, sen1, pos, isTitle);
		if (flag = 1)
		{
			insertSentence(root, sen2, pos, isTitle);
			flag = 0;
		}

	}
}

void searchEngine::insertWord(TrieNode*& root, string word, int& pos, bool isTitle)
{
	int len = word.length();
	int index;

	TrieNode* cur = root;

	for (int i = 0; i < len; ++i)
	{
		index = findIndex(word[i]);
		if (cur->children[i] == nullptr)
			cur->children[i] = createNode();
		
		cur = cur->children[i];
	}

	cur->isEndOfWord = true;
	cur->isTitle = isTitle;
	cur->pos.push_back(pos);
	++pos;
}


void searchEngine::insertSentence(TrieNode*& root, string sen, int& pos, bool isTitle)
{
	sen = filter(sen);
	
	stringstream spliter;
	spliter << sen;
	string word;
	while (!spliter.eof())
	{
		spliter >> word;
		insertWord(root, word, pos, isTitle);
	}
}




