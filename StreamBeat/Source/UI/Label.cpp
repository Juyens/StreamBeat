#include "Label.h"
#include "Drawing.h"

namespace sb
{
	Label::Label() = default;

	Label::Label(const Vector2i& position, const std::string& text)
		: Widget(position, Vector2i(static_cast<int>(text.length()), 1), PalettePresets::Default)
		, text_(text) {}

	void Label::setText(const std::string& text)
	{
		text_ = text;
		size_ = { static_cast<int>(text.length()), 1 };
	}

	const std::string& Label::getText() const
	{
		return text_;
	}

	void Label::render()
	{
		Drawing::drawText(position_.x(), position_.y(), text_, palette_);
	}
}