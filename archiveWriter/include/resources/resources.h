#pragma once

namespace resources {
	enum requiredArguments {
		ARGUMENT_PATH,
		ARGUMENT_TARGET,
		ARGUMENT_OBJECTS,
		ARGUMENT_OUTPUT,
		ARGUMENT_COUNT
	};

	enum failure {
		FAILURE_ARGUMENT_COUNT,
		FAILURE_DIR_NOT_FOUND
	};

	enum constants {
		FILE_NAME_MAX_LENGTH = 2048
	};

	void compile(int argc, char **argv);
};