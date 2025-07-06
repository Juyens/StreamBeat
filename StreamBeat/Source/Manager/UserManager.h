#pragma once

#include "User.h"
#include "Library.h"

namespace sb
{
    class UserManager
    {
    public:
        static UserManager& instance();

        bool registerUser(const User& user);
        bool login(const std::string& email, const std::string& password);
        void logout();

        Library& getCurrentLibrary();
        const User& getCurrentUser() const;
        bool isUserLoggedIn() const;

    private:
        UserManager() = default;
        bool userExists(const std::string& email);
        static std::string getFilePath();
        bool isLoggedIn_{ false };
        User currentUser_;
        Library currentLibrary_;
    };
}