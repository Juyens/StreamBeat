#pragma once

#include "List.h"
#include <string>

class Credits
{
private:
    List<std::string>& authors_;
    std::string discography_;

public:
    Credits(List<std::string>& authors, const std::string& discography)
        : authors_(authors), discography_(discography) {}

    ~Credits() = default;

    List<std::string>& getAuthors()
    {
        return authors_;
    }

    std::string getDiscography() const
    {
        return discography_;
    }

    void setDiscography(const std::string& discography)
    {
        discography_ = discography;
    }

    void addAuthor(const std::string& author)
    {
        authors_.push_back(author);
    }
};