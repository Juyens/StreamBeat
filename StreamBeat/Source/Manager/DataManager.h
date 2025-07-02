#pragma once

#include "List.h"
#include "Song.h"
#include "Album.h"
#include "Artist.h"

#include <fstream>
#include <sstream>
#include <memory>
#include <string>

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

        std::string fileName_ = "Data/MusicData.data";

        List<std::shared_ptr<Song>> songs_;
        List<std::shared_ptr<Album>> albums_;
        List<std::shared_ptr<Artist>> artists_;
    };
}