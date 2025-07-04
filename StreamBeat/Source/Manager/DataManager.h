#pragma once

#include "List.h"
#include "Song.h"
#include "Album.h"
#include "Artist.h"
#include "AVLTree.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <algorithm>

namespace sb
{
    class DataManager
    {
    public:
        static DataManager& instance();

        DataManager(const DataManager&) = delete;
        DataManager& operator=(const DataManager&) = delete;

        List<std::shared_ptr<Song>>& getSongs();
        List<std::shared_ptr<Album>>& getAlbums();
        List<std::shared_ptr<Artist>>& getArtists();

        void addSong(const std::shared_ptr<Song>& song);
        void addAlbum(const std::shared_ptr<Album>& album);
        void addArtist(const std::shared_ptr<Artist>& artist);

        void loadDataFromFile();

		template<typename T>
		List<std::shared_ptr<T>> findByNameContains(const std::string& namePart) const
		{
			const List<std::shared_ptr<T>>* list = nullptr;

			if constexpr (std::is_same_v<T, Artist>)
				list = &artists_;
			else if constexpr (std::is_same_v<T, Album>)
				list = &albums_;
			else if constexpr (std::is_same_v<T, Song>)
				list = &songs_;
			else
				throw std::logic_error("Tipo no soportado en findByNameContains");

			std::string query = namePart;
			std::transform(query.begin(), query.end(), query.begin(), ::tolower);

			List<std::shared_ptr<T>> result;

			if (namePart.empty())
				return result;

			for (uint i = 0; i < list->size(); ++i)
			{
				const auto& item = (*list)[i];
				std::string itemName = item->getName();

				std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

				if (itemName.find(query) != std::string::npos)
				{
					result.push_back(item);
				}
			}
			return result;
		}

		template<typename T>
		std::shared_ptr<T> getByNameExact(const std::string& name, const AVLTree<std::string>& index) const
		{
			if (!index.contains(name))
				return nullptr;

			const List<std::shared_ptr<T>>* list = nullptr;

			if constexpr (std::is_same_v<T, Artist>)
				list = &artists_;
			else if constexpr (std::is_same_v<T, Album>)
				list = &albums_;
			else if constexpr (std::is_same_v<T, Song>)
				list = &songs_;
			else
				throw std::logic_error("Tipo no soportado en getByNameExact");

			for (uint i = 0; i < list->size(); ++i)
			{
				if ((*list)[i]->getName() == name)
					return (*list)[i];
			}

			return nullptr;
		}

    private:
        DataManager() = default;
        ~DataManager() = default;

        void recursiveData(std::ifstream& file, int previousLevel,
            std::shared_ptr<Artist>& currentArtist,
            std::shared_ptr<Album>& currentAlbum,
            std::shared_ptr<Song>& currentSong,
            std::shared_ptr<Credits>& currentCredits);

        int countTabs(const std::string& line);
        std::shared_ptr<List<std::string>> split(const std::string& input, char delimiter);

        std::string fileName_ = "Data/MusicCatalog.data";

        List<std::shared_ptr<Song>> songs_;
        List<std::shared_ptr<Album>> albums_;
        List<std::shared_ptr<Artist>> artists_;

        AVLTree<std::string> artistIndex_;
        AVLTree<std::string> albumIndex_;
        AVLTree<std::string> songIndex_;
    };
}