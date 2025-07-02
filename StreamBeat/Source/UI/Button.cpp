#include "Button.h"
#include "Drawing.h"
#include "BoxStyle.h"
#include "PalettePresets.h"
#include "Console.h"

namespace sb
{
	Button::Button()
		: Interactive()
	{
		updateSize();
	}

	Button::Button(const Vector2i& position, std::string text)
		: Interactive(position, { std::max(static_cast<int>(text.size()) + 4, 4), 3 })
		, text_(std::move(text)) {}

	void Button::setText(const std::string& text)
	{
		text_ = text;
		updateSize();
	}

	void Button::render()
	{
		Palette activePalette = getBorderPalette();

		if (hasActive() && hasFocus())
		{
			activePalette = getFocusPalette();
		}
		else if (!hasActive() && hasFocus())
		{
			activePalette = getInactivePalette();
		}

		const int paddingX = 2;
		const int minWidth = 4;
		const int height = 3;

		const int contentWidth = static_cast<int>(text_.size()) + paddingX * 2;
		const int width = std::max(contentWidth, minWidth);

		const int boxX = getPosition().x();
		const int boxY = getPosition().y();

		if (isBorderVisible_)
		{
			Drawing::drawBox(boxX, boxY, width, height, BoxStyles::SingleLineBox, activePalette);
		}

		const int textX = boxX + (isBorderVisible_ ? (width - static_cast<int>(text_.size())) / 2 : 0);
		const int textY = boxY + (isBorderVisible_ ? height / 2 : 0);

		Drawing::drawText(textX, textY, text_, activePalette);
	}

	void Button::handleInput(const InputEvent& ev)
	{
		if (!hasFocus()) return;

		if (ev.specialKey.has_value())
		{
			switch (*ev.specialKey)
			{
			case Key::Enter:
				if (onEnter_) onEnter_();
				break;
			default:
				break;
			}
		}
	}

	void Button::reset()
	{
		activate();
	}

	void Button::updateSize()
	{
		if (isBorderVisible_)
		{
			const int paddingX = 2;
			const int minWidth = 4;
			const int height = 3;
			const int width = std::max(static_cast<int>(text_.size()) + paddingX * 2, minWidth);
			setSize({ width, height });
		}
		else
		{
			setSize({ static_cast<int>(text_.length()), 1 });
		}
	}
}