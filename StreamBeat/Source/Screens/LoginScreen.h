#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"

namespace sb 
{
	class LoginScreen : public Screen 
	{
	public:
		LoginScreen();

	protected:
		void onCreate() override;
		void onReset() override;

	private:
		void login();

	private:
		Label* titleLb_{ nullptr };

		Label* emailLb_{ nullptr };
		Label* passwordLb_{ nullptr };
		Label* warningLb_{ nullptr };

		TextBox* emailBox_{ nullptr };
		TextBox* passwordBox_{ nullptr };

		Button* loginButton_{ nullptr };
		Button* registerButton_{ nullptr };
	};
}