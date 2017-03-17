#include <resources/archive.h>
#include <resources/formatter.h>
#include <xxhash/xxhash.h>

#include <algorithm>
#include <iostream>
#include <fstream>

Archive::entry Archive::createEntry(const std::string file) const
{
	entry entry;

	entry.name = file.substr(file.find_last_of('\\') + 1, file.find_last_of('.') - file.find_last_of('\\') - 1);
	entry.path = file;
	
	return entry;
}

std::string Archive::getObjPath(const Archive::entry entry, const std::string dir) const
{
	return dir + entry.name + ".obj";
}

void Archive::writeObject(
	const std::string object,
	const std::vector<char> file,
	const std::string extension,
	const uint32_t hash) const
{
	std::vector<char> formatted = formatter::format(file, extension);

	std::ofstream out(object, std::ios::binary);
	out.write((const char*)&hash, sizeof(uint32_t));
	out.write((const char*)formatted.data(), formatted.size());
	out.close();

	std::cout << "Updating " + object << std::endl;
}

Archive::Archive(const std::vector<std::string> fileNames, const uint8_t flags)
:flags(flags)
{
	for(const auto &file : fileNames)
		entries.push_back(createEntry(file));

	std::sort(entries.begin(), entries.end());
}

void Archive::writeObjects(const std::string objects) const
{
	for(const auto &entry : entries)
	{
		const std::string extension = entry.path.substr(entry.path.length() - 3, 3);
		std::ifstream sourceIn(entry.path, std::ios::binary);
		std::vector<char> file((std::istreambuf_iterator<char>(sourceIn)), (std::istreambuf_iterator<char>()));
		sourceIn.close();

		uint32_t hash = XXH32(file.data(), file.size(), 0);

		std::ifstream objectIn(getObjPath(entry, objects), std::ios::binary);
		if(objectIn.is_open())
		{
			uint32_t storedHash;

			objectIn.read((char*)&storedHash, sizeof(uint32_t));
			objectIn.close();

			if(storedHash != hash)
				writeObject(getObjPath(entry, objects), file, extension, hash);
		}
		else
			writeObject(getObjPath(entry, objects), file, extension, hash);
	}
}

void Archive::compile(const std::string objects, const std::string file) const
{

}