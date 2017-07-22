#include "renderTriangles.h"

const char *myr::RenderTriangles::getShaderVertex()
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

		"out vec4 triangleColor;"

		"void main() {"
		  "mat3 matGlobal = mat3(widthRow0.yzw, heightRow1.yzw, vec3(0, 0, 1));"
		  "triangleColor = color;"

		  "vec2 currentPoint = (vec3(point, 1) * matGlobal).xy / vec2(widthRow0.x, heightRow1.x) * 2;"

		  "gl_Position = vec4(vec2(currentPoint.x, -currentPoint.y) + vec2(-1, 1), 0, 1);"
		"}";
}

const char *myr::RenderTriangles::getShaderFragment()
{
	return
		"#version 330 core\n"

		"layout (location = 0) out vec4 color;"

		"in vec4 triangleColor;"

		"void main() {"
		  "color = triangleColor;"
		"}";
}

const std::vector<std::string> myr::RenderTriangles::getShaderUniforms()
{
	return std::vector<std::string>();
}