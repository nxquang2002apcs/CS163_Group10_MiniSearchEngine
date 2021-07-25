#include "function.h"


TrieNode* searchEngine::createNode()
{
	TrieNode* p = new TrieNode;
	p->isTitle = p->isEndOfWord = false;

	for (int i = 0; i < 42; ++i)
		p->children[i] = nullptr;

	return p;
}
void searchEngine::Initialize(TrieNode**& root, int n) {
	root = new TrieNode*[n];
	for (int i = 0; i < n; ++i) {
		root[i] = createNode();
	}
}
//===========================================================
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
//===========================================================
bool searchEngine::isAccepted(char& key) {
	// lowercase and numbers
	if ((97 <= key && key <= 122) || (48 <= key && key <= 57))
		return true;
	// uppercase -> lowercase
	if (65 <= key && key <= 90) {
		key += 32;
		return true;
	}
	// enter (\n), single quote (') -> space
	if (key == '\n' || key == 39) {
		key = 32;
		return true;
	}
	// special characters
	if ((35 <= key && key <= 37) || key == 45 || key == 32)
		return true;
	return false;
}

int searchEngine::convert(char key) {
	if (key >= 48 && key <= 57) {
		key -= 48;
		return key;
	}
	else if (97 <= key && key <= 122) {
		key -= 87;
		return key;
	}
	else if (65 <= key && key <= 90) {
		key -= 55;
		return key;
	}
	switch (key) {
	case 32:
		return 36;
		break;
	case 46:
		return 37;
		break;
	case 35:
		return 38;
		break;
	case 37:
		return 39;
		break;
	case 36:
		return 40;
		break;
	case 45:
		return 41;
		break;
	}
	return -1;
}
string searchEngine::filter(string sen) {
	string res;
	for (int i = 0; i < sen.length(); i++) {
		if (isAccepted(sen[i]))
			res.push_back(sen[i]);
		else if (sen[i] == 46) {
			if (48 <= sen[i - 1] && sen[i - 1] <= 57 && 48 <= sen[i + 1] && sen[i + 1] <= 57)
				res.push_back(sen[i]);
			else
				return res;
		}
	}
	return res;
}
//===========================================================
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
	while (spliter >> word)
	{
		insertWord(root, word, pos, isTitle);
	}
}
//===========================================================
TrieNode* searchEngine::searchWord(TrieNode* root, string word, bool isTitle) {
	if (!root) return nullptr;
	TrieNode* pCur = root;
	for (int i = 0; i < word.length(); ++i) {
		int u = convert(word[i]);
		if (u == -1) continue;
		if (pCur->children[u] == nullptr) return nullptr;
		else pCur = pCur->children[u];
	}
	if (pCur != nullptr) {
		if (pCur->isEndOfWord == false)	return nullptr;
		else if (pCur->isTitle != isTitle) return nullptr;
		else return pCur;
	}
	return nullptr;
}
bool searchEngine::searchTrie(TrieNode* root, TrieNode* stopwordRoot, vector<int> pos, int rankScore, string query) {
	stringstream sstream;
	sstream << query;
	string word;
	while (sstream >> word) {
		TrieNode* search;
		if (word[0] = '-') {
			string temp = word.substr(1);
			if (searchWord(root, temp, false) != nullptr) return false;	 //University -science => if find "science" in Trie => false
			continue;
		}
		if (word == "OR") {
			sstream >> word;
			search = searchWord(root, word, false);
			if (search) {
				merge(pos, search->pos);
				rankScore += search->pos.size();
			}
			continue;
		}
		if (word == "AND") {
			if (pos.size() == 0) return false;		//A AND B but cannot find A => false
			sstream >> word;
			search = searchWord(root, word, false);
			if (!search) return false;				//A AND B but cannot find B => false		
			else {
				merge(pos, search->pos);
				rankScore += search->pos.size();
			}
			continue;
		}
		if (searchWord(stopwordRoot, word, false) != nullptr) continue;
	}
}
void searchEngine::merge(vector<int>& vec1, vector<int> vec2) {		//Function to merge the two vector 
	if (vec1.size() == 0) { vec1 = vec2; return; }
	if (vec2.size() == 0) return;
	vector<int> res;
	int i = 0, j = 0;
	while (i < vec1.size() && j < vec2.size()) {
		if (vec1[i] < vec2[j]) {
			res.push_back(vec1[i]);
			i++;
		}
		else if (vec2[j] < vec1[i]) {
			res.push_back(vec2[j]);
			j++;
		}
		else {
			res.push_back(vec1[i]);
			i++;
			j++;
		}
	}
	for (; i < vec1.size(); ++i) res.push_back(vec1[i]);
	for (; j < vec2.size(); ++j) res.push_back(vec2[j]);
	vec1.clear();
	vec1 = res;
}
