#include "RegisterScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "UserManager.h"

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

		firstNameBox_ = addElement<TextBox>();
		firstNameBox_->centerX(consoleSize.x());
		firstNameBox_->setY(baseY + 5);

		firstNameLb_ = addElement<Label>();
		firstNameLb_->setText("Nombres:");
		firstNameLb_->setX(firstNameBox_->getX() + 1);
		firstNameLb_->setY(baseY + 4);

		lastNameBox_ = addElement<TextBox>();
		lastNameBox_->centerX(consoleSize.x());
		lastNameBox_->setY(baseY + 10);

		lastNameLb_ = addElement<Label>();
		lastNameLb_->setText("Apellidos:");
		lastNameLb_->setX(firstNameBox_->getX() + 1);
		lastNameLb_->setY(baseY + 9);

		dniBox_ = addElement<TextBox>();
		dniBox_->centerX(consoleSize.x());
		dniBox_->setY(baseY + 15);

        dniLb_ = addElement<Label>();
        dniLb_->setText("DNI:");
        dniLb_->setX(firstNameBox_->getX() + 1);
        dniLb_->setY(baseY + 14);

        planBox_ = addElement<TextBox>();
        planBox_->centerX(consoleSize.x());
        planBox_->setY(baseY + 20);

        planLb_ = addElement<Label>();
        planLb_->setText("Plan:");
        planLb_->setX(firstNameBox_->getX() + 1);
        planLb_->setY(baseY + 19);

        emailBox_ = addElement<TextBox>();
        emailBox_->centerX(consoleSize.x());
        emailBox_->setY(baseY + 25);

        emailLb_ = addElement<Label>();
        emailLb_->setText("Correo:");
        emailLb_->setX(firstNameBox_->getX() + 1);
        emailLb_->setY(baseY + 24);

        passwordBox_ = addElement<TextBox>();
        passwordBox_->centerX(consoleSize.x());
        passwordBox_->setY(baseY + 30);

        passwordLb_ = addElement<Label>();
        passwordLb_->setText("Password:");
        passwordLb_->setX(firstNameBox_->getX() + 1);
        passwordLb_->setY(baseY + 29);

        genderBox_ = addElement<TextBox>();
        genderBox_->centerX(consoleSize.x());
        genderBox_->setY(baseY + 35);

        genderLb_ = addElement<Label>();
        genderLb_->setText("Genero:");
        genderLb_->setX(firstNameBox_->getX() + 1);
        genderLb_->setY(baseY + 34);

        ageBox_ = addElement<TextBox>();
        ageBox_->centerX(consoleSize.x());
        ageBox_->setY(baseY + 40);

        ageLb_ = addElement<Label>();
        ageLb_->setText("Edad:");
        ageLb_->setX(firstNameBox_->getX() + 1);
        ageLb_->setY(baseY + 39);

        registerButton_ = addElement<Button>();
        registerButton_->setLabel("Registrarse");
        registerButton_->centerX(consoleSize.x());
        registerButton_->setY(baseY + 44);

        registerButton_->setOnEnter([this] {
                User user{};
                user.setFirstName(firstNameBox_->getText());
                user.setLastName(lastNameBox_->getText());
                user.setDni(dniBox_->getText());
                user.setPlan(planBox_->getText());
                user.setEmail(emailBox_->getText());
                user.setPassword(passwordBox_->getText());
                user.setGender(genderBox_->getText());
                try 
                {
                    user.setAge(std::stoi(ageBox_->getText()));
                }
                catch (...) {
                    user.setAge(0);
                }

                if (UserManager::instance().registerUser(user))
                {
                    warningLb_->setText("Registro exitoso");
                    ScreenManager::instance().setActive(ScreenNames::Login);
                }
                else
                {
                    warningLb_->setText("Usuario ya existe");
                }
                warningLb_->show();
            });

        warningLb_ = addElement<Label>();
        warningLb_->setText("No se pudo registrar. Verifica tus datos");
        warningLb_->centerX(consoleSize.x());
        warningLb_->setY(baseY + 2);
        warningLb_->setForeground(Color::Foreground::LightRed);
        warningLb_->hide();
	}
}
