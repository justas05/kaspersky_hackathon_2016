#include "includes.h"
#include "functions.h"

char * ReadAllBytes(const char * filename, size_t& read)
{
	ifstream ifs(filename, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	size_t length = pos;

	char *pChars = new char[length];
	ifs.seekg(0, ios::beg);
	ifs.read(pChars, length);

	ifs.close();
	read = length;
	return pChars;
}

int Crypt(char* key, char* text, size_t size_text, char* outfile)
{
	unsigned __int32 *key_block = (unsigned __int32*)key;
	unsigned __int32 *text_block = (unsigned __int32*)text;
	unsigned __int32 current_block;
	unsigned __int32 current_cipher_value = 0;
	unsigned __int32 prev = 0;
	
	int index_key(0);
	int count_blocks = (size_text % 4) ? size_text / 4 + 1 : size_text / 4;
	
	ofstream of(outfile, ios::binary);

	for (int i(0); i < count_blocks; ++i)
	{
		if (i == 0)
			current_block = key_block[index_key] ^ 0;
		else
			current_block = prev ^ (key_block[index_key]);

		prev = current_block * 134775813 + 1;
		current_cipher_value = prev ^ (*text_block);

		char* ptr = (char*)&current_cipher_value;
		if (i == count_blocks - 1)
			for (int k(0); k < size_text - i * 4; ++k)
				of << *(ptr + k);
		else
		{
			char c[4] = { *ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3) };

			of << c[0] << c[1] << c[2] << c[3];
		}

		++text_block;
		++index_key;
		index_key %= 8;
	}

	of.close();
	return 0;
}
