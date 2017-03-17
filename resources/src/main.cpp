#include <iostream>

#include <resources/resources.h>
#include <resources/archive.h>

int main(int argc, char **argv)
{
	try
	{
		resources::compile(argc, argv);
	}
	catch(enum resources::failure &failure)
	{
		switch(failure)
		{
		case resources::FAILURE_ARGUMENT_COUNT:
			std::cout << "Wrong number of arguments supplied" << std::endl;
			break;
		case resources::FAILURE_DIR_NOT_FOUND:
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

	getchar();
}