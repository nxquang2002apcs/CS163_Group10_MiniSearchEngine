#include "Function.h"
#include "ConsoleManagement.h"

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
void searchEngine::inputFile(TrieNode*& root, ifstream& file, string path)
{
	file.open(path);
	if (!file.is_open())
	{
		cout << "Can not open file" << endl;
		return;
	}
	else {
		cout << "Open successfully!" << endl;
	}
	root = createNode();

	int pos = 1;
	bool isTitle = true;

	string sen;
	getline(file, sen,'.');
	insertSentence(root, sen, pos, isTitle); // Lấy vào dòng đầu tiên là tiêu đề
	isTitle = false;

	string sen1, sen2;
	while (!file.eof())						// Insert vào các câu tiếp theo
	{
		getline(file, sen1, '.');
		while (isNumber(sen1.back()))
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
	if(cur->isTitle == false)
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
		if (word == "s") continue;
		insertWord(root, word, pos, isTitle);
	}
} 
void searchEngine::releaseTrie(TrieNode*& root) {
	if (root == nullptr) return;
	for (int i = 0; i < 42; ++i) {
		releaseTrie(root->children[i]);
	}
	delete root;
	root = nullptr;
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
		else if (isTitle == true && pCur->isTitle == false) return nullptr;
		else return pCur;
	}
	return nullptr;
}
bool searchEngine::searchTrie(TrieNode* root, TrieNode* stopwordRoot, vector<int>& pos, int& rankScore, string query) {
	stringstream sstream;
	sstream << query;
	string word;
	bool isTitle = false;	//to activate intitle:
	while (sstream >> word) {
		TrieNode* search;
		if (word[0] == '"') {
			vector<vector<int>> matchPos;
			int len = 0;
			bool stop = false;
			string nextWord = word.substr(1);
			if (nextWord.back() == '"') {
				nextWord.erase(nextWord.end() - 1);
				stop = true;
			}

			search = searchWord(root, nextWord, isTitle);
			if (!search) return false;
			else {
				matchPos.push_back(search->pos);
				len++;
				while (!stop && sstream >> nextWord) {
					if (nextWord == "") {
						stop = true;
						break;
					}
					else if (nextWord.back() == '"') {
						nextWord.erase(nextWord.end() - 1);
						stop = true;
					}
					search = searchWord(root, nextWord, isTitle);
					if (!search) return false;
					matchPos.push_back(search->pos);
					len++;
				}
			}
			if (stop) {
				if (len <= 1) {
					merge(pos, matchPos[0]);
					rankScore += matchPos[0].size();
				}
				else {
					for (int i = 0; i < len-1; ++i) 
						match(matchPos[i], matchPos[i + 1], 0);
					for (int i = len - 1; i > 0; --i) 
						match(matchPos[i-1], matchPos[i], 0);
					for (int i = 0; i < len; ++i) {
						if (matchPos[i].empty()) {
							rankScore = 0;
							return false;
						}
						merge(pos, matchPos[i]);
						rankScore += matchPos[i].size();
					}
				}
			}
			continue;
		}
		if (word.substr(0, 8) == "intitle:") {
			string nextWord = word.substr(8);
			search = searchWord(root, nextWord, true);
			if (!search) return false;
			else {
				rankScore += search->pos.size();
				merge(pos, search->pos);
				isTitle = true;
			}
			/*
			while (sstream >> word) {
				search = searchWord(root, word, true);
				if (search == nullptr) return false;
				rankScore += search->pos.size();
				merge(pos, search->pos);
			}*/
			continue;
		}
		pair<int,int> asterisk = findAsterisk(query);	
		if(asterisk.second != 0){									//Number of wildcards != 0
			vector<vector<int>> matchPos;
			int len = 0;
			if (word != "*") {
				search = searchWord(root, word, isTitle);
				if (!search) return false;
				else {
					int pivot = 0; //to note where the first "*" appear
					matchPos.push_back(search->pos);
					len++;
					while (sstream >> word) {
						if (word == "*") continue;
						search = searchWord(root, word, isTitle);
						if (!search) {
							rankScore = 0;
							return false;
						}
						else {
							matchPos.push_back(search->pos);
							len++;
						}
					}
					if (len == 1) {
						merge(pos, matchPos[0]);
						rankScore += matchPos[0].size();
					}
					else {
						for (int i = 0; i < len - 1; ++i)
							if (i + 1 == asterisk.first)
								match(matchPos[i], matchPos[i + 1], asterisk.second);
							else match(matchPos[i], matchPos[i + 1], 0);
						for (int i = len - 1; i > 0; --i)
							if (i == asterisk.first)
								match(matchPos[i - 1], matchPos[i], asterisk.second);
							else match(matchPos[i - 1], matchPos[i], 0);
						for (int i = 0; i < len; ++i) {
							if (matchPos[i].empty()) {
								rankScore = 0;
								return false;
							}
							merge(pos, matchPos[i]);
							rankScore += matchPos[i].size();
						}
					}
				}
			}
			continue;
		}
		if (word[0] == '-') {
			string nextWord = word.substr(1);
			if (searchWord(root, nextWord, isTitle) != nullptr) return false;	 //University -science => if find "science" in Trie => false
			continue;
		}
		if (word == "OR") {
			sstream >> word;
			search = searchWord(root, word, isTitle);
			if (search) {
				merge(pos, search->pos);
				rankScore += search->pos.size();
			}
			continue;
		} 
		/*
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
		}*/
		if (word == "AND") continue;			//default is AND, so don't need to check this operator
		//if (searchWord(stopwordRoot, word, false) != nullptr) continue;
		if (word.find("..") != string::npos) {
			if (word[0] != '$' && !isNumber(word[0]))
				return false;
			double low = 0.0, high = 0.0;
			findRange(word, low, high);
			if (low == 0 && high == 0) return false;
			vector<int> numPos;
			double num = 0;
			if (word[0] == '$') {
				if (!root->children[40]) return false;
				searchNumber_DFS(root->children[40], low, high, num, 1, numPos);
			}
			else searchNumber_DFS(root, low, high, num, 1, numPos);
			if (numPos.empty()) return false;
			else {
				merge(pos, numPos);
				rankScore += numPos.size();
			}
			continue;
		}
		if (word.substr(0, 9) == "filetype:") {
			string extension = word.substr(9);
			if (extension != "txt")
				return false;
			else continue;
		}
		if (word[0] == '~') {
			vector<string> syno;
			Synonyms(word.substr(1), syno);
			for (int i = 0; i < syno.size(); ++i) {
				search = searchWord(root, syno[i], isTitle);
				if (search) {
					merge(pos, search->pos);
					rankScore += search->pos.size();
				}
			}
			continue;
		}
		search = searchWord(root, word, isTitle);
		if (search) {							//Nếu tìm thấy từ trong Trie
			rankScore += search->pos.size();
			merge(pos, search->pos);
		}
		else {									
			bool find = false;
			while (sstream >> word) {
				if (word == "OR") {				//Nếu từ đó không được tìm thấy mà có OR ở kế bên thì tiếp tục xét từ tiếp theo
					sstream >> word;			//Ví dụ: slknvsknejpojwef OR cat
					search = searchWord(root, word, isTitle);
					if (search == nullptr)		//Nếu từ tiếp theo vẫn không tìm thấy thì vẫn tiếp tục kiểm tra OR có ở tiếp theo hay không
						continue;	
					else {						
						rankScore += search->pos.size();
						merge(pos, search->pos);
						find = true;			//Có ít nhất một từ vẫn được tìm thấy
					}
				}
				else {
					if (find) {
						search = searchWord(root, word, isTitle);
						if (search) {
							rankScore += search->pos.size();
							merge(pos, search->pos);
						}
						else find = false;
					}
					else {
						rankScore = 0;
						return false;
					}
				}
			}
			if (find == false) {				//Trong tất cả những từ vô nghĩa, có ít nhất một từ có thể tìm thấy
				rankScore = 0;					//Ví dụ: oigwoijowijgoijwgi OR phone OR viosnionione
				return false;
			}	
		}										
	}
	return true;
}
//=========================================================================================================================
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
void searchEngine::match(vector<int>& vec1, vector<int>& vec2, int asterisk) {
	if (vec1.empty() || vec2.empty()) return;
	vector<int> res1, res2;
	int i = 0, j = 0;
	while (i < vec1.size() && j < vec2.size()) {
		if (vec1[i] + asterisk + 1 < vec2[j]) i++;
		else if (vec1[i] + asterisk + 1 > vec2[j]) j++;
		else {
			res1.push_back(vec1[i++]);
			res2.push_back(vec2[j++]);
		}
	}
	vec1.clear();
	vec2.clear();
	vec1 = res1;
	vec2 = res2;
}
pair<int,int> searchEngine::findAsterisk(string query) {
	stringstream ss;
	int count = 0;
	ss << query;
	string word;
	int index = 0;
	bool check = false;
	while (ss >> word) {
		if (word == "*") {
			count++;
			check = true;
		}
		if (!check) index++;		//If '*' appear, don't need to find the index of "*" anymore
	}
	
	if (count == 0) index = -1;
	return { index, count };		//The first is the index where '*' appear, and the second is the number of '*'
}
//=========================================================================================================================
void searchEngine::findRange(string query, double& low, double& high) {
	int start, end;
	size_t found = query.find("..");
	size_t check = query.find("..$");
	// high 
	if (check != string::npos)
		found += 3;
	else
		found += 2;
	end = found;
	while (query[end] != 32 && query[end]) {
		end++;
	}
	string num1 = query.substr(found, end - found);
	stringstream ss1, ss2;
	ss1 << num1;
	ss1 >> high;
	// low
	if (check != string::npos)
		found -= 3;
	else
		found -= 2;
	start = found - 1;
	while (query[start] != '$' && query[start] != 32 && start)
		start--;
	if (query[start] == '$' || query[start] == 32)
		start += 1;

	string num2 = query.substr(start, found - start);
	ss2 << num2;
	ss2 >> low;
}
void searchEngine::searchNumber_DFS(TrieNode* root, double low, double high, double num, int power, vector<int>& pos) {
 	if (num > high) return;
	else if (num >= low && num <= high && root->isEndOfWord == true) {
		merge(pos, root->pos);
	}
	int temp;
	for (int i = 0; i <= 9; ++i) {
		temp = num;
		if (root->children[i]) {
			if (power == 1)
				temp = temp * 10 + i;
			else {
				temp += i * pow(10, power);
				power--;
			}
			searchNumber_DFS(root->children[i], low, high, temp,power, pos);
		}
	}
	if (root->children[37]) {
		temp = num;
		power = -1;
		searchNumber_DFS(root->children[37], low, high, temp, power, pos);
	}
}
//=========================================================================================================================
void searchEngine::Synonyms(string key, vector<string>& syno) {
	syno.push_back(key);
	ifstream in;
	in.open("Gutenberg.txt");
	if (!in.is_open()) return;
	string sen, word;
	while (!in.eof()) {
		getline(in, sen);
		stringstream sstream;
		sstream << sen;
		sstream >> word;
		if (word != "KEY:") continue;
		else {
			sstream >> word;
			if (word[0] >= 65 && word[0] <= 90) word[0] += 32;
			if (!isAlphabet(word.back())) word.pop_back();
			if (word != key) continue;
			else {
				getline(in, sen);
				while (sen.back() == ',') {
					string nextSen;
					getline(in, nextSen);
					sen += ' ' + nextSen;
				}
				sstream.clear();
				sstream << sen;
				sstream >> word;
				if (word != "SYN:") continue;
				while (sstream >> word) {
					if (word == "[See") {
						sstream >> word;
						while (isAlphabet(word.back())) 
							word.pop_back();
						if (word != "") {
							for (int i = 0; i < word.size(); ++i)
								word[i] += 32;
						}
						continue;
					}
					if (!isAlphabet(word[0])) continue;
					else if (word[0] >= 65 && word[0] <= 90) word[0] += 32;
					if (!isAlphabet(word.back())) word.pop_back();
					syno.push_back(word);
				}
			}
		}
	}
}
//=========================================================================================================================
int searchEngine::countWord(string sen) {	//Function to count the number of words in a sentence
	stringstream ss;
	ss << sen;
	string word;
	int count = 0;
	while (ss >> word)
		count++;
	return count;
}
void searchEngine::display(File file) {
	if (file.score == 0 || file.pos.empty())
		return;
	ifstream in;
	in.open(file.name);
	if (!in.is_open()) {
		cout << "Cannot open file!" << endl;
		return;
	}
	string sen, sen2, word;
	int count = 1, idxOfPos = 0, totalLength = 0;
	getline(in, sen, '.');	//title

	int length = countWord(sen);
	totalLength += length;
	if (totalLength >= file.pos[idxOfPos]) {
		stringstream sstream;
		sstream << sen;
		while (sstream >> word) {
			if (idxOfPos < file.pos.size() && count == file.pos[idxOfPos]) {
				TextColor(14);
				cout << word << " ";
				TextColor(15);
				idxOfPos++;
			}
			else cout << word << " ";
			count++;
		}
	}
	else {
		cout << sen;
		count += length;
	}
	cout << endl << endl;
	while (!in.eof() && idxOfPos < file.pos.size()){
		getline(in, sen, '.');
		while (isNumber(sen.back())){
			if (!in.eof()){
				getline(in, sen2, '.');
				if (isNumber(sen2[0]))
					sen = sen + "." + sen2;
				else {
					sen = sen + " " + sen2;
				}
			}
		}
		length = countWord(sen);
		totalLength += length;
		if (totalLength < file.pos[idxOfPos]) {
			count += length;
			continue;
		}
		else {
			cout << "...";
			stringstream sstream;
			sstream << sen;
			while (sstream >> word) {
				if (idxOfPos < file.pos.size() && count == file.pos[idxOfPos]) {
					TextColor(14);
					cout << word << " ";
					TextColor(15);
					count++;
					idxOfPos++;
				}
				else{
					cout << word << " ";
					count++;
				}
			}
			cout << "..." << endl;
		}
	}
	in.close();
}

