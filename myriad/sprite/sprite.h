#pragma once

#include <cstdint>
#include <memory>

#include "renderer/atlas.h"
#include "spriteDecoder.h"

namespace myr
{
	class Sprite final
	{
	public:
		Sprite();
		Sprite(const std::string name, SpriteDecoder *decoder);
		~Sprite();
		bool isSet() const;
		void draw();

	private:
		std::string name;
		std::unique_ptr<SpriteDecoder> decoder;
		myr::Atlas::Location location;
		uint8_t flags;

		void load();

		enum flags
		{
			LOADED = 0x01,
			UNSET = 0x02
		};
	};
}