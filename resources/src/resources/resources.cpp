#include <Windows.h>
#include <iostream>
#include <vector>

#include <resources/resources.h>
#include <resources/archive.h>

static void readDirectory(std::vector<std::string> &fileNames, const char *dir)
{
	WIN32_FIND_DATA foundFile;
	HANDLE foundHandle = NULL;
	char fileName[resources::FILE_NAME_MAX_LENGTH];

	sprintf(fileName, "%s\\*.*", dir);

	if((foundHandle = FindFirstFile(fileName, &foundFile)) == INVALID_HANDLE_VALUE)
		throw resources::FAILURE_DIR_NOT_FOUND;
	
	do
	{
		if(strcmp(foundFile.cFileName, ".") != 0 && strcmp(foundFile.cFileName, "..") != 0)
		{
			sprintf(fileName, "%s%s", dir, foundFile.cFileName);

			if(foundFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				readDirectory(fileNames, fileName);
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

	std::vector<std::string> fileNames;

	readDirectory(fileNames, argv[ARGUMENT_TARGET]);

	const Archive archive = Archive(fileNames, 0);
	archive.writeObjects(argv[ARGUMENT_OBJECTS]);
	archive.compile(argv[ARGUMENT_OUTPUT]);
}