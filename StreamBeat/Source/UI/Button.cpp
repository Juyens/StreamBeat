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

	Button::Button(const Vector2i& position, std::string label)
		: Interactive(
			position,
			Vector2i(std::max(static_cast<int>(label.size()) + 4, 4), 3),
			PalettePresets::Default
		)
		, label_(std::move(label)) {}

	void Button::setLabel(const std::string& text)
	{
		label_ = text;
		updateSize();
	}

	void Button::render()
	{
		const Palette& activePalette = hasFocus() ? getFocusPalette() : getPalette();

		const int paddingX = 2;
		const int minWidth = 4;
		const int height = 3;
		const int width = std::max(static_cast<int>(label_.size()) + paddingX * 2, minWidth);

		Drawing::drawBox(getPosition().x(), getPosition().y(), width, height, BoxStyles::SingleLineBox, activePalette);

		const int textX = getPosition().x() + (width - static_cast<int>(label_.size())) / 2;
		const int textY = getPosition().y() + height / 2;

		Drawing::drawText(textX, textY, label_, activePalette);
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

	void Button::updateSize()
	{
		const int paddingX = 2;
		const int minWidth = 4;
		const int height = 3;
		const int width = std::max(static_cast<int>(label_.size()) + paddingX * 2, minWidth);
		setSize(width, height);
	}
}