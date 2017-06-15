#pragma once

#include "defaultRenderTarget.h"
#include "quad/quad.h"

namespace myr
{
	class RenderTarget final : public DefaultRenderTarget, public Quad
	{
	public:
		RenderTarget(const Color &clearColor, const Rect &rect, Renderer *renderer);
		~RenderTarget() override;
		void draw(
			const Transform &transform) const override;
		void draw(
			const Transform &transform,
			const Vector &scale) const override;
		void draw(
			const int x,
			const int y) const override;
		void draw(
			const int x,
			const int y,
			const Vector &scale) const override;
		void draw(
			const int x,
			const int y,
			const Vector &scale,
			const float angle) const override;
		using DefaultRenderTarget::setRect;

	private:
		void generateFBO();
		void deleteFBO();
		void resize();

		GLuint texture;
	};
}