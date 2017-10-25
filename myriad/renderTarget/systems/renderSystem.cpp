#include "renderSystem.h"

myr::RenderSystem::RenderSystem(const size_t instanceSize)
:instanceCapacity(0), instanceCount(0), instanceSize(instanceSize), instances(nullptr)
{
	glGenBuffers(1, &buffer);
	glGenVertexArrays(1, &vao);
}

myr::RenderSystem::~RenderSystem()
{
	free(instances);

	glDeleteBuffers(1, &buffer);
	glDeleteVertexArrays(1, &vao);
}

void myr::RenderSystem::render(Shader *shader)
{
	upload();

	shader->bind();
}

void myr::RenderSystem::push(const void *element)
{
	if(ensureCapacity())
		instances = realloc(instances, instanceSize * instanceCapacity);

	memcpy((char*)instances + instanceSize * instanceCount++, element, instanceSize);
}

void myr::RenderSystem::vaoBind() const
{
	glBindVertexArray(vao);
}

void myr::RenderSystem::vaoRelease() const
{
	glBindVertexArray(0);
}

void myr::RenderSystem::bufferBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

bool myr::RenderSystem::ensureCapacity()
{
	if(instanceCount == instanceCapacity)
	{
		if(instanceCapacity == 0)
			instanceCapacity = INSTANCE_CAPACITY_INITIAL;
		else
			instanceCapacity <<= 1;

		return true;
	}

	return false;
}

void myr::RenderSystem::upload()
{
	bufferBind();
	
	if(instanceCount > bufferCapacity)
	{
		while(instanceCount > bufferCapacity)
		{
			if(bufferCapacity == 0)
				bufferCapacity = BUFFER_CAPACITY_INITIAL;
			else
				bufferCapacity <<= 1;
		}

		glBufferData(GL_ARRAY_BUFFER, bufferCapacity * instanceSize, NULL, GL_DYNAMIC_DRAW);
	}
	
	glBufferSubData(
		GL_ARRAY_BUFFER, 
		0,
		instanceCount * instanceSize,
		instances);
}