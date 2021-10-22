#pragma once

#include <functional>
#include <string>
#include <chrono>

using namespace std;

extern bool show_decrypted_pass;

extern function<bool(const string& s)> is_printable_ASCII_string;

int collatz_conjecture(const int& ch);

string to_lower(const string& s);

string encryptor(const string& raw_password);

extern void (*statement_generator)(string);

list<string> sentense_to_words(const string& statement);

list<string> get_possible_charater_group(const string& current_string, const string& encoded);

bool rescursive_decoder_small_alpha(string statement, const string& encoded_str);

bool rescursive_decoder_all_ascii(string statement, const string& encoded_str, const chrono::steady_clock::time_point& start_time);