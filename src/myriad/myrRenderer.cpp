#include <opengl/opengl.h>
#include <myriad/myrRenderer.h>

#include <iostream>

myr::Renderer::Renderer(const Color clearColor, const Rect size)
	:clearColor(clearColor), renderTarget(size)
{
	ogl_LoadFunctions();
}

myr::Renderer::~Renderer()
{
	
}

void myr::Renderer::render() const
{
	glClearColor(clearColor.getRed(), clearColor.getGreen(), clearColor.getBlue(), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
