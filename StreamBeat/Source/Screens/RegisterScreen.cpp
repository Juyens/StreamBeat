#include "RegisterScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "UserManager.h"
#include "Utils.h"

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

        constexpr int baseY = 8;
        constexpr int fieldWidth = 30;
        constexpr int fieldHeight = 3;
        constexpr int spacing = 5;

        titleLb_ = addElement<Label>();
        titleLb_->setText("< StreamBeat - Register >");
        titleLb_->centerX(consoleSize.x());
        titleLb_->setY(baseY);

        const int yName = baseY + 5;
        const int startXName = utils::centeredX(consoleSize.x(), fieldWidth * 2 + spacing);

        firstNameBox_ = addElement<TextBox>();
        firstNameBox_->setSize({ fieldWidth, fieldHeight });
        firstNameBox_->setX(startXName);
        firstNameBox_->setY(yName);

        lastNameBox_ = addElement<TextBox>();
        lastNameBox_->setSize({ fieldWidth, fieldHeight });
        lastNameBox_->setX(startXName + fieldWidth + spacing);
        lastNameBox_->setY(yName);

        firstNameLb_ = addElement<Label>();
        firstNameLb_->setText("Nombres:");
        firstNameLb_->setX(firstNameBox_->getX() + 1);
        firstNameLb_->setY(firstNameBox_->getY() - 1);

        lastNameLb_ = addElement<Label>();
        lastNameLb_->setText("Apellidos:");
        lastNameLb_->setX(lastNameBox_->getX() + 1);
        lastNameLb_->setY(lastNameBox_->getY() - 1);

        // DNI & Plan
        const int yDniPlan = baseY + 10;
        const int startXDniPlan = utils::centeredX(consoleSize.x(), fieldWidth * 2 + spacing);

        dniBox_ = addElement<TextBox>();
        dniBox_->setSize({ fieldWidth, fieldHeight });
        dniBox_->setX(startXDniPlan);
        dniBox_->setY(yDniPlan);

        planComboBox_ = addElement<ComboBox<std::string>>();
        planComboBox_->setX(startXDniPlan + fieldWidth + spacing);
        planComboBox_->setY(yDniPlan);
        planComboBox_->addItem("Free");
        planComboBox_->addItem("Premium");
        planComboBox_->addItem("Estudiante");
        planComboBox_->addItem("Artista");
        planComboBox_->setItemToString([] (const std::string& s) { return s; });

        dniLb_ = addElement<Label>();
        dniLb_->setText("DNI:");
        dniLb_->setX(dniBox_->getX() + 1);
        dniLb_->setY(dniBox_->getY() - 1);

        planLb_ = addElement<Label>();
        planLb_->setText("Plan:");
        planLb_->setX(planComboBox_->getX() + 1);
        planLb_->setY(planComboBox_->getY() - 1);

        // Email & Password
        const int yEmailPass = baseY + 15;
        const int startXEmailPass = utils::centeredX(consoleSize.x(), fieldWidth * 2 + spacing);

        emailBox_ = addElement<TextBox>();
        emailBox_->setSize({ fieldWidth, fieldHeight });
        emailBox_->setX(startXEmailPass);
        emailBox_->setY(yEmailPass);

        passwordBox_ = addElement<TextBox>();
        passwordBox_->setSize({ fieldWidth, fieldHeight });
        passwordBox_->setX(startXEmailPass + fieldWidth + spacing);
        passwordBox_->setY(yEmailPass);

        emailLb_ = addElement<Label>();
        emailLb_->setText("Correo:");
        emailLb_->setX(emailBox_->getX() + 1);
        emailLb_->setY(emailBox_->getY() - 1);

        passwordLb_ = addElement<Label>();
        passwordLb_->setText("Password:");
        passwordLb_->setX(passwordBox_->getX() + 1);
        passwordLb_->setY(passwordBox_->getY() - 1);

        // Gender & Age
        const int yGenderAge = baseY + 20;
        const int startXGenderAge = utils::centeredX(consoleSize.x(), fieldWidth * 2 + spacing);

        genderComboBox_ = addElement<ComboBox<std::string>>();
        genderComboBox_->setX(startXGenderAge);
        genderComboBox_->setY(yGenderAge);
        genderComboBox_->addItem("Masculino");
        genderComboBox_->addItem("Femenino");
        genderComboBox_->setItemToString([] (const std::string& s) { return s; });

        ageBox_ = addElement<TextBox>();
        ageBox_->setSize({ fieldWidth, fieldHeight });
        ageBox_->setX(startXGenderAge + fieldWidth + spacing);
        ageBox_->setY(yGenderAge);

        genderLb_ = addElement<Label>();
        genderLb_->setText("Genero:");
        genderLb_->setX(genderComboBox_->getX() + 1);
        genderLb_->setY(genderComboBox_->getY() - 1);

        ageLb_ = addElement<Label>();
        ageLb_->setText("Edad:");
        ageLb_->setX(ageBox_->getX() + 1);
        ageLb_->setY(ageBox_->getY() - 1);

        // Register Button
        registerButton_ = addElement<Button>();
        registerButton_->setLabel("Registrarse");
        registerButton_->centerX(consoleSize.x());
        registerButton_->setY(baseY + 25);

        registerButton_->setOnEnter([this] {
            User user{};
            user.setFirstName(firstNameBox_->getText());
            user.setLastName(lastNameBox_->getText());
            user.setDni(dniBox_->getText());
            user.setPlan(planComboBox_->getSelectedItem() ? *planComboBox_->getSelectedItem() : "");
            user.setEmail(emailBox_->getText());
            user.setPassword(passwordBox_->getText());
            user.setGender(genderComboBox_->getSelectedItem() ? *genderComboBox_->getSelectedItem() : "");

            try 
            {
                user.setAge(std::stoi(ageBox_->getText()));
            }
            catch (...) 
            {
                user.setAge(0);
            }

            if (!isValidEmail(user.getEmail())) 
            {
                warningLb_->setText("El correo ingresado no es valido. Verifica el formato (ej: usuario@dominio.com)");
                warningLb_->centerX(Console::getViewportSize().x());
                warningLb_->show();
                return;
            }

            if (UserManager::instance().registerUser(user)) 
            {
                ScreenManager::instance().setActive(ScreenNames::Login);
            }
            else 
            {
                warningLb_->setText("Ya existe un usuario con esos datos. Intenta con otro correo o DNI");
                warningLb_->centerX(Console::getViewportSize().x());
                warningLb_->show();
            }

            warningLb_->show();
            });

        // Warning 
        warningLb_ = addElement<Label>();
        warningLb_->setText("No se pudo registrar. Verifica tus datos");
        warningLb_->centerX(consoleSize.x());
        warningLb_->setY(baseY + 2);
        warningLb_->setTextForeground(Color::Foreground::LightRed);
        warningLb_->hide();
    }

    bool RegisterScreen::isValidEmail(const std::string& email)
    {
        const auto atPos = email.find('@');
        const auto dotPos = email.rfind('.');

        return !email.empty() &&
            atPos != std::string::npos &&
            dotPos != std::string::npos &&
            atPos > 0 &&
            dotPos > atPos + 1 &&
            dotPos < email.size() - 1 &&
            email.find(' ') == std::string::npos &&
            email.find('@', atPos + 1) == std::string::npos;
    }
}
