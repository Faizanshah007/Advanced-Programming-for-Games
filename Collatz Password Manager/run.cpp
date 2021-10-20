#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "utility.h"

using namespace std;

class Credential {
public:
	Credential(string uname, string raw_password): username(uname) {
		encrypted_password = encryptor(raw_password);
	}
	Credential(){}
	void write_to_file(const string& fnmae);
	bool get_credentials(const string& uname, const string& fname);
	bool verify_credential(const string& pass) { return (encryptor(pass) == encrypted_password); }

private:
	string username;
	string encrypted_password;
	friend string encryptor(const string& raw_password);
};

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

int main() {

	int choice = 0, attempts_left = 3;
	string username, password;
	
	const int EXIT = 6;
	const string PASSWORD_FILE_NAME = "password.txt1";

	Credential* cred = NULL;

	while (choice != EXIT) {

		choice = 0;
		attempts_left = 3;

		cout << "\n\nSelect your option: \n"
			<< "1. Create username/password\n"
			<< "2. Check username and password\n"
			<< "3. Generate password strength analysis file\n"
			<< "4. Analysis password strength analysis file\n"
			<< "5. Decode the well known english sentence\n"
			<< "6. Exit\n";

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

			try {
				cred->write_to_file(PASSWORD_FILE_NAME);
			}
			catch (const invalid_argument& iae) {
				cout << " Unable to read data : " << iae.what() << "\n";
				delete cred;
				cred = NULL;
			}

			break;

		case 2:

			cout << "Enter Username: ";
			cin >> username;

			try {

				if (cred != NULL) {
					delete cred;
					cred = NULL;
				}

				cred = new Credential();

				if (!cred->get_credentials(username, PASSWORD_FILE_NAME)) {
					cout << "failure!" << endl; break;
				}

				while (attempts_left != 0) {
					cout << "Enter Password: ";
					cin.ignore();
					getline(cin, password);
					if (cred->verify_credential(password)) {
						cout << "success!" << endl;
						break;
					}
					cout << "failure!" << endl;
					--attempts_left;
				}

				delete cred;
				cred = NULL;
			}
			catch (const invalid_argument& iae) {
				cout << " Unable to read data : " << iae.what() << "\n";
				if (cred != NULL) {
					delete cred;
					cred = NULL;
				}
			}

			break;

		case 5:
			cout << "List of possible decoded sentences: " << endl;
			statement_generator("");
			break;

		case 6:
			break;

		default:
			cout << "Invalid Choice." << endl;
			break;
		}

	}

	if (cred != NULL) {
		delete cred;
		cred = NULL;
	}

	return 0;
}