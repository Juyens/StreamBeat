#include "Interactive.h"

namespace sb
{
	Interactive::Interactive()
		: Widget() {}

	Interactive::Interactive(const Vector2i& position, const Vector2i& size, bool focused)
		: Widget(position, size)
		, hasFocus_(focused) {}

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

	void Interactive::setInactivePalette(const Palette& palette)
	{
		inactivePalette_ = palette;
	}

	const Palette& Interactive::getInactivePalette() const
	{
		return inactivePalette_;
	}

	void Interactive::setInactiveForeground(WORD foreground)
	{
		inactivePalette_.foreground = foreground;
	}

	void Interactive::setInactiveBackground(WORD background)
	{
		inactivePalette_.background = background;
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

	void Interactive::setMonopolizeFocus(bool enable)
	{
		monopolizeFocus_ = enable;
	}

	bool Interactive::wantsExclusiveInput() const
	{
		return monopolizeFocus_;
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

	void Interactive::activate()
	{
		active_ = true;
	}

	void Interactive::deactivate()
	{
		active_ = false;
	}

	bool Interactive::hasActive() const
	{
		return active_;
	}
}