#pragma once

#include "Color.h"
#include "Palette.h"

namespace sb::PalettePresets
{
	inline constexpr Palette Default        { Color::Foreground::White,       Color::Background::Black };
	inline constexpr Palette Focus			{ Color::Foreground::LightGreen,  Color::Background::Black };
	inline constexpr Palette Inactive		{ Color::Foreground::DarkGray,    Color::Background::Black };
	inline constexpr Palette Selected		{ Color::Foreground::DarkCyan,    Color::Background::Black };
}