#include <cctype>
#include <iostream>
#include <string>
#include <set>
# include <fstream>
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

	list<string> result = get_possible_charater_group(statement, encoded);

	for (auto i = result.begin(); i != result.end(); ++i) {
		rescursive_statement_generator(statement + *i);
	}
}

void (*statement_generator)(string) = &rescursive_statement_generator;