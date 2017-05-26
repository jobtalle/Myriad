#include "renderSprites.h"

const char *myr::RenderSprites::UNIFORM_ATLAS = "atlas";

const char *myr::RenderSprites::getShaderVertex()
{
	return
		"#version 330 core\n"

		"layout (std140) uniform sharedUniforms"
		"{"
		"  float width;"
		"  float height;"
		"};"

		"layout (location = 0) in vec2 vertex;"
		"layout (location = 1) in vec4 pixels;"
		"layout (location = 2) in vec4 location;"

		"void main() {"
		"  gl_Position = vec4(width, height, 0, 1);"
		"}";
}

const char *myr::RenderSprites::getShaderFragment()
{
	return
		"#version 330 core\n"

		"uniform sampler2D atlas;"

		"layout (location = 0) out vec4 color;"

		"void main() {"
		"  color = texture(atlas, vec2(0, 0));"
		"}";
}

const std::vector<std::string> myr::RenderSprites::getShaderUniforms()
{
	return std::vector<std::string>({
		RenderSprites::UNIFORM_ATLAS
	});
}

const std::vector<myr::Vector> myr::RenderSprites::getQuad()
{
	return std::vector<Vector>({
		Vector(0, 0),
		Vector(0, 1),
		Vector(1, 1),
		Vector(1, 0)
	});
}