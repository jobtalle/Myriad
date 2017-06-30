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
			SpriteDecoder &decoder,
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
		void setFrame(const unsigned int frame);
		void animate(const float seconds);

	private:
		struct FrameData
		{
			FrameData(
				const std::string name,
				const Atlas::Location location,
				const float duration)
				:name(name), location(location), duration(duration) {}

			std::string name;
			Atlas::Location location;
			float duration;
		};

		std::vector<FrameData> frames;
		unsigned int currentFrame;
		float frameCounter;

		void load(const std::string name, SpriteDecoder &decoder);
		const Atlas::Location &getLocation() const;
	};
}