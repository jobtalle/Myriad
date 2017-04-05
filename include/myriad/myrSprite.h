#pragma once

#include <cstdint>
#include <string>
#include <archive/archive.h>

#include "myrRect.h"

namespace myr {
	class Sprite {
	public:
		Sprite();
		Sprite(const ArchiveFile &file);
		~Sprite();
		bool isSet() const;
		void draw();

	private:
		const ArchiveFile file;
		uint8_t flags;

		void load();

		enum flags {
			LOADED = 0x01,
			UNSET = 0x02
		};
	};
}