#pragma once

#include <functional>
#include <string>

using namespace std;


extern function<bool(const string& s)> is_printable_ASCII_string;

int collatz_conjecture(const int& ch);

string to_lower(const string& s);

string encryptor(const string& raw_password);

extern void (*statement_generator)(string);

list<string> sentense_to_words(const string& statement);

list<string> get_possible_charater_group(const string& current_string, const string& encoded);

bool rescursive_decoder(string statement, const string& encoded_str);

list<string> get_possible_charater_group_all_ascii_no_rep(const string& current_string, const string& encoded);