#include "function.h"

bool isSubstring(string s1, string s2)
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

bool checkOperator(string sen) {
	if (isSubstring("AND", sen) || isSubstring("OR", sen) || isSubstring("-", sen) || isSubstring("+", sen) )
		return true;
	if (isSubstring("filetype", sen) || isSubstring("intitle", sen) || isSubstring("~", sen))
		return true;
	if (isSubstring("#", sen) || isSubstring("*", sen) || isSubstring("..", sen))
		return true;
	return false;
}

