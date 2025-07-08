#pragma once

#include "Graph.h"
#include "Song.h"
#include "DataManager.h"
#include "SongManager.h"
#include "List.h"
#include "HashTable.h"

#include <memory>

namespace sb
{
    class RecommendationManager
    {
    public:
        static RecommendationManager& instance();

        List<std::shared_ptr<Song>> getRecommendations(size_t count = 5);

    private:
        RecommendationManager() = default;
        Graph<std::string, int> graph_;
    };
}