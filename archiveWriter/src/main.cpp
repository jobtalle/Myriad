#include <iostream>

#include <archive/archiver.h>
#include <archive/archive.h>

int main(int argc, char **argv)
{
	try
	{
		archiver::compile(argc, argv);
	}
	catch(enum archiver::failure &failure)
	{
		switch(failure)
		{
		case archiver::FAILURE_ARGUMENT_COUNT:
			std::cout << "Wrong number of arguments supplied" << std::endl;
			break;
		case archiver::FAILURE_DIR_NOT_FOUND:
			std::cout << "Directory could not be read" << std::endl;
			break;
		}
	}
	catch(enum Archive::failure &failure)
	{
		switch(failure)
		{
		case Archive::FAILURE_NAME_COLLISION:
			std::cout << "Name collision" << std::endl;
			break;
		}
	}
}