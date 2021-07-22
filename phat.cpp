#include "function.h"

bool searchEngine::isAccepted(char key) {
	// lowercase and numbers
	if ((97 <= key && key <= 122) || (48 <= key && key <= 57)) 
		return true;	
	// uppercase -> lowercase
	if (65 <= key && key <= 90) {
		key += 32;
		return true;
	}
	// enter (\n), single quote (') -> space
	if (key == '\n' || key == 39 ) {
		key = 32;
		return true;
	}
	// special characters
	if ((35 <= key && key <=37) || key == 45 || key == 32)
		return true;
	return false;
}

int searchEngine::convert(char key) {
	if (key >= 48 && key <= 57){
		key -= 48;
		return key;
	}
	else if (97 <= key && key <= 122){
		key -= 87;
		return key;
	}
	else if (65 <= key && key <= 90) {
		key -= 55;
		return key;
	}
	switch (key) {
	case 32:
		key = 36;
		break;
	case 46:
		key = 37;
		break;
	case 35:
		key = 38;
		break;	
	case 37:
		key = 39;
		break;
	case 36:
		key = 40;
		break;
	case 45:
		key = 41;
		break;
	}
	return key;
}

string searchEngine::filter(string sen) {
	string res;
	for (int i = 0; i < sen.length(); i++) {
		if(isAccepted(sen[i]))
			res.push_back(sen[i]);
		else if(sen[i] == 46) {
			if (48 <= sen[i-1] && sen[i-1] <= 57 && 48 <= sen[i+1] && sen[i+1] <= 57)
				res.push_back(sen[i]);
			else 
				return res;
		}
	}
	return res;
}


