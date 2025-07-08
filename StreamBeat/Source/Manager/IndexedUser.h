#pragma once

#include "User.h"

namespace sb
{
    class IndexedUser
    {
    public:
        explicit IndexedUser(const User& user)
            : user_(user)
        {
        }

        bool operator<(const IndexedUser& other) const
        {
            return user_.getEmail() < other.user_.getEmail();
        }

        bool operator>(const IndexedUser& other) const
        {
            return user_.getEmail() > other.user_.getEmail();
        }

        bool operator==(const IndexedUser& other) const
        {
            return user_.getEmail() == other.user_.getEmail();
        }

        const std::string& getEmail() const
        {
            return user_.getEmail();
        }

        const User& getUser() const
        {
            return user_;
        }

    private:
        User user_;
    };
}