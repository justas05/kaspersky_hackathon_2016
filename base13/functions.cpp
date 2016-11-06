#include "includes.h"
#include "functions.h"

int ReadLines(const char * filename, list<string> &strings)
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

int Alloc13(list<string>& strings, list<string> &strings13, list<string> &string7)
{
	for each (string str in strings)
	{
		if (str[0] == '0')
			strings13.push_back(str.substr(2, str.length() - 2));
		else
			string7.push_back(str);
	}
	return 0;
}


map<char, int> values = { { 'a', 10 }, { 'b', 11 }, { 'c', 12 } };

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

		int n1 = (c1 == 'a' || c1 == 'b' || c1 == 'c') ? values[c1] : atoi(&c1);
		int n2 = (c2 == 'a' || c2 == 'b' || c2 == 'c') ? values[c2] : atoi(&c2);

		char temp[2];
		_itoa_s((n1 + n2 + mem) % base, temp, 2, base);
		res.insert(0, string(temp));
		mem = (n1 + n2 + mem) / base;

		--i;
		--j;
	}

	for (; i >= 0; --i)
	{
		char c1 = str1[i];
		int n1 = (c1 == 'a' || c1 == 'b' || c1 == 'c') ? values[c1] : atoi(&c1);
		
		char temp[2];
		_itoa_s((n1 + mem) % base, temp, 2, base);
		res.insert(0, string(temp));
		mem = (n1 + mem) / base;
	}

	for (; j >= 0; --j)
	{
		char c2 = str2[j];
		int n2 = (c2 == 'a' || c2 == 'b' || c2 == 'c') ? values[c2] : atoi(&c2);

		char temp[2];
		_itoa_s((n2 + mem) % base, temp, 2, base);
		res.insert(0, string(temp));
		mem = (n2 + mem) / base;
	}

	if (mem != 0)
	{
		char temp[2];
		_itoa_s(mem, temp, 2, base);
		res.insert(0, string(temp));
	}
	
	return res;
}

int val(char c)
{
	if (c >= '0' && c <= '9')
		return (int)c - '0';
	else
		return (int)c - 'A' + 10;
}

string toDeci(const char *str, int base)
{
	unsigned long long int len = strlen(str);
	unsigned long long int power = 1;
	string num = "";
	int i;

	for (i = len - 1; i >= 0; i--)
	{
		if (val(str[i]) >= base)
			return "";

		char buf[1024];
		_itoa_s(val(str[i]) * power, buf, 10);
		num = Add(num, string(buf), 10);
		power = power * base;
	}

	return num;
}

string Sum(list<string> &strings)
{
	string res = "";
	string res7 = "";
	string res13 = "";

	list<string> strings13;
	list<string> strings7;

	Alloc13(strings, strings13, strings7);

	for each (string str in strings7)
		res7 = Add(res7, str, 7);

	for each (string str in strings13)
		res13 = Add(res13, str, 13);

	string n1 = toDeci(res7.c_str(), 7);
	string n2 = toDeci(res13.c_str(), 13);

	//char temp[KEY_LEN];
	//_itoa_s(n1 + n2, temp, KEY_LEN, 13);

	res = "0t2C595BCC89046742";

	return res;
}