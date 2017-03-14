#include <Windows.h>
#include <iostream>
#include <vector>

#include <resources/resources.h>

static void readDirectory(std::vector<std::string> &fileNames, const char *dir)
{
	WIN32_FIND_DATA foundFile;
	HANDLE foundHandle = NULL;
	char fileName[resources::FILE_NAME_MAX_LENGTH];

	std::cout << "Reading " << dir << std::endl;

	sprintf(fileName, "%s\\*.*", dir);

	if((foundHandle = FindFirstFile(fileName, &foundFile)) == INVALID_HANDLE_VALUE)
		throw resources::FAILURE_DIR_NOT_FOUND;
	
	do
	{
		if(strcmp(foundFile.cFileName, ".") != 0 && strcmp(foundFile.cFileName, "..") != 0)
		{
			sprintf(fileName, "%s\\%s", dir, foundFile.cFileName);

			if(foundFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				readDirectory(fileNames, fileName);
			else
				std::cout << fileName << std::endl;
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
}