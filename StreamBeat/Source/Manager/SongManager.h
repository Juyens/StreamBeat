#pragma once

#include "Queue.h"
#include "Stack.h"
#include "Song.h"
#include "Album.h"
#include "Playlist.h"
#include "Drawing.h"

#include <memory>

namespace sb
{
    class SongManager
    {
    private:
        Queue<std::shared_ptr<Song>> playQueue_;
        Stack<std::shared_ptr<Song>> history_;
        std::shared_ptr<Song> currentSong_ = nullptr;

        SongManager() = default;

    public:
        SongManager(const SongManager&) = delete;
        SongManager& operator=(const SongManager&) = delete;
        ~SongManager() = default;

        static SongManager& instance();

        void play(std::shared_ptr<Album> album);
        void play(std::shared_ptr<Playlist> playlist);
        void play(std::shared_ptr<Song> song);
        void show();

        void enqueue(std::shared_ptr<Song> song);
        void next();

        Stack<std::shared_ptr<Song>>& getHistory();
        Queue<std::shared_ptr<Song>>& getPlayQueue();
    };
}
