#include "renderPoints.h"

const char *myr::RenderPoints::getShaderVertex()
{
	return
		"#version 330 core\n"

		"layout (std140) uniform sharedUniforms"
		"{"
			"vec4 widthRow0;"
			"vec4 heightRow1;"
		"};"

		"layout (location = 0) in vec4 color;"
		"layout (location = 1) in vec2 point;"

		"flat out vec4 pointColor;"

		"void main() {"
		  "mat3 matGlobal = mat3(widthRow0.yzw, heightRow1.yzw, vec3(0, 0, 1));"
		  "vec2 point = (vec3(point, 1) * matGlobal).xy / vec2(widthRow0.x, heightRow1.x) * 2;"

		  "pointColor = color;"

		  "gl_Position = vec4(vec2(point.x, -point.y) + vec2(-1, 1), 0, 1);"
		"}";
}

const char *myr::RenderPoints::getShaderFragment()
{
	return
		"#version 330 core\n"

		"layout (location = 0) out vec4 color;"

		"flat in vec4 pointColor;"

		"void main() {"
		  "color = pointColor;"
		"}";
}

const std::vector<std::string> myr::RenderPoints::getShaderUniforms()
{
	return std::vector<std::string>();
}