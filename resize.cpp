//resize.cpp
#include "Matrix.h"
#include "Image.h"
#include "processing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

	ifstream fin(argv[1]);

	if (!fin.is_open())
	{
		cout << "Error opening file: " << argv[1] << endl;
	}
	else if (argc != 4 && argc != 5)
	{
		cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
			<< "WIDTH and HEIGHT must be less than or equal to original" << endl;
	}
	else
	{
		int width = atoi(argv[3]);
		int height = atoi(argv[4]);

		Image* img = new Image();
		Image_init(img, fin);

		if (height > 0 && height <= Image_height(img) && width > 0 && width <= Image_width(img))
		{
			seam_carve(img, width, height);
			Image_print(img, cout);
		}
		else
		{
			cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
				<< "WIDTH and HEIGHT must be less than or equal to original" << endl;
		}
	}
}