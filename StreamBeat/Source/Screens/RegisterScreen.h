#pragma once

#include "Screen.h"
#include "UI.h"
#include "Console.h"
#include "ComboBox.h"

namespace sb
{
	class RegisterScreen : public Screen
	{
	public:
		RegisterScreen();

	protected:
		void onCreate() override;
		void onReset() override;
		void onKeyPress(Key key) override;

	private:
		bool isValidEmail(const std::string& email);
		bool isValidDni(const std::string& dni);

	private:
		Label* titleLb_{ nullptr };

		Label* firstNameLb_{ nullptr };
		Label* lastNameLb_{ nullptr };
		Label* dniLb_{ nullptr };
		Label* planLb_{ nullptr };
		Label* emailLb_{ nullptr };
		Label* passwordLb_{ nullptr };
		Label* genderLb_{ nullptr };
		Label* ageLb_{ nullptr };
		Label* warningLb_{ nullptr };

		TextBox* firstNameBox_{ nullptr };
		TextBox* lastNameBox_{ nullptr };
		TextBox* dniBox_{ nullptr };
		TextBox* emailBox_{ nullptr };
		TextBox* passwordBox_{ nullptr };
		TextBox* ageBox_{ nullptr };

		Button* registerButton_{ nullptr };
		Button* backButton_{ nullptr };

		ComboBox<std::string>* genderComboBox_{ nullptr };
		ComboBox<std::string>* planComboBox_{ nullptr };
	};
}