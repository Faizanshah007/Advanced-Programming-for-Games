#include "credential.h"
#include <tuple>

class Strength_Analysis : public Credential {
public:
	bool repetition_allowed;
	tuple<int, int> ascii_range;

	Strength_Analysis(const bool& can_repeat, const tuple<int, int> range) : repetition_allowed(can_repeat), ascii_range(range) {}

	string generate_encrypted_passwords(const int& password_length);

	void decode_test(const string& fname);
};

class Non_rep_all_ascii : public Strength_Analysis {
public:
	Non_rep_all_ascii() : Strength_Analysis(false, make_tuple(1, 255)), x(3) {}
	int x;
};

class Rep_small_alpha : public Strength_Analysis {
public:
	Rep_small_alpha() : Strength_Analysis(true, make_tuple((int)('a'), (int)('z'))), x(4) {}
	int x;
};

void write_data_to_file(const string& fname, const string& data);

void decode_test(const string& fname);