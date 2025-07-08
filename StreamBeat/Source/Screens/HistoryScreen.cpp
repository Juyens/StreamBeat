#include "HistoryScreen.h"
#include "ScreenNames.h"
#include "SongManager.h"
#include "ScreenManager.h"
#include "SubSongScreen.h"

namespace sb
{
    HistoryScreen::HistoryScreen()
        : Screen(ScreenNames::History)
    {
        onCreate();
        initializeFocus();
    }

    void HistoryScreen::onCreate()
    {
        const auto consoleSize = Console::getViewportSize();
        const int baseY = 3;

        titleLb_ = addElement<Label>();
        titleLb_->setText("[ StreamBeat - History ]");
        titleLb_->centerX(consoleSize.x());
        titleLb_->setY(1);

        tableView_ = addElement<TableView<Song>>();
        tableView_->setGridSize({ 2, 30 });
        tableView_->centerX(consoleSize.x());
        tableView_->setY(baseY + 2);
        tableView_->setItemAction([] (std::shared_ptr<Song> selectedSong) {
            ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(selectedSong));
            });

        refreshHistory();
    }

    void HistoryScreen::onKeyPress(Key key)
    {

    }

    void HistoryScreen::onReset()
    {
        refreshHistory();
    }

    void HistoryScreen::update()
    {
        auto& history = SongManager::instance().getHistory();
        if (history.size() != prevHistorySize_)
        {
            refreshHistory();
        }
    }

    void HistoryScreen::refreshHistory()
    {
        auto& history = SongManager::instance().getHistory();

        std::vector<std::shared_ptr<Song>> songs;

        while (!history.empty())
        {
            songs.push_back(history.top());
            history.pop();
        }

        for (auto it = songs.rbegin(); it != songs.rend(); ++it)
        {
            history.push(*it);
        }

        List<std::shared_ptr<Song>> items;
        for (const auto& song : songs)
        {
            items.push_back(song);
        }

        prevHistorySize_ = history.size();
        tableView_->setItems(items);
    }
}
