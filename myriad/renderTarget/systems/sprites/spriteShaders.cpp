#include "renderSprites.h"

const char *myr::RenderSprites::UNIFORM_ATLAS = "atlas";

const char *myr::RenderSprites::getShaderVertex()
{
	return
		"#version 330 core\n"

		"layout (std140) uniform sharedUniforms"
		"{"
			"vec4 widthRow0;"
			"vec4 heightRow1;"
		"};"

		"layout (location = 0) in vec2 vertex;"
		"layout (location = 1) in vec4 pixels;"
		"layout (location = 2) in vec4 scaleRotate;"
		"layout (location = 3) in vec4 transform;"

		"out vec2 uv;"

		"void main() {"
		  "mat3 matLocal = mat3(vec3(scaleRotate.xy, transform.z), vec3(scaleRotate.zw, transform.w), vec3(0, 0, 1));"
		  "mat3 matGlobal = mat3(widthRow0.yzw, heightRow1.yzw, vec3(0, 0, 1));"
		  "vec2 point = (vec3(vertex.x - transform.x, vertex.y - transform.y, 1) * matLocal * matGlobal).xy;"

		  "uv = pixels.xy + vertex * pixels.zw;"

		  "gl_Position = vec4("
		    "vec2(point.x, -point.y) /"
		    "vec2(widthRow0.x, heightRow1.x) * 2 + vec2(-1, 1),"
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