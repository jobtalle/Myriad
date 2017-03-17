#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Archive {
	uint8_t flags;

public:
	Archive(const std::vector<std::string> filenames, const uint8_t flags);
	void writeObjects(const std::string directory) const;
	void compile(const std::string file) const;
};