#pragma once

#include <cstdint>
#include <archive/archive.h>

namespace myr {
	class Sprite {
	public:
		Sprite();
		Sprite(const ArchiveFile &file);
		~Sprite();
		Sprite &operator=(const Sprite &other);
		bool isSet() const;
		void draw();

	private:
		ArchiveFile file;
		uint8_t flags;

		void load();

		enum flags {
			LOADED = 0x01,
			UNSET = 0x02
		};
	};
}