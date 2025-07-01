#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"

namespace sb
{
	class RegisterScreen : public Screen
	{
	public:
		RegisterScreen();

	protected:
		void onCreate() override;

	private:
		Label* titleLb_{ nullptr };

		Label* usernameLb_{ nullptr };
		Label* passwordLb_{ nullptr };
		Label* warningLb_{ nullptr };

		TextBox* usernameBox_{ nullptr };
		TextBox* passwordBox_{ nullptr };

		Button* registerButton_{ nullptr };
	};
}