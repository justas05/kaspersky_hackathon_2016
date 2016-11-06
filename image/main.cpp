#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_DEPRECATE
#define _SCL_SECURE_NO_WARNINGS


#include <cstdio>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "bitmap_image.h"

using namespace std;


int main(int argc, char** argv)
{
	if (argc < 3)
	{
		cout << "usage: " << argv[0] << " [bmp_image] [out_key_file_name]" << endl;
		system("pause");
		return -1;
	}

	bitmap_image image(argv[1]);

	if (!image)
	{
		cout << "Error - Failed to open bmp\\n" << endl;
		system("pause");
		return 1;
	}

	unsigned char red;
	unsigned char green;
	unsigned char blue;

	unsigned int total_number_of_pixels = 0;

	const unsigned int height = image.height();
	const unsigned int width = image.width();

	vector<char> key;

	for (std::size_t y = 0; y < height && total_number_of_pixels < 32; ++y)
	{
		for (std::size_t x = 0; x < width && total_number_of_pixels < 32; ++x)
		{
			image.get_pixel(x, y, red, green, blue);
			if (red == green && green == blue)
			{
				key.push_back(red);
				++total_number_of_pixels;
			}
		}
	}

	ofstream ofs(argv[2], ios::binary);
	for (auto it = key.begin(); it != key.end(); ++it)
		ofs << *it;
	ofs.close();

	return 0;
}