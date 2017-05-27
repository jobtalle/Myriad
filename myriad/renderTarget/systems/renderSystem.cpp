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

void myr::RenderSystem::render(const RenderBatch &batch, Shader *shader)
{
	upload(batch);

	shader->bind();
}

void myr::RenderSystem::vaoBind() const
{
	glBindVertexArray(vao);
}

void myr::RenderSystem::vaoRelease() const
{
	glBindVertexArray(0);
}

void myr::RenderSystem::bindBuffer() const
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void myr::RenderSystem::upload(const RenderBatch &batch)
{
	const size_t requiredSize = batch.getEnd() - batch.getStart();
	
	bindBuffer();

	if(requiredSize > bufferCapacity)
	{
		while(requiredSize > bufferCapacity)
		{
			if(bufferCapacity == 0)
				bufferCapacity = BUFFER_CAPACITY_INITIAL;
			else
				bufferCapacity <<= 1;
		}

		glBufferData(GL_ARRAY_BUFFER, bufferCapacity * getBufferSizeof(), NULL, GL_DYNAMIC_DRAW);
	}
	
	glBufferSubData(
		GL_ARRAY_BUFFER, 
		0,
		requiredSize * getBufferSizeof(),
		(char*)getBufferData() + batch.getStart() * getBufferSizeof());
}