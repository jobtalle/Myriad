#pragma once

#include "renderSystems.h"
#include "shader/shader.h"
#include "renderer/opengl/opengl.h"

namespace myr
{
	class RenderSystem
	{
		friend class RenderRenderTargets;

	public:
		RenderSystem(const size_t instance_size);
		virtual ~RenderSystem();
		virtual void render(Shader *shader);
		virtual void push(const void *element);

	protected:
		void vaoBind() const;
		void vaoRelease() const;
		void bindBuffer() const;

		bool ensureCapacity();

		static const size_t INSTANCE_CAPACITY_INITIAL = 1;
		void *instances;
		size_t instanceCount;
		size_t instanceCapacity;

	private:
		static const size_t BUFFER_CAPACITY_INITIAL = 1;

		size_t instanceSize;
		size_t bufferCapacity;
		GLuint vao;
		GLuint buffer;

		void upload();
	};
}