//========================================Khanh ghi lai ham display=======================================================================

bool searchEngine::checkAppear(const vector<string>& inQuery, string s)
{
	for (int i = 0; i < inQuery.size(); ++i)
		if (s == inQuery[i])
			return true;
	return false;
}

void searchEngine::display(File file)
{
	if (file.score == 0 || file.pos.empty())
		return;
	ifstream in;
	in.open(file.name);
	if (!in.is_open())
	{
		cout << "Cannot open file!" << endl;
		return;
	}
	vector<string> inQuery;
	string sen, sen2, word;
	int count = 1, idxOfPos = 0, totalLength = 0;
	getline(in, sen, '.');	//title

	int length = countWord(sen);
	totalLength += length;
	if (totalLength >= file.pos[idxOfPos])
	{
		stringstream sstream;
		sstream << sen;
		while (sstream >> word)
		{
			if (idxOfPos < file.pos.size() && count == file.pos[idxOfPos]) { // count la bien dem vi tri tu trong file
				inQuery.push_back(word);
				TextColor(14);
				cout << word << " ";
				TextColor(15);
				idxOfPos++;  // la index cua vector pos
			}
			else cout << word << " ";
			count++;
		}
	}
	else {
		cout << sen;
		count += length;
	}

	int soCau = 0;

	cout << endl << endl;
	while (!in.eof() && idxOfPos < file.pos.size())
	{ // Van con cai de in
		getline(in, sen, '.');
		while (isNumber(sen[sen.length() - 1]))
		{
			if (!in.eof())
			{
				getline(in, sen2, '.');
				if (isNumber(sen2[0]))
					sen = sen + "." + sen2;
				else {
					sen = sen + " " + sen2;
				}
			}
		}
		length = countWord(sen);
		totalLength += length;
		if (totalLength < file.pos[idxOfPos] || support(sen, file, idxOfPos, count, inQuery) == false)
		{
			count += length;
			continue;
		}

		else  // else nay xay ra chinh la trong cau da co chu, va cau can duoc in
		{
			++soCau;
			cout << "...";
			stringstream sstream;
			sstream << sen;
			while (sstream >> word)
			{
				if (idxOfPos < file.pos.size() && count == file.pos[idxOfPos])
				{
					inQuery.push_back(word);
					TextColor(14);
					cout << word << " ";
					TextColor(15);
					count++;
					idxOfPos++;
				}
				else
				{
					cout << word << " ";
					count++;
				}
			}
			cout << "..." << endl;
		}
		if (soCau == 3)
			break;
	}
	in.close();
}

// Ham xu ly cau co 1 tu da xuat hien
bool searchEngine::support(string sen, File file, int idxOfPos, int count, const vector<string>& inQuery)
{
	stringstream sstream;
	sstream << sen;
	string word;

	while (sstream >> word)
	{
		if (idxOfPos < file.pos.size() && count == file.pos[idxOfPos])
			if (checkAppear(inQuery, word) == false) // Chua xuat hien
				return true;
	}

	return false;
}