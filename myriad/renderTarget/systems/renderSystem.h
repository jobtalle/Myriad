#pragma once

#include "renderSystems.h"
#include "shader/shader.h"
#include "renderer/opengl/opengl.h"

namespace myr
{
	class RenderSystem
	{
	public:
		RenderSystem();
		virtual ~RenderSystem();
		virtual void render(Shader *shader);
		virtual void push(const void *element) = 0;
		virtual size_t getBufferIndex() const = 0;

	protected:
		virtual size_t getBufferSizeof() const = 0;
		virtual const void *getBufferData() const = 0;
		void vaoBind() const;
		void vaoRelease() const;
		void bindBuffer() const;

	private:
		static const size_t BUFFER_CAPACITY_INITIAL = 1;

		size_t bufferCapacity = 0;
		GLuint vao;
		GLuint buffer;

		void upload();
	};
}