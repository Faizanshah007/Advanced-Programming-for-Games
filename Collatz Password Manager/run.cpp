#include <iostream>
#include <list>
#include <memory>
#include <fstream>

#include "utility.h"
#include "credential.h"
#include "strength_analysis.h"

using namespace std;

const string encoded1 = "332328232810326232823411528231083423108101261083911634231162610821461113411652361163485267694436854454671065231281081374611611413953915108342341851193428152010821412328411165223202020332815711310113738151211334116833910";

int main() {

	int choice = 0, attempts_left = 3, len = 0;
	string username, password;
	
	const int EXIT = 6;
	const string PASSWORD_FILE_NAME = "password.txt", PASSWORD_TEST_FILE_NAME = "passwordtest.txt";

	Credential* cred = NULL;

	list<string> temp; //removeeeeeee

	while (choice != EXIT) {

		choice = 0;
		attempts_left = 3;

		//unique_ptr<Strength_Analysis[]>
		unique_ptr<Strength_Analysis> sa_first_half[10000], sa_second_half[10000];

		for (int itr = 0; itr < 10000; ++itr) {
			sa_first_half[itr] = make_unique<Non_rep_all_ascii>();
			sa_second_half[itr] = make_unique<Rep_small_alpha>();
		}

		cout << "\n\nSelect your option: \n"
			<< "1. Create username/password\n"
			<< "2. Check username and password\n"
			<< "3. Generate password strength analysis file\n"
			<< "4. Analysis password strength analysis file\n"
			<< "5. Decode the well known english sentence\n"
			<< "6. Exit\n";

		cin >> choice;

		string pwdtest1 = "", pwdtest2 = "";

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

		case 3:
			len = 0;
			for (int itr = 0; itr < 10000; ++itr) {
				if (itr % 100 == 0) ++len;
				pwdtest1 += static_cast<Non_rep_all_ascii*>(sa_first_half[itr].get())->generate_encrypted_passwords(len) + "\n";
				pwdtest2 += static_cast<Rep_small_alpha*>(sa_second_half[itr].get())->generate_encrypted_passwords(len) + "\n";
			}

			try {
				write_data_to_file(PASSWORD_TEST_FILE_NAME, pwdtest1 + pwdtest2);
			}
			catch (const invalid_argument& iae) {
				cout << " Unable to read data : " << iae.what() << "\n";
			}
			break;

		case 4:
			//Add except handle;
			//decode_test(PASSWORD_TEST_FILE_NAME);
			//rescursive_decoder("", "67261192118108125931003716100");
			/*temp = get_possible_charater_group_all_ascii("", "31");
			for (auto itr = temp.begin(); itr != temp.end(); ++itr) {
				cout << *itr << " " << (int)(unsigned char)(*itr)[0] << endl;
			}*/
			//encryptor("")

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