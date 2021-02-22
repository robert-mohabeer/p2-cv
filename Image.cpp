// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
using namespace std;

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
	assert(height > 0 && height < MAX_MATRIX_HEIGHT);
	assert(width > 0 && width < MAX_MATRIX_WIDTH);
	img->height = height;
	img->width = width;
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
	string head;
	getline(is, head);

	is >> img->width;
	is >> img->height;

	string skip;
	is >> skip;

	for (int x = 0; x < img->height; x++)
	{
		for (int y = 0; y < img->width; y++)
		{
			is >> *(img->red_channel.data + x * img->width + y);
			is >> *(img->green_channel.data + x * img->width + y);
			is >> *(img->blue_channel.data + x * img->width + y);
		}
	}
  //assert(false); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
	assert(img->height > 0 && img->width > 0);
	os << "P3" << endl;
	os << img->width << " " << img->height << endl;
	os << "255" << endl;
	for (int x = 0; x < img->height; x++)
	{
		for (int y = 0; y < img->width; y++)
		{
			cout << *(img->red_channel.data + x * img->width + y) << " ";
			cout << *(img->green_channel.data + x * img->width + y) << " ";
			cout << *(img->blue_channel.data + x * img->width + y) << " ";
		}
		cout << endl;
	}
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  assert(img->width > 0);
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
	assert(img->height> 0);
	return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
	assert(img->height > 0 && img->width > 0);
	assert(row >= 0 && row < img->height);
	assert(column >= 0 && column < img->width);

	int steps = row * Image_width(img) + column;
  return { *(img->red_channel.data + steps), *(img->green_channel.data + steps), *(img->blue_channel.data + steps) };
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
	assert(img->height > 0 && img->width > 0);
	assert(row >= 0 && row < img->height);
	assert(column >= 0 && column < img->width);

	int steps = row * Image_width(img) + column;

	*(img->red_channel.data + steps) = color.r;
	*(img->green_channel.data + steps) = color.g;
	*(img->blue_channel.data + steps) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
	assert(img->height > 0 && img->width > 0);

	for (int x = 0; x < img->height; x++)
	{
		for (int y = 0; y < img->width; y++)
		{
			*(img->red_channel.data + x * img->width + y) = color.r;
			*(img->green_channel.data + x * img->width + y) = color.g;
			*(img->blue_channel.data + x * img->width + y) = color.b;
		}
		cout << endl;
	}
}
