#pragma once

#include "Screen.h"
#include "ScreenNames.h"
#include "UI.h"

#include <string>

namespace sb
{
	class SubScreen : public Screen
	{
	public:
		SubScreen()
			: Screen(ScreenNames::Temporary) {}

	protected:
		Label* titleLb_{ nullptr };
	};
}