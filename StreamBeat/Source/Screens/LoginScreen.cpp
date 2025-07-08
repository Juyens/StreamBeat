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
		titleLb_->setText("[ StreamBeat - Login ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(baseY);

		emailBox_ = addElement<TextBox>();
		emailBox_->centerX(consoleSize.x());
		emailBox_->setY(baseY + 5);

		emailLb_ = addElement<Label>();
		emailLb_->setText("Email:");
		emailLb_->setX(emailBox_->getX() + 1);
		emailLb_->setY(baseY + 4);

		passwordBox_ = addElement<TextBox>();
		passwordBox_->centerX(consoleSize.x());
		passwordBox_->setY(baseY + 10);

		passwordBox_->setOnEnter([this] { login(); });

		passwordLb_ = addElement<Label>();
		passwordLb_->setText("Password:");
		passwordLb_->setX(emailBox_->getX() + 1);
		passwordLb_->setY(baseY + 9);

		loginButton_ = addElement<Button>();
		loginButton_->setText("Ingresar");
		loginButton_->setX(passwordBox_->getX());
		loginButton_->setY(baseY + 14);

		loginButton_->setOnEnter([this] { login(); });

		passwordBox_->setOnEnter([this] { login(); });

		registerButton_ = addElement<Button>();
		registerButton_->setText("Registrarse");
		registerButton_->setX(passwordBox_->getX() + 15);
		registerButton_->setY(baseY + 14);

		registerButton_->setOnEnter([] { ScreenManager::instance().navigateToRoot(ScreenNames::Register); });

		warningLb_ = addElement<Label>();
		warningLb_->setText("No se pudo iniciar sesion. Verifica tus datos");
		warningLb_->centerX(consoleSize.x());
		warningLb_->setY(baseY + 2);
		warningLb_->setTextForeground(Color::Foreground::LightRed);
		warningLb_->hide();
	}

	void LoginScreen::onReset()
	{
		warningLb_->hide();
	}

	void LoginScreen::login()
	{
		const std::string email = emailBox_->getText();
		const std::string pass = passwordBox_->getText();
		if (UserManager::instance().login(email, pass))
		{
			ScreenManager::instance().navigateToRoot(ScreenNames::Main);
			ScreenManager::instance().setupScreenBar();
		}
		else
		{
			warningLb_->show();
		}
	}
}
