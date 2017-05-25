#include "shader.h"
#include "renderer/renderer.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace {
	myr::Shader *current = nullptr;
}

myr::Shader::Shader(
	const std::string vertex,
	const std::string fragment,
	const std::vector<std::string> uniforms,
	const Renderer *renderer)
{
	program = glCreateProgram();

	const GLuint shaderVertex = createShader(GL_VERTEX_SHADER, vertex);
	const GLuint shaderFragment = createShader(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(program, shaderVertex);
	glAttachShader(program, shaderFragment);
	
	glLinkProgram(program);

	locateUniforms(uniforms);

	glUniformBlockBinding(
		program,
		glGetUniformBlockIndex(
			program,
			renderer->sharedUniforms.name()),
		renderer->sharedUniforms.index);
	
	glDetachShader(program, shaderVertex);
	glDetachShader(program, shaderFragment);

	glDeleteShader(shaderVertex);
	glDeleteShader(shaderFragment);
}

myr::Shader::~Shader()
{
	glDeleteProgram(program);
}

void myr::Shader::bind()
{
	if(current != this)
	{
		current = this;

		glUseProgram(program);
	}
}

GLuint myr::Shader::getUniformLocation(const std::string name) const
{
	return uniformLocations.at(name);
}

GLuint myr::Shader::createShader(const GLenum type, const std::string source) const
{
	const GLuint shader = glCreateShader(type);
	const GLint length = (GLint)source.length();
	const char *sourceStr = source.c_str();

	glShaderSource(shader, 1, &sourceStr, &length);
	glCompileShader(shader);
	
#ifdef _DEBUG
	GLint logLength;
	
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	
	if(logLength != 0)
	{
		std::unique_ptr<char> buf(new char[logLength + 1]);

		glGetShaderInfoLog(shader, logLength, NULL, buf.get());
		std::cout << "Error compiling shader:" << std::endl << buf.get() << std::endl;
	}
#endif

	return shader;
}

void myr::Shader::locateUniforms(const std::vector<std::string> uniforms)
{
	for(auto uniform : uniforms)
		uniformLocations.insert(std::make_pair(uniform, glGetUniformLocation(program, uniform.c_str())));
}