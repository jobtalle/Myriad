#include <archive/archive.h>
#include <archive/formatter.h>
#include <xxhash/xxhash.h>
#include <miniz/miniz.h>

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
	entry &entry,
	const uint32_t hash) const
{
	const std::string extension = entry.path.substr(entry.path.length() - 3, 3);
	const std::vector<char> formatted = formatter::format(file, extension);

	std::ofstream out(object, std::ios::binary);
	out.write((const char*)&hash, sizeof(uint32_t));
	
	if(flags & ARCHIVE_FLAG_BATCH)
		out.write((const char*)formatted.data(), formatted.size());
	else
	{
		mz_ulong compressedSize = mz_compressBound((mz_ulong)formatted.size());
		char *compressed = new char[compressedSize];

		mz_compress2((unsigned char*)compressed, &compressedSize, (unsigned char*)formatted.data(), (mz_ulong)formatted.size(), 10);
		out.write(compressed, compressedSize);

		delete compressed;
	}
	
	out.close();

	entry.size = formatted.size();

	std::cout << "Updated " << object << std::endl;
}

std::vector<char> Archive::writeStringTab() const
{
	std::vector<char> result;
	uint64_t offset = 0;

	for(const entry entry:entries)
	{
		result.insert(result.end(), entry.name.begin(), entry.name.end());
		result.push_back('\0');
		result.insert(result.end(), (const char*)&offset, (const char*)&offset + sizeof(offset));

		offset += entry.size;
	}

	return result;
}

Archive::Archive(const std::vector<std::string> fileNames, const uint8_t flags)
:flags(flags)
{
	for(const auto &file : fileNames)
		entries.push_back(createEntry(file));

	std::sort(entries.begin(), entries.end());
}

bool Archive::writeObjects(const std::string objects)
{
	bool changed = false;

	for(auto &entry : entries)
	{
		std::ifstream sourceIn(entry.path, std::ios::binary);
		std::vector<char> file((std::istreambuf_iterator<char>(sourceIn)), (std::istreambuf_iterator<char>()));
		sourceIn.close();

		uint32_t hash = XXH32(file.data(), file.size(), 0);

		if(flags & ARCHIVE_FLAG_CLEAN)
		{
			writeObject(getObjPath(entry, objects), file, entry, hash);

			changed = true;
		}
		else
		{
			std::ifstream objectIn(getObjPath(entry, objects), std::ios::binary);
			if(objectIn.is_open())
			{
				uint32_t storedHash;

				objectIn.read((char*)&storedHash, sizeof(uint32_t));
				objectIn.close();

				if(storedHash != hash)
				{
					writeObject(getObjPath(entry, objects), file, entry, hash);

					changed = true;
				}
			}
			else
			{
				writeObject(getObjPath(entry, objects), file, entry, hash);

				changed = true;
			}
		}
	}

	return changed;
}

void Archive::compile(const std::string objects, const std::string file) const
{
	std::ofstream out(file, std::ios::binary);

	out.write((const char*)&flags, sizeof(flags));
	
	if(flags & ARCHIVE_FLAG_BATCH)
	{
		std::vector<char> archive = writeStringTab();

		for(const entry &entry : entries)
		{
			std::ifstream sourceIn(getObjPath(entry, objects), std::ios::binary);
			std::vector<char> file((std::istreambuf_iterator<char>(sourceIn)), (std::istreambuf_iterator<char>()));
			sourceIn.close();

			archive.insert(archive.end(), file.begin(), file.end());
		}

		mz_ulong compressedSize = mz_compressBound((mz_ulong)archive.size());
		char *compressed = new char[compressedSize];
		
		mz_compress2((unsigned char*)compressed, &compressedSize, (unsigned char*)archive.data(), (mz_ulong)archive.size(), 10);
		out.write((const char*)&compressedSize, sizeof(uint64_t));
		out.write(compressed, compressedSize);
		
		std::cout << "Wrote batch with " << ((float)archive.size() / compressedSize) * 100 << "% compression" << std::endl;

		delete compressed;
	}
	else
	{
		std::vector<char> stringTab = writeStringTab();
		mz_ulong compressedSize = mz_compressBound((mz_ulong)stringTab.size());
		char *compressedStringTab = new char[compressedSize];

		mz_compress2((unsigned char*)compressedStringTab, &compressedSize, (unsigned char*)stringTab.data(), (mz_ulong)stringTab.size(), 10);
		out.write((const char*)&compressedSize, sizeof(uint64_t));
		out.write(compressedStringTab, compressedSize);

		delete compressedStringTab;

		for(const entry &entry : entries)
		{
			std::ifstream sourceIn(getObjPath(entry, objects), std::ios::binary);
			std::vector<char> file((std::istreambuf_iterator<char>(sourceIn)), (std::istreambuf_iterator<char>()));
			sourceIn.close();

			out.write(file.data() + sizeof(uint32_t), file.size() - sizeof(uint32_t));
		}

		std::cout << "Wrote archive" << std::endl;
	}

	out.close();
}