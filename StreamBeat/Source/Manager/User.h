#pragma once

#include <string>

namespace sb
{
    class User
    {
    public:
        User()
            : firstName_("User"),
            lastName_("Default"),
            dni_("00000000"),
            plan_("Free"),
            email_("default@test.com"),
            password_("StreamBeat"),
            gender_("N/A"),
            age_(0)
        {}

        User(const std::string& firstName,
            const std::string& lastName,
            const std::string& dni,
            const std::string& plan,
            const std::string& email,
            const std::string& password,
            const std::string& gender,
            int age)
            : firstName_(firstName),
            lastName_(lastName),
            dni_(dni),
            plan_(plan),
            email_(email),
            password_(password),
            gender_(gender),
            age_(age)
        {}

        const std::string& getFirstName() const { return firstName_; }
        void setFirstName(const std::string& value) { firstName_ = value; }

        const std::string& getLastName() const { return lastName_; }
        void setLastName(const std::string& value) { lastName_ = value; }

        const std::string& getDni() const { return dni_; }
        void setDni(const std::string& value) { dni_ = value; }

        const std::string& getPlan() const { return plan_; }
        void setPlan(const std::string& value) { plan_ = value; }

        const std::string& getEmail() const { return email_; }
        void setEmail(const std::string& value) { email_ = value; }

        const std::string& getPassword() const { return password_; }
        void setPassword(const std::string& value) { password_ = value; }

        const std::string& getGender() const { return gender_; }
        void setGender(const std::string& value) { gender_ = value; }

        int getAge() const { return age_; }
        void setAge(int value) { age_ = value; }

    private:
        std::string firstName_;
        std::string lastName_;
        std::string dni_;
        std::string plan_;
        std::string email_;
        std::string password_;
        std::string gender_;
        int age_{ 0 };
    };
}