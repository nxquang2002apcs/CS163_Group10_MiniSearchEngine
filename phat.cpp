#include "function.h"

bool searchEngine::isSubstring(string s1, string s2)
{
    int M = s1.length();
    int N = s2.length();
 
    for (int i = 0; i <= N - M; i++) {
        int j;
 
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
 
        if (j == M)
            return true;
    }
    return false;
}

bool searchEngine::checkOperator(string sen) {
	if (isSubstring("AND", sen) || isSubstring("OR", sen) || isSubstring("-", sen) || isSubstring("+", sen) )
		return true;
	if (isSubstring("filetype", sen) || isSubstring("intitle", sen) || isSubstring("~", sen))
		return true;
	if (isSubstring("#", sen) || isSubstring("*", sen) || isSubstring("..", sen))
		return true;
	return false;
}

void searchEngine::findRange(string query, double& low, double& high) {
	size_t pos1 = query.find('$') + 1;
	size_t pos2 = query.find("..$");
	string num1 = query.substr(pos1, pos2 - pos1);
	pos2 += 3;
	stringstream ss1, ss2;
	ss1 << num1;
	ss1 >> low;
	size_t pos3 = pos2 + 1;
	while (query[pos3] >= 48 && query[pos3] <= 57) 
		pos3++;
	string num2 = query.substr(pos2, pos3 - pos2);
	ss2 << num2;
	ss2 >> high;
}
void deleteFile(ofstream& ofs, string path) {
	ofs.open(path);
	ofs.close();
}




