#pragma once

namespace myr {
	class Shader {
		friend class Renderer;

	public:
		Shader();
		~Shader();
		void bind();
	};
}