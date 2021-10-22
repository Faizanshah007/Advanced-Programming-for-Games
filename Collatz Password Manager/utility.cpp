#include <list>
#include <iostream>
#include<chrono>

#include "utility.h"

using namespace std;

function<bool(const string& s)> is_printable_ASCII_string = [](const string& s) {
	for (const auto& ch : s) {
		if (ch < 32 || ch > 126) {
			return false;
		}
	}
	return true;
};


int collatz_conjecture(const int& ch) {

	int result = ch, iter_count = 0;

	while (result != 1) {
		if (result % 2 == 0) {
			result /= 2;
		}
		else if (result % 2 == 1) {
			result = (3 * result) + 1;
		}
		++iter_count;
	}
	return iter_count;
}

string to_lower(const string& s) {
	string result = "";
	for (const char& ch : s) {
		result += tolower(ch);
	}
	return result;
}

string encryptor(const string& raw_password) {
	string encrypted_password = "";
	int offset = 0;
	for (const unsigned char& ch : raw_password) {
		offset = collatz_conjecture(ch + offset);
		encrypted_password += to_string(offset);
	}
	return encrypted_password;
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

list<string> get_possible_charater_group(const string& current_string, const string& encoded) {
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

list<string> get_possible_charater_group_small_alpha_rep(const string& current_string, const string& encoded) {
	string encrypt_s = "";
	list<string> group;

	for (int i = 'a'; i <= 'z'; ++i) {

		string temp;

		temp = current_string + (char)i;
		encrypt_s = encryptor(temp);
		if (encoded.find(encrypt_s) == 0) {
			group.push_back(string("") + (char)i);
		}
	}
	return group;
}

bool rescursive_decoder_small_alpha(string statement, const string& encoded_str) {

	if (encryptor(statement) == encoded_str) {
		if (show_decrypted_pass) {
			cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << statement << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		return true;
	}

	list<string> result = get_possible_charater_group_small_alpha_rep(statement, encoded_str);

	for (auto i = result.begin(); i != result.end(); ++i) {
		if (rescursive_decoder_small_alpha((statement + *i), encoded_str)) return true;
	}

	return false;
}

list<string> get_possible_charater_group_all_ascii_no_rep(const string& current_string, const string& encoded) {
	string encrypt_s = "";
	list<string> group;

	for (int i = 1; i <= 255; ++i) {

		if (current_string.find((unsigned char)i) != -1) continue;

		string temp;

		temp = current_string + (char)i;
		encrypt_s = encryptor(temp);
		if (encoded.find(encrypt_s) == 0) {
			group.push_back(string("") + (char)i);
		}
	}
	return group;
}

bool rescursive_decoder_all_ascii(string statement, const string& encoded_str, const chrono::steady_clock::time_point& start_time) {

	if ((chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start_time).count()) > 10) return false;

	string encrypted_statement = encryptor(statement);

	if (encryptor(statement) == encoded_str) {
		if (show_decrypted_pass) {
			cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << statement << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		return true;
	}

	list<string> result = get_possible_charater_group_all_ascii_no_rep(statement, encoded_str);

	for (auto i = result.begin(); i != result.end(); ++i) {
		if (rescursive_decoder_all_ascii((statement + *i), encoded_str, start_time)) return true;
	}

	return false;
}


