#include "includes.h"
#include "functions.h"

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		cout << argv[0] << " [in_file] [out_key_file]" << endl;
		return -1;
	}

	vector<string> strings;
	ReadLines(argv[1], strings);

	string result = Sum(strings);
	
	ofstream of(argv[2]);
	of << result.c_str();
	of.close();

	return 0;
}