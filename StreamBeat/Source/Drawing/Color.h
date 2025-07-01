#pragma once

#include "WindowHeader.h"

namespace sb
{
	namespace Color::Foreground
	{
		constexpr WORD Black = 0;
		constexpr WORD DarkBlue = FOREGROUND_BLUE;
		constexpr WORD DarkGreen = FOREGROUND_GREEN;
		constexpr WORD DarkRed = FOREGROUND_RED;
		constexpr WORD DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE;
		constexpr WORD DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE;
		constexpr WORD DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN;
		constexpr WORD Gray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

		constexpr WORD Bright = FOREGROUND_INTENSITY;

		constexpr WORD LightBlue = Bright | DarkBlue;
		constexpr WORD LightGreen = Bright | DarkGreen;
		constexpr WORD LightRed = Bright | DarkRed;
		constexpr WORD LightCyan = Bright | DarkCyan;
		constexpr WORD LightMagenta = Bright | DarkMagenta;
		constexpr WORD LightYellow = Bright | DarkYellow;
		constexpr WORD White = Bright | Gray;
	}

	namespace Color::Background
	{
		constexpr WORD Black = 0;
		constexpr WORD DarkBlue = BACKGROUND_BLUE;
		constexpr WORD DarkGreen = BACKGROUND_GREEN;
		constexpr WORD DarkRed = BACKGROUND_RED;
		constexpr WORD DarkCyan = BACKGROUND_GREEN | BACKGROUND_BLUE;
		constexpr WORD DarkMagenta = BACKGROUND_RED | BACKGROUND_BLUE;
		constexpr WORD DarkYellow = BACKGROUND_RED | BACKGROUND_GREEN;
		constexpr WORD Gray = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

		constexpr WORD Bright = BACKGROUND_INTENSITY;

		constexpr WORD LightBlue = Bright | DarkBlue;
		constexpr WORD LightGreen = Bright | DarkGreen;
		constexpr WORD LightRed = Bright | DarkRed;
		constexpr WORD LightCyan = Bright | DarkCyan;
		constexpr WORD LightMagenta = Bright | DarkMagenta;
		constexpr WORD LightYellow = Bright | DarkYellow;
		constexpr WORD White = Bright | Gray;
	}
}