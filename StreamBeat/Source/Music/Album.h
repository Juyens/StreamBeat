#pragma once

#include "List.h"
#include "Song.h"

#include <string>
#include <memory>

class Album
{
private:
    std::string name_;
    List<std::shared_ptr<Song>>& songs_;

public:
    Album(const std::string& name, List<std::shared_ptr<Song>>& songs)
        : name_(name), songs_(songs) {}

    ~Album() = default;

    void addSong(std::shared_ptr<Song> song) 
    {
        songs_.push_back(song);
    }

    List<std::shared_ptr<Song>>& getSongs() 
    {
        return songs_;
    }

    std::string getName() const
    {
        return name_;
    }

    void setName(const std::string& name)
    {
        name_ = name;
    }
};
