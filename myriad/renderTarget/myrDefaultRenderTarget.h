#pragma once

#include "renderer/opengl/opengl.h"
#include "systems/myrRenderBatch.h"
#include "systems/myrRenderSystem.h"

#include "types/myrRect.h"
#include "types/myrColor.h"

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

		void render();
		void createRenderSystems();
		void flushRenderSystems();

		enum flags {
			BOUND = 0x01
		};
	};
}