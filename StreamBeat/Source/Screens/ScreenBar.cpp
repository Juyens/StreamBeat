#include "ScreenBar.h"

namespace sb
{
	void ScreenBar::render()
	{

	}

	void ScreenBar::handlerInput(const InputEvent& ev)
	{

	}

	void ScreenBar::focus()
	{
		hasFocus_ = true;
	}

	void ScreenBar::blur()
	{
		hasFocus_ = false;
	}

	bool ScreenBar::hasFocus() const
	{
		return hasFocus_;
	}
}
