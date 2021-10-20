#include <cctype>
#include <iostream>
#include <string>
#include <set>
# include < fstream >
#include <list>
#include "utility.h"


using namespace std;

string encryptor(const string& raw_password);

class Dictionary {
public:
	Dictionary() {
		ifstream dict;
		dict.open(string("dict.txt").c_str());
		for (string line; getline(dict, line);) {
			_words.insert(line);
		}
	}
	bool contains(string const& word) const { return _words.count(to_lower(word)); }
private:
	set<string> _words;
}dictionary;

const string encoded = "27322810313331033910211452912207344136146925461033281533271031012815108114101";


list<string> get_possible_charater_group(const string& current_string) {
	string encrypt_s = "";
	list<string> group;
	bool prev_alpha_space = ((current_string != "") && (current_string.back() == ' ')) ? true : false;
	for (int i = 32; i <= 126; ++i) {
		string temp;
		if (!isalpha(i) && (char)i != ' ') continue;
		temp = current_string + (char)i;
		encrypt_s = encryptor(temp);
		if (encoded.find(encrypt_s) == 0) {
			if ((char)i == ' ' && prev_alpha_space == false) {
				group.clear();
				group.push_back(" ");
				return group;
			}
			group.push_back(string("") + (char)i);
		}
	}
	return group;
}

list<string> sentense_to_words(const string& statement) {
	list<string> result;
	string temp = "";
	for (const char& alpha : statement) {
		if (alpha != ' ') {
			temp += alpha;
		}
		else {
			result.push_back(temp);
			temp = "";
		}
	}
	if (temp != "") {
		result.push_back(temp);
	}
	return result;
}

void rescursive_statement_generator(string statement) {
	if (statement != "" && statement.back() == ' ') {
		if (!dictionary.contains(sentense_to_words(statement).back())) return;
	}
	if (encryptor(statement) == encoded) {
		if (dictionary.contains(sentense_to_words(statement).back())) {
			cout << statement << endl;
		}
		return;
	}

	list<string> result = get_possible_charater_group(statement);

	for (auto i = result.begin(); i != result.end(); ++i) {
		rescursive_statement_generator(statement + *i);
	}
}

void (*statement_generator)(string) = &rescursive_statement_generator;