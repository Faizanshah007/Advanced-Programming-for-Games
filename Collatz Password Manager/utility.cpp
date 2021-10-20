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