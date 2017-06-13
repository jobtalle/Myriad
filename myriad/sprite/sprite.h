#pragma once

#include <cstdint>
#include <memory>

#include "renderer/atlas.h"
#include "types/transform.h"
#include "spriteDecoder.h"

namespace myr
{
	class Sprite final
	{
	public:
		Sprite(
			const std::string &name,
			SpriteDecoder *decoder,
			const int originX = 0,
			const int originY = 0);
		~Sprite();
		void draw(
			const Transform &transform);
		void draw(
			const Transform &transform,
			const Vector &scale);
		void draw(
			const int x,
			const int y);
		void draw(
			const int x,
			const int y,
			const Vector &scale);
		void draw(
			const int x,
			const int y,
			const Vector &scale,
			const float angle);
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