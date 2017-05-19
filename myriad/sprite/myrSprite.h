#pragma once

#include <cstdint>
#include <memory>

#include "renderer/myrAtlas.h"
#include "myrSpriteDecoder.h"

namespace myr
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(const std::string name, SpriteDecoder *decoder);
		~Sprite();
		bool isSet() const;
		void draw();

	private:
		std::string name;
		std::auto_ptr<SpriteDecoder> decoder;
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