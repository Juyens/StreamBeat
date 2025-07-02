#include "Drawing.h"

namespace sb
{
	void Drawing::drawText(int x, int y, const std::string& text, const Palette& palette)
	{
		Console::writeAt(x, y, text, palette.foreground, palette.background);
	}

	void Drawing::drawTextCenter(int y, const std::string& text, const Palette& palette)
	{
		const auto size = Console::getViewportSize();
		int x = (size.x() - static_cast<int>(text.length())) / 2;
		Console::writeAt(x, y, text, palette.foreground, palette.background);
	}

	void Drawing::drawLine(int x1, int y1, int x2, int y2, char ch, const Palette& palette)
	{
		if (y1 == y2) // Horizontal line
		{
			int from = std::min(x1, x2);
			int to = std::max(x1, x2);
			for (int x = from; x <= to; ++x)
			{
				Console::writeAt(x, y1, std::string(1, ch), palette.foreground, palette.background);
			}
		}
		else if (x1 == x2) // Vertical line
		{
			int from = std::min(y1, y2);
			int to = std::max(y1, y2);
			for (int y = from; y <= to; ++y)
			{
				Console::writeAt(x1, y, std::string(1, ch), palette.foreground, palette.background);
			}
		}
		else
		{
			Console::writeAt(x1, y1, "?", palette.foreground, palette.background);
		}
	}

	void Drawing::drawBox(int x, int y, int width, int height, const BoxStyle& style, const Palette& palette)
	{
		if (width < 2 || height < 2) return;

		Console::writeAt(x, y, std::string(1, style.topLeft), palette.foreground, palette.background);
		Console::writeAt(x + width - 1, y, std::string(1, style.topRight), palette.foreground, palette.background);
		Console::writeAt(x, y + height - 1, std::string(1, style.bottomLeft), palette.foreground, palette.background);
		Console::writeAt(x + width - 1, y + height - 1, std::string(1, style.bottomRight), palette.foreground, palette.background);

		for (int i = 1; i < width - 1; ++i)
		{
			Console::writeAt(x + i, y, std::string(1, style.horizontal), palette.foreground, palette.background);
			Console::writeAt(x + i, y + height - 1, std::string(1, style.horizontal), palette.foreground, palette.background);
		}

		for (int i = 1; i < height - 1; ++i)
		{
			Console::writeAt(x, y + i, std::string(1, style.vertical), palette.foreground, palette.background);
			Console::writeAt(x + width - 1, y + i, std::string(1, style.vertical), palette.foreground, palette.background);
		}
	}

	void Drawing::drawArt(int x, int y, const std::vector<std::string>& art, const Palette& palette)
	{
		for (size_t i = 0; i < art.size(); ++i)
		{
			Console::writeAt(x, y + i, art[i], palette.foreground, palette.background);
		}
	}
}