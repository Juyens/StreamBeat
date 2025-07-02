#pragma once

#include "Credits.h"
#include "List.h"

#include <string>
#include <iostream>

class Song
{
private:
    List<std::string> genres_;
    std::string name_;
    std::uint32_t duration_{ 0 };
    std::uint64_t reproductions_{ 0 };
    Credits credits_;

public:
    Song() = default;
    Song(List<std::string>& genres, const std::string& name, std::uint32_t duration,
        std::uint64_t reproductions, Credits& credits)
        : genres_(std::move(genres)), name_(name), duration_(duration),
        reproductions_(reproductions), credits_(credits) {}

    ~Song() = default;

    List<std::string>& getGenres()
    {
        return genres_;
    }

    void setGenresContent(const List<std::string>& genres)
    {
        genres_.clear();
        for (uint i = 0; i < genres.size(); ++i)
        {
            genres_.push_back(genres[i]);
        }
    }

    void clearGenres()
    {
        genres_.clear();
    }


    std::string getName() const
    {
        return name_;
    }

    void setName(const std::string& name)
    {
        name_ = name;
    }

    std::uint32_t getDuration() const
    {
        return duration_;
    }

    void setDuration(std::uint32_t duration)
    {
        duration_ = duration;
    }

    std::uint64_t getReproductions() const
    {
        return reproductions_;
    }

    void setReproductions(std::uint64_t reproductions)
    {
        reproductions_ = reproductions;
    }

    void setCredits(const Credits& credits)
    {
        credits_ = credits;
    }

    Credits& getCredits()
    {
        return credits_;
    }

    void addGenre(const std::string& genre)
    {
        genres_.push_back(genre);
    }
};