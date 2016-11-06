#include "includes.h"
#include "functions.h"

int ReadLines(const char * filename, vector<string> &strings)
{
	ifstream ifs(filename);
	while (!ifs.eof())
	{
		char buf[KEY_LEN];
		ifs.getline(buf, KEY_LEN);
		if(strlen(buf) != 0)
			strings.push_back(string(buf));
	}
	ifs.close();
	return 0;
}

string Add(string str1, string str2, int base)
{
	if (str1.length() == 0)
		return str2;
	else if (str2.length() == 0)
		return str1;

	int max_len = max(str1.size(), str2.size());
	string res;
	
	int i = str1.length() - 1;
	int j = str2.length() - 1;

	int mem(0);
	while (i >= 0 && j >= 0)
	{
		char c1 = str1[i];
		char c2 = str2[j];

		int n1 = atoi(&c1);
		int n2 = atoi(&c2);

		char temp[2];
		_itoa_s((n1 + n2 + mem) % base, temp, 2, 10);
		res.insert(0, string(temp));
		mem = (n1 + n2 + mem) / base;

		--i;
		--j;
	}

	for (; i >= 0; --i)
	{
		char c1 = str1[i];
		int n1 = atoi(&c1);
		
		char temp[2];
		_itoa_s((n1 + mem) % base, temp, 2, 10);
		res.insert(0, string(temp));
		mem = (n1 + mem) / base;
	}

	for (; j >= 0; --j)
	{
		char c2 = str2[j];
		int n2 = atoi(&c2);

		char temp[2];
		_itoa_s((n2 + mem) % base, temp, 2, 10);
		res.insert(0, string(temp));
		mem = (n2 + mem) / base;
	}

	if (mem != 0)
	{
		char temp[2];
		_itoa_s(mem, temp, 2, 10);
		res.insert(0, string(temp));
	}
	
	return res;
}

string Sum(vector<string> strings)
{
	string res = "";

	for each (string str in strings)
		res = Add(res, str, 7);

	return res;
}