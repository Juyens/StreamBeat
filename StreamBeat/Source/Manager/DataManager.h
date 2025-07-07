#pragma once

#include "List.h"
#include "Song.h"
#include "Album.h"
#include "Artist.h"
#include "HashTable.h"
#include "BSTree.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <algorithm>
#include <thread>
#include <atomic>

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

		template <typename T>
		List<std::shared_ptr<T>> findByNameContains(const std::string& namePart) const
		{
			std::string query = namePart;
			std::transform(query.begin(), query.end(), query.begin(), ::tolower);

			List<std::shared_ptr<T>> result;
			if (query.empty())
				return result;

			const BSTree<std::shared_ptr<T>, CompareByName<T>>* tree = nullptr;

			if constexpr (std::is_same_v<T, Artist>)
				tree = &artistPartialIndex_;
			else if constexpr (std::is_same_v<T, Album>)
				tree = &albumPartialIndex_;
			else if constexpr (std::is_same_v<T, Song>)
				tree = &songPartialIndex_;
			else
				throw std::logic_error("Tipo no soportado");

			tree->inOrderTraversal([&] (const std::shared_ptr<T>& item)
				{
					std::string lowered = item->getName();
					std::transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);

					if (lowered.find(query) != std::string::npos)
					{
						result.push_back(item);
					}
				});

			return result;
		}

		template<typename T>
		std::shared_ptr<T> getByNameExact(const std::string& name) const
		{
			const HashTable<std::string, std::shared_ptr<T>>* table = nullptr;

			if constexpr (std::is_same_v<T, Artist>)
				table = &artistByName_;
			else if constexpr (std::is_same_v<T, Album>)
				table = &albumByName_;
			else if constexpr (std::is_same_v<T, Song>)
				table = &songByName_;
			else
				throw std::logic_error("Tipo no soportado en getByNameExact");

			auto ptr = table->find(name);
			return ptr ? *ptr : nullptr;
		}

		std::shared_ptr<Song> getSongByName(const std::string& name);
		std::shared_ptr<Album> getAlbumByName(const std::string& name);
		std::shared_ptr<Artist> getArtistByName(const std::string& name);

		std::shared_ptr<Album> getAlbumForSong(const std::string& songName);
		std::shared_ptr<Artist> getArtistForSong(const std::string& songName);

		List<std::shared_ptr<Song>> getSongsByGenre(const std::string& genre);

		std::shared_ptr<Song> getMostPlayedSong();

		List<std::shared_ptr<Album>> getAlbumsByArtist(const std::string& artistName);

		List<std::shared_ptr<Song>> getSongsByArtist(const std::string& artistName);
		List<std::shared_ptr<Song>> getSongsByAlbum(const std::string& albumName);
		List<std::shared_ptr<Song>> getSongsByDuration(uint minSeconds, uint maxSeconds);

		List<std::shared_ptr<Song>> getSongsByReproductionsDesc();
		List<std::shared_ptr<Song>> getSongsByReproductionsAsc();

		void loadAsync();
		bool isLoadInProgress() const;
		bool isLoadCompleted() const;

	private:
		std::thread loadThread_;
		std::atomic<bool> isLoading_{ false };
		std::atomic<bool> loadFinished_{ false };

		void loadDataFromFile();

	private:
		DataManager() = default;
		~DataManager() = default;

		void storeCurrentAlbum(std::shared_ptr<Artist>& currentArtist, std::shared_ptr<Album>& currentAlbum);
		void storeCurrentArtist(std::shared_ptr<Artist>& currentArtist);

		int countTabs(const std::string& line);
		std::shared_ptr<List<std::string>> split(const std::string& input, char delimiter);

		std::string fileName_ = "Data/MusicCatalog.data";

		List<std::shared_ptr<Song>> songs_;
		List<std::shared_ptr<Album>> albums_;
		List<std::shared_ptr<Artist>> artists_;

		BSTree<std::shared_ptr<Artist>, CompareByName<Artist>> artistPartialIndex_;
		BSTree<std::shared_ptr<Album>, CompareByName<Album>> albumPartialIndex_;
		BSTree<std::shared_ptr<Song>, CompareByName<Song>> songPartialIndex_;

		HashTable<std::string, std::shared_ptr<Artist>> artistByName_;
		HashTable<std::string, std::shared_ptr<Album>> albumByName_;
		HashTable<std::string, std::shared_ptr<Song>> songByName_;

		HashTable<std::string, std::string> songToAlbum_;
		HashTable<std::string, std::string> albumToArtist_;
	};
}