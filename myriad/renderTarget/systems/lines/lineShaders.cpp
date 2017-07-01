#include "renderLines.h"

const char *myr::RenderLines::getShaderVertex()
{
	return
		"#version 330 core\n"

		"layout (std140) uniform sharedUniforms"
		"{"
			"vec4 widthRow0;"
			"vec4 heightRow1;"
		"};"

		"layout (location = 0) in float vertex;"
		"layout (location = 1) in vec4 points;"
		"layout (location = 2) in vec4 color;"

		"flat out vec4 lineColor;"

		"void main() {"
		  "mat3 matGlobal = mat3(widthRow0.yzw, heightRow1.yzw, vec3(0, 0, 1));"
		  "vec2 point = (vec3(mix(points.xy, points.zw, vertex), 1) * matGlobal).xy / vec2(widthRow0.x, heightRow1.x) * 2;"

		  "lineColor = color;"

		  "gl_Position = vec4(vec2(point.x, -point.y) + vec2(-1, 1), 0, 1);"
		"}";
}

const char *myr::RenderLines::getShaderFragment()
{
	return
		"#version 330 core\n"

		"layout (location = 0) out vec4 color;"

		"flat in vec4 lineColor;"

		"void main() {"
		  "color = lineColor;"
		"}";
}

const std::vector<std::string> myr::RenderLines::getShaderUniforms()
{
	return std::vector<std::string>();
}