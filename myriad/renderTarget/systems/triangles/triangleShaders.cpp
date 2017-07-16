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

		"layout (location = 0) in float vertex;"
		"layout (location = 1) in vec4 colorA;"
		"layout (location = 2) in vec4 colorB;"
		"layout (location = 3) in vec4 colorC;"
		"layout (location = 4) in vec4 pointAB;"
		"layout (location = 5) in vec2 pointC;"

		"out vec4 triangleColor;"

		"void main() {"
		  "mat3 matGlobal = mat3(widthRow0.yzw, heightRow1.yzw, vec3(0, 0, 1));"
		  "vec2 point = mix(mix(pointAB.xy, pointAB.zw, min(1, vertex)), pointC, max(0, vertex - 1));"
		  "triangleColor = mix(mix(colorA, colorB, min(1, vertex)), colorC, max(0, vertex - 1));"

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