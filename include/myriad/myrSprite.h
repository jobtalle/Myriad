#pragma once

#include <cstdint>
#include <string>
#include <archive/archive.h>

#include "myrRect.h"

namespace myr {
	class Sprite {
	public:
		Sprite(Archive *archive, const std::string name);
		~Sprite();
		void draw();

	private:
		uint8_t flags;
		char *pixels;

		void load();

		enum flags {
			LOADED = 0x01
		};
	};
}