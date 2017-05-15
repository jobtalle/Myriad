#pragma once

#include <cstdint>
#include <memory>

#include "archive/archive.h"
#include "myriad/renderer/myrAtlas.h"

namespace myr {
	class Sprite {
	public:
		Sprite();
		Sprite(ArchiveFile *file);
		~Sprite();
		bool isSet() const;
		void draw();

	private:
		myr::Atlas::Location location;
		std::auto_ptr<ArchiveFile> file;
		uint8_t flags;

		void load();

		enum flags {
			LOADED = 0x01,
			UNSET = 0x02
		};
	};
}