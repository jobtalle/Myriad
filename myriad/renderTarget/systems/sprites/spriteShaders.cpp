#include "renderSprites.h"

const char *myr::RenderSprites::getShaderVertex()
{
	return
		"#version 330 core\n"

		"layout (std140) uniform sharedUniforms\n"
		"{\n"
		"  float width;\n"
		"  float height;\n"
		"};\n"

		"void main() {\n"
		"  gl_Position = vec4(0, 0, 0, 1);\n"
		"}";
}

const char *myr::RenderSprites::getShaderFragment()
{
	return
		"#version 330 core\n"

		"uniform sampler2D atlas;"

		"layout (location = 0) out vec4 color;\n"

		"void main() {\n"
		"  color = vec4(1, 0, 0, 0);\n"
		"}";
}

const std::vector<std::string> myr::RenderSprites::getShaderUniforms()
{
	return std::vector<std::string>({
		"atlas"
	});
}