#pragma once

#include "List.h"
#include "Album.h"
#include <string>
#include <memory>

class Artist
{
private:
    std::string name_;
    List<std::shared_ptr<Album>>& albums_;

public:
    Artist(const std::string& name, List<std::shared_ptr<Album>>& albums)
        : name_(name), albums_(albums) {}

    ~Artist() = default;

    void addAlbum(std::shared_ptr<Album> album)
    {
        albums_.push_back(album);
    }

    List<std::shared_ptr<Album>>& getAlbums() 
    {
        return albums_;
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
