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
			const Vector &origin = Vector(0, 0));
		~Sprite();
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
		void setOrigin(const int originX, const int originY);

		unsigned int getFrame() const;
		unsigned int getFrames() const;
		void animate(const float seconds);

	private:
		std::string name;
		std::unique_ptr<SpriteDecoder> decoder;
		std::vector<Atlas::Location> locations;
		float frame;

		void load();
		const Atlas::Location &getLocation() const;
	};
}