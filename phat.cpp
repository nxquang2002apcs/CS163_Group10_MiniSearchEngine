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
	int start, end;
	size_t found = query.find("..");
	size_t check = query.find("..$");
	// high 
	if (check != string::npos)
		found += 3;
	else 
		found += 2;
	end = found;
	while(query[end] != 32 && query[end]){
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
	while(query[start] != '$' && query[start] != 32 && start)
		start--;
	if(query[start] == '$' || query[start] == 32)
		start += 1;
	
	string num2 = query.substr(start, found - start);
	ss2 << num2;
	ss2 >> low;
	cout << "low: "<< low <<endl;
	cout << "high: " << high;
}

void deleteFile(ofstream& ofs, string path) {
	ofs.open(path);
	ofs.close();
}




