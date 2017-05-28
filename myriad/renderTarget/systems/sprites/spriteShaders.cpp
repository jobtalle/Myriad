#include "renderSprites.h"

const char *myr::RenderSprites::UNIFORM_ATLAS = "atlas";

const char *myr::RenderSprites::getShaderVertex()
{
	return
		"#version 330 core\n"

		"layout (std140) uniform sharedUniforms"
		"{"
		  "float width;"
		  "float height;"
		"};"

		"layout (location = 0) in vec2 vertex;"
		"layout (location = 1) in vec4 pixels;"
		"layout (location = 2) in vec4 location;"
		"layout (location = 3) in vec3 transform;"

		"out vec2 uv;"

		"void main() {"
		  "float c = cos(transform.z);"
		  "float s = sin(transform.z);"
		  "mat2 rotate = mat2(c, -s, s, c);"

		  "uv = pixels.xy + vertex * pixels.zw;"

		  "gl_Position = vec4("
		    "(vec2(location.x, -location.y) +"
		    "rotate * vec2(vertex.x * location.z - transform.x, -vertex.y * location.w + transform.y)) /"
		    "vec2(width, height) * 2 + vec2(-1, 1),"
		    "0, 1);"
		"}";
}

const char *myr::RenderSprites::getShaderFragment()
{
	return
		"#version 330 core\n"

		"uniform sampler2D atlas;"

		"layout (location = 0) out vec4 color;"

		"in vec2 uv;"

		"void main() {"
		  "color = texture(atlas, uv);"
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