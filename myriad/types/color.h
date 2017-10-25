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
		Color(const Color &color);
		Color(const unsigned int hex);
		Color(const float r, const float g, const float b);
		Color(const float r, const float g, const float b, const float a);

		Color &operator+=(const Color &color);
		Color &operator-=(const Color &color);
		Color &operator*=(const Color &color);
		Color &operator*=(const float f);
		Color operator+(const Color &color) const;
		Color operator-(const Color &color) const;
		Color operator*(const Color &color) const;
		Color operator*(const float f) const;

		bool operator==(const Color &color) const;
		bool operator!=(const Color &color) const;

		float getRed() const;
		float getGreen() const;
		float getBlue() const;
		float getAlpha() const;
		float *getArray();

		static const Color
			WHITE,
			BLACK,
			RED,
			GREEN,
			BLUE,
			YELLOW,
			MAGENTA,
			CYAN;
	};
}