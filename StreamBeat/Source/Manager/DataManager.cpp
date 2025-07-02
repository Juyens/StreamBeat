#include "DataManager.h"

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

        std::shared_ptr<Artist> currentArtist = nullptr;
        std::shared_ptr<Album> currentAlbum = nullptr;
        std::shared_ptr<Song> currentSong = nullptr;
        std::shared_ptr<Credits> currentCredits = nullptr;

        recursiveData(file, 0, currentArtist, currentAlbum, currentSong, currentCredits);
    }

    void DataManager::recursiveData(std::ifstream& file, int previous,
        std::shared_ptr<Artist>& currentArtist,
        std::shared_ptr<Album>& currentAlbum,
        std::shared_ptr<Song>& currentSong,
        std::shared_ptr<Credits>& currentCredits)
    {
        std::string line;
        if (!getline(file, line))
        {
            if (previous == 2 && currentArtist && currentAlbum)
            {
                currentArtist->addAlbum(currentAlbum);
                artists_.push_back(currentArtist);
            }
            return;
        }

        if (line.empty())
        {
            recursiveData(file, previous, currentArtist, currentAlbum, currentSong, currentCredits);
            return;
        }

        int tabLevel = countTabs(line);

        if (tabLevel == 0)
        {
            if (previous == 2 && currentArtist && currentAlbum)
            {
                currentArtist->addAlbum(currentAlbum);
                artists_.push_back(currentArtist);
            }

            std::string nameArtist = line.substr(line.find(":") + 2);
            currentArtist = std::make_shared<Artist>();
            currentArtist->setName(nameArtist);
        }
        else if (tabLevel == 1)
        {
            if (previous == 2 && currentArtist && currentAlbum)
            {
                currentArtist->addAlbum(currentAlbum);
            }

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

            if (line.find("Song") != std::string::npos)
            {
                std::string nameSong = line.substr(line.find(":") + 2);
                currentSong->setName(nameSong);
            }
            else if (line.find("Genres") != std::string::npos)
            {
                std::string genres = line.substr(line.find(":") + 2);
                currentSong->setGenresContent(*split(genres, ','));
            }
            else if (line.find("Duration") != std::string::npos)
            {
                std::uint32_t duration = std::stoi(line.substr(line.find(":") + 2));
                currentSong->setDuration(duration);
            }
            else if (line.find("Reproductions") != std::string::npos)
            {
                std::uint64_t reproductions = std::stoll(line.substr(line.find(":") + 2));
                currentSong->setReproductions(reproductions);
            }
            else if (line.find("Discography") != std::string::npos)
            {
                std::string discography = line.substr(line.find(":") + 2);
                currentCredits->setDiscography(discography);
            }
            else if (line.find("Authors") != std::string::npos)
            {
                std::string authors = line.substr(line.find(":") + 2);
                currentCredits->setAuthorsContent(*split(authors, ','));
                currentSong->setCredits(std::move(*currentCredits));
                currentAlbum->addSong(currentSong);
                songs_.push_back(currentSong);

                currentSong = nullptr;
                currentCredits = nullptr;
            }
        }

        recursiveData(file, tabLevel, currentArtist, currentAlbum, currentSong, currentCredits);
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