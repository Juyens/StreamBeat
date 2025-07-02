#pragma once

#include "Console.h"
#include "Vector2.h"
#include "BoxStyle.h"
#include "Palette.h"
#include "PalettePresets.h"
#include "Art.h"

#include <vector>
#include <string>

namespace sb
{
	class Drawing
	{
	public:
		static void drawText(int x, int y, const std::string& text, const Palette& palette = PalettePresets::Default);
		static void drawTextCenter(int y, const std::string& text, const Palette& palette = PalettePresets::Default);
		static void drawLine(int x1, int y1, int x2, int y2, char ch = '*', const Palette& palette = PalettePresets::Default);
		static void drawBox(int x, int y, int width, int height, const BoxStyle& style = BoxStyles::SingleLineBox, 
			const Palette& palette = PalettePresets::Default);
		static void drawArt(int x, int y, const std::vector<std::string>& art, const Palette& palette);
	};
}
