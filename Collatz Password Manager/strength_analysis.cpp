#include "credential.h"
#include <tuple>
#include <random>
#include <fstream>
#include "strength_analysis.h"

#include <iostream>

using namespace std;

std::random_device                  rand_dev;
std::mt19937                        generator(rand_dev());

string Strength_Analysis::generate_encrypted_passwords(const int& password_length) {
	uniform_int_distribution<int>  distr(get<0>(ascii_range), get<1>(ascii_range));
	string raw_password = "";
	for (int itr = 0; itr < password_length; ++itr) {
		char random_ascii = distr(generator);
		if (!repetition_allowed) {
			while (raw_password.find(random_ascii) != -1) {
				random_ascii = distr(generator);
			}
		}
		raw_password += random_ascii;
	}
	encrypted_password = encryptor(raw_password);
	cout << encrypted_password << " " << password_length << endl;
	return encrypted_password;
}

bool time_to_go = false;

void reset() {

}

void decode_test(const string& fname) {
	ifstream data_file;
	string encoded_pass;
	data_file.open(fname.c_str());
	if (data_file.fail())
		throw invalid_argument("No file exists " + fname);
	int count = 0;
	while (data_file >> encoded_pass) {

		if(rescursive_decoder("", encoded_pass)) ++count;
		cout << "Succesfull Count - " << count << "last encoded_pass - " << encoded_pass << endl;
	}
}

void write_data_to_file(const string& fname, const string& data) {
	ofstream data_file;
	data_file.open(fname.c_str(), ios_base::app);
	if (data_file.fail())
		throw invalid_argument("No file exists " + fname);
	data_file << (data + "\n");
	data_file.close();
}