#include "RecommendationManager.h"
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

namespace sb
{
    RecommendationManager& RecommendationManager::instance()
    {
        static RecommendationManager instance;
        return instance;
    }

    List<std::shared_ptr<Song>> RecommendationManager::getRecommendations(size_t count)
    {
        List<std::shared_ptr<Song>> result;
        std::vector<std::shared_ptr<Song>> historySongs;

        auto& history = SongManager::instance().getHistory();
        while (!history.empty())
        {
            historySongs.push_back(history.top());
            history.pop();
        }
        for (auto it = historySongs.rbegin(); it != historySongs.rend(); ++it)
        {
            history.push(*it);
        }

        if (historySongs.empty())
            return result;

        Graph<std::string, int> graph;
        std::unordered_set<std::string> vertices;
        std::unordered_set<std::string> seedNames;
        std::unordered_map<std::string, std::unordered_map<std::string, int>> weights;

        for (const auto& song : historySongs)
        {
            const auto& name = song->getName();
            if (vertices.insert(name).second)
                graph.addVertex(name);
            seedNames.insert(name);
        }

        for (const auto& seed : historySongs)
        {
            auto& genres = seed->getGenres();
            for (uint i = 0; i < genres.size(); ++i)
            {
                auto songsByGenre = DataManager::instance().getSongsByGenre(genres[i]);
                for (uint j = 0; j < songsByGenre.size(); ++j)
                {
                    auto candidate = songsByGenre[j];
                    const auto& toName = candidate->getName();
                    const auto& fromName = seed->getName();

                    if (toName == fromName)
                        continue;

                    if (vertices.insert(toName).second)
                        graph.addVertex(toName);

                    ++weights[fromName][toName];
                }
            }
        }

        for (const auto& [from, dests] : weights)
            for (const auto& [to, w] : dests)
                graph.addEdge(from, to, w);

        std::unordered_map<std::string, int> score;

        for (const auto& seed : historySongs)
        {
            graph.forEachEdge(seed->getName(), [&] (const std::string& to, const int& weight) {
                if (seedNames.count(to) == 0)
                    score[to] += weight;
                });
        }

        std::vector<std::pair<std::string, int>> sorted(score.begin(), score.end());
        std::sort(sorted.begin(), sorted.end(), [] (auto& a, auto& b) { return a.second > b.second; });

        size_t added = 0;
        for (const auto& [name, s] : sorted)
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