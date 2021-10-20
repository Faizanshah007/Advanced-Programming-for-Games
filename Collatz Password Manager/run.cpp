#include <iostream>
#include <string>

#include "utility.h"

using namespace std;

class Credential {
public:
	Credential(string uname, string raw_password): username(uname) {
		encrypted_password = encryptor(raw_password);
	}
	void write_to_file(const string& fnmae);

private:
	string username;
	string encrypted_password;
	string encryptor(const string& raw_password);
};

string Credential::encryptor(const string& raw_password) {
	string encrypted_password = "";
	int offset = 0;
	for (const auto& ch : raw_password) {
		offset = collatz_conjecture(ch+offset);
		encrypted_password += to_string(offset);
	}
	cout << encrypted_password << endl;
	return encrypted_password;
}

void Credential::write_to_file(const string& fname) {

}



int main() {

	int choice = 0;
	string username, password;
	
	const int EXIT = 5;
	const string PASSWORD_FILE_NAME = "password.txt";

	Credential* cred = NULL;

	while (choice != EXIT) {

		choice = 0;

		cout << "\n\nSelect your option: \n"
			<< "1. Create username/password\n"
			<< "2. Check username and password\n"
			<< "3. Generate password strength analysis file\n"
			<< "4. Analysis password strength analysis file\n"
			<< "5. Exit\n";

		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter Username: ";
			cin >> username;

			cout << "Enter Password: ";
			cin.ignore();
			getline(cin, password);

			if (!is_printable_ASCII_string(password)) {
				cout << "Invalid Input: Password characters are limited to the printable ASCII characters." << endl;
				continue;
			}

			if (cred != NULL) {
				delete cred;
				cred = NULL;
			}

			cred = new Credential(username, password);

			cred->write_to_file(PASSWORD_FILE_NAME);

			break;
		}

	}

	if (cred != NULL) {
		delete cred;
		cred = NULL;
	}

	return 0;
}