#include "ExploreScreen.h"
#include "ScreenNames.h"
#include "ScreenManager.h"
#include "SubSongScreen.h"

namespace sb
{
	ExploreScreen::ExploreScreen()
		: Screen(ScreenNames::Explore)
	{
		onCreate();
		initializeFocus();
	}

	void ExploreScreen::onCreate()
	{
		const auto consoleSize = Console::getViewportSize();
		const int baseY = 3;

		titleLb_ = addElement<Label>();
		titleLb_->setText("[ StreamBeat - Explore ]");
		titleLb_->centerX(consoleSize.x());
		titleLb_->setY(1);

		tableView_ = addElement<TableView<Song>>();
		tableView_->setGridSize({ 2, 30 });
		tableView_->centerX(consoleSize.x());
		tableView_->setY(baseY + 2);
		tableView_->setItemAction([] (std::shared_ptr<Song> selectedSong) {
			ScreenManager::instance().pushSubScreen(std::make_unique<SubSongScreen>(selectedSong));
			});

		if (DataManager::instance().isLoadCompleted())
			refreshRecommendations();
	}

	void ExploreScreen::onKeyPress(Key key)
	{

	}

	void ExploreScreen::onReset()
	{
		if (DataManager::instance().isLoadCompleted())
			refreshRecommendations();
	}

	void ExploreScreen::update()
	{
		if (!DataManager::instance().isLoadCompleted())
			return;

		auto& history = SongManager::instance().getHistory();
		if (!recommendationsLoaded_ || history.size() != prevHistorySize_)
		{
			refreshRecommendations();
			recommendationsLoaded_ = true;
			prevHistorySize_ = history.size();
		}
	}

	void ExploreScreen::refreshRecommendations()
	{
		auto items = RecommendationManager::instance().getRecommendations(60);
		tableView_->setItems(items);
	}
}
