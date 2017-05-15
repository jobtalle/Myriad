#pragma once

namespace myr
{
	class Color
	{
		union
		{
			struct
			{
				float r, g, b;
			};

			float v[3];
		};

	public:
		Color(const float r, const float g, const float b);

		Color operator+(const Color &color);
		Color operator-(const Color &color);
		Color operator*(const float f);

		float getRed() const;
		float getGreen() const;
		float getBlue() const;
		float *getArray();
	};
}