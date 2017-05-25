#pragma once

#include "renderer/opengl/opengl.h"
#include "systems/renderBatch.h"
#include "systems/renderSystem.h"

#include "types/rect.h"
#include "types/color.h"

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

	public:
		DefaultRenderTarget(const Color clearColor, const Rect rect, Renderer *renderer);
		Rect getRect() const;
		void bind();
		void clear() const;

	protected:
		Rect rect;
		GLuint fbo;

		void setRect(const Rect rect);
		void unbind();
		Renderer *getRenderer() const;
		static DefaultRenderTarget *getCurrent();

	private:
		std::queue<RenderBatch> batches;
		std::unique_ptr<RenderSystem> systems[RENDER_SYSTEM_COUNT];
		Renderer *renderer;
		Color clearColor;
		unsigned char flags;
		
		void render(const RenderSystems system, const void *element);
		void render();
		void createRenderSystems();

		enum flags {
			BOUND = 0x01
		};
	};
}