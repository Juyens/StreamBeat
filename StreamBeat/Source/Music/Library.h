#pragma once

#include "List.h"
#include "Playlist.h"
#include "Artist.h"
#include "Album.h"
#include "Song.h"
#include "DataManager.h"

#include <memory>
#include <string>
#include <fstream>

namespace sb
{
    class Library
    {
    private:
        List<std::shared_ptr<Artist>> artists_{};
        List<std::shared_ptr<Album>> albums_{};
        List<std::shared_ptr<Playlist>> playlists_{};
        std::string ownerId_{};

        enum class Section { NONE, ARTISTS, ALBUMS, PLAYLIST };

    public:
        Library() = default;
        Library(const std::string& ownerId);
        Library(Library&&) noexcept = default;
        Library& operator=(Library&&) noexcept = default;
        ~Library() = default;

        List<std::shared_ptr<Artist>> getArtists();
        List<std::shared_ptr<Album>> getAlbums();
        List<std::shared_ptr<Playlist>> getPlaylists();

        void setOwnerId(const std::string& ownerId);

        void add(const std::shared_ptr<Artist>& artist);
        void add(const std::shared_ptr<Album>& album);
        void add(const std::shared_ptr<Song>& song, const std::string& playlistName = "Unnamed");

        void addPlaylist(const std::string& name);
        void deletePlaylist(const std::string& name);

        void loadFromFile(const std::string& ownerId);
        void saveToFile(const std::string& ownerId) const;
    };
}