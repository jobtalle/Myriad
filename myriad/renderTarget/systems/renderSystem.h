#pragma once

#include "renderSystems.h"
#include "renderBatch.h"
#include "renderer/opengl/opengl.h"

namespace myr
{
	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
		void flush();
		virtual void render(const RenderBatch &batch);
		virtual void push(const void *element);

	protected:
		virtual size_t getBufferSize() const = 0;
		virtual const void *getBufferData() const = 0;

	private:
		enum flags {
			UPLOADED = 0x01
		};

		unsigned char flags = 0;
		size_t bufferIndex = 0;
		size_t bufferCapacity = 0;
		static const size_t bufferCapacityInitial = 64;
		GLuint buffer;

		void upload();
	};
}