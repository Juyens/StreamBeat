#pragma once

#include "List.h"

#include <string>

class Credits
{
private:
    List<std::string> authors_;
    std::string discography_;

public:
    Credits() = default;
    Credits(List<std::string>& authors, const std::string& discography)
        : authors_(std::move(authors)), discography_(discography) {}

    ~Credits() = default;

    List<std::string>& getAuthors()
    {
        return authors_;
    }

    void setAuthorsContent(const List<std::string>& authors)
    {
        authors_.clear();
        for (uint i = 0; i < authors.size(); ++i)
        {
            authors_.push_back(authors[i]);
        }
    }

    void clearAuthors()
    {
        authors_.clear();
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