#pragma once

#include "renderSystems.h"
#include "renderBatch.h"
#include "shader/shader.h"
#include "renderer/opengl/opengl.h"

namespace myr
{
	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
		virtual void flush();
		virtual void render(const RenderBatch &batch, Shader *shader);
		virtual void push(const void *element) = 0;
		virtual size_t getBufferIndex() const = 0;

	protected:
		virtual size_t getBufferSize() const = 0;
		virtual const void *getBufferData() const = 0;
		virtual void vaoConfigure() {};
		void vaoBind() const;
		void vaoRelease() const;

	private:
		enum flags {
			UPLOADED = 0x01
		};

		unsigned char flags = 0;
		size_t bufferCapacity = 0;
		static const size_t bufferCapacityInitial = 64;
		GLuint vao;
		GLuint buffer;

		void upload();
	};
}