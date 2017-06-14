#pragma once

#include <cstdint>
#include <memory>

#include "renderer/atlas.h"
#include "spriteDecoder.h"
#include "quad/quad.h"

namespace myr
{
	class Sprite final : public Quad
	{
	public:
		Sprite(
			const std::string &name,
			SpriteDecoder *decoder,
			const int originX = 0,
			const int originY = 0);
		~Sprite();
		void draw(
			const Transform &transform) override;
		void draw(
			const Transform &transform,
			const Vector &scale) override;
		void draw(
			const int x,
			const int y) override;
		void draw(
			const int x,
			const int y,
			const Vector &scale) override;
		void draw(
			const int x,
			const int y,
			const Vector &scale,
			const float angle) override;
		void setOrigin(const int originX, const int originY);
		short int getWidth() const;
		short int getHeight() const;
		int getOriginX() const;
		int getOriginY() const;

	private:
		std::string name;
		std::unique_ptr<SpriteDecoder> decoder;
		myr::Atlas::Location location;
		short int width;
		short int height;
		int originX;
		int originY;
		Vector origin;

		void load();
	};
}