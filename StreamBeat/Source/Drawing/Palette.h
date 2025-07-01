#pragma once

#include "WindowHeader.h"
#include "Color.h"

namespace sb
{
	class Palette
	{
	public:
		WORD foreground;
		WORD background;

		constexpr Palette(WORD fg = Color::Foreground::White, WORD bg = Color::Background::Black)
			: foreground(fg), background(bg) {}

		[[nodiscard]] constexpr WORD getAttribute() const
		{
			return foreground | background;
		}

		[[nodiscard]] constexpr Palette inverted() const
		{
			return Palette{ background, foreground };
		}
	};
}
