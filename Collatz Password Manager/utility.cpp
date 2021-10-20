#include "utility.h"

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
	for (const auto& ch : raw_password) {
		offset = collatz_conjecture(ch + offset);
		encrypted_password += to_string(offset);
	}
	return encrypted_password;
}