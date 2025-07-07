#include "DataManager.h"
#include "MergeSort.h"
#include "QuickSort.h"

namespace sb
{
    DataManager& DataManager::instance()
    {
        static DataManager instance;
        return instance;
    }

    List<std::shared_ptr<Song>>& DataManager::getSongs()
    {
        return songs_;
    }

    List<std::shared_ptr<Album>>& DataManager::getAlbums()
    {
        return albums_;
    }

    List<std::shared_ptr<Artist>>& DataManager::getArtists()
    {
        return artists_;
    }

    void DataManager::addSong(const std::shared_ptr<Song>& song)
    {
        songs_.push_back(song);
    }

    void DataManager::addAlbum(const std::shared_ptr<Album>& album)
    {
        albums_.push_back(album);
    }

    void DataManager::addArtist(const std::shared_ptr<Artist>& artist)
    {
        artists_.push_back(artist);
    }

    void DataManager::loadDataFromFile()
    {
        std::ifstream file(fileName_);
        if (!file.is_open())
            return;

        std::string line;
        std::shared_ptr<Artist> currentArtist = nullptr;
        std::shared_ptr<Album> currentAlbum = nullptr;
        std::shared_ptr<Song> currentSong = nullptr;
        std::shared_ptr<Credits> currentCredits = nullptr;

        int previousLevel = -1;

        while (std::getline(file, line))
        {
            if (line.empty()) continue;

            int tabLevel = countTabs(line);

            if (tabLevel == 0)
            {
                if (previousLevel == 2)
                    storeCurrentAlbum(currentArtist, currentAlbum);
                storeCurrentArtist(currentArtist);

                std::string nameArtist = line.substr(line.find(":") + 2);
                currentArtist = std::make_shared<Artist>();
                currentArtist->setName(nameArtist);
            }
            else if (tabLevel == 1)
            {
                if (previousLevel == 2)
                    storeCurrentAlbum(currentArtist, currentAlbum);

                std::string nameAlbum = line.substr(line.find(":") + 2);
                currentAlbum = std::make_shared<Album>();
                currentAlbum->setName(nameAlbum);
            }
            else if (tabLevel == 2)
            {
                if (!currentSong)
                    currentSong = std::make_shared<Song>();
                if (!currentCredits)
                    currentCredits = std::make_shared<Credits>();

                const std::string key = line.substr(0, line.find(":"));
                const std::string value = line.substr(line.find(":") + 2);

                if (key.find("Song") != std::string::npos)
                {
                    currentSong->setName(value);
                }
                else if (key.find("Genres") != std::string::npos)
                {
                    currentSong->setGenresContent(*split(value, ','));
                }
                else if (key.find("Duration") != std::string::npos)
                {
                    currentSong->setDuration(std::stoul(value));
                }
                else if (key.find("Reproductions") != std::string::npos)
                {
                    currentSong->setReproductions(std::stoull(value));
                }
                else if (key.find("Discography") != std::string::npos)
                {
                    currentCredits->setDiscography(value);
                }
                else if (key.find("Authors") != std::string::npos)
                {
                    currentCredits->setAuthorsContent(*split(value, ','));
                    currentSong->setCredits(std::move(*currentCredits));

                    currentAlbum->addSong(currentSong);
                    songs_.push_back(currentSong);

                    songByName_.insert(currentSong->getName(), currentSong);
                    songToAlbum_.insert(currentSong->getName(), currentAlbum->getName());
                    songPartialIndex_.insert(currentSong);

                    currentSong = nullptr;
                    currentCredits = nullptr;
                }
            }

            previousLevel = tabLevel;
        }

        storeCurrentAlbum(currentArtist, currentAlbum);
        storeCurrentArtist(currentArtist);
    }


    std::shared_ptr<Song> DataManager::getSongByName(const std::string& name)
    {
        auto ptr = songByName_.find(name);
        return ptr ? *ptr : nullptr;
    }

    std::shared_ptr<Album> DataManager::getAlbumByName(const std::string& name)
    {
        auto ptr = albumByName_.find(name);
        return ptr ? *ptr : nullptr;
    }

    std::shared_ptr<Artist> DataManager::getArtistByName(const std::string& name)
    {
        auto ptr = artistByName_.find(name);
        return ptr ? *ptr : nullptr;
    }

    std::shared_ptr<Album> DataManager::getAlbumForSong(const std::string& songName)
    {
        auto albumNamePtr = songToAlbum_.find(songName);
        if (!albumNamePtr) return nullptr;

        return getAlbumByName(*albumNamePtr);
    }

    std::shared_ptr<Artist> DataManager::getArtistForSong(const std::string& songName)
    {
        auto albumNamePtr = songToAlbum_.find(songName);
        if (!albumNamePtr) return nullptr;

        auto artistNamePtr = albumToArtist_.find(*albumNamePtr);
        if (!artistNamePtr) return nullptr;

        return getArtistByName(*artistNamePtr);
    }

