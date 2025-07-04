#include "RegisterScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "UserManager.h"
#include "Utils.h"

#include <algorithm>

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

        constexpr int baseY = 7;
        constexpr int fieldWidth = 30;
        constexpr int fieldHeight = 3;
        constexpr int spacing = 5;

        titleLb_ = addElement<Label>();
        titleLb_->setText("[ StreamBeat - Register ]");
        titleLb_->centerX(consoleSize.x());
        titleLb_->setY(baseY);

        const int yName = baseY + 5;
        const int startXName = utils::centered(consoleSize.x(), fieldWidth * 2 + spacing);

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
        const int startXDniPlan = utils::centered(consoleSize.x(), fieldWidth * 2 + spacing);

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
        const int startXEmailPass = utils::centered(consoleSize.x(), fieldWidth * 2 + spacing);

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
        const int startXGenderAge = utils::centered(consoleSize.x(), fieldWidth * 2 + spacing);

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

        registerButton_ = addElement<Button>();
        registerButton_->setText("Registrarse");
        registerButton_->setY(baseY + 25);
        registerButton_->setX(firstNameBox_->getX() + firstNameBox_->getWidth() - registerButton_->getWidth());

        registerButton_->setOnEnter([this] {
            warningLb_->hide();

            const std::string firstName = firstNameBox_->getText();
            const std::string lastName = lastNameBox_->getText();
            const std::string dni = dniBox_->getText();
            const std::string email = emailBox_->getText();
            const std::string password = passwordBox_->getText();
            const std::string plan = planComboBox_->getSelectedItem() ? *planComboBox_->getSelectedItem() : "";
            const std::string gender = genderComboBox_->getSelectedItem() ? *genderComboBox_->getSelectedItem() : "";
            const std::string ageStr = ageBox_->getText();

            if (firstName.empty() || lastName.empty() || dni.empty() || email.empty() ||
                password.empty() || plan.empty() || gender.empty() || ageStr.empty()) 
            {
                warningLb_->setText("Todos los campos son obligatorios.");
                warningLb_->centerX(Console::getViewportSize().x());
                warningLb_->show();
                return;
            }

            if (dni.size() != 8 || !std::all_of(dni.begin(), dni.end(), ::isdigit)) 
            {
                warningLb_->setText("El DNI debe tener exactamente 8 digitos numericos.");
                warningLb_->centerX(Console::getViewportSize().x());
                warningLb_->show();
                return;
            }

            if (!isValidEmail(email)) 
            {
                warningLb_->setText("El correo ingresado no es valido. Verifica el formato (ej: usuario@dominio.com)");
                warningLb_->centerX(Console::getViewportSize().x());
                warningLb_->show();
                return;
            }

            int age = 0;
            try 
            {
                age = std::stoi(ageStr);
                if (age <= 0)
                    throw std::invalid_argument("Edad invalida");
            }
            catch (...) 
            {
                warningLb_->setText("La edad debe ser un numero valido mayor que cero.");
                warningLb_->centerX(Console::getViewportSize().x());
                warningLb_->show();
                return;
            }

            User user{};
            user.setFirstName(firstName);
            user.setLastName(lastName);
            user.setDni(dni);
            user.setPlan(plan);
            user.setEmail(email);
            user.setPassword(password);
            user.setGender(gender);
            user.setAge(age);

            if (UserManager::instance().registerUser(user)) 
            {
                ScreenManager::instance().navigateToRoot(ScreenNames::Login);
            }
            else 
            {
                warningLb_->setText("Ya existe un usuario con esos datos. Intenta con otro correo o DNI");
                warningLb_->centerX(Console::getViewportSize().x());
                warningLb_->show();
            }
            });

        backButton_ = addElement<Button>();
        backButton_->setText("Volver");
        backButton_->setY(baseY + 25);
        backButton_->setX(lastNameBox_->getX());

        backButton_->setOnEnter([] { ScreenManager::instance().navigateToRoot(ScreenNames::Login); });

        warningLb_ = addElement<Label>();
        warningLb_->setText("No se pudo registrar. Verifica tus datos");
        warningLb_->centerX(consoleSize.x());
        warningLb_->setY(baseY + 2);
        warningLb_->setTextForeground(Color::Foreground::LightRed);
        warningLb_->hide();
    }

    void RegisterScreen::onReset()
    {
        warningLb_->hide();
    }

    void RegisterScreen::onKeyPress(Key key)
    {
        if (key == Key::Escape)
        {
            ScreenManager::instance().navigateToRoot(ScreenNames::Login);
        }
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

    bool RegisterScreen::isValidDni(const std::string& dni)
    {
        return dni.size() == 8 && std::all_of(dni.begin(), dni.end(), ::isdigit);
    }
}
