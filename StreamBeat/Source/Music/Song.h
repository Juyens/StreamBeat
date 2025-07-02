#pragma once

#include "Credits.h"
#include "List.h"

#include <string>
#include <iostream>

class Song
{
private:
    List<std::string>& genres_;
    std::string name_;
    std::uint32_t duration_;
    std::uint64_t reproductions_;
    Credits& credits_;

public:
    Song(List<std::string>& genres, const std::string& name, std::uint32_t duration,
        std::uint64_t reproductions, Credits& credits)
        : genres_(genres), name_(name), duration_(duration),
        reproductions_(reproductions), credits_(credits) {}

    ~Song() = default;

    List<std::string>& getGenres()
    {
        return genres_;
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

    Credits& getCredits()
    {
        return credits_;
    }

    void addGenre(const std::string& genre)
    {
        genres_.push_back(genre);
    }
};