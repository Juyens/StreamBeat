#include "UserManager.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace sb
{
    std::string UserManager::getFilePath()
    {
        return "Data/users.csv";
    }

    UserManager& UserManager::instance()
    {
        static UserManager instance;
        return instance;
    }

    bool UserManager::userExists(const std::string& email)
    {
        std::ifstream file(getFilePath());
        if (!file.is_open())
            return false;

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string token;
            int index = 0;
            std::string lineEmail;
            while (std::getline(ss, token, ','))
            {
                if (index == 4)
                {
                    lineEmail = token;
                    break;
                }
                ++index;
            }
            if (lineEmail == email)
                return true;
        }
        return false;
    }

    bool UserManager::registerUser(const User& user)
    {
        std::filesystem::create_directory("Data");

        if (userExists(user.getEmail()))
            return false;

        std::ofstream file(getFilePath(), std::ios::app);
        if (!file.is_open())
            return false;

        file << user.getFirstName() << ','
            << user.getLastName() << ','
            << user.getDni() << ','
            << user.getPlan() << ','
            << user.getEmail() << ','
            << user.getPassword() << ','
            << user.getGender() << ','
            << user.getAge() << '\n';

        return true;
    }

    bool UserManager::login(const std::string& email, const std::string& password)
    {
        std::ifstream file(getFilePath());
        if (!file.is_open())
            return false;

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string token;
            std::string values[8];
            int idx = 0;
            while (std::getline(ss, token, ',') && idx < 8)
            {
                values[idx++] = token;
            }

            if (idx >= 6 && values[4] == email && values[5] == password)
            {
                currentUser_ = User(
                    values[0], // nombre
                    values[1], // apellido
                    values[2], // dni
                    values[3], // plan
                    values[4], // email
                    values[5], // password
                    values[6], // genero
                    std::stoi(values[7]) // edad
                );
                isLoggedIn_ = true;
                return true;
            }
        }
        return false;
    }

    void UserManager::logout()
    {
        isLoggedIn_ = false;
        currentUser_ = User();
    }

    Library& UserManager::getCurrentLibrary()
    {
        return currentLibrary_;
    }

    const User& UserManager::getCurrentUser() const
    {
        return currentUser_;
    }

    bool UserManager::isUserLoggedIn() const
    {
        return isLoggedIn_;
    }
}