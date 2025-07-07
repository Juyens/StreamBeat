#include "RecommendationManager.h"
#include <algorithm>

namespace sb
{
    RecommendationManager& RecommendationManager::instance()
    {
        static RecommendationManager instance;
        return instance;
    }

    void RecommendationManager::buildGraph()
    {
        if (graphBuilt_)
            return;

        auto& songs = DataManager::instance().getSongs();
        for (uint i = 0; i < songs.size(); ++i)
        {
            graph_.addVertex(songs[i]->getName());
        }

        for (uint i = 0; i < songs.size(); ++i)
        {
            auto& genresA = songs[i]->getGenres();
            for (uint j = i + 1; j < songs.size(); ++j)
            {
                auto& genresB = songs[j]->getGenres();
                int weight = 0;
                for (uint a = 0; a < genresA.size(); ++a)
                {
                    for (uint b = 0; b < genresB.size(); ++b)
                    {
                        if (genresA[a] == genresB[b])
                            ++weight;
                    }
                }
                if (weight > 0)
                {
                    graph_.addEdge(songs[i]->getName(), songs[j]->getName(), weight);
                    graph_.addEdge(songs[j]->getName(), songs[i]->getName(), weight);
                }
            }
        }

        graphBuilt_ = true;
    }

    List<std::shared_ptr<Song>> RecommendationManager::getRecommendations(size_t count)
    {
        buildGraph();

        std::unordered_map<std::string, int> scores;
        std::vector<std::shared_ptr<Song>> seeds;

        auto& history = SongManager::instance().getHistory();
        while (!history.empty())
        {
            seeds.push_back(history.top());
            history.pop();
        }
        for (auto it = seeds.rbegin(); it != seeds.rend(); ++it)
        {
            history.push(*it);
        }

        for (const auto& seed : seeds)
        {
            graph_.forEachEdge(seed->getName(), [&] (const std::string& to, const int& weight)
                {
                    bool isSeed = false;
                    for (const auto& s : seeds)
                    {
                        if (s->getName() == to)
                        {
                            isSeed = true;
                            break;
                        }
                    }
                    if (!isSeed)
                        scores[to] += weight;
                });
        }

        std::vector<std::pair<std::string, int>> sorted(scores.begin(), scores.end());
        std::sort(sorted.begin(), sorted.end(), [] (auto& a, auto& b) { return a.second > b.second; });

        List<std::shared_ptr<Song>> result;
        size_t added = 0;
        for (const auto& [name, w] : sorted)
        {
            auto song = DataManager::instance().getSongByName(name);
            if (song)
            {
                result.push_back(song);
                if (++added >= count)
                    break;
            }
        }

        return result;
    }
}