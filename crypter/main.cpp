#include "includes.h"
#include "functions.h"

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cout << "Uasge: " << argv[0] << " [text_file] [key_file] [out_file]" << endl;
		return -1;
	}

	size_t len;
	char * key = new char[KEY_LEN];
	memset(key, '\0', KEY_LEN);

	char* temp = ReadAllBytes(argv[2], len);
	for (unsigned int i = 0; i < len && i < KEY_LEN; i++)
		key[i] = temp[i];

	char * text = ReadAllBytes(argv[1], len);

	Crypt(key, text, len, argv[3]);

	return 0;
}