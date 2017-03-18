#include <archive/formatter.h>
#include <lodepng/lodepng.h>
#include <iostream>

std::vector<char> formatter::formatPng(std::vector<char> file)
{
	unsigned char *result;
	unsigned int width, height;

	lodepng_decode_memory(&result, &width, &height, (unsigned char*)file.data(), file.size(), LCT_RGBA, 8);
	
	return std::vector<char>(result, result + width * height * 4);
}

std::vector<char> formatter::format(std::vector<char> file, const std::string extension)
{
	if(extension == "png")
		return formatPng(file);
	else
		return file;
}