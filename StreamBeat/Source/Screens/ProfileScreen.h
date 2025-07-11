#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"

namespace sb
{
	class ProfileScreen : public Screen
	{
	public:
		ProfileScreen();

	protected:
		void onCreate() override;
		void onKeyPress(Key key) override;
		void onReset() override;

	private:
		Label* titleLb_{ nullptr };
		Button* viewInfo{ nullptr };
		Button* changePass{ nullptr };
		Button* changeUser{ nullptr };
		Button* changePlan{ nullptr };
	};
}