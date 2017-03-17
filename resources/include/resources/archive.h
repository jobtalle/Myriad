#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Archive {
	typedef struct entry {
		std::string name;
		std::string path;

		bool operator < (const struct entry &entry) const
		{
			return name.compare(entry.name) < 0;
		}
	} entry;

	std::vector<entry> entries;
	uint8_t flags;

	entry createEntry(const std::string file) const;
	std::string getObjPath(const entry entry, const std::string dir) const;
	void writeObject(
		const std::string object,
		const std::vector<char> file,
		const std::string extension,
		const uint32_t hash) const;

public:
	Archive(const std::vector<std::string> fileNames, const uint8_t flags);
	void writeObjects(const std::string objects) const;
	void compile(const std::string objects, const std::string file) const;

	enum failure {
		FAILURE_NAME_COLLISION
	};
};