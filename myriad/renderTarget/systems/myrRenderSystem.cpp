#include "myrRenderSystem.h"

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
}

void myr::RenderSystem::render()
{

}