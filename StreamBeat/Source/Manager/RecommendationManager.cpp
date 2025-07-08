#include "RecommendationManager.h"
#include "QuickSort.h"
#include "Comparators.h"
#include "Stack.h"

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

        // Copy history without modifying the original stack
        auto& history = SongManager::instance().getHistory();
        Stack<std::shared_ptr<Song>> tmp;
        while (!history.empty())
        {
            auto song = history.top();
            history.pop();
            historySongs.push_back(song);
            tmp.push(song);
        }
        while (!tmp.empty())
        {
            history.push(tmp.top());
            tmp.pop();
        }

        if (historySongs.empty())
            return result;

        graph_ = Graph<std::string, int>();
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
                graph_.addVertex(name);
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
                        graph_.addVertex(toName);
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
                graph_.addEdge(from, to, w);
            }
        }

        HashTable<std::string, int> score;
        for (uint i = 0; i < historySongs.size(); ++i)
        {
            const std::string& seedName = historySongs[i]->getName();
            graph_.forEachEdge(seedName, [&] (const std::string& to, const int& weight)
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
        QuickSort<std::pair<std::string, int>, sb::CompareByScoreDesc>::sort(sorted);

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