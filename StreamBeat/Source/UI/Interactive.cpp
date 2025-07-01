#include "Interactive.h"

namespace sb
{
	Interactive::Interactive()
		: Widget() {}

	Interactive::Interactive(const Vector2i& position, const Vector2i& size,
		bool focused, const Palette& borderPalette)
		: Widget(position, size)
		, hasFocus_(focused) 
		, borderPalette_(borderPalette) {}

	void Interactive::setBorderPalette(const Palette& palette)
	{
		borderPalette_ = palette;
	}

	const Palette& Interactive::getBorderPalette() const
	{
		return borderPalette_;
	}

	void Interactive::setBorderForeground(WORD foreground)
	{
		borderPalette_.foreground = foreground;
	}

	void Interactive::setBorderBackground(WORD background)
	{
		borderPalette_.background = background;
	}

	void Interactive::setFocusPalette(const Palette& palette)
	{
		focusPalette_ = palette;
	}

	const Palette& Interactive::getFocusPalette() const
	{
		return focusPalette_;
	}

	void Interactive::setFocusForeground(WORD foreground)
	{
		focusPalette_.foreground = foreground;
	}

	void Interactive::setFocusBackground(WORD background)
	{
		focusPalette_.background = background;
	}

	void Interactive::setOnEnter(std::function<void()> callback)
	{
		onEnter_ = std::move(callback);
	}

	void Interactive::setFocus(bool isFocus)
	{
		if (isFocus)
			focus();
		else
			blur();
	}

	bool Interactive::hasFocus() const
	{
		return hasFocus_;
	}

	void Interactive::focus()
	{
		if (!hasFocus_)
		{
			hasFocus_ = true;
			onFocus();
		}
	}

	void Interactive::blur()
	{
		if (hasFocus_)
		{
			hasFocus_ = false;
			onBlur();
		}
	}
}