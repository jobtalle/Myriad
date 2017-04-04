#include <myriad/myrShader.h>

namespace {
	myr::Shader *current = nullptr;
}

myr::Shader::Shader()
{

}

myr::Shader::~Shader()
{

}

void myr::Shader::bind()
{
	if(current != this)
	{
		current = this;
	}
}