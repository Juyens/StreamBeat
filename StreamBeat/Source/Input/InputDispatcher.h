#pragma once

#include "Interactive.h"
#include "KeyboardInput.h"
#include "Key.h"

namespace sb
{
	class InputDispatcher
	{
	public:
		void setFocus(Interactive* widget)
		{
			if (focused_ == widget)
				return;

			if (focused_)
				focused_->blur();

			focused_ = widget;

			if (focused_)
				focused_->focus();
		}

		void clearFocus()
		{
			if (focused_)
			{
				focused_->blur();
				focused_ = nullptr;
			}
		}

		Interactive* getFocused() const { return focused_; }

		void update()
		{
			if (!focused_)
				return;

			auto keyOpt = KeyboardInput::getPressedKey();
			if (!keyOpt.has_value())
				return;

			Key key = *keyOpt;

			if (isArrowKey(key))
			{
				focused_->handleSpecialKey(static_cast<int>(key));
			}

			else if (isPrintableKey(key))
			{
				focused_->handleKey(mapKeyToChar(key));
			}
		}

	private:
		Interactive* focused_ = nullptr;

		bool isArrowKey(Key key)
		{
			return key == Key::Up || key == Key::Down || key == Key::Left || key == Key::Right;
		}

		bool isPrintableKey(Key key)
		{
			return (key >= Key::A && key <= Key::Z) ||
				key == Key::Space || key == Key::Backspace || key == Key::Enter;
		}

		char mapKeyToChar(Key key)
		{
			if (key == Key::Space) return ' ';
			if (key == Key::Enter) return '\r';
			if (key == Key::Backspace) return '\b';

			if (key >= Key::A && key <= Key::Z)
				return 'A' + (static_cast<int>(key) - static_cast<int>(Key::A));

			return '\0';
		}
	};
}
