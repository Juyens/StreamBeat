#pragma once

#include <string>

namespace sb
{
	struct BoxStyle
	{
		char topLeft;
		char topRight;
		char bottomLeft;
		char bottomRight;
		char horizontal;
		char vertical;
	};

	namespace BoxStyles
	{
		// Double-line pseudo graphic box (CP850 compatible)
		inline constexpr BoxStyle DoubleLineBox{
			'\xC9', // ╔
			'\xBB', // ╗
			'\xC8', // ╚
			'\xBC', // ╝
			'\xCD', // ═
			'\xBA'  // ║
		};

		// Single-line pseudo graphic box (CP850 compatible)
		inline constexpr BoxStyle SingleLineBox{
			'\xDA', // ┌
			'\xBF', // ┐
			'\xC0', // └
			'\xD9', // ┘
			'\xC4', // ─
			'\xB3'  // │
		};
	}
}