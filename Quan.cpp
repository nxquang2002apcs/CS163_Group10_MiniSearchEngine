#include "function.h"

bool searchEngine::isNumber(char key)
{
	return key >= 48 && key <= 57;
}

bool searchEngine::isAlphabet(char key)
{
	return (key >= 65 && key <= 90) || (key >= 97 && key <= 122);
}

string searchEngine::intToString(int num)
{
	stringstream ss;
	ss << num;
	string out_string = ss.str();
	return out_string;
}

string searchEngine::floatToString(float num)
{
	stringstream ss;
	ss << num;
	string out_string = ss.str();
	return out_string;
}

void searchEngine::insertStopWord(TrieNode*& stopword, string word)
{
	int len = word.length();
	int index;

	TrieNode* cur = stopword;

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
}

