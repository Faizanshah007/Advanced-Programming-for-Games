#pragma once
#include <string>
#include "utility.h"

using namespace std;

class Credential {
public:
	Credential(string uname, string raw_password) : username(uname) {
		encrypted_password = encryptor(raw_password);
	}
	Credential() {}
	void write_to_file(const string& fnmae);
	bool get_credentials(const string& uname, const string& fname);
	bool verify_credential(const string& pass) { return (encryptor(pass) == encrypted_password); }

protected:
	string username;
	string encrypted_password;
	friend string encryptor(const string& raw_password);
};