#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Archive {
	typedef struct {
		std::string name;
		std::string path;
	} entry;

	std::vector<entry> entries;
	uint8_t flags;

	entry createEntry(const std::string file) const;
	void writeObject(
		const std::string object,
		const std::vector<char> file,
		const std::string extension,
		const uint32_t hash) const;

public:
	Archive(const std::vector<std::string> fileNames, const uint8_t flags);
	void writeObjects(const std::string directory) const;
	void compile(const std::string file) const;

	enum failure {
		FAILURE_NAME_COLLISION
	};
};