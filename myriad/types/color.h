#pragma once

namespace myr
{
	class Color final
	{
		union
		{
			struct
			{
				float r, g, b, a;
			};

			float v[4];
		};

	public:
		Color(const float r, const float g, const float b);
		Color(const float r, const float g, const float b, const float a);

		Color operator+(const Color &color);
		Color operator-(const Color &color);
		Color operator*(const float f);

		float getRed() const;
		float getGreen() const;
		float getBlue() const;
		float getAlpha() const;
		float *getArray();
	};
}