#include <iostream>
#include <list>

#include "utility.h"
#include "credential.h"

using namespace std;

int main() {

	int choice = 0, attempts_left = 3;
	string username, password;
	
	const int EXIT = 6;
	const string PASSWORD_FILE_NAME = "password.txt";

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