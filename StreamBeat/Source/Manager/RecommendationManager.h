#pragma once

#include "Graph.h"
#include "Song.h"
#include "DataManager.h"
#include "SongManager.h"
#include "List.h"

#include <unordered_map>
#include <vector>
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
        void buildGraph();

        Graph<std::string, int> graph_;
        bool graphBuilt_{ false };
    };
}