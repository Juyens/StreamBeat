#include "HistoryScreen.h"
#include "ScreenNames.h"
#include "SongManager.h"

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
        const int baseY = 1;

        titleLb_ = addElement<Label>();
        titleLb_->setText("[ StreamBeat - History ]");
        titleLb_->centerX(consoleSize.x());
        titleLb_->setY(baseY);

        tableView_ = addElement<TableView<Song>>();
        tableView_->setGridSize({ 2, 25 });
        tableView_->centerX(consoleSize.x());
        tableView_->setY(baseY + 2);

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

        Stack<std::shared_ptr<Song>> temp;
        List<std::shared_ptr<Song>> items;

        while (!history.empty())
        {
            auto song = history.top();
            temp.push(song);
            history.pop();
        }

        while (!temp.empty())
        {
            auto song = temp.top();
            history.push(song);
            items.push_front(song);
            temp.pop();
        }

        prevHistorySize_ = history.size();
        tableView_->setItems(items);
    }
}
