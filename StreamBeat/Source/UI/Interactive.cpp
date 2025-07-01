#include "Interactive.h"

namespace sb
{
	Interactive::Interactive()
		: Widget() {}

	Interactive::Interactive(const Vector2i& position, const Vector2i& size, const Palette& palette,
		bool focused, const Palette& focusPalette)
		: Widget(position, size, palette)
		, hasFocus_(focused) 
		, focusPalette_(focusPalette) {}

	void Interactive::setFocusPalette(const Palette& palette)
	{
		focusPalette_ = palette;
	}

	const Palette& Interactive::getFocusPalette() const
	{
		return focusPalette_;
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