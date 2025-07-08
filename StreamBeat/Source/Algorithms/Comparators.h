#pragma once

#include "Song.h"
#include <memory>

namespace sb
{
    class CompareByReproductionsAsc
    {
    public:
        bool operator()(const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) const
        {
            return a->getReproductions() < b->getReproductions();
        }
    };

    class CompareByReproductionsDesc
    {
    public:
        bool operator()(const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) const
        {
            return a->getReproductions() > b->getReproductions();
        }
    };

    class CompareByDurationAsc
    {
    public:
        bool operator()(const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) const
        {
            return a->getDurationSeconds() < b->getDurationSeconds();
        }
    };

    class CompareByDurationDesc
    {
    public:
        bool operator()(const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) const
        {
            return a->getDurationSeconds() > b->getDurationSeconds();
        }
    };
}