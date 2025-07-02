#include "Label.h"
#include "Drawing.h"

namespace sb
{
	Label::Label() = default;

	Label::Label(const Vector2i& position, const std::string& text)
		: Widget(position, { static_cast<int>(text.length()), 1 })
		, text_(text) {}

	void Label::setText(const std::string& text)
	{
		text_ = text;
		size_ = { static_cast<int>(text.length()), 1 };
	}

	void Label::setBorderVisible(bool visible)
	{
		isBorderVisible_ = visible;
		updateSize();
	}

	void Label::render()
	{
		const int paddingX = 2;
		const int minWidth = 4;
		const int height = 3;

		const int contentWidth = static_cast<int>(text_.size()) + paddingX * 2;
		const int width = std::max(contentWidth, minWidth);

		const int boxX = getPosition().x();
		const int boxY = getPosition().y();

		if (isBorderVisible_)
		{
			Drawing::drawBox(boxX, boxY, width, height, BoxStyles::UnderscoreLineBox, borderPalette_);
		}

		const int textX = boxX + (isBorderVisible_ ? (width - static_cast<int>(text_.size())) / 2 : 0);
		const int textY = boxY + (isBorderVisible_ ? height / 2 : 0);

		Drawing::drawText(textX, textY, text_, textPalette_);
	}

	void Label::updateSize()
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