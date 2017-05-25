#include "renderSystem.h"

myr::RenderSystem::RenderSystem()
{
	glGenBuffers(1, &buffer);
}

myr::RenderSystem::~RenderSystem()
{
	glDeleteBuffers(1, &buffer);
}

void myr::RenderSystem::flush()
{
	bufferIndex = 0;
	flags = 0;
}

void myr::RenderSystem::render(const RenderBatch &batch)
{
	if(!(flags & UPLOADED))
		upload();
}

void myr::RenderSystem::push(const void *element)
{

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