    List<std::shared_ptr<Song>> DataManager::getSongsByGenre(const std::string& genre)
    {
        List<std::shared_ptr<Song>> result;
        std::string query = genre;
        std::transform(query.begin(), query.end(), query.begin(), ::tolower);

        for (uint i = 0; i < songs_.size(); ++i)
        {
            const auto& song = songs_[i];
            const auto& genres = song->getGenres();
            for (uint j = 0; j < genres.size(); ++j)
            {
                std::string lowered = genres[j];
                std::transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);
                if (lowered == query)
                {
                    result.push_back(song);
                    break;
                }
            }
        }
        return result;
    }

    List<std::shared_ptr<Song>> DataManager::getSongsByReproductionsDesc()
    {
        List<std::shared_ptr<Song>> result;
        for (uint i = 0; i < songs_.size(); ++i)
            result.push_back(songs_[i]);

        QuickSort<std::shared_ptr<Song>, std::function<bool(const std::shared_ptr<Song>&, const std::shared_ptr<Song>&)>>::sort(
            result,
            [] (const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b)
            {
                return a->getReproductions() > b->getReproductions();
            });

        return result;
    }

    List<std::shared_ptr<Song>> DataManager::getSongsByReproductionsAsc()
    {
        List<std::shared_ptr<Song>> result;
        for (uint i = 0; i < songs_.size(); ++i)
            result.push_back(songs_[i]);

        MergeSort<std::shared_ptr<Song>, std::function<bool(const std::shared_ptr<Song>&, const std::shared_ptr<Song>&)>>::sort(
            result,
            [] (const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b)
            {
                return a->getReproductions() < b->getReproductions();
            });

        return result;
    }

    std::shared_ptr<Song> DataManager::getMostPlayedSong()
    {
        if (songs_.empty()) return nullptr;

        std::shared_ptr<Song> mostPlayed = songs_[0];
        for (uint i = 1; i < songs_.size(); ++i)
        {
            if (songs_[i]->getReproductions() > mostPlayed->getReproductions())
                mostPlayed = songs_[i];
        }
        return mostPlayed;
    }

    List<std::shared_ptr<Album>> DataManager::getAlbumsByArtist(const std::string& artistName)
    {
        auto artist = getArtistByName(artistName);
        List<std::shared_ptr<Album>> result;

        if (!artist)
            return result;

        const auto& albums = artist->getAlbums();
        for (uint i = 0; i < albums.size(); ++i)
        {
            result.push_back(albums[i]);
        }

        return result;
    }

    List<std::shared_ptr<Song>> DataManager::getSongsByArtist(const std::string& artistName)
    {
        auto artist = getArtistByName(artistName);
        List<std::shared_ptr<Song>> result;

        if (!artist) return result;

        const auto& albums = artist->getAlbums();
        for (uint i = 0; i < albums.size(); ++i)
        {
            const auto& songs = albums[i]->getSongs();
            for (uint j = 0; j < songs.size(); ++j)
                result.push_back(songs[j]);
        }

        return result;
    }

    List<std::shared_ptr<Song>> DataManager::getSongsByAlbum(const std::string& albumName)
    {
        List<std::shared_ptr<Song>> result;

        auto album = getAlbumByName(albumName);
        if (!album)
            return result;

        const auto& songs = album->getSongs();
        for (uint i = 0; i < songs.size(); ++i)
            result.push_back(songs[i]);

        return result;
    }

    List<std::shared_ptr<Song>> DataManager::getSongsByDuration(uint minSeconds, uint maxSeconds)
    {
        List<std::shared_ptr<Song>> result;

        for (uint i = 0; i < songs_.size(); ++i)
        {
            uint duration = songs_[i]->getDuration();
            if (duration >= minSeconds && duration <= maxSeconds)
            {
                result.push_back(songs_[i]);
            }
        }

        return result;
    }

    void DataManager::loadAsync()
    {
        if (isLoading_)
            return;

        isLoading_ = true;
        loadFinished_ = false;

        loadThread_ = std::thread([this] ()
            {
                this->loadDataFromFile();
                isLoading_ = false;
                loadFinished_ = true;
            });
        loadThread_.detach();
    }

    bool DataManager::isLoadInProgress() const
    {
        return isLoading_;
    }

    bool DataManager::isLoadCompleted() const
    {
        return loadFinished_;
    }

    void DataManager::storeCurrentAlbum(std::shared_ptr<Artist>& currentArtist, std::shared_ptr<Album>& currentAlbum)
    {
        if (currentArtist && currentAlbum)
        {
            currentArtist->addAlbum(currentAlbum);
            albums_.push_back(currentAlbum);

            albumByName_.insert(currentAlbum->getName(), currentAlbum);
            albumToArtist_.insert(currentAlbum->getName(), currentArtist->getName());
            albumPartialIndex_.insert(currentAlbum);

            currentAlbum = nullptr;
        }
    }

    void DataManager::storeCurrentArtist(std::shared_ptr<Artist>& currentArtist)
    {
        if (currentArtist)
        {
            artists_.push_back(currentArtist);

            artistByName_.insert(currentArtist->getName(), currentArtist);
            artistPartialIndex_.insert(currentArtist);

            currentArtist = nullptr;
        }
    }

    int DataManager::countTabs(const std::string& line)
    {
        int count = 0;
        for (char c : line)
        {
            if (c == '\t') ++count;
            else break;
        }
        return count;
    }

    std::shared_ptr<List<std::string>> DataManager::split(const std::string& input, char delimiter)
    {
        auto result = std::make_shared<List<std::string>>();
        std::stringstream ss(input);
        std::string item;

        while (std::getline(ss, item, delimiter))
        {
            result->push_back(item);
        }

        return result;
    }
}