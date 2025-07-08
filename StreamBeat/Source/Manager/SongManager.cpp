#include "SongManager.h"
#include "Utils.h"

namespace sb
{
    SongManager& SongManager::instance()
    {
        static SongManager instance;
        return instance;
    }

    void SongManager::play(std::shared_ptr<Album> album)
    {
        playQueue_.clear();

        auto& songs = album->getSongs();
        for (uint i = 0; i < songs.size(); ++i)
        {
            auto song = songs[i];
            playQueue_.enqueue(song);
        }

        if (!playQueue_.empty())
            currentSong_ = playQueue_.peek();
    }

    void SongManager::play(std::shared_ptr<Playlist> playlist)
    {
        playQueue_.clear();

        auto& songs = playlist->getSongs();
        for (uint i = 0; i < songs.size(); ++i)
        {
            auto song = songs[i];
            playQueue_.enqueue(song);
        }

        if (!playQueue_.empty())
            currentSong_ = playQueue_.peek();
    }

    void SongManager::play(std::shared_ptr<Song> song)
    {
        playQueue_.clear();
        playQueue_.enqueue(song);
        currentSong_ = song;
    }

    void SongManager::show()
    {
        if (playQueue_.empty())
            return;

        auto song = playQueue_.peek();
        auto name = ">> Playing: " + song->getName() + " <<";
        Drawing::drawText(utils::centered(Console::getViewportSize().x(), static_cast<int>(name.size())), 38, name);
    }

    void SongManager::enqueue(std::shared_ptr<Song> song)
    {
        playQueue_.enqueue(song);
    }

    void SongManager::next()
    {
        if (!playQueue_.empty() && currentSong_)
        {
            history_.push(currentSong_);
            playQueue_.dequeue();
            currentSong_ = playQueue_.empty() ? nullptr : playQueue_.peek();
        }
    }

    Stack<std::shared_ptr<Song>>& SongManager::getHistory()
    {
        return history_;
    }

    Queue<std::shared_ptr<Song>>& SongManager::getPlayQueue()
    {   
        return playQueue_;
    }
}