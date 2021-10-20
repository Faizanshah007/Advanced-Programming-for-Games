#include <string>
#include <fstream>

#include "credential.h"

void Credential::write_to_file(const string& fname) {
	ofstream data_file;
	data_file.open(fname.c_str(), ios_base::app);
	if (data_file.fail())
		throw invalid_argument("No file exists " + fname);
	data_file << (username + " " + encrypted_password + "\n");
}

bool Credential::get_credentials(const string& uname, const string& fname) {
	ifstream data_file;
	string u_name, encrpted_pass;
	data_file.open(fname.c_str());
	if (data_file.fail())
		throw invalid_argument("No file exists " + fname);
	while (data_file >> u_name && data_file >> encrpted_pass) {

		if (u_name == uname) {
			username = u_name;
			encrypted_password = encrpted_pass;
			return true;
		}
	}
	return false;
}