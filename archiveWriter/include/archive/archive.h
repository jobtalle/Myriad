#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Archive {
	typedef struct entry {
		std::string name;
		std::string path;
		uint64_t size;

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
		entry &entry,
		const uint32_t hash) const;
	std::vector<char> writeStringTab() const;

public:
	Archive(const std::vector<std::string> fileNames, const uint8_t flags);
	bool writeObjects(const std::string objects);
	void compile(const std::string objects, const std::string file) const;

	enum failure {
		FAILURE_NAME_COLLISION
	};

	enum flags {
		ARCHIVE_FLAG_BATCH = 0x01,
		ARCHIVE_FLAG_CLEAN = 0x02
	};
};