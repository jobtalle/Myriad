#include <Windows.h>
#include <iostream>
#include <vector>

#include <resources/resources.h>
#include <resources/archive.h>

static void readDirectory(std::vector<std::string> &fileNames, const std::string dir)
{
	WIN32_FIND_DATA foundFile;
	HANDLE foundHandle = NULL;
	std::string fileName;

	fileName = dir + "\\*.*";

	if((foundHandle = FindFirstFile(fileName.data(), &foundFile)) == INVALID_HANDLE_VALUE)
		throw resources::FAILURE_DIR_NOT_FOUND;
	
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

void resources::compile(int argc, char **argv)
{
	if(argc != resources::ARGUMENT_COUNT)
		throw resources::FAILURE_ARGUMENT_COUNT;

	CreateDirectory(argv[ARGUMENT_OBJECTS], NULL);

	std::vector<std::string> fileNames;

	readDirectory(fileNames, argv[ARGUMENT_TARGET]);

	const Archive archive = Archive(fileNames, 0);
	archive.writeObjects(argv[ARGUMENT_OBJECTS]);
	archive.compile(argv[ARGUMENT_OUTPUT]);
}