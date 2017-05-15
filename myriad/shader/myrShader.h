#pragma once

#include "renderer/opengl/opengl.h"

#include <map>
#include <vector>
#include <string>

namespace myr
{
	class Shader {
	public:
		Shader(
			const std::string vertex,
			const std::string fragment,
			const std::vector<std::string> uniforms);
		~Shader();
		void bind();
		GLuint getUniformLocation(const std::string name) const;

	private:
		GLuint program;
		std::map<std::string, GLint> uniformLocations;

		GLuint createShader(const GLenum type, const std::string source) const;
		void locateUniforms(const std::vector<std::string> uniforms);
	};
}