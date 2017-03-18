#pragma once

#include <vector>
#include <string>

namespace formatter {
	std::vector<char> formatPng(std::vector<char> file);

	std::vector<char> format(std::vector<char>, const std::string extension);
}