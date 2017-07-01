#include "renderLines.h"

myr::RenderLines::RenderLines()
:RenderSystem(), instanceCapacity(INSTANCE_CAPACITY_INITIAL), instanceCount(0)
{
	vaoBind();

	glGenBuffers(1, &line);
	glBindBuffer(GL_ARRAY_BUFFER, line);
	glBufferData(GL_ARRAY_BUFFER, getLine().size() * sizeof(float), getLine().data(), GL_STATIC_DRAW);

	configureBufferAttribs();

	bindBuffer();

	configureInstanceAttribs();

	vaoRelease();

	instances = (myr::LineAttributes*)malloc(sizeof(LineAttributes)* instanceCapacity);
}

myr::RenderLines::~RenderLines()
{
	free(instances);

	glDeleteBuffers(1, &line);
}

void myr::RenderLines::render(Shader *shader)
{
	RenderSystem::render(shader);

	vaoBind();
	glDrawArraysInstanced(GL_LINES, 0, 2, (GLsizei)instanceCount);
	vaoRelease();

	instanceCount = 0;
}

void myr::RenderLines::push(const void *element)
{
	if(instanceCount == instanceCapacity)
	{
		instanceCapacity <<= 1;

		instances = (LineAttributes*)realloc(instances, instanceCapacity * sizeof(LineAttributes));
	}

	instances[instanceCount++] = *((LineAttributes*)element);
}

size_t myr::RenderLines::getBufferIndex() const
{
	return instanceCount;
}

size_t myr::RenderLines::getBufferSizeof() const
{
	return sizeof(LineAttributes);
}

const void *myr::RenderLines::getBufferData() const
{
	return instances;
}

void myr::RenderLines::configureBufferAttribs() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(float), NULL);
}

void myr::RenderLines::configureInstanceAttribs() const
{
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineAttributes),
		(GLvoid*)offsetof(LineAttributes, attributePoints));

	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(LineAttributes),
		(GLvoid*)offsetof(LineAttributes, attributeColor));
}