#pragma once

#include "UI.h"
#include "Console.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "UserManager.h"
#include "Vector2.h"

namespace sb
{
	class ScreenBar
	{
	public:
		ScreenBar() = default;

		void render();
		void handlerInput(const InputEvent& ev);
		void focus();
		void blur();
		bool hasFocus() const;

	private:
		bool hasFocus_{ false };

		Button* music_{ nullptr };
		Button* main_{ nullptr };
		Button* libray_{ nullptr };
	};
}