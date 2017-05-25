#pragma once

#include "renderSystems.h"
#include "renderer/opengl/opengl.h"

namespace myr
{
	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
		void flush();
		virtual void render();

	private:
		size_t bufferIndex = 0;
		size_t bufferCapacity = 0;
		GLuint buffer;
	};
}