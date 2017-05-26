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
		virtual void flush() = 0;
		virtual void render(const RenderBatch &batch, Shader *shader);
		virtual void push(const void *element) = 0;
		virtual size_t getBufferIndex() const = 0;

	protected:
		virtual size_t getBufferSizeof() const = 0;
		virtual const void *getBufferData() const = 0;
		virtual void vaoConfigure() {};
		void vaoBind() const;
		void vaoRelease() const;

	private:
		static const size_t BUFFER_CAPACITY_INITIAL = 1;

		size_t bufferCapacity = 0;
		GLuint vao;
		GLuint buffer;

		void upload(const RenderBatch &batch);
	};
}