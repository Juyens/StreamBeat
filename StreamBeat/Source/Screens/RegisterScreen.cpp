#include "RegisterScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"

namespace sb
{
	RegisterScreen::RegisterScreen()
		: Screen(ScreenNames::Register)
	{
		onCreate();
		initializeFocus();
	}

	void RegisterScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 10;

		titleLb_ = addElement<Label>();
		titleLb_->setText("< StreamBeat - Register >");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);

		usernameBox_ = addElement<TextBox>();
		usernameBox_->centerX(consoleSize.x());
		usernameBox_->setY(baseY + 5);

		usernameLb_ = addElement<Label>();
		usernameLb_->setText("Username:");
		usernameLb_->setX(usernameBox_->getX() + 1);
		usernameLb_->setY(baseY + 4);

		passwordBox_ = addElement<TextBox>();
		passwordBox_->centerX(consoleSize.x());
		passwordBox_->setY(baseY + 10);

		passwordLb_ = addElement<Label>();
		passwordLb_->setText("Password:");
		passwordLb_->setX(usernameBox_->getX() + 1);
		passwordLb_->setY(baseY + 9);

		registerButton_ = addElement<Button>();
		registerButton_->setLabel("Registrarse");
		registerButton_->centerX(consoleSize.x());
		registerButton_->setY(baseY + 14);

		registerButton_->setOnEnter(
			[] {
				ScreenManager::instance().setActive(ScreenNames::Login);
			});

		warningLb_ = addElement<Label>();
		warningLb_->setText("No se pudo iniciar sesion. Verifica tus datos");
		warningLb_->centerX(consoleSize.x());
		warningLb_->setY(baseY + 2);
		warningLb_->setForeground(Color::Foreground::LightRed);
		warningLb_->hide();
	}
}
