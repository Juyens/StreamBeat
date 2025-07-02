#pragma once

#include "User.h"

namespace sb
{
    class UserManager
    {
    public:
        static UserManager& instance();

        bool registerUser(const User& user);
        bool login(const std::string& email, const std::string& password);
        void logout();

        const User& getCurrentUser() const;
        bool isUserLoggedIn() const;

    private:
        UserManager() = default;
        bool userExists(const std::string& email);
        static std::string getFilePath();
        bool isLoggedIn_{ false };
        User currentUser_;
    };
}