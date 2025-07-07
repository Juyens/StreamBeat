#include "Library.h"
#include "DataManager.h"

#include <filesystem>

namespace sb
{
    Library::Library(const std::string& ownerId)
        : ownerId_(ownerId)
    {
        loadFromFile(ownerId);
    }

    List<std::shared_ptr<Artist>> Library::getArtists()
    {
        List<std::shared_ptr<Artist>> result;
        for (uint i = 0; i < artists_.size(); ++i)
        {
            result.push_back(artists_[i]);
        }
        return result;
    }

    List<std::shared_ptr<Album>> Library::getAlbums()
    {
        List<std::shared_ptr<Album>> result;
        for (uint i = 0; i < albums_.size(); ++i)
        {
            result.push_back(albums_[i]);
        }
        return result;
    }

    List<std::shared_ptr<Playlist>> Library::getPlaylists()
    {
        List<std::shared_ptr<Playlist>> result;
        for (uint i = 0; i < playlists_.size(); ++i)
        {
            result.push_back(playlists_[i]);
        }
        return result;
    }

    void Library::setOwnerId(const std::string& ownerId)
    {
        ownerId_ = ownerId;
    }

    void Library::add(const std::shared_ptr<Artist>& artist)
    {
        artists_.push_back(artist);
        saveToFile(ownerId_);
    }

    void Library::add(const std::shared_ptr<Album>& album)
    {
        albums_.push_back(album);
        saveToFile(ownerId_);
    }

    void Library::add(const std::shared_ptr<Song>& song, const std::string& playlistName)
    {
        if (playlistName != "Unnamed")
        {
            for (uint i = 0; i < playlists_.size(); ++i)
            {
                auto& pl = playlists_[i];
                if (pl && pl->getName().find(playlistName) != std::string::npos)
                {
                    pl->addSong(song);
                    saveToFile(ownerId_);
                    break;
                }
            }
        }
    }

    void Library::addPlaylist(const std::string& name)
    {
        playlists_.push_back(std::make_shared<Playlist>(name));
        saveToFile(ownerId_);
    }

    void Library::deletePlaylist(const std::string& name)
    {
        for (uint i = 0; i < playlists_.size(); ++i)
        {
            auto& pl = playlists_[i];
            if (pl && pl->getName() == name)
            {
                playlists_.remove(i);
                break;
            }
        }
        saveToFile(ownerId_);
    }

    void Library::loadFromFile(const std::string& ownerId)
    {
        std::filesystem::create_directory("Data/Libraries");
        std::ifstream file("Data/Libraries/" + ownerId + "_library.data");
        if (!file.is_open())
        {
            std::ofstream create("Data/Libraries/" + ownerId + "_library.data");
            return;
        }

        std::string line;
        Section section = Section::NONE;
        std::shared_ptr<Playlist> currentPlaylist = nullptr;

        while (std::getline(file, line))
        {
            if (line == "Artists:")
            {
                section = Section::ARTISTS;
            }
            else if (line == "Albums:")
            {
                section = Section::ALBUMS;
            }
            else if (line.rfind("Playlist: ", 0) == 0)
            {
                section = Section::PLAYLIST;
                std::string playlistName = line.substr(10);
                currentPlaylist = std::make_shared<Playlist>(playlistName);
                playlists_.push_back(currentPlaylist);
            }
            else if (!line.empty())
            {
                switch (section)
                {
                case Section::ARTISTS:
                {
                    auto artist = sb::DataManager::instance().getArtistByName(line);
                    if (artist) artists_.push_back(artist);
                    break;
                }
                case Section::ALBUMS:
                {
                    auto album = sb::DataManager::instance().getAlbumByName(line);
                    if (album) albums_.push_back(album);
                    break;
                }
                case Section::PLAYLIST:
                {
                    auto song = sb::DataManager::instance().getSongByName(line);
                    if (song && currentPlaylist) currentPlaylist->addSong(song);
                    break;
                }
                default:
                    break;
                }
            }
        }
    }

    void Library::saveToFile(const std::string& ownerId) const
    {
        std::filesystem::create_directory("Data/Libraries");
        std::ofstream file("Data/Libraries/" + ownerId + "_library.data");
        if (!file.is_open())
            return;

        file << "Artists:\n";
        for (uint i = 0; i < artists_.size(); ++i)
            file << artists_[i]->getName() << "\n";

        file << "\nAlbums:\n";
        for (uint i = 0; i < albums_.size(); ++i)
            file << albums_[i]->getName() << "\n";

        for (uint i = 0; i < playlists_.size(); ++i)
        {
            auto& pl = playlists_[i];
            if (!pl) continue;
            file << "\nPlaylist: " << pl->getName() << "\n";
            auto& songs = pl->getSongs();
            for (uint j = 0; j < songs.size(); ++j)
                file << songs[j]->getName() << "\n";
        }
    }
}