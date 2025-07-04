#include "TextBox.h"
#include "Drawing.h"
#include "BoxStyle.h"
#include "PalettePresets.h"
#include "Console.h"

namespace sb
{
	TextBox::TextBox()
		: Interactive()
	{
		setSize({ 30, 3 });
	}

	TextBox::TextBox(const Vector2i& position, const Vector2i& size)
		: Interactive(position, size) {}

	void TextBox::setText(const std::string& text)
	{
		text_ = text;
		cursor_.setIndex(static_cast<int>(text.size()));
	}

	const std::string& TextBox::getText() const
	{
		return text_;
	}

	void TextBox::handleInput(const InputEvent& ev)
	{
		if (!hasFocus()) return;

		if (ev.character.has_value())
		{
			text_.insert(cursor_.getIndex(), 1, *ev.character);
			cursor_.insert();
		}
		else if (ev.specialKey.has_value())
		{
			switch (*ev.specialKey)
			{
			case Key::Enter:
				if (onEnter_) onEnter_();
				break;
			case Key::Backspace:
				if (cursor_.getIndex() > 0)
				{
					text_.erase(cursor_.getIndex() - 1, 1);
					cursor_.eraseBefore();
				}
				break;
			case Key::Delete:
				if (cursor_.getIndex() < static_cast<int>(text_.size()))
				{
					text_.erase(cursor_.getIndex(), 1);
					cursor_.eraseAfter(static_cast<int>(text_.size()));
				}
				break;
			default:
				break;
			}
		}
	}

	void TextBox::render()
	{
		if (!isVisible())
			return;

		Palette activePalette = getBorderPalette();

		if (hasActive() && hasFocus())
		{
			activePalette = getFocusPalette();
			cursor_.activate();
		}
		else if (!hasActive() && hasFocus())
		{
			activePalette = getInactivePalette();
			cursor_.deactivate();
		}

		Drawing::drawBox(position_.x(), position_.y(), size_.x(), size_.y(), BoxStyles::SingleLineBox, activePalette);

		const int paddingX = 1;
		const int textAreaWidth = size_.x() - paddingX * 2;
		const int textX = position_.x() + paddingX;
		const int textY = position_.y() + size_.y() / 2;

		cursor_.clampScroll(textAreaWidth);

		std::string visibleText = text_.substr(cursor_.getScrollOffset(), textAreaWidth);
		if (static_cast<int>(visibleText.size()) < textAreaWidth)
			visibleText += std::string(textAreaWidth - visibleText.size(), ' ');

		Drawing::drawText(textX, textY, visibleText);

		cursor_.updateBlink();
		if (hasFocus() && cursor_.isVisible())
		{
			int cursorRel = cursor_.getIndex() - cursor_.getScrollOffset();
			if (cursorRel >= 0 && cursorRel < textAreaWidth)
			{
				const int cursorX = textX + cursorRel;
				Drawing::drawText(cursorX, textY, "_");
			}
		}
	}

	void TextBox::reset()
	{
		text_.clear();
		cursor_.reset();
		activate();
	}

	void TextBox::onFocus()
	{
		cursor_.show();
	}

	void TextBox::onBlur()
	{
		cursor_.hide();
	}
}