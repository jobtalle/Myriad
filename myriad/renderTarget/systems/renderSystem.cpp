#include "renderSystem.h"

#include <iostream> // TODO: Debug

myr::RenderSystem::RenderSystem()
{
	glGenBuffers(1, &buffer);
	glGenVertexArrays(1, &vao);
}

myr::RenderSystem::~RenderSystem()
{
	glDeleteBuffers(1, &buffer);
	glDeleteVertexArrays(1, &vao);
}

void myr::RenderSystem::flush()
{
	flags = 0;
}

void myr::RenderSystem::render(const RenderBatch &batch, Shader *shader)
{
	if(!(flags & UPLOADED))
		upload();
	
	shader->bind();
}

void myr::RenderSystem::upload()
{
	flags |= UPLOADED;
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	if(getBufferSize() > bufferCapacity)
	{
		while(getBufferSize() > bufferCapacity)
		{
			if(bufferCapacity == 0)
				bufferCapacity = bufferCapacityInitial;
			else
				bufferCapacity <<= 1;
		}

		glBufferData(GL_ARRAY_BUFFER, bufferCapacity, NULL, GL_DYNAMIC_DRAW);
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, getBufferSize(), getBufferData());
}