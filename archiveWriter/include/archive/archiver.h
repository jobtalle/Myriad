#pragma once

namespace archiver {
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

	void compile(int argc, char **argv);
};