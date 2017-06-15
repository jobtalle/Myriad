#pragma once

#include "renderer/opengl/opengl.h"
#include "systems/renderSystem.h"
#include "../shader/shader.h"

#include "types/rect.h"
#include "types/color.h"
#include "types/transform.h"

#include <queue>
#include <vector>
#include <memory>

namespace myr
{
	class Renderer;

	class DefaultRenderTarget
	{
		friend class Renderer;
		friend class Sprite;
		friend class RenderTarget;

	public:
		DefaultRenderTarget(
			const Color &clearColor,
			const Rect &size,
			Renderer *renderer);
		virtual ~DefaultRenderTarget();
		Transform getTransform() const;
		void setTransform(const Transform &transform);
		void bind();
		void clear() const;

	protected:
		GLuint fbo;

		void unbind();
		Renderer *getRenderer() const;
		static DefaultRenderTarget *getCurrent();
		void createRenderSystems();

	private:
		RenderSystems currentSystem;
		std::unique_ptr<RenderSystem> systems[RENDER_SYSTEM_COUNT];
		Shader *shaders[RENDER_SYSTEM_COUNT];
		Renderer *renderer;
		Color clearColor;
		Transform transform;
		unsigned char flags;
		
		virtual Rect getResolution() const;
		virtual void resize();
		void render(const RenderSystems system, const void *element);
		void render();

		enum flags {
			BOUND = 0x01
		};
	};
}