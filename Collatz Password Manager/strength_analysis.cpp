#include "credential.h"
#include <tuple>
#include <random>
#include <fstream>
#include <chrono>
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

void decode_test(const string& fname) {
	ifstream data_file;
	string encoded_pass;
	data_file.open(fname.c_str());
	if (data_file.fail())
		throw invalid_argument("No file exists " + fname);
	int count = 0, total_count = 0, loop_count = 0;
	chrono::steady_clock::time_point prev_time = chrono::steady_clock::now();
	while (data_file >> encoded_pass) {
		if (loop_count % 100 == 0) {
			count = 0;
			if (loop_count != 0) {
				chrono::steady_clock::time_point curent_time = chrono::steady_clock::now();
				cout << "\nAverage Time per password for this category = " << (chrono::duration_cast<chrono::nanoseconds>(curent_time - prev_time).count())/(float)(100.00) << "[ns]" << endl;
				prev_time = chrono::steady_clock::now();
			}
			cout << "\n\n\n***************************** Starting Category " + to_string(loop_count + 1) + " to " + to_string(loop_count + 100) + " *****************************\n\n" << endl;
			
		}
		if (loop_count < 10000) {
			if (rescursive_decoder_small_alpha("", encoded_pass)) {
				++count; ++total_count;
			}
		}
		else {
			chrono::steady_clock::time_point start_time = chrono::steady_clock::now();
			if (rescursive_decoder_all_ascii("", encoded_pass, start_time)) {
				++count; ++total_count;
			}
		}
		cout << count << "% Complete. last encoded_pass: " << encoded_pass << endl;
		++loop_count;
	}
	cout << "Succesfull Count - " << total_count << endl;
}

void write_data_to_file(const string& fname, const string& data) {
	ofstream data_file;
	data_file.open(fname.c_str(), ios_base::app);
	if (data_file.fail())
		throw invalid_argument("No file exists " + fname);
	data_file << (data + "\n");
	data_file.close();
}