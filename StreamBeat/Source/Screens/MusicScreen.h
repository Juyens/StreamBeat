#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"

namespace sb
{
	class MusicScreen : public Screen
	{
	public:
		MusicScreen();

	protected:
		void onCreate() override;
		void onKeyPress(Key key) override;
		void onReset() override;

	private:
		Label* titleLb_{ nullptr };
	};
}