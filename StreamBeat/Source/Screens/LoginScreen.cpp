#include "LoginScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "UserManager.h"

namespace sb
{
	LoginScreen::LoginScreen()
		: Screen(ScreenNames::Login)
	{
		onCreate();
		initializeFocus();
	}

	void LoginScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 10;

		titleLb_ = addElement<Label>();
		titleLb_->setText("< StreamBeat - Login >");
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

		loginButton_ = addElement<Button>();
		loginButton_->setLabel("Ingresar");
		loginButton_->setX(passwordBox_->getX());
		loginButton_->setY(baseY + 14);

		loginButton_->setOnEnter( [this] 
			{
				const std::string email = usernameBox_->getText();
				const std::string pass = passwordBox_->getText();
				if (UserManager::instance().login(email, pass))
				{
					warningLb_->hide();
				}
				else
				{
					warningLb_->show();
				}
			});

		passwordBox_->setOnEnter([
			this
		] {
				const std::string email = usernameBox_->getText();
				const std::string pass = passwordBox_->getText();
				if (UserManager::instance().login(email, pass))
					warningLb_->hide();
				else
					warningLb_->show();
			});

		registerButton_ = addElement<Button>();
		registerButton_->setLabel("Registrarse");
		registerButton_->setX(passwordBox_->getX() + 15);
		registerButton_->setY(baseY + 14);

		registerButton_->setOnEnter(
			[] {
				ScreenManager::instance().setActive(ScreenNames::Register);
			});

		warningLb_ = addElement<Label>();
		warningLb_->setText("No se pudo iniciar sesion. Verifica tus datos");
		warningLb_->centerX(consoleSize.x());
		warningLb_->setY(baseY + 2);
		warningLb_->setTextForeground(Color::Foreground::LightRed);
		warningLb_->hide();
	}
}
