#include "UserManager.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace sb
{
    UserManager::UserManager()
    {
        loadUsersFromFile();
    }

    void UserManager::loadUsersFromFile()
    {
        std::ifstream file(getFilePath());
        if (!file.is_open())
            return;

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string values[8];
            std::string token;
            int idx = 0;

            while (std::getline(ss, token, ',') && idx < 8)
            {
                values[idx++] = token;
            }

            if (idx == 8)
            {
                User user(
                    values[0], values[1], values[2], values[3],
                    values[4], values[5], values[6], std::stoi(values[7])
                );
                userIndex_.insert(IndexedUser(user));
            }
        }
    }

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
        User dummy("", "", "", "", email, "", "", 0);
        return userIndex_.contains(IndexedUser(dummy));
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

        userIndex_.insert(IndexedUser(user));
        return true;
    }

    bool UserManager::login(const std::string& email, const std::string& password)
    {
        User dummy("", "", "", "", email, "", "", 0);
        IndexedUser searchKey(dummy);

        if (!userIndex_.contains(searchKey))
            return false;

        bool found = false;
        userIndex_.inOrderTraversal([&](const IndexedUser& indexedUser)
        {
            const User& user = indexedUser.getUser();
            if (user.getEmail() == email && user.getPassword() == password)
            {
                currentUser_ = user;
                currentLibrary_ = Library(user.getDni());
                isLoggedIn_ = true;
                found = true;
            }
        });

    return found;
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