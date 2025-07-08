#include "RecommendationManager.h"

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
        List<std::shared_ptr<Song>> historySongs;

        auto& history = SongManager::instance().getHistory();
        while (!history.empty())
        {
            historySongs.push_back(history.top());
            history.pop();
        }

        for (int i = historySongs.size() - 1; i >= 0; --i)
        {
            history.push(historySongs[i]);
        }

        if (historySongs.empty())
            return result;

        Graph<std::string, int> graph;
        HashTable<std::string, bool> vertices;
        HashTable<std::string, bool> seedNames;
        HashTable<std::string, HashTable<std::string, int>> weights;

        for (uint i = 0; i < historySongs.size(); ++i)
        {
            const auto& song = historySongs[i];
            const auto& name = song->getName();
            if (!vertices.find(name))
            {
                vertices.insert(name, true);
                graph.addVertex(name);
            }
            seedNames.insert(name, true);
        }

        for (uint i = 0; i < historySongs.size(); ++i)
        {
            const auto& seed = historySongs[i];
            auto& genres = seed->getGenres();
            for (uint j = 0; j < genres.size(); ++j)
            {
                auto songsByGenre = DataManager::instance().getSongsByGenre(genres[j]);
                for (uint k = 0; k < songsByGenre.size(); ++k)
                {
                    auto candidate = songsByGenre[k];
                    const auto& toName = candidate->getName();
                    const auto& fromName = seed->getName();

                    if (toName == fromName)
                        continue;

                    if (!vertices.find(toName))
                    {
                        vertices.insert(toName, true);
                        graph.addVertex(toName);
                    }

                    if (!weights.find(fromName))
                        weights.insert(fromName, HashTable<std::string, int>());

                    auto* table = weights.find(fromName);
                    if (!table->find(toName))
                        table->insert(toName, 1);
                    else
                        (*table)[toName]++;
                }
            }
        }

        List<std::pair<std::string, HashTable<std::string, int>>> weightList = weights.toList();
        for (uint i = 0; i < weightList.size(); ++i)
        {
            const auto& from = weightList[i].first;
            const auto& destinations = weightList[i].second.toList();
            for (uint j = 0; j < destinations.size(); ++j)
            {
                const auto& to = destinations[j].first;
                int w = destinations[j].second;
                graph.addEdge(from, to, w);
            }
        }

        HashTable<std::string, int> score;
        for (uint i = 0; i < historySongs.size(); ++i)
        {
            const std::string& seedName = historySongs[i]->getName();
            graph.forEachEdge(seedName, [&] (const std::string& to, const int& weight)
                {
                    if (!seedNames.find(to))
                    {
                        if (!score.find(to))
                            score.insert(to, weight);
                        else
                            score[to] += weight;
                    }
                });
        }

        List<std::pair<std::string, int>> sorted = score.toList();

        for (uint i = 0; i < sorted.size(); ++i)
        {
            for (uint j = i + 1; j < sorted.size(); ++j)
            {
                if (sorted[j].second > sorted[i].second)
                {
                    std::swap(sorted[i], sorted[j]);
                }
            }
        }

        size_t added = 0;
        for (uint i = 0; i < sorted.size(); ++i)
        {
            const auto& name = sorted[i].first;
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