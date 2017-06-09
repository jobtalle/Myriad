#pragma once

#include "renderer/opengl/opengl.h"

#include <unordered_map>
#include <vector>
#include <string>

namespace myr
{
	class Renderer;

	class Shader final
	{
	public:
		Shader(
			const std::string &vertex,
			const std::string &fragment,
			const std::vector<std::string> &uniforms,
			const Renderer *renderer);
		Shader(
			const std::string &vertex,
			const std::string &fragment,
			const Renderer *renderer);
		~Shader();
		void bind();
		GLuint getUniformLocation(const std::string &name) const;

	private:
		GLuint program;
		std::unordered_map<std::string, GLint> uniformLocations;

		GLuint createShader(const GLenum type, const std::string &source) const;
		void locateUniforms(const std::vector<std::string> &uniforms);
	};
}