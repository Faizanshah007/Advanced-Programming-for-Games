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