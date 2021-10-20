#pragma once

#include <functional>
#include <string>

using namespace std;


extern function<bool(const string& s)> is_printable_ASCII_string;

int collatz_conjecture(const int& ch);