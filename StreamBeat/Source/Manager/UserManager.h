#pragma once

#include "IndexedUser.h"
#include "AVLTree.h"
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
        UserManager();

        static std::string getFilePath();
        void loadUsersFromFile();
        bool userExists(const std::string& email);

        bool isLoggedIn_{ false };
        User currentUser_;
        Library currentLibrary_;

        AVLTree<IndexedUser> userIndex_;
    };
}