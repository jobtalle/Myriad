#include <Windows.h>
#include <iostream>
#include <vector>

#include <archive/archiver.h>
#include <archive/archive.h>

static void readDirectory(std::vector<std::string> &fileNames, const std::string dir)
{
	WIN32_FIND_DATA foundFile;
	HANDLE foundHandle = NULL;
	std::string fileName;

	fileName = dir + "\\*.*";

	if((foundHandle = FindFirstFile(fileName.data(), &foundFile)) == INVALID_HANDLE_VALUE)
		throw archiver::FAILURE_DIR_NOT_FOUND;
	
	do
	{
		if(strcmp(foundFile.cFileName, ".") != 0 && strcmp(foundFile.cFileName, "..") != 0)
		{
			fileName = dir + foundFile.cFileName;

			if(foundFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				readDirectory(fileNames, fileName + '\\');
			else
				fileNames.push_back(fileName);
		}
	}
	while(FindNextFile(foundHandle, &foundFile));

	FindClose(foundHandle);
}

void archiver::compile(int argc, char **argv)
{
	if(argc < archiver::ARGUMENT_COUNT)
		throw archiver::FAILURE_ARGUMENT_COUNT;

	CreateDirectory(argv[ARGUMENT_OBJECTS], NULL);

	uint8_t flags = 0;

	for(size_t i = archiver::ARGUMENT_COUNT; i < argc; ++i)
	{
		if(strcmp(argv[i], "batch") == 0)
			flags |= Archive::ARCHIVE_FLAG_BATCH;
		else if(strcmp(argv[i], "clean") == 0)
			flags |= Archive::ARCHIVE_FLAG_CLEAN;
	}

	std::vector<std::string> fileNames;
	readDirectory(fileNames, argv[ARGUMENT_TARGET]);

	Archive archive = Archive(fileNames, flags);
	if(archive.writeObjects(argv[ARGUMENT_OBJECTS]))
		archive.compile(argv[ARGUMENT_OBJECTS], argv[ARGUMENT_OUTPUT]);